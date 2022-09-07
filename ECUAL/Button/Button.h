 /******************************************************************************
 * Module: Button
 * File Name: Button.h
 * Description: Header file for the Button Module
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#ifndef ECUAL_BUTTON_BUTTON_H_
#define ECUAL_BUTTON_BUTTON_H_

/*******************************************************************************
 *                       Header Files & Libraries Includes                     *
 *******************************************************************************/
#include "../../Utils/std_types.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/External_Interrupts/Ext_Interrupts.h"


/*******************************************************************************
 *                  internal module data types                                 *
 *******************************************************************************/
/* Enum type for return type, to handle APIs error */
typedef enum EN_buttonError_t{
	OK_BUTTON, ERROR_BUTTON_DIO_INIT, ERROR_BUTTON_EXT_INT_INIT
}EN_buttonError_t;


/*******************************************************************************
 *                      Function Definitions                                    *
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
EN_buttonError_t Button_Init(void);


#endif /* ECUAL_BUTTON_BUTTON_H_ */
