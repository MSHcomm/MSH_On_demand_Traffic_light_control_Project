 /******************************************************************************
 * Module: External_Interrupts
 * File Name: Ext_Interrupts.c
 * Description: Source file for the AVR External Interrupts driver
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#include "Ext_Interrupts.h"
#include "Ext_Interrupts_Cfg.h"
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the address of the call back function For External interrupt 0*/
static volatile void (*g_Ext_Int_callBackPtr0)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function For External interrupt 1*/
static volatile void (*g_Ext_Int_callBackPtr1)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function For External interrupt 2*/
static volatile void (*g_Ext_Int_callBackPtr2)(void) = NULL_PTR;


/*******************************************************************************
 *                          Functions Definition                               *
 *******************************************************************************/

/* API to (enable)  set global interrupt in SREG */
void _SEI(void){
	__asm__ __volatile__("sei" ::: "memory");
}


/* API to (disable) clear global interrupt in SREG */
void _CLI(void){
	__asm__ __volatile__("cli" ::: "memory");
}


/*
 * Service Name		: Ext_Interrupts_Init
 * Parameters (in)	: *Ext_Int_ConfigPTR
 * Parameters (out)	: None
 * Return value		: EN_ExtIntError_t
 * Description		: Function to Setup the External Interrupts configuration:
 *  					1- The External Interrupt Id
 *  					2- The External Interrupt Mode (LowLevel, ChangeLevel, FailingEdge, RisingEdge)
 *  					3- The External Interrupt Enable must be TRUE to Enable INT bit in GICR (General Interrupt Control Register)
 *  					4- Enable General Interrupt bit (I-bit)
 *					If the External Interrupt initialization does not done correctly,
 *					The function will return EN_ExtIntError_t type according to the error.
 */
