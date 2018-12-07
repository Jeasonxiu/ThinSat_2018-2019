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

#ifndef xSL01_h
#define xSL01_h

// Include File Headers
#include "xCore.h"

// I2C Chip Addresses
#define VEML6075_I2C_ADDRESS 		0x10	// I2C Address of Chip
#define TSL4531_I2C_ADDRESS 		0x29	// I2C Address of Chip

// Defines VEML6075 Registers
#define VEML6075_REG_CONF        	0x00 	// Configuration register 
#define VEML6075_REG_UVA         	0x07 	// UVA register
#define VEML6075_REG_DUMMY			0x08 	
#define VEML6075_REG_UVB         	0x09 	// UVB register
#define VEML6075_REG_UVCOMP1     	0x0A 	// Visible compensation register
#define VEML6075_REG_UVCOMP2    	0x0B 	// IR compensation register

// Defines VEML6075
#define VEML6075_CONF_HD_NORM		0x00	// Normal Dynamic Setting
#define VEML6075_CONF_HD_HIGH		0x80	// High Dynamic Setting
#define VEML6075_CONF_UV_TRIG_ONCE	0x04	// Triggers UV Measurement Once
#define VEML6075_CONF_UV_TRIG_NORM	0x00	// Normal Mode Operation
#define VEML6075_CONF_AF_FORCE 		0x00	// Normal Mode Enabled
#define VEML6075_CONF_AF_AUTO		0x02	// Active Force Mode Disabled
#define VEML6075_CONF_SD_OFF		0x00	// Power ON
#define VEML6075_CONF_SD_ON			0x01	// Power OFF

#define VEML6075_CONF_IT_50			0x00	// 50ms
#define VEML6075_CONF_IT_100		0x10	// 100ms
#define VEML6075_CONF_IT_200		0x20	// 200ms
#define VEML6075_CONF_IT_400		0x30	// 400ms
#define VEML6075_CONF_IT_800		0x40	// 800ms

#define VEML6075_UVA_VIS_COEFF		3.33
#define VEML6075_UVA_IR_COEFF		2.5
#define VEML6075_UVB_VIS_COEFF		3.66
#define VEML6075_UVB_IR_COEFF		2.75
#define VEML6075_UVA_RESP 			0.001
#define VEML6075_UVB_RESP			0.00125


// Defines TSL4531 Registers
#define TSL4531_REG_CONTROL 		0x00	// Control Register Address
#define TSL4531_REG_CONF			0x01	// Configuration Register Address
#define TSL4531_REG_DATA_LOW		0x04	// ADC low byte
#define TSL4531_REG_DATA_HIGH		0x05	// ADC high byte

// Defines TSL4531
#define TSL4531_WRITE_CMD			0x80	// Command Register. Must write as 1.
#define TSL4531_CONF_PWR_DOWN 		0x00	// Power OFF
#define TSL4531_CONF_ONE_RUN 		0x02	// Run ONCE then Power OFF
#define TSL4531_CONF_START 			0x03	// Power ON

#define TSL4531_CONF_IT_100			0x02	// 100ms
#define	TSL4531_CONF_IT_200			0x01	// 200ms
#define	TSL4531_CONF_IT_400			0x00	// 400ms

#define TSL4531_CONF_PSAVE 			0x08

class xSL01: public xCoreClass
{
	public:
		xSL01();
		bool 	begin(void);
		void 	poll(void);
		
		float 	getUVA(void);
		float 	getUVB(void);
		float 	getLUX(void);

	private:
		void 	readTSL(void);
		void 	readVEML(void);
		void 	readUVdata(void);
		void 	readRawLux(void);
			
		float 	UVAintensity;
		float 	UVBintensity;
		float 	LUX;
		
		uint16_t	UVA;
		uint16_t	Dummy;
		uint16_t	UVB;
		uint16_t	UVcomp1;
		uint16_t	UVcomp2;
		
		uint8_t 	raw_LUX_L;
		uint8_t 	raw_LUX_H;
};

extern xSL01 SL01;
#endif

