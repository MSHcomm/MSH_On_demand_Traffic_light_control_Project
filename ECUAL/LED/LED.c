 /******************************************************************************
 * Module: LED
 * File Name: LED.c
 * Description: Source file for the LED Module
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

/*******************************************************************************
 *                       Header Files & Libraries Includes                     *
 *******************************************************************************/
#include "LED.h"
#include "../../MCAL/DIO/DIO_cfg.h"

/*******************************************************************************
 *                                Global variables                             *
 *******************************************************************************/


/*******************************************************************************
 *                      Function Definitions                                    *
 *******************************************************************************/
/*
 * Service Name		: LED_init
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Function to Setup the LED configuration:
 *					If the led initialization does not done correctly,
 *					The function will return EN_LEDError_t type according to the led color.
 */
EN_LEDError_t LED_init(void){

	/* Initialize the DIO pins of red, yellow, and green Car LEDs PA0, PA1, PA2 */
	/* Initialize the DIO pins of red, yellow, and green pedestrian LEDs PB0, PB1, PB2 */
	if(DIO_Init(&g_LED_red) != OK_DOI){
		return ERROR_LED_RED;
	}
	else if(DIO_Init(&g_LED_yellow) != OK_DOI){
		return ERROR_LED_YALLOW;
	}
	else if(DIO_Init(&g_LED_green) != OK_DOI){
		return ERROR_LED_GREEN;
	}
	else if(DIO_Init(&g_LED_pedestrian_red) != OK_DOI){
		return ERROR_LED_RED;
	}
	else if(DIO_Init(&g_LED_pedestrian_yellow) != OK_DOI){
		return ERROR_LED_YALLOW;
	}
	else if(DIO_Init(&g_LED_pedestrian_green) != OK_DOI){
		return ERROR_LED_GREEN;
	}
	else{
		/* Initialize the state of red, yellow, and green LEDs as LED_OFF */
		LED_setOff(&g_LED_red);
		LED_setOff(&g_LED_yellow);
		LED_setOff(&g_LED_green);
		LED_setOff(&g_LED_pedestrian_red);
		LED_setOff(&g_LED_pedestrian_yellow);
		LED_setOff(&g_LED_pedestrian_green);

		return OK_LED;
	}
}


/*
 * Service Name		: LED_setOn
 * Parameters (in)	: *ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Set the LED state to ON
 *					in case of fail to set LED to ON, The function will return ERROR_LED
 */
EN_LEDError_t LED_setOn(ST_DIO_ConfigPin_t *ledPTR){
	if(Dio_WritePin(ledPTR, LED_ON) == OK_DOI){
		return OK_LED;
	}
	else{
		return ERROR_LED;
	}
}


/*
 * Service Name		: LED_setOff
 * Parameters (in)	: *ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Set the LED state to OFF
 *					in case of fail to set LED to OFF, The function will return ERROR_LED
 */
EN_LEDError_t LED_setOff(ST_DIO_ConfigPin_t *ledPTR){
	if(Dio_WritePin(ledPTR, LED_OFF) == OK_DOI){
		return OK_LED;
	}
	else{
		return ERROR_LED;
	}
}


/*
 * Service Name		: LED_toggle
 * Parameters (in)	: *ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Toggle the LED state
 *					in case of fail to toggling LED state, The function will return ERROR_LED
 */
EN_LEDError_t LED_toggle(ST_DIO_ConfigPin_t *ledPTR){
	if(Dio_TogglePin(ledPTR) == OK_DOI){
		return OK_LED;
	}
	else{
		return ERROR_LED;
	}
}


/*
 * Service Name		: LED_toggle
 * Parameters (in)	: *ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Refresh the LED state, by reading led output value on pin and rewrite the same value
 *					in case of fail to Refreshing LED state, The function will return ERROR_LED
 */
/* Description: Refresh the LED state */
EN_LEDError_t LED_refreshOutput(ST_DIO_ConfigPin_t *ledPTR){
	boolean state = LED_OFF;
	if(Dio_ReadPin(ledPTR,&state) == OK_LED){
		if(Dio_WritePin(ledPTR,state) == OK_LED){
			return OK_LED;
		}
		else{
			return ERROR_LED;
		}
	}
	else{
		return ERROR_LED;
	}
}



