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

/*
	FILE:		 idDHT22.h
	VERSION:	 0.0.1
	PURPOSE:	 Interrupt driven Lib for DHT11 with Arduino.
	LICENCE:	GPL v3 (http://www.gnu.org/licenses/gpl.html)
	DATASHEET: http://www.micro4you.com/files/sensor/DHT11.pdf
	
	Based on DHT11 library: http://playground.arduino.cc/Main/DHT11Lib
*/

/*
	Modified by Paul Kourany for DHT22, Mar 28, 2014
	Originally ported to Spark.Core
	January 18, 2014
	Scott Piette

	Original version from niesteszek located @ https://github.com/niesteszeck/idDHT22
*/
#include "application.h"
#include "math.h"

/************************************ _iDHT.h **************************/
/*
FILE: idDHT22.h
VERSION: 0.1
PURPOSE: Interrupt driven Lib for DHT11 with Arduino.
LICENCE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
DATASHEET: http://www.micro4you.com/files/sensor/DHT11.pdf
Based on DHT11 library: http://playground.arduino.cc/Main/DHT11Lib
*/


#define idDHT22LIB_VERSION "0.1"

// state codes
#define IDDHTLIB_OK						0
#define IDDHTLIB_ACQUIRING				1
#define IDDHTLIB_ACQUIRED				2
#define IDDHTLIB_RESPONSE_OK			3

// error codes
#define IDDHTLIB_ERROR_CHECKSUM				-1
#define IDDHTLIB_ERROR_ISR_TIMEOUT			-2
#define IDDHTLIB_ERROR_RESPONSE_TIMEOUT		-3
#define IDDHTLIB_ERROR_DATA_TIMEOUT			-4
#define IDDHTLIB_ERROR_ACQUIRING			-5
#define IDDHTLIB_ERROR_DELTA				-6
#define IDDHTLIB_ERROR_NOTSTARTED			-7

#define idDHT22_CHECK_STATE		if(_state == STOPPED)					\
									return _status;						\
								else if(_state != ACQUIRED)				\
									return IDDHTLIB_ERROR_ACQUIRING;

class idDHT22
{
public:
	idDHT22(int sigPin, void (*isrCallback_wrapper)());
    void init(int sigPin, void (*isrCallback_wrapper)());
	void isrCallback();
	int acquire();
	int acquireAndWait();
	float getCelsius();
	float getFahrenheit();
	float getKelvin();
	double getDewPoint();
	double getDewPointSlow();
	float getHumidity();
	bool acquiring();
	int getStatus();

private:
	void (*isrCallback_wrapper)(void);

	enum states{RESPONSE=0,DATA=1,ACQUIRED=2,STOPPED=3,ACQUIRING=4};
	volatile states _state;
	volatile int _status;
	volatile uint8_t _bits[6];
	volatile uint8_t _cnt;
	volatile uint8_t _idx;
	volatile unsigned long _us;
	int _sigPin;
	int _type;
	unsigned long _lastreadtime;
	volatile float _hum;
	volatile float _temp;
};

