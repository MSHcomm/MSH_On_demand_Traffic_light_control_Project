 /******************************************************************************
 * Module: DIO - GPIO
 * File Name: DIO.c
 * Description: Source file for the AVR DIO driver
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#include "DIO.h"

/*
 * Service Name		: DIO_Init
 * Parameters (in)	: ST_DIO_ConfigPin_t *pinPTR
 * Parameters (out)	: None
 * Return value		: EN_returnError_t
 * Description		: Function to Setup the pin configuration:
 *					Setup the pin as Digital GPIO pin
 *					Setup the internal resistor for i/p pin
 *					Setup the mode of alternative function
 *					Setup the initial value of the pin High or Low
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t DIO_Init(ST_DIO_ConfigPin_t *pinPTR){
	/*
	 * Check if the input port number is greater than NUM_OF_MCU_PORTS value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if(pinPTR->pinNumber >= NUM_OF_PINS_PER_PORT){
		return WRONG_PIN;
	}
	else if(pinPTR->portNumber >= NUM_OF_MCU_PORTS){
		return WRONG_PORT;
	}
	else{
		/* Setup the pin pinPTR->pinDirection as required */
		switch(pinPTR->portNumber){
		case PORTA_ID:
			if(pinPTR->pinDirection == PIN_OUTPUT){
				SET_BIT(DDRA,pinPTR->pinNumber);			/* Set direction as output */
				CLEAR_BIT(PORTA,pinPTR->pinNumber);			/* set the initial value 0 */
				return OK_DOI;
			}
			else if(pinPTR->pinDirection == PIN_INPUT){
				CLEAR_BIT(DDRA,pinPTR->pinNumber);			/* Set direction as input */

				/* check if pull-up is required */
				if(pinPTR->pinInternalResistor == PULL_UP){
					SET_BIT(PORTA,pinPTR->pinNumber);		/* Activate pull-up resistor */
					CLEAR_BIT(PINA, pinPTR->pinNumber);		/* set the initial value 0 */
				}
				else {
					CLEAR_BIT(PORTA,pinPTR->pinNumber);		/* Deactivate pull-up resistor */
				}
				return OK_DOI;
			}
			else{
				/* return WRONG_DIRCTION if direction not PIN_INPUT nor PIN_OUTPUT*/
				return WRONG_DIRCTION;
			}
			break;
		case PORTB_ID:
			if(pinPTR->pinDirection == PIN_OUTPUT){
				SET_BIT(DDRB,pinPTR->pinNumber);			/* Set direction as output */
				CLEAR_BIT(PORTB,pinPTR->pinNumber);			/* set the initial value 0 */
				return OK_DOI;
			}
			else if(pinPTR->pinDirection == PIN_INPUT){
				CLEAR_BIT(DDRB,pinPTR->pinNumber);			/* Set direction as input */

				/* check if pull-up is required */
				if(pinPTR->pinInternalResistor == PULL_UP){
					SET_BIT(PORTB,pinPTR->pinNumber);		/* Activate pull-up resistor */
					CLEAR_BIT(PINB, pinPTR->pinNumber);		/* set the initial value 0 */
				}
				else {
					CLEAR_BIT(PORTB,pinPTR->pinNumber);		/* Deactivate pull-up resistor */
				}
				return OK_DOI;
			}
			else{
				/* return WRONG_DIRCTION if direction not PIN_INPUT nor PIN_OUTPUT*/
				return WRONG_DIRCTION;
			}
			break;
		case PORTC_ID:
			if(pinPTR->pinDirection == PIN_OUTPUT){
				SET_BIT(DDRC,pinPTR->pinNumber);			/* Set direction as output */
				CLEAR_BIT(PORTC,pinPTR->pinNumber);			/* set the initial value 0 */
				return OK_DOI;
			}
			else if(pinPTR->pinDirection == PIN_INPUT){
				CLEAR_BIT(DDRC,pinPTR->pinNumber);			/* Set direction as input */

				/* check if pull-up is required */
				if(pinPTR->pinInternalResistor == PULL_UP){
					SET_BIT(PORTC,pinPTR->pinNumber);		/* Activate pull-up resistor */
					CLEAR_BIT(PINC, pinPTR->pinNumber);		/* set the initial value 0 */
				}
				else {
					CLEAR_BIT(PORTC,pinPTR->pinNumber);		/* Deactivate pull-up resistor */
				}
				return OK_DOI;
			}
			else{
				/* return WRONG_DIRCTION if direction not PIN_INPUT nor PIN_OUTPUT*/
				return WRONG_DIRCTION;
			}
			break;
		case PORTD_ID:
			if(pinPTR->pinDirection == PIN_OUTPUT){
				SET_BIT(DDRD,pinPTR->pinNumber);			/* Set direction as output */
				CLEAR_BIT(PORTD,pinPTR->pinNumber);			/* set the initial value 0 */
				return OK_DOI;
			}
			else if(pinPTR->pinDirection == PIN_INPUT){
				CLEAR_BIT(DDRD,pinPTR->pinNumber);			/* Set direction as input */

				/* check if pull-up is required */
				if(pinPTR->pinInternalResistor == PULL_UP){
					SET_BIT(PORTD,pinPTR->pinNumber);		/* Activate pull-up resistor */
					CLEAR_BIT(PIND, pinPTR->pinNumber);		/* set the initial value 0 */
				}
				else {
					CLEAR_BIT(PORTD,pinPTR->pinNumber);		/* Deactivate pull-up resistor */
				}
				return OK_DOI;
			}
			else{
				/* return WRONG_DIRCTION if direction not PIN_INPUT nor PIN_OUTPUT*/
				return WRONG_DIRCTION;
			}
			break;
		default:
			return WRONG_PORT;
			break;
		}
		if(pinPTR->pinInternalResistor == PULL_UP){
			CLEAR_BIT(SFIOR,PUD);  /* clear PUD bit in SFIOR register to enable all pull-ups in all ports */
		}

	}

}


