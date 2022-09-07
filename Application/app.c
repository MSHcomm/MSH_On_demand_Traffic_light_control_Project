 /******************************************************************************
 * Module: Application
 * File Name: app.c
 * Description: source file for application
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/


/*******************************************************************************
 *                       Header Files & Libraries Includes                     *
 *******************************************************************************/
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/Button/Button.h"
#include "../MCAL/gpTimer/Gpt.h"
#include "app.h"
#include <assert.h>
#include <stdlib.h>


/*******************************************************************************
 *                                Global variables                             *
 *******************************************************************************/
/* flag to know when the timer finish counting */
volatile uint16 g_timer_delay = 0;


/* flag to know when the timer2 finish counting, means the delay time is finished */
volatile boolean g_Delay_LED_blinking = FALSE;


/* flag to know when the the Button was pressed by Ext. InterruptINT0 */
volatile boolean g_Button_pressed  = FALSE;


/* boolean flag to know the current state of traffic light LEDs */
volatile boolean g_red_flag    = FALSE;
volatile boolean g_yellow_flag = FALSE;
volatile boolean g_green_flag  = FALSE;


/* Global variable to hold the configuration For Timer0 & Timer1 */
extern ST_Timer_Config_t g_Timer0_Config;
extern ST_Timer_Config_t g_Timer2_Config;


/* global variable to define DIO of all LEDs */
extern ST_DIO_ConfigPin_t g_LED_red;
extern ST_DIO_ConfigPin_t g_LED_yellow;
extern ST_DIO_ConfigPin_t g_LED_green;
extern ST_DIO_ConfigPin_t g_LED_pedestrian_red;
extern ST_DIO_ConfigPin_t g_LED_pedestrian_yellow;
extern ST_DIO_ConfigPin_t g_LED_pedestrian_green;
extern ST_DIO_ConfigPin_t g_Button_PD2;
extern ST_DIO_ConfigPin_t g_PIN_TEST;
/*******************************************************************************
 *                                Function Definition                          *
 *******************************************************************************/

static void LED_handleTimer(void){
	g_timer_delay++;
}



static void BlinkingLED_handlerTimer2(void){
	g_Delay_LED_blinking = TRUE;
}



static void Button_handleExternalInterrupt0(void){
	g_Button_pressed = TRUE;
}



/*
 * Service Name		: APP_Init
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_appError_t
 * Description		: Function to Setup the application configuration
 * 					  initialize LEDs as output and Button as input
 * 					  set the call back functions
 *					If the initialization processed correctly, The function will return OK_APP
 *					else return as EN_appError_t type for error handling according to task fail
 */
EN_appError_t APP_Init(void){

	/* set call back function to get notification for 5 second timer delay for timer0 */
	Timer0_setCallBack( LED_handleTimer );

	/* set call back function to get notification for 250 millisecond timer delay for timer2  */
	Timer2_setCallBack( BlinkingLED_handlerTimer2 );

	/* set call back function to get notification if the button pressed */
	Ext_Interrupt0_setCallBack( Button_handleExternalInterrupt0 );


	/* Initialize and SetOFF all LEDs */
	if (LED_init() != OK_LED){
		return ERROR_APP_LED_INIT;
	}

	/* Initialize the button as INT0 */
	else if(Button_Init() != OK_BUTTON){
		return ERROR_APP_BUTTON_INIT;
	}

	/* Initialize the timer0 */
	else if(Timer_init(&g_Timer0_Config) != OK_TIMER){
		return ERROR_APP_TIMER_INIT;
	}

	/* Initialize the timer2 */
	else if(Timer_init(&g_Timer2_Config) != OK_TIMER){
		return ERROR_APP_TIMER_INIT;
	}

	/* Parameter initialization and return OK */
	else{
		g_timer_delay = 0;
		g_Delay_LED_blinking = FALSE;
		return OK_APP;
	}
}



/* Yellow Task */


