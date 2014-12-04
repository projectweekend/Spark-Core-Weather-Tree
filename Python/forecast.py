import uuid
import json
import pika


class ForecastClient(object):

	def __init__(self, rabbit_url):
		self._connection = pika.BlockingConnection(pika.URLParameters(rabbit_url))
		self._channel = self._connection.channel()

		result = self._channel.queue_declare(exclusive=True)
		self._callback_queue = result.method.queue

		self._channel.basic_consume(self._on_response, no_ack=True, queue=self._callback_queue)

	def _on_response(self, channel, method, properties, body):
		if self._corr_id == properties.correlation_id:
			self._response = json.loads(body)

	def close_connection(self):
		self._connection.close()

	def get_forecast(self, latitude, longitude, options={}):
		body = {
			'latitude': latitude,
			'longitude': longitude
		}
		if options:
			body['options'] = options
		body = json.dumps(body)

		self._response = None
		self._corr_id = str(uuid.uuid4())
		props = pika.BasicProperties(reply_to=self._callback_queue, correlation_id=self._corr_id)
		self._channel.basic_publish(exchange='', routing_key='forecast.get', properties=props,
			body=body)

		while self._response is None:
			self._connection.process_data_events()

		return self._response
