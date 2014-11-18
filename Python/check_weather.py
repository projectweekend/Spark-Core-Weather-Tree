import os
import sys

import requests
import forecastio
from pyecho import echo, FailingTooHard


FORECAST_IO_KEY = os.getenv('FORECAST_IO_KEY')
assert FORECAST_IO_KEY

FORECAST_IO_LATITUDE = os.getenv('FORECAST_IO_LATITUDE')
assert FORECAST_IO_LATITUDE

FORECAST_IO_LONGITUDE = os.getenv('FORECAST_IO_LONGITUDE')
assert FORECAST_IO_LONGITUDE

SPARK_DEVICE_ID = os.getenv('SPARK_DEVICE_ID')
assert SPARK_DEVICE_ID

SPARK_AUTH_TOKEN = os.getenv('SPARK_AUTH_TOKEN')
assert SPARK_AUTH_TOKEN

SPARK_URL_TEMPLATE = "https://api.spark.io/v1/devices/{0}/{1}"


@echo(5)
def send_to_spark(function_name):
	url = SPARK_URL_TEMPLATE.format(SPARK_DEVICE_ID, function_name)
	headers = {'Authorization': "Bearer {0}".format(SPARK_AUTH_TOKEN)}
	return requests.post(url, headers=headers)


def report_snow():
	return send_to_spark('snow')


def report_sleet():
	return send_to_spark('sleet')


def report_rain():
	return send_to_spark('rain')


def report_no_percipitation():
	return send_to_spark('none')


def main():
	forecast = forecastio.load_forecast(FORECAST_IO_KEY, FORECAST_IO_LATITUDE,
				FORECAST_IO_LONGITUDE)
	currently = forecast.currently()

	percipitation = {
		'rain': report_rain,
		'snow': report_snow,
		'sleet': report_sleet
	}

	try:
		try:
			response = percipitation[currently.d['icon']]()
		except KeyError:
			response = report_no_percipitation()
	except FailingTooHard:
		# TODO: send email, blink LED...something to alert me that request is failing
		sys.exit(1)

	if response.status_code != 200:
		# TODO: send email, blink LED...something to alert me that request is bad
		sys.exit(1)

	sys.exit(0)


if __name__ == '__main__':
	main()