static EN_appError_t YellowON(void){
	g_red_flag    = FALSE;
	g_yellow_flag = TRUE;
	g_green_flag  = FALSE;

	if (LED_setOff(&g_LED_red) 						!= OK_LED){
		return ERROR_APP_YELLOW_ON;
	}
	else if (LED_setOff(&g_LED_green) 				!= OK_LED){
		return ERROR_APP_YELLOW_ON;
	}
	else if (LED_setOff (&g_LED_pedestrian_yellow)	!= OK_LED){
		return ERROR_APP_YELLOW_ON;
	}
	else if (LED_setOff(&g_LED_pedestrian_green)	!= OK_LED){
		return ERROR_APP_YELLOW_ON;
	}

	g_timer_delay = 0;				/* Rest the timer delay counter for 5 second */
	g_Delay_LED_blinking = FALSE; 	/* Rest the timer delay flag for 250 millisecond blinking */
	while(g_timer_delay <= 20){
		if (LED_setOn(&g_LED_pedestrian_red)	!= OK_LED){
			return ERROR_APP_YELLOW_ON;
		}
		if(g_Delay_LED_blinking){
			if (LED_toggle(&g_LED_yellow)		 	!= OK_LED){
				return ERROR_APP_YELLOW_ON;
			}
			g_Delay_LED_blinking = FALSE; /* Releasing the blinking flag */
		}
	}

	if(g_Button_pressed){
		pedestrianMode();
	}
	return OK_APP;
}




/* Red Task */
static EN_appError_t RedON(void){
	g_red_flag    = TRUE;
	g_yellow_flag = FALSE;
	g_green_flag  = FALSE;

	if (LED_setOff(&g_LED_yellow) 					!= OK_LED){
		return ERROR_APP_RED_ON;
	}
	else if (LED_setOff(&g_LED_green) 				!= OK_LED){
		return ERROR_APP_RED_ON;
	}
	else if (LED_setOff(&g_LED_pedestrian_red)		!= OK_LED){
		return ERROR_APP_RED_ON;
	}
	else if (LED_setOff(&g_LED_pedestrian_yellow)	!= OK_LED){
		return ERROR_APP_RED_ON;
	}

	g_timer_delay = 0;			/* Rest the timer delay counter for 5 second */
	while(g_timer_delay <= 20){
		if (LED_setOn(&g_LED_red) 					!= OK_LED){
			return ERROR_APP_RED_ON;
		}
		if (LED_setOn(&g_LED_pedestrian_green) 		!= OK_LED){
			return ERROR_APP_RED_ON;
		}
	}

	/* If the Button presses, "Do Not Any Thing", just releasing Button */
	if(g_Button_pressed){
		/* Releasing pedestrian mode */
		g_Button_pressed = FALSE;
	}

	return OK_APP;
}



/* Green task */
static EN_appError_t GreenON(void){
	g_red_flag    = FALSE;
	g_yellow_flag = FALSE;
	g_green_flag  = TRUE;

	if (LED_setOff(&g_LED_red) 						!= OK_LED){
		return ERROR_APP_GREEN_ON;
	}
	else if	(LED_setOff(&g_LED_yellow) 				!= OK_LED){
		return ERROR_APP_GREEN_ON;
	}
	else if (LED_setOff(&g_LED_pedestrian_yellow) 	!= OK_LED){
		return ERROR_APP_GREEN_ON;
	}
	else if (LED_setOff(&g_LED_pedestrian_green) 	!= OK_LED){
		return ERROR_APP_GREEN_ON;
	}

	g_timer_delay = 0;			/* Rest the timer delay counter for 5 second */
	while(g_timer_delay <= 20){
		if (LED_setOn(&g_LED_green) 				!= OK_LED){
			return ERROR_APP_GREEN_ON;
		}
		else if (LED_setOn(&g_LED_pedestrian_red)	!= OK_LED){
			return ERROR_APP_GREEN_ON;
		}
	}

	if(g_Button_pressed){
		pedestrianMode();
	}

	return OK_APP;
}



/*
 * Service Name		: normalMode
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_appError_t
 * Description		: Function to call the yellow, red, and green tasks in the normal sequence required
 * 					Cars' LEDs will be changed every five seconds
 * 					the sequence starting from Green then yellow then red then yellow then Green.
 *					If all tasks processed correctly, The function will return OK_APP
 *					else return as EN_appError_t type for error handling according to task fail
 */
EN_appError_t normalMode(void){

	/* Calling Green ON Task */
	if (GreenON() 				!= OK_APP){
		return ERROR_APP_YELLOW_ON;
	}


	/* Calling Yellow ON Task before red */
	else if (YellowON() 		!= OK_APP){
		return ERROR_APP_YELLOW_ON;
	}

	/* Calling Red ON Task */
	else if (RedON() 			!= OK_APP){
		return ERROR_APP_RED_ON;
	}

	/* Calling Yellow ON Task after red */
	else if (YellowON() 		!= OK_APP){
		return ERROR_APP_YELLOW_ON;
	}

	/* return OK_APP if the all takes done correctly */
	else{
		return OK_APP;
	}
}



