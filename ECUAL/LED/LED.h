 /******************************************************************************
 * Module: LED
 * File Name: LED.h
 * Description: Header file for the LED Module
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#ifndef ECUAL_LED_LED_H_
#define ECUAL_LED_LED_H_

/*******************************************************************************
 *                       Header Files & Libraries Includes                     *
 *******************************************************************************/
/* Standard types and common macros */
#include "../../Utils/std_types.h"
#include "../../Utils/Common_Macros.h"

#include "../../MCAL/DIO/DIO.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* Set the led ON/OFF according to its configuration Positive logic or negative logic */
#define LED_ON  LOGIC_HIGH
#define LED_OFF LOGIC_LOW


/*******************************************************************************
 *                              Internal Module Data Types                     *
 *******************************************************************************/
/* Enum type for return type, to handle APIs error */
typedef enum EN_LEDError_t{
	OK_LED, ERROR_LED ,ERROR_LED_RED, ERROR_LED_YALLOW, ERROR_LED_GREEN
}EN_LEDError_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*
 * Service Name		: LED_init
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Function to Setup the LED configuration:
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_LEDError_t type.
 */
EN_LEDError_t LED_init(void);


/*
 * Service Name		: LED_setOn
 * Parameters (in)	: ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Set the LED state to ON
 *					in case of fail to set LED to ON, The function will return ERROR_LED
 */
EN_LEDError_t LED_setOn(ST_DIO_ConfigPin_t *ledPTR);


/*
 * Service Name		: LED_setOff
 * Parameters (in)	: *ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Set the LED state to OFF
 *					in case of fail to set LED to OFF, The function will return ERROR_LED
 */
EN_LEDError_t LED_setOff(ST_DIO_ConfigPin_t *ledPTR);


/*
 * Service Name		: LED_toggle
 * Parameters (in)	: *ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Toggle the LED state
 *					in case of fail to toggling LED state, The function will return ERROR_LED
 */
EN_LEDError_t LED_toggle(ST_DIO_ConfigPin_t *ledPTR);


/*
 * Service Name		: LED_toggle
 * Parameters (in)	: *ledPTR
 * Parameters (out)	: None
 * Return value		: EN_LEDError_t
 * Description		: Refresh the LED state, by reading led output value on pin and rewrite the same value
 *					in case of fail to Refreshing LED state, The function will return ERROR_LED
 */
/* Description: Refresh the LED state */
EN_LEDError_t LED_refreshOutput(ST_DIO_ConfigPin_t *ledPTR);



#endif /* ECUAL_LED_LED_H_ */
