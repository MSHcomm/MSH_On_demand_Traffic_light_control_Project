 /******************************************************************************
 * Module: Button
 * File Name: Button.c
 * Description: Source file for the Button Module
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/
#include "Button.h"
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                                Global variables                             *
 *******************************************************************************/
/* Global variable to hold the configuration For Button on PD0 */
extern ST_DIO_ConfigPin_t g_Button_PD2;

/* Global variable to hold the configuration For interrupt INT0 activation on PD0 */
extern ST_Ext_Int_Config_t g_Ext_Int0_Config;



/*******************************************************************************
 *                                Function Definition                          *
 *******************************************************************************/

/*
 * Service Name		: Button_Init
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Function to Setup the LED configuration:
 *					If the led initialization does not done correctly,
 *					The function will return EN_buttonError_t type
 *					according to the DIO or external interrupt error
 *					otherwise return OK_BUTTON
 */
EN_buttonError_t Button_Init(void){
	/* Initialize PORTD PIN2 as INPUT and activate Pull-up resistor */
	if (DIO_Init(&g_Button_PD2) != OK_DOI){
		return ERROR_BUTTON_DIO_INIT;
	}

	/* Initialize the External Interrupt INT0  */
	else if (Ext_Interrupts_Init(&g_Ext_Int0_Config) != OK_EXT_INT){
		return ERROR_BUTTON_EXT_INT_INIT;
	}

	else{
		return OK_BUTTON;
	}
}



