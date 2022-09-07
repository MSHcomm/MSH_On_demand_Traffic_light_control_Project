 /******************************************************************************
 * Module: Application
 * File Name: app.h
 * Description: Header file for application
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_

/*******************************************************************************
 *                       Header Files & Libraries Includes                     *
 *******************************************************************************/


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                              Internal Module Data Types                     *
 *******************************************************************************/
/* Enum type for return type, to handle APIs error */
typedef enum EN_appError_t{
	OK_APP, ERROR_APP_LED_INIT, ERROR_APP_BUTTON_INIT, ERROR_APP_TIMER_INIT,
	ERROR_APP_RED_ON, ERROR_APP_YELLOW_ON, ERROR_APP_GREEN_ON,
	ERROR_NORMAL_MODE, ERROR_PEDESTRIAN_MODE
}EN_appError_t;


/*******************************************************************************
 *                      Function Definitions                                    *
 *******************************************************************************/


/*
 * Service Name		: normalMode
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_appError_t
 * Description		: Function to call the yellow, red, and green tasks in the normal sequence required
 *					If all tasks processed correctly, The function will return OK_APP
 *					else return as EN_appError_t type for error handling according to task fail
 */
EN_appError_t normalMode(void);



/*
 * Service Name		: pedestrianMode
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_appError_t
 * Description		: Function to be called if the Button pressed
 *					If all tasks checking the cases of pressing Button correctly, The function will return OK_APP
 *					else return as EN_appError_t type for error handling according to task fail
 */
EN_appError_t pedestrianMode(void);



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
EN_appError_t APP_Init(void);



/*
 * Service Name		: APP_start
 * Parameters (in)	: None
 * Parameters (out)	: None
 * Return value		: EN_appError_t
 * Description		: Function to start the application by calling modes
 *					If mode called correctly, The function will return OK_APP
 *					else return as EN_appError_t type for error handling according to mode fail
 */
EN_appError_t APP_start(void);


void APP_Test(void);

#endif /* APPLICATION_APP_H_ */
