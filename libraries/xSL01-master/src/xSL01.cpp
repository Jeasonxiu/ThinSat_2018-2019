/*
	This is a library for the SL01 Digital Light Sensor
	breakout board.

	The board uses I2C for communication.
	
	The board communicates with two I2C devices:
	* 	VEML6075  
	*	TSL4531
	
	Data Sheets:
	VEML6075	- http://www.vishay.com/docs/84304/veml6075.pdf
	TSL4531		- http://wisense.in/datasheets/TSL4531.pdf
*/

#include "xSL01.h"
/********************************************************
 	Constructor
*********************************************************/
xSL01::xSL01() {
	UVAintensity = 0.0;
	UVBintensity = 0.0; 
	LUX = 0.0;
}

/********************************************************
 	Configure Sensor
*********************************************************/
bool xSL01::begin(){
	xCore.write8(VEML6075_I2C_ADDRESS , VEML6075_REG_CONF, VEML6075_CONF_IT_100 + VEML6075_CONF_AF_FORCE + VEML6075_CONF_SD_OFF);
	xCore.write1(0);
	xCore.write8(TSL4531_I2C_ADDRESS , (TSL4531_WRITE_CMD | TSL4531_REG_CONTROL), TSL4531_CONF_START);
	xCore.write8(TSL4531_I2C_ADDRESS , (TSL4531_WRITE_CMD | TSL4531_REG_CONF), (TSL4531_CONF_IT_100 | TSL4531_CONF_PSAVE));
}

/********************************************************
 	Reads Sensor Data
*********************************************************/
void xSL01::poll() {
	readTSL();
	readVEML();
}

/********************************************************
 	Request UVA data in micoWatts/cm^2
*********************************************************/
float xSL01::getUVA(){
	return UVAintensity;
}

/********************************************************
 	Request UVB data in micoWatts/cm^2
*********************************************************/
float xSL01::getUVB(){
	return UVBintensity;
}

/********************************************************
 	Request ambeint light in LUX
*********************************************************/
float xSL01::getLUX(){
	return LUX;
}

/*---Private Function---*/

/********************************************************
 	Reads Data from TSL4531
*********************************************************/
void xSL01::readTSL() {
	int multi = 4;
	raw_LUX_H = xCore.read8(TSL4531_I2C_ADDRESS, (TSL4531_WRITE_CMD | TSL4531_REG_DATA_HIGH));
	raw_LUX_L = xCore.read8(TSL4531_I2C_ADDRESS, (TSL4531_WRITE_CMD | TSL4531_REG_DATA_LOW));
	LUX = multi*(((float)raw_LUX_H * 256) + (float)raw_LUX_L);
}

/********************************************************
 	Reads data from VEML6075
*********************************************************/
void xSL01::readVEML(){
	float UVAsensitivity = 0.46;
	float UVBsensitivity = 1.05;
	
	readUVdata();
	
	UVAintensity = (float)UVA/UVAsensitivity;
	UVBintensity = (float)UVB/UVBsensitivity;
}

/********************************************************
 	Reads data from VEML6075
*********************************************************/
void xSL01::readUVdata(){
	uint16_t data;
	uint8_t a, b;
	
	data = xCore.read16(VEML6075_I2C_ADDRESS, VEML6075_REG_UVA);
	a = (uint8_t)((data & 0xFF00) >> 8);
	b = (uint8_t)(data & 0x00FF);
	UVA = b<<8 | a;
	
	data = xCore.read16(VEML6075_I2C_ADDRESS, VEML6075_REG_UVB);
	a = (uint8_t)((data & 0xFF00) >> 8);
	b = (uint8_t)(data & 0x00FF);
	UVB = b<<8 | a;
	
	UVcomp1 = xCore.read16(VEML6075_I2C_ADDRESS, VEML6075_REG_UVCOMP1);
	UVcomp2 = xCore.read16(VEML6075_I2C_ADDRESS, VEML6075_REG_UVCOMP2);
}

xSL01 SL01 = xSL01();
