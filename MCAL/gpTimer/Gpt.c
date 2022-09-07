 /******************************************************************************
 * Module: GPT - General purpose Timer
 * File Name: Gpt.c
 * Description: Source file for the Timer (Gpt) driver
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/
#include "Gpt.h"
#include "Gpt_Cfg.h"
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function For Timer 0*/
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function For Timer 1*/
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function For Timer 2*/
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;


/*******************************************************************************
 *                          Functions Definition                               *
 *******************************************************************************/

/*
 * Service Name		: Timer_init
 * Parameters (in)	: *Timer_Config
 * Parameters (out)	: None
 * Return value		: EN_TimerError_t
 * Description		: Function to Setup the TIMER configuration:
 *  					1- The Timer Id
 *  					2- The Timer Mode (Normal , Compare)
 *  					3- The Timer Prescalar
 *  					4- The Timer Initial Value That will start counting from it
 *  					5- The The Timer Compare Value (In Compare Mode Only)
 *					If the Timer initialization does not done correctly,
 *					The function will return EN_TimerError_t type according to the timer.
 */
EN_TimerError_t Timer_init(const ST_Timer_Config_t *Timer_ConfigPTR){
	switch (Timer_ConfigPTR->Timer_ID) {
		case Timer0:{
			if(Timer_ConfigPTR->Timer_mode == Normal_Mode){
				/* Configure the timer control register TCCR0
				* 1. Non PWM mode FOC0=1 (Force Output Compare)
				* 2. Normal Mode WGM01=0 & WGM00=0
				* 3. Normal Port Mode (OC0 Disconnected) COM00=0 & COM01=0
				* 4. Timer0 Prescalar is configured using CS2:0 in TCCR0 Register
				*/
				TCCR0 = (1<<FOC0) | ((Timer_ConfigPTR->Prescalar) & 0x07);

				// Set Timer0 initial value
				TCNT0 = Timer_ConfigPTR->Timer_Initial_value;

				// Timer0 Overflow Interrupt Enable
				TIMSK |= (1 << TOIE0);

				// Global Interrupt Enable (I-bit)
				SREG  |= (1<<7);
			}
			else if(Timer_ConfigPTR->Timer_mode == Compare_Mode){
				/* Configure the timer control register TCCR0
				 * 1. Non PWM mode FOC0=1 (Force Output Compare)
				 * 2. Compare Match Mode WGM01=1 & WGM00=0 (Clear Timer on Compare Match (CTC) mode)
				 * 3. Disconnect OC0 COM00=0 & COM01=0
				 * 4. Timer0 Prescalar is configured using CS2:0 in TCCR0 Register
				*/
				TCCR0 = (1<<FOC0) | (1<<WGM01) |((Timer_ConfigPTR->Prescalar) & 0x07);

				// Set Timer0 initial value
				TCNT0 = Timer_ConfigPTR->Timer_Initial_value;

				// Set Timer0 Compare Match Value
				OCR0 = Timer_ConfigPTR->Timer_Compare_value;

				// Timer0 Compare Match Interrupt Enable
				TIMSK |= (1 << OCIE0);

				// Global Interrupt Enable (I-bit)
				SREG  |= (1<<7);
			}
			else{
				return ERROR_TIMER_MODE;
			}
			return OK_TIMER;
		}
			break;
		case Timer1:{
			if(Timer_ConfigPTR->Timer_mode == Normal_Mode){
				/* Configure the timer control register TCCR1A & TCCR1B
				 * 1. Non PWM mode FOC1A = 1 & FOC1B = 1 (Force Output Compare)
				 * 2. Normal Mode WGM10=0 & WGM11=0 & WGM12 =0 & WGM13 =0
				 * 3. Normal Port Mode (Disconnect OC0) COM1A0/COM1B0 = 0 & COM1A1/COM1B0 = 0
				 * 4. Timer1 Prescalar is configured using CS12:0 in TCCR1B Register
				*/
				TCCR1A = (1<<FOC1A) | (1<<FOC1B);
				TCCR1B = (Timer_ConfigPTR->Prescalar);

				// Set Timer1 initial value
				TCNT1 = Timer_ConfigPTR->Timer_Initial_value;

				// Timer1 Overflow Interrupt Enable
				TIMSK |= (1<<TOIE1);

				// Global Interrupt Enable (I-bit)
				SREG  |= (1<<7);
			}

			else if(Timer_ConfigPTR->Timer_mode == Compare_Mode){
				/* Configure the timer control register TCCR1A & TCCR1B
				 * 1. Non PWM mode FOC1A =1 & FOC1B = 1 (Force Output Compare)
				 * 2. Compare Match Mode WGM10 =0 & WGM11 =0 & WGM12 =1 & WGM13 =0
				 * 3. Normal Port Mode (Disconnect OC0) COM1A0/COM1B0 = 0 & COM1A1/COM1B0 = 0
				 * 4. Timer1 Prescalar is configured using CS12:0 in TCCR1B Register
				*/
				TCCR1A = (1<<FOC1A) | (1<<FOC1B);
				TCCR1B = (1<<WGM12) | (Timer_ConfigPTR->Prescalar) ;

				// Set Timer1 initial value
				TCNT1 = Timer_ConfigPTR->Timer_Initial_value;

				// Set Timer1 Compare Match Value
				OCR1A = Timer_ConfigPTR->Timer_Compare_value;

				// Timer1 Compare Match Interrupt Enable (Channel A)
				TIMSK |= (1 << OCIE1A);

				// Global Interrupt Enable (I-bit)
				SREG  |= (1<<7);
			}

			else{
				return ERROR_TIMER_MODE;
			}
			return OK_TIMER;
		}
			break;
		case Timer2:{
			if(Timer_ConfigPTR->Timer_mode == Normal_Mode){
				/* Configure the timer control register TCCR2
				 * 1. Non PWM mode FOC2=1 (Force Output Compare)
		    	 * 2. Normal Mode WGM20=0 & WGM21=0
				 * 3. Normal Port Mode (OC0 Disconnected) COM20=0 & COM21=0
				 * 4. Timer2 Prescalar is configured using CS21:0 in TCCR2 Register
				*/
				  TCCR2 = (1<<FOC2) | ((Timer_ConfigPTR->timer2_prescalar) & 0x07);

				 // Set Timer2 initial value
				 TCNT2 = Timer_ConfigPTR->Timer_Initial_value;

				 // Timer2 Overflow Interrupt Enable
				 TIMSK |= (1 << TOIE2);

				 // Global Interrupt Enable (I-bit)
				 SREG  |= (1<<7);
			}

			else if(Timer_ConfigPTR->Timer_mode == Compare_Mode){
				/* Configure the timer control register TCCR2
				 * 1. Non PWM mode FOC2=1 (Force Output Compare)
				 * 2. Compare Match Mode WGM20=0 & WGM21=1 (Clear Timer on Compare Match (CTC) mode)
				 * 3. Disconnect OC0 COM20=0 & COM21=0
				 * 4. Timer2 Prescalar is configured using CS22:0 in TCCR2 Register
				 */
				 TCCR2 = (1<<FOC2) | (1<<WGM21) | ((Timer_ConfigPTR->timer2_prescalar) & 0x07);

				 /* Set Timer2 initial value */
				 TCNT2 = Timer_ConfigPTR->Timer_Initial_value;

				 /* Set Timer2 Compare Match Value */
				 OCR2 = Timer_ConfigPTR->Timer_Compare_value;

				 /* Timer2 Compare Match Interrupt Enable */
				 TIMSK |= (1 << OCIE2);

				/* Global Interrupt Enable (I-bit) */
				SREG  |= (1<<7);
			}
			else{
				return ERROR_TIMER_MODE;
			}
			return OK_TIMER;
		}
			break;
		default:
			return ERROR_TIMER_ID;
			break;
	}

}


