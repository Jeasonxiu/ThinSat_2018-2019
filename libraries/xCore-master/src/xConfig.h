/********************************************************
 *  This is a library for the XinaBox Configuration  	*
 *													  	*
 *	Core Functions include:								*
 *	-	I2C Communication								*
 *	-	Inter device communication						*
 *														*
 ********************************************************/

#ifndef xConfig_h
#define xConfig_h

#include <stdint.h>

// Defines the BAUD rate
#define BAUD 9600

/********************************************************
 *				 RGB LED Pin Map 			    		*
 ********************************************************/
#if defined(ARDUINO_AVR_CC010)
	#define RED 14
	#define GREEN 15
	#define BLUE 15
	
#elif defined(ARDUINO_AVR_CW01)
	#define RED 14
	#define GREEN 15
	#define BLUE 15
	
#elif defined(ARDUINO_AVR_CR01)
	#define RED 14
	#define GREEN 15
	#define BLUE 15
#endif

#endif
