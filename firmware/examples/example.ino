// This #include statement was automatically added by the Spark IDE.
#include "idDHT22/idDHT22.h"


// declaration for DHT11 handler
int idDHT22pin = D4; //Digital pin for comunications
void dht22_wrapper(); // must be declared before the lib initialization

// DHT instantiate
idDHT22 DHT22(idDHT22pin, dht22_wrapper);


void setup()
{
	Serial.begin(9600);
	while(!Serial.available()) {
	    Serial.println("hit a key");
	    delay(1000);
	}
	Serial.println("idDHT22 Example program");
	Serial.print("LIB version: ");
	Serial.println(idDHT22LIB_VERSION);
	Serial.println("---------------");
}
// This wrapper is in charge of calling
// mus be defined like this for the lib work
void dht22_wrapper() {
	DHT22.isrCallback();
}
void loop()
{

	Serial.print("\nRetrieving information from sensor: ");
	Serial.print("Read sensor: ");
	//delay(100);
	DHT22.acquire();
	while (DHT22.acquiring())
		;
	int result = DHT22.getStatus();
	switch (result)
	{
		case IDDHTLIB_OK:
			Serial.println("OK");
			break;
		case IDDHTLIB_ERROR_CHECKSUM:
			Serial.println("Error\n\r\tChecksum error");
			break;
		case IDDHTLIB_ERROR_ISR_TIMEOUT:
			Serial.println("Error\n\r\tISR Time out error");
			break;
		case IDDHTLIB_ERROR_RESPONSE_TIMEOUT:
			Serial.println("Error\n\r\tResponse time out error");
			break;
		case IDDHTLIB_ERROR_DATA_TIMEOUT:
			Serial.println("Error\n\r\tData time out error");
			break;
		case IDDHTLIB_ERROR_ACQUIRING:
			Serial.println("Error\n\r\tAcquiring");
			break;
		case IDDHTLIB_ERROR_DELTA:
			Serial.println("Error\n\r\tDelta time to small");
			break;
		case IDDHTLIB_ERROR_NOTSTARTED:
			Serial.println("Error\n\r\tNot started");
			break;
		default:
			Serial.println("Unknown error");
			break;
	}
	Serial.print("Humidity (%): ");
	Serial.println(DHT22.getHumidity(), 2);

	Serial.print("Temperature (oC): ");
	Serial.println(DHT22.getCelsius(), 2);

	Serial.print("Temperature (oF): ");
	Serial.println(DHT22.getFahrenheit(), 2);

	Serial.print("Temperature (K): ");
	Serial.println(DHT22.getKelvin(), 2);

	Serial.print("Dew Point (oC): ");
	Serial.println(DHT22.getDewPoint());

	Serial.print("Dew Point Slow (oC): ");
	Serial.println(DHT22.getDewPointSlow());

	delay(2000);
}
