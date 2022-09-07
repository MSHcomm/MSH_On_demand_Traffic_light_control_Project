 /******************************************************************************
 * Module: DIO - GPIO
 * File Name: DIO.h
 * Description: Header file for the AVR DIO driver
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

/*******************************************************************************
 *                       Header Files & Libraries Includes                   *
 *******************************************************************************/

/* Standard types and common macros */
#include "../../Utils/std_types.h"
#include "../../Utils/Common_Macros.h"

/* AVR ATmege32 register file */
#include <avr/io.h>
#include <avr/iom32.h>


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_MCU_PORTS		(4U)
#define NUM_OF_PINS_PER_PORT	(8U)

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7


/*******************************************************************************
 *                              Internal Module Data Types                     *
 *******************************************************************************/


/* Enum type to define the pin direction */
typedef enum EN_pinDirection{
	PIN_INPUT=0 , PIN_OUTPUT=1
}EN_pinDirection;


/* Enum type to define the port direction */
typedef enum EN_portDirection{
	PORT_INPUT=0 , PORT_OUTPUT=0xFF
}EN_portDirection;


/* Enum type to define the alternative function of pin */
typedef enum EN_pinAlternative{
	PIN_DIO=0, PIN_ANALOUGE, PIN_COUNTER, PIN_COMPARATOR, PIN_ICU, PIN_SPI_MOSI, PIN_SPI_MISO, PIN_UART_TX, PIN_UART_RX, PIN_PWM
}EN_pinAlternative;


/* Enum type to define the internal resistor status */
typedef enum EN_pinInternalResisrot{
	OFF, PULL_UP, PULL_DOWN
}EN_pinInternalResisrot;


typedef struct ST_DIO_ConfigPin_t{
	uint8					portNumber;
	uint8 					pinNumber;
	EN_pinDirection 		pinDirection;			/* PIN_INPUT or PIN_OUTPUT */
	EN_pinAlternative 		alternativeFunction;	/* select the pin mode as GPIO or alternative function... */
	EN_pinInternalResisrot 	pinInternalResistor;    /* OFF, PULL_UP, or PULL_DOWN */
	uint8 					pinLevelValue;          /* LOGIC_HIGH or LOGIC_LOW */
}ST_DIO_ConfigPin_t;


/* Enum type for return type, to handle APIs error */
typedef enum EN_returnError_t
{
	OK_DOI, WRONG_PIN, WRONG_PORT, WRONG_DIRCTION
}EN_returnError_t;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*
 * Service Name		: DIO_Init
 * Parameters (in)	: portNumber, pinNumber, direction, alternative
 * Parameters (out)	: None
 * Return value		: EN_returnError_t
 * Description		: Function to Setup the pin configuration:
 *					Setup the pin as Digital GPIO pin
 *					Setup the internal resistor for i/p pin
 *					Setup the mode of alternative function
 *					Setup the initial value of the pin High or Low
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t DIO_Init(ST_DIO_ConfigPin_t *pinPTR);


/*
 * Service Name		: DIO_PortInit
 * Parameters (in)	: portNumber, direction
 * Parameters (out)	: None
 * Return value		: EN_returnError_t
 * Description		: Function to Setup the PORT configuration:
 *					Setup the PORT as Digital GPIO pin
 *					Setup the initial value of the port High or Low
 *					If the input port number is not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t DIO_PortInit(uint8 portNumber, EN_portDirection direction);


/*
 * Service Name		: Dio_ReadPin
 * Parameters (in)	: *pinPTRr
 * Parameters (out)	: *readValue
 * Return value		: EN_returnError_t
 * Description		: write the value for the required pin, it should be LOGIC_HIGH or LOGIC_LOW.
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t Dio_ReadPin(ST_DIO_ConfigPin_t *pinPTR, boolean *readValue);


/*
 * Service Name		: Dio_WritePin
 * Parameters (in)	: *pinPTRr, writeValue
 * Parameters (out)	: None
 * Return value		: EN_returnError_t
 * Description		: Write input value for the required pin, it should be LOGIC_HIGH or LOGIC_LOW.
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t Dio_WritePin(ST_DIO_ConfigPin_t *pinPTR, boolean writeValue);


/*
 * Service Name		: Dio_ToggelPin
 * Parameters (in)	: *pinPTRr
 * Parameters (out)	: None
 * Return value		: EN_returnError_t
 * Description		: Toggle the value for the required pin, it should flapping LOGIC_HIGH to LOGIC_LOW and vice versa .
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t Dio_TogglePin(ST_DIO_ConfigPin_t *pinPTR);


#endif /* MCAL_DIO_DIO_H_ */
