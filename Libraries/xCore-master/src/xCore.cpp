/********************************************************
 	This is a library for the XinaBox Core Functions	

 	Core Functions include:								
 	-	I2C Communication												
 	-	Inter device communication

	Currently Spport Models:
	-	CW01
	-	CC01
	-	CR01	
*********************************************************/
 
#include "xCore.h"

/********************************************************
 	Writes an 8 bit value over I2C
*********************************************************/
void xCoreClass::write8(byte device, byte reg, byte value) {
	Wire.beginTransmission((uint8_t)device);
	Wire.write((uint8_t)reg);
	Wire.write((uint8_t)value);
	Wire.endTransmission(false);
}

/********************************************************
 	Writes over I2C
*********************************************************/
void xCoreClass::write(byte device, byte value){
	Wire.beginTransmission((uint8_t)device);
	Wire.write((uint8_t)value);
}

void xCoreClass::write1(byte value){
	Wire.write((uint8_t)value);
}

/********************************************************
 	Writes an 16 bit value over I2C
*********************************************************/
void xCoreClass::write16(byte device, byte reg, uint16_t value) {
	Wire.beginTransmission((uint8_t)device);
	Wire.write((uint8_t)reg);
	Wire.write((0xFF & (value >> 0)));
	Wire.write((0xFF & (value << 8)));
	Wire.endTransmission(false);
}

/********************************************************
 	Reads an 8 bit value over I2C
*********************************************************/
uint8_t xCoreClass::read8(byte device, byte reg) {
	uint8_t value;
	Wire.beginTransmission((uint8_t)device);
	Wire.write((uint8_t)reg);
	Wire.endTransmission(false);
	Wire.requestFrom((uint8_t)device, (uint8_t)1);
	value = Wire.read();
	return value;
}

/********************************************************
 	Reads an 16 bit value over I2C
*********************************************************/
uint16_t xCoreClass::read16(byte device, byte reg) {
	uint16_t value;
	Wire.beginTransmission((uint8_t)device);
	Wire.write((uint8_t)reg);
	Wire.endTransmission(false);
	Wire.requestFrom((uint8_t)device, (uint8_t)2);
	value = Wire.read(); 
	value <<= 8;
	value |= Wire.read();
	return value;
}

int16_t xCoreClass::readS16(byte device, byte reg) {
	return (int16_t)read16(device, reg);
}

int16_t xCoreClass::readS16_LE(byte device, byte reg){
    return (int16_t)read16_LE(device, reg);
}

uint16_t xCoreClass::read16_LE(byte device, byte reg) {
    uint16_t temp = read16(device, reg);
    return (temp >> 8) | (temp << 8);
}

uint16_t xCoreClass::request16(byte device){
	uint16_t value;
	Wire.requestFrom((uint8_t)device,(uint8_t)2);
	value = Wire.read();
	value <<= 8;
	value |= Wire.read();
	return value;
} 

/********************************************************
 	Reads a signed 24 bit value over I2C
*********************************************************/
uint32_t xCoreClass::read24(byte device, byte reg) {
	uint32_t value;
	Wire.beginTransmission((uint8_t)device);
	Wire.write((uint8_t)reg);
	Wire.endTransmission(false);
	Wire.requestFrom((uint8_t)device, (uint8_t)3);
	value = Wire.read();
	value <<= 8;
	value |= Wire.read();
	value <<= 8;
	value |= Wire.read();
	return value;
}

xCoreClass xCore = xCoreClass();
