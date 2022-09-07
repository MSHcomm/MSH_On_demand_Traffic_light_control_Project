 /******************************************************************************
 * Module: DIO - GPIO
 * File Name: DIO_Cfg.h
 * Description: Pre-Compile Configuration Header file for the AVR DIO driver
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#ifndef MCAL_DIO_DIO_CFG_H_
#define MCAL_DIO_DIO_CFG_H_

#include "DIO.h"

ST_DIO_ConfigPin_t g_LED_red = {
	PORTA_ID,		/* portNumber */
	0, 				/* pinNumber */
	PIN_OUTPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	OFF,			/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	0 				/* pinLevelValue */
};

ST_DIO_ConfigPin_t g_LED_yellow = {
	PORTA_ID,		/* portNumber */
	1, 				/* pinNumber */
	PIN_OUTPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	OFF,			/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	0 				/* pinLevelValue */
};

ST_DIO_ConfigPin_t g_LED_green = {
	PORTA_ID,		/* portNumber */
	2, 				/* pinNumber */
	PIN_OUTPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	OFF,			/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	0 				/* pinLevelValue */
};


ST_DIO_ConfigPin_t g_LED_pedestrian_red = {
	PORTB_ID,		/* portNumber */
	0, 				/* pinNumber */
	PIN_OUTPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	OFF,			/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	0 				/* pinLevelValue */
};

ST_DIO_ConfigPin_t g_LED_pedestrian_yellow = {
	PORTB_ID,		/* portNumber */
	1, 				/* pinNumber */
	PIN_OUTPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	OFF,			/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	0 				/* pinLevelValue */
};

ST_DIO_ConfigPin_t g_LED_pedestrian_green = {
	PORTB_ID,		/* portNumber */
	2, 				/* pinNumber */
	PIN_OUTPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	OFF,			/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	0 				/* pinLevelValue */
};

ST_DIO_ConfigPin_t g_Button_PD2 = {
	PORTD_ID,		/* portNumber */
	2, 				/* pinNumber */
	PIN_INPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	PULL_UP,		/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	1 				/* pinLevelValue */
};


ST_DIO_ConfigPin_t g_PIN_TEST = {
	PORTA_ID,		/* portNumber */
	9, 				/* pinNumber */
	PIN_OUTPUT,		/* pinDirection */			/* PIN_INPUT or PIN_OUTPUT */
	0, 				/* alternativeFunction */	/* select the pin mode as GPIO or alternative function... */
	OFF,			/* pinInternalResistor */    /* OFF, PULL_UP, or PULL_DOWN */
	0 				/* pinLevelValue */
};
#endif /* MCAL_DIO_DIO_CFG_H_ */