EN_ExtIntError_t Ext_Interrupts_Init(ST_Ext_Int_Config_t *Ext_Int_ConfigPTR){


	switch (Ext_Int_ConfigPTR->Ext_Int_ID) {

	/************************************ External Interrupts 0 ***************************************/
			case EXT_INT0:
				/* Masking ISC01=0 & ISC00=0, so The low level by default
				 * of INT0 is generating an interrupt request */
				MCUCR &= (~(1<<ISC01) & ~(1<<ISC00));
				switch(Ext_Int_ConfigPTR->Ext_Int_Mode){
				case LowLevel:
					/* ISC01=0 & ISC00=0 The low level of INT0 generates an interrupt request */
					break;
				case ChangeLevel:
					/* ISC01=0 & ISC00=1 Any logical change on INT0 generates an interrupt request. */
					MCUCR |= (1<<ISC00);
					break;
				case FailingEdge:
					/* ISC01=1 & ISC00=0 The falling edge of INT0 generates an interrupt request */
					MCUCR |= (1<<ISC01);
					break;
				case RisingEdge:
					/* ISC01=1 & ISC00=1 The rising edge of INT0 generates an interrupt request */
					MCUCR |= ((1<<ISC01) | (1<<ISC00));
					break;
				default:
					/* return OK_EXT_INT means external interrupt 0 configured correctly for error handling */
					return ERROR_EXT_INT_MODE;
					break;
				}

				if(Ext_Int_ConfigPTR->Ext_Int_Enable == TRUE){
					/* Enable External Interrupt Request 0 */
					GICR |= (1<<INT0);
					/* set global interrupt enable */
					_SEI();
					/* return OK_EXT_INT means external interrupt 0 configured correctly for error handling */
					return OK_EXT_INT;
				}
				else{
					/* Return ERROR_EXT_INT0 for error handling
					 * in case of could not configure external interrupt 0 correctly
					 * due to Ext_Int_Enable in *Ext_Int_ConfigPTR is not enabled (FALSE/0) */
					return ERROR_EXT_INT0;
				}
				break;


				/************************************ External Interrupts 1 ***************************************/
			case EXT_INT1:
				/* Masking ISC11=0 & ISC10=0, so The low level by default
				 * of INT1 is generating an interrupt request */
				MCUCR &= (~(1<<ISC11) & ~(1<<ISC10));
				switch(Ext_Int_ConfigPTR->Ext_Int_Mode){
				case LowLevel:
					/* ISC11=0 & ISC10=0 The low level of INT1 generates an interrupt request */
					break;
				case ChangeLevel:
					/* ISC11=0 & ISC10=1 Any logical change on INT1 generates an interrupt request. */
					MCUCR |= (1<<ISC10);
					break;
				case FailingEdge:
					/* ISC11=1 & ISC10=0 The falling edge of INT1 generates an interrupt request */
					MCUCR |= (1<<ISC11);
					break;
				case RisingEdge:
					/* ISC11=1 & ISC10=1 The rising edge of INT1 generates an interrupt request */
					MCUCR |= ((1<<ISC11) | (1<<ISC10));
					break;
				default:
					/* In case of configuring mode with different from traditional modes above
					 * return ERROR_EXT_INT_MODE for error handling  */
					return ERROR_EXT_INT_MODE;
					break;
				}

				if(Ext_Int_ConfigPTR->Ext_Int_Enable == TRUE){
					/* Enable External Interrupt Request 1 */
					GICR |= (1<<INT1);
					/* set global interrupt enable */
					_SEI();
					/* return OK_EXT_INT means external interrupt 1 configured correctly for error handling */
					return OK_EXT_INT;
				}
				else{
					/* Return ERROR_EXT_INT1 for error handling
					 * in case of could not configure external interrupt 1 correctly
					 * due to Ext_Int_Enable in *Ext_Int_ConfigPTR is not enabled (FALSE/0) */
					return ERROR_EXT_INT1;
				}
				break;

				/************************************ External Interrupts 2 ***************************************/
			case EXT_INT2:
				/* Masking ISC2=0, so The Failing Edge by default
				 * of INT2 is generating an interrupt request */
				MCUCSR &= ~(1<<ISC2);
				switch(Ext_Int_ConfigPTR->Ext_Int_Mode){
				case FailingEdge:
					/* ISC2=0 The falling edge of INT2 generates an interrupt request */
					break;
				case RisingEdge:
					/* ISC2=1 The rising edge of INT2 generates an interrupt request */
					MCUCSR |= (1<<ISC2);
					break;
				default:
					/* In case of configuring mode with different from traditional modes above
					 * return ERROR_EXT_INT_MODE for error handling  */
					return ERROR_EXT_INT_MODE;
					break;
				}

				if(Ext_Int_ConfigPTR->Ext_Int_Enable == TRUE){
					/* Enable External Interrupt Request 2 */
					GICR |= (1<<INT2);
					/* set global interrupt enable */
					_SEI();
					/* return OK_EXT_INT means external interrupt 2 configured correctly for error handling */
					return OK_EXT_INT;
				}
				else{
					/* Return ERROR_EXT_INT2 for error handling
					 * in case of could not configure external interrupt 2 correctly
					 * due to Ext_Int_Enable in *Ext_Int_ConfigPTR is not enabled (FALSE/0) */
					return ERROR_EXT_INT2;
				}
				break;

				/************************************ ************ ***********************************************/
			default:
				/* return ERROR_EXT_INT_ID means external interrupt ID wrong configured, for error handling,
				 * Ext_Int_ID have to configured as EXT_INT0=0, EXT_INT1=1, or EXT_INT2=2*/
				return ERROR_EXT_INT_ID;
				break;
	}


}


/*
 * Service Name		: Ext_Interrupts_deinit
 * Parameters (in)	: *Ext_Int_ConfigPTR
 * Parameters (out)	: None
 * Return value		: EN_ExtIntError_t
 * Description		: Function to uninitialize the External Interrupts configuration:
 *  					1- The External Interrupt Id
 *  					2- The External Interrupt must be disabled (Ext_Int_Enable = FALSE or 0) in Ext_Int_ConfigPTR
 *  					   to clear INT0, INT1, or INT2 bit in GICR (General Interrupt Control Register)
 *					If the External Interrupt uninitialized correctly,
 *					The function will return EN_ExtIntError_t type according to the error.
 */
