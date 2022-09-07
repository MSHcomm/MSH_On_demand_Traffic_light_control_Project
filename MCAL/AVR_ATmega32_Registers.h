 /******************************************************************************
 * Module: Common - Platform Types Abstraction
 * File Name: AVR_ATmega32_Registers.h
 * Description: types for AVR
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/
#ifndef MCAL_AVR_ATMEGA32_REGISTERS_H_
#define MCAL_AVR_ATMEGA32_REGISTERS_H_

#include "../Utils/std_types.h"

#define PORTA *((volatile uint8*)0x3B)
#define DDRA  *((volatile uint8*)0x3B)
#define PINA  *((volatile uint8*)0x3B)




#endif /* MCAL_AVR_ATMEGA32_REGISTERS_H_ */
