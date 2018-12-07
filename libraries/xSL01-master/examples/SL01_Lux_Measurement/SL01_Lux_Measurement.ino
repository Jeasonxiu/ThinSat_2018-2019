/*************************************************************
	This is an examples for the SW01
	Ambient, UVA and UVB light sensor
	
	You can buy one on our store!
	-----> https://xinabox.cc/SL01/
	
	This example request a LUX meausrement to be 
	made by the SL01 and display the data over the Serial
	bus.
	
	Currently Supported on the following ☒CHIP:
	- CW01
	- CC01
	- CR01
	
	The sensor communicates over the I2C Bus.

	------------------------TIPS--------------------------
	Change this line ----->Wire.begin(2,14);
	to this			 ----->Wire.begin();
	to allow this sensor to communicate with CC01 and CR01
	
*************************************************************/
#include <xCore.h>
#include <xSL01.h>

const int DELAY_TIME = 1000;

void setup() {
	// Start the Serial Monitor
	Serial.begin(115200);
	
	// Start the I2C Comunication
	Wire.begin(2,14);
	
	// Start the  SL01 Sensor
	SL01.begin();

	// Delayy for Sensor to normalise
	delay(5000);
	
	Serial.println("================================");
	Serial.println(" XINABOX SL01 LUX Measurements  ");
	Serial.println("================================"); 
}

void loop() {
	  // Create a variable to store the incoming measurements
	  // from SL01 sensor
	  float lux;
	  lux = 0;

	  // Poll Sensor for collect data
	  SL01.poll();

	  // Request SL01 to return calculated UVB intensity
	  lux = SL01.getLUX();

	  // Display Data on the Serial monitor
	  Serial.print("Ambient Light Level: ");
	  Serial.print(lux);
	  Serial.println(" LUX");

	  delay(DELAY_TIME);
}
