 /******************************************************************************
 * Module: GPT - General purpose Timer
 * File Name: Gpt.h
 * Description: Header file for the Timer (Gpt) driver
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#ifndef MCAL_GPTIMER_GPT_H_
#define MCAL_GPTIMER_GPT_H_

/*******************************************************************************
 *                       Header Files & Libraries Includes                     *
 *******************************************************************************/

/* Standard types and common macros */
#include "../../Utils/std_types.h"
#include "../../Utils/Common_Macros.h"




/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                              Internal Module Data Types                     *
 *******************************************************************************/

/* NOTE: 	Timer0 :  8-bit counter
 *			Timer1 : 16-bit counter
 *   		Timer2 :  8-bit counter */

/* enum data type to choose one of the 3 AVR timers */
typedef enum EN_Timer_Number{
	Timer0, Timer1, Timer2
}EN_Timer_Number;


/* enum data type to choose AVR Timer Mode */
typedef enum EN_Timer_Modes{
	Normal_Mode, Compare_Mode
}EN_Timer_Modes;


/* enum data type to choose AVR Timer Prescalar For Timer 0,1 */
typedef enum EN_Timer_Prescalar{
	No_Clock, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024,
	Ext_CLK_Falling_Edge, Ext_CLK_Rising_Edge
}EN_Timer_Prescalar;


/* enum data type to choose AVR Timer Prescalar For Timer2 as it has different prescalar than TIMERS 0,1 */
typedef enum EN_Timer2_Prescalar{
	no_clock, f_cpu_clock, f_cpu_8, f_cpu_32, f_cpu_64, f_cpu_128,
	f_cpu_256, f_Cpu_1024
}EN_Timer2_Prescalar;


/* Configuration Structure for AVR Timer Driver Which configure:
 1- The timer ID we want to use (0,1,2)
 2- The Timer driver modes (NormalMode or Compare_mode)
 3- The Timer Prescalar
 4- The Timer Initial value
 5- The Timer Compare Value
*/
typedef struct ST_Timer_Config_t{
	EN_Timer_Number		Timer_ID;
	EN_Timer_Modes		Timer_mode ;
	EN_Timer_Prescalar	Prescalar;
	EN_Timer2_Prescalar	timer2_prescalar;
	uint16 				Timer_Initial_value;
	uint16 				Timer_Compare_value;
}ST_Timer_Config_t;


/* Enum type for return type, to handle APIs error */
typedef enum EN_TimerError_t{
	 ERROR_TIMER0 ,ERROR_TIMER1, ERROR_TIMER2, ERROR_TIMER_ID, ERROR_TIMER_MODE, OK_TIMER
}EN_TimerError_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
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
EN_TimerError_t Timer_init(const ST_Timer_Config_t *Timer_ConfigPTR);



/*
 * Description: Function to set the Call Back function address of Timer0.
 */
void Timer0_setCallBack(void(*T0_ptr)(void));

/*
 * Description: Function to set the Call Back function address of Timer1.
 */
void Timer1_setCallBack(void(*T1_ptr)(void));

/*
 * Description: Function to set the Call Back function address of Timer2.
 */
void Timer2_setCallBack(void(*T2_ptr)(void));












#endif /* MCAL_GPTIMER_GPT_H_ */
