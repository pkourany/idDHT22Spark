/***
 *     __          __     _____  _   _ _____ _   _  _____                                              
 *     \ \        / /\   |  __ \| \ | |_   _| \ | |/ ____|  _                                          
 *      \ \  /\  / /  \  | |__) |  \| | | | |  \| | |  __  (_)                                         
 *       \ \/  \/ / /\ \ |  _  /| . ` | | | | . ` | | |_ |                                             
 *        \  /\  / ____ \| | \ \| |\  |_| |_| |\  | |__| |  _                                          
 *      ___\/  \/_/_   \_\_|_ \_\_| \_|_____|_| \_|\_____|_(_)____   _                                 
 *     |  __ \ / __ \  | \ | |/ __ \__   __| | |  | |/ ____|  ____| | |                                
 *     | |  | | |  | | |  \| | |  | | | |    | |  | | (___ | |__    | |                                
 *     | |  | | |  | | | . ` | |  | | | |    | |  | |\___ \|  __|   | |                                
 *     | |__| | |__| | | |\  | |__| | | |    | |__| |____) | |____  |_|                                
 *     |_____/ \____/  |_| \_|\____/  |_|     \____/|_____/|______| (_)      _       _           _     
 *     | |    (_) |                              | |                        (_)     | |         | |    
 *     | |     _| |__  _ __ __ _ _ __ _   _    __| | ___ _ __  _ __ ___  ___ _  __ _| |_ ___  __| |    
 *     | |    | | '_ \| '__/ _` | '__| | | |  / _` |/ _ \ '_ \| '__/ _ \/ __| |/ _` | __/ _ \/ _` |    
 *     | |____| | |_) | | | (_| | |  | |_| | | (_| |  __/ |_) | | |  __/ (__| | (_| | ||  __/ (_| |    
 *     |______|_|_.__/|_|  \__,_|_|   \__, |  \__,_|\___| .__/|_|  \___|\___|_|\__,_|\__\___|\__,_|    
 *                                     __/ |            | |                                            
 *      _    _            _____ _     |___/_       _    |_|     _                _____  _    _ _______ 
 *     | |  | |          |  __ (_)    | | | |     | |          | |              |  __ \| |  | |__   __|
 *     | |  | |___  ___  | |__) |  ___| |_| |_ ___| |_ ___  ___| |__            | |  | | |__| |  | |   
 *     | |  | / __|/ _ \ |  ___/ |/ _ \ __| __/ _ \ __/ _ \/ __| '_ \           | |  | |  __  |  | |   
 *     | |__| \__ \  __/ | |   | |  __/ |_| ||  __/ ||  __/ (__| | | |  ______  | |__| | |  | |  | |   
 *      \____/|___/\___| |_|   |_|\___|\__|\__\___|\__\___|\___|_| |_| |______| |_____/|_|  |_|  |_|   
 *                                                                                            
 */


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
