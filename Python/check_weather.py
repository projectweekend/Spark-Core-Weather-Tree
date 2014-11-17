import os

import requests
import forecastio


FORECAST_IO_KEY = os.getenv('FORECAST_IO_KEY')
FORECAST_IO_LATITUDE = os.getenv('FORECAST_IO_LATITUDE')
FORECAST_IO_LONGITUDE = os.getenv('FORECAST_IO_LONGITUDE')
SPARK_DEVICE_ID = os.getenv('SPARK_DEVICE_ID')
SPARK_AUTH_TOKEN = os.getenv('SPARK_AUTH_TOKEN')


def send_to_spark(function_name):
	print(function_name)


def report_snow():
	send_to_spark('snow')


def report_sleet():
	send_to_spark('sleet')


def report_rain():
	send_to_spark('rain')


def report_no_percipitation():
	send_to_spark('noPercipitation')


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
		return percipitation[currently.d['icon']]()
	except KeyError:
		return report_no_percipitation()


if __name__ == '__main__':
	main()
