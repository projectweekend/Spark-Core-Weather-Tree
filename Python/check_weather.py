#!/usr/bin/env python
import os
import sys

import mandrill
import requests
from pyecho import echo, FailingTooHard

from forecast import ForecastClient


NOTIFICATION_EMAIL = os.getenv('NOTIFICATION_EMAIL')
assert NOTIFICATION_EMAIL

MANDRILL_KEY = os.getenv('MANDRILL_KEY')
assert MANDRILL_KEY

MANDRILL_FROM_EMAIL = os.getenv('MANDRILL_FROM_EMAIL')
assert MANDRILL_FROM_EMAIL

RABBIT_URL = os.getenv('RABBIT_URL')
assert RABBIT_URL

FORECAST_IO_LATITUDE = os.getenv('FORECAST_IO_LATITUDE')
assert FORECAST_IO_LATITUDE

FORECAST_IO_LONGITUDE = os.getenv('FORECAST_IO_LONGITUDE')
assert FORECAST_IO_LONGITUDE

SPARK_DEVICE_ID = os.getenv('SPARK_DEVICE_ID')
assert SPARK_DEVICE_ID

SPARK_AUTH_TOKEN = os.getenv('SPARK_AUTH_TOKEN')
assert SPARK_AUTH_TOKEN

SPARK_URL_TEMPLATE = 'https://api.spark.io/v1/devices/{0}/{1}'


def send_error_email(message_subject, message_text):
	client = mandrill.Mandrill(MANDRILL_KEY)
	message = {
		'from_email': MANDRILL_FROM_EMAIL,
		'subject': message_subject,
		'html': '<p>{0}</p>'.format(message_text),
		'to': [{'email': NOTIFICATION_EMAIL}]
	}
	client.messages.send(message=message, async=True)


@echo(3)
def send_to_spark(function_name):
	url = SPARK_URL_TEMPLATE.format(SPARK_DEVICE_ID, function_name)
	headers = {'Authorization': "Bearer {0}".format(SPARK_AUTH_TOKEN)}
	return requests.post(url, headers=headers)


@echo(3)
def forecast_currently():
	forecast_client = ForecastClient(rabbit_url=RABBIT_URL)
	data = forecast_client.get_forecast(
			latitude=float(FORECAST_IO_LATITUDE),
			longitude=float(FORECAST_IO_LONGITUDE),
			options={'exclude': ['minutely', 'hourly', 'daily', 'alerts', 'flags']})
	forecast_client.close_connection()
	return data['currently']


def report_snow():
	return send_to_spark('snow')


def report_sleet():
	return send_to_spark('sleet')


def report_rain():
	return send_to_spark('rain')


def report_no_percipitation():
	return send_to_spark('none')


def main():
	try:
		currently = forecast_currently()
	except FailingTooHard:
		email_subject = 'Weather Tree: Forecast.io RPC Service Error'
		email_body = 'Unable to reach Forecast.io RPC service'
		send_error_email(email_subject, email_body)
		# TODO: maybe an blink LED too?
		return 1

	percipitation = {
		'rain': report_rain,
		'snow': report_snow,
		'sleet': report_sleet
	}

	try:
		try:
			response = percipitation[currently['icon']]()
		except KeyError:
			response = report_no_percipitation()
	except FailingTooHard:
		email_subject = 'Weather Tree: Spark Core Communication Error'
		email_body = 'Unable to connect to Spark Core with ID {0}'.format(SPARK_DEVICE_ID)
		send_error_email(email_subject, email_body)
		# TODO: maybe an blink LED too?
		return 2

	if response.status_code != 200:
		email_subject = 'Weather Tree: Spark Core Request Error'
		email_body = 'Bad request to Spark Core with ID {0}'.format(SPARK_DEVICE_ID)
		send_error_email(email_subject, email_body)
		# TODO: maybe an blink LED too?
		return 3

	return 0


if __name__ == '__main__':
	sys.exit(main())