EN_ExtIntError_t Ext_Interrupts_deinit(ST_Ext_Int_Config_t *Ext_Int_ConfigPTR){
	if (Ext_Int_ConfigPTR->Ext_Int_Enable == FALSE){
		switch(Ext_Int_ConfigPTR->Ext_Int_ID){
		case EXT_INT0:
			/* Disable External Interrupt Request 0 */
			GICR &= ~(1<<INT0);
			break;
		case EXT_INT1:
			/* Disable External Interrupt Request 1 */
			GICR &= ~(1<<INT1);
			break;
		case EXT_INT2:
			/* Disable External Interrupt Request 2 */
			GICR &= ~(1<<INT2);
			break;
		default:
			/* return ERROR_EXT_INT_ID means external interrupt ID wrong configured, for error handling,
			 * Ext_Int_ID have to configured as EXT_INT0=0, EXT_INT1=1, or EXT_INT2=2*/
			return ERROR_EXT_INT_ID;
			break;
		}
		/* return OK_EXT_INT means external interrupt uninitialized correctly for error handling */
		return OK_EXT_INT;
	}

	else{
		/* return ERROR_EXT_INT0, ERROR_EXT_INT1, or ERROR_EXT_INT2 for error handling,
		 *  means external interrupt can not uninitialized correctly because
		 *  Ext_Int_Enable field in Ext_Int_ConfigPTR not (FALSE) yet */
		switch(Ext_Int_ConfigPTR->Ext_Int_ID){
				case EXT_INT0:
					return ERROR_EXT_INT0;
					break;

				case EXT_INT1:
					return ERROR_EXT_INT1;
					break;

				case EXT_INT2:
					return ERROR_EXT_INT2;
					break;
				default:
					/* return ERROR_EXT_INT_ID means external interrupt ID wrong configured, for error handling,
					 * Ext_Int_ID have to configured as EXT_INT0=0, EXT_INT1=1, or EXT_INT2=2*/
					return ERROR_EXT_INT_ID;
					break;
		}
	}
}


/*
 * Description: Function to set the Call Back function address of External interrupt 0.
 */
void Ext_Interrupt0_setCallBack(void(*T0_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_Ext_Int_callBackPtr0 = T0_ptr;
}


/*
 * Description: Function to set the Call Back function address of External interrupt 1.
 */
void Ext_Interrupt1_setCallBack(void(*T1_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_Ext_Int_callBackPtr1 = T1_ptr;
}


/*
 * Description: Function to set the Call Back function address of External interrupt 2.
 */
void Ext_Interrupt2_setCallBack(void(*T2_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_Ext_Int_callBackPtr2 = T2_ptr;
}

/*******************************************************************************
 *                      Interrupt Service Routines                             *
 *******************************************************************************/
/* ISR For External Interrupt 0 request */
ISR(INT0_vect){
	if(g_Ext_Int_callBackPtr0 != NULL_PTR){
		/* Call the Call Back function in the application after Timer0 Overflow Occurs*/
		(*g_Ext_Int_callBackPtr0)(); /* call the function of Timer0 ISR using pointer to function g_callBackPtr0(); */
	}
}


/* ISR For External Interrupt 1 request */
ISR(INT1_vect){
	if(g_Ext_Int_callBackPtr1 != NULL_PTR){
		/* Call the Call Back function in the application after Timer0 Overflow Occurs*/
		(*g_Ext_Int_callBackPtr1)(); /* call the function of Timer0 ISR using pointer to function g_callBackPtr0(); */
	}
}


/* ISR For External Interrupt 2 request */
ISR(INT2_vect){
	if(g_Ext_Int_callBackPtr2 != NULL_PTR){
		/* Call the Call Back function in the application after Timer0 Overflow Occurs*/
		(*g_Ext_Int_callBackPtr2)(); /* call the function of Timer0 ISR using pointer to function g_callBackPtr0(); */
	}
}