/*
 * Description: Function to set the Call Back function address of Timer0.
 */
void Timer0_setCallBack( void(*T0_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr0 = T0_ptr;
}

/*
 * Description: Function to set the Call Back function address of Timer1.
 */
void Timer1_setCallBack( void(*T1_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr1 = T1_ptr;
}

/*
 * Description: Function to set the Call Back function address of Timer2.
 */
void Timer2_setCallBack( void(*T2_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 = T2_ptr;
}


/*******************************************************************************
 *                      Interrupt Service Routines                             *
 *******************************************************************************/

/* ISR For Timer0 Normal (Overflow) Mode */
ISR(TIMER0_OVF_vect){
	if(g_callBackPtr0 != NULL_PTR){
		/* Call the Call Back function in the application after Timer0 Overflow Occurs*/
		(*g_callBackPtr0)(); /* call the function of Timer0 ISR using pointer to function g_callBackPtr0(); */
	}
}

/* ISR For Timer1 Normal (Overflow) Mode */
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr1 != NULL_PTR){
		/* Call the Call Back function in the application after Timer1 Overflow Occurs*/
		(*g_callBackPtr1)(); /* call the function of Timer1 ISR using pointer to function g_callBackPtr1(); */
	}
}

/* ISR For Timer2 Normal (Overflow) Mode */
ISR(TIMER2_OVF_vect){
	if(g_callBackPtr2 != NULL_PTR){
		/* Call the Call Back function in the application after Timer2 Overflow Occurs*/
		(*g_callBackPtr2)(); /* call the function of Timer2 ISR using pointer to function g_callBackPtr2(); */
	}
}


/* ISR For Timer0 Compare Match Mode */
ISR(TIMER0_COMP_vect){
	if(g_callBackPtr0 != NULL_PTR)	{
		/* Call the Call Back function in the application after Timer0 Compare Match Occurs*/
		(*g_callBackPtr0)(); /* call the function of Timer0 ISR using pointer to function g_callBackPtr0(); */
	}
}

/* ISR For Timer1 Compare Match Mode (Channel A) */
ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr1 != NULL_PTR){
		/* Call the Call Back function in the application after Timer1 Compare Match Occurs*/
		(*g_callBackPtr1)(); /* call the function of Timer1 ISR using pointer to function g_callBackPtr1(); */
	}
}

/* ISR For Timer1 Compare Match Mode */
ISR(TIMER2_COMP_vect){
	if(g_callBackPtr2 != NULL_PTR){
		/* Call the Call Back function in the application after Timer2 Compare Match Occurs*/
		(*g_callBackPtr2)(); /* call the function of Timer2 ISR using pointer to function g_callBackPtr2(); */
	}
}