/*
 * Service Name		: pedestrianMode
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_appError_t
 * Description		: Function to be called if the Button pressed
 *					If all tasks checking the cases of pressing Button correctly, The function will return OK_APP
 *					else return as EN_appError_t type for error handling according to task fail
 */
EN_appError_t pedestrianMode(void){
	/* FIRST CASE: when the cars' Red LED is on, the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds,
	 * this means that pedestrians can cross the street while the pedestrian's Green LED is on */
	if((g_red_flag) && (!g_yellow_flag) && (!g_green_flag)){
		/* Do Not Any Thing */
		/* Releasing pedestrian mode */
		g_Button_pressed = FALSE;
		return OK_APP;
	}

	/* SECOND CASE:   when the cars' Green LED is on or the cars' Yellow LED is blinking,
	 * the pedestrian Red LED will be on
	 * 1- Both Yellow LEDs start to blink for five seconds,
	 * 2- then the cars' Red LED and pedestrian Green LEDs are on for five seconds,
	 * this means that pedestrian must wait until the Green LED is on */
	else if((!g_red_flag) && ((g_yellow_flag) || (g_green_flag))){
		/* Seting red, green, pedestrian red, and pedestrian green LEDs off */
		if (LED_setOff(&g_LED_red) 					!= OK_LED){
			return ERROR_PEDESTRIAN_MODE;
		}
		if (LED_setOff(&g_LED_green)				!= OK_LED){
			return ERROR_PEDESTRIAN_MODE;
		}
		if (LED_setOff(&g_LED_pedestrian_red)		!= OK_LED){
			return ERROR_PEDESTRIAN_MODE;
		}
		if (LED_setOff(&g_LED_pedestrian_green)		!= OK_LED){
			return ERROR_PEDESTRIAN_MODE;
		}

		/* 1- Both Yellow LEDs blinking for five seconds */
		g_timer_delay = 0;
		g_Delay_LED_blinking = FALSE;
		while(g_timer_delay <= 20){
			if(g_Delay_LED_blinking){
				if (LED_toggle(&g_LED_yellow)			!= OK_LED){
					return ERROR_PEDESTRIAN_MODE;
				}
				if (LED_toggle(&g_LED_pedestrian_yellow)!= OK_LED){
					return ERROR_PEDESTRIAN_MODE;
				}

				/* Releasing the blinking flag */
				g_Delay_LED_blinking = FALSE;
			}
		}

		/* 2- then the cars' Red LED and pedestrian Green LEDs are on for five seconds */
		if (RedON() 									!= OK_APP){
			return ERROR_APP_RED_ON;
		}

		/* Releasing pedestrian mode */
		g_Button_pressed = FALSE;
		return OK_APP;
	}

	else{
		g_Button_pressed = FALSE;
		return OK_APP;
	}
}



/*
 * Service Name		: APP_start
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_appError_t
 * Description		: Function to start the application by calling modes
 *					If mode called correctly, The function will return OK_APP
 *					else return as EN_appError_t type for error handling according to mode fail
 */
EN_appError_t APP_start(void){
	if (normalMode() != OK_APP){
		return ERROR_NORMAL_MODE;
	}
	else{
		return OK_APP;
	}
}



void APP_Test(void){
	/************************************************************************************
	* Test ID :TestCase1_DIO
	* Description: Test for
	* 						DIO_Init, DIO_PortInit,Write, Read and toggle Channel API's
	*************************************************************************************/


		boolean readValue;

		assert(DIO_Init(&g_PIN_TEST)				 != OK_DOI);
		assert(DIO_PortInit(PORTA_ID, PORT_OUTPUT)	 == OK_DOI);
		assert(Dio_ReadPin(&g_Button_PD2, &readValue)!= OK_DOI);
		assert(Dio_WritePin(&g_LED_red, readValue)	 != OK_DOI);
		assert(Dio_TogglePin(&g_LED_red)	 		 != OK_DOI);

//	void TestCase1(void){
//		assert(APP_Init()	 						!= OK_APP);
//		assert(normalMode() 						!= OK_APP);
//		assert(YellowON()	 						!= OK_APP);
//		assert(RedON()		 						!= OK_APP);
//		assert(GreenON()	 						!= OK_APP);
//	}
}