/*
 * Service Name		: Dio_ReadPin
 * Parameters (in)	: *pinPTRr
 * Parameters (out)	: *readValue
 * Return value		: EN_returnError_t
 * Description		: write the value for the required pin, it should be LOGIC_HIGH or LOGIC_LOW.
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t Dio_ReadPin(ST_DIO_ConfigPin_t *pinPTR, boolean *readValue){
	*readValue = LOGIC_LOW;

		/*
		 * Check if the input port number is greater than NUM_OF_MCU_PORTS value.
		 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
		 * In this case the input is not valid port/pin number
		 */
	if(pinPTR->pinNumber >= NUM_OF_PINS_PER_PORT){
		return WRONG_PIN;
	}
	else if(pinPTR->portNumber >= NUM_OF_MCU_PORTS){
		return WRONG_PORT;
	}
	else{
		/* Read the pin value as required */
		switch(pinPTR->portNumber){
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pinPTR->pinNumber)){
				*readValue = LOGIC_HIGH;
			}
			else{
				*readValue = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pinPTR->pinNumber)){
				*readValue = LOGIC_HIGH;
			}
			else{
				*readValue = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pinPTR->pinNumber)){
				*readValue = LOGIC_HIGH;
			}
			else{
				*readValue = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pinPTR->pinNumber)){
				*readValue = LOGIC_HIGH;
			}
			else{
				*readValue = LOGIC_LOW;
			}
			break;
		default:
			return WRONG_PORT;
			break;
		}
		return OK_DOI;
	}
}


/*
 * Service Name		: Dio_WritePin
 * Parameters (in)	: *pinPTRr, writeValue
 * Parameters (out)	: None
 * Return value		: EN_returnError_t
 * Description		: Write input value for the required pin, it should be LOGIC_HIGH or LOGIC_LOW.
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t Dio_WritePin(ST_DIO_ConfigPin_t *pinPTR, boolean writeValue){
	/*
	 * Check if the input port number is greater than NUM_OF_MCU_PORTS value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if(pinPTR->pinNumber >= NUM_OF_PINS_PER_PORT){
		return WRONG_PIN;
	}
	else if(pinPTR->portNumber >= NUM_OF_MCU_PORTS){
		return WRONG_PORT;
	}
	else{
		/* Read the pin value as required */
		switch(pinPTR->portNumber){
		case PORTA_ID:
			if(writeValue == LOGIC_HIGH){
				SET_BIT(PORTA,pinPTR->pinNumber);
			}
			else{
				CLEAR_BIT(PORTA,pinPTR->pinNumber);
			}
			break;
		case PORTB_ID:
			if(writeValue == LOGIC_HIGH){
				SET_BIT(PORTB,pinPTR->pinNumber);
			}
			else{
				CLEAR_BIT(PORTB,pinPTR->pinNumber);
			}
			break;
		case PORTC_ID:
			if(writeValue == LOGIC_HIGH){
				SET_BIT(PORTC,pinPTR->pinNumber);
			}
			else{
				CLEAR_BIT(PORTC,pinPTR->pinNumber);
			}
			break;
		case PORTD_ID:
			if(writeValue == LOGIC_HIGH){
				SET_BIT(PORTD,pinPTR->pinNumber);
			}
			else{
				CLEAR_BIT(PORTD,pinPTR->pinNumber);
			}
			break;
		default:
			return WRONG_PORT;
			break;
		}
		return OK_DOI;
	}
}


/*
 * Service Name		: Dio_ToggelPin
 * Parameters (in)	: *pinPTRr
 * Parameters (out)	: None
 * Return value		: EN_returnError_t
 * Description		: Toggle the value for the required pin, it should flapping LOGIC_HIGH to LOGIC_LOW and vice versa .
 *					If the input port number or pin number are not correct, The function will return WRONG_RETURN as EN_returnError_t type.
 */
EN_returnError_t Dio_TogglePin(ST_DIO_ConfigPin_t *pinPTR){
	/*
	 * Check if the input port number is greater than NUM_OF_MCU_PORTS value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if(pinPTR->pinNumber >= NUM_OF_PINS_PER_PORT){
		return WRONG_PIN;
	}
	else if(pinPTR->portNumber >= NUM_OF_MCU_PORTS){
		return WRONG_PORT;
	}
	else if(pinPTR->pinDirection == PIN_OUTPUT){
		/* Read the pin value as required */
		switch(pinPTR->portNumber){
		case PORTA_ID:
			TOGGLE_BIT(PORTA,pinPTR->pinNumber);
			break;
		case PORTB_ID:
			TOGGLE_BIT(PORTB,pinPTR->pinNumber);
			break;
		case PORTC_ID:
			TOGGLE_BIT(PORTC,pinPTR->pinNumber);
			break;
		case PORTD_ID:
			TOGGLE_BIT(PORTD,pinPTR->pinNumber);
			break;
		default:
			return WRONG_PORT;
			break;
		}
		return OK_DOI;
	}
	else{
		return WRONG_DIRCTION;
	}
}


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
EN_returnError_t DIO_PortInit(uint8 portNumber, EN_portDirection direction){
	/*
	 * Check if the input number is greater than NUM_OF_MCU_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(portNumber >= NUM_OF_MCU_PORTS)
	{
		return WRONG_PORT;
	}
	else if((direction == PORT_INPUT) || (direction == PORT_OUTPUT)){
		/* Setup the port direction as required */
		switch(portNumber)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		default:
			return WRONG_PORT;
			break;
		}
		return OK_DOI;
	}
	else {
		return WRONG_DIRCTION;
	}
}

