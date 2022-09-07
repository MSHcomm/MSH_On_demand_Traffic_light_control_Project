 /******************************************************************************
 * Module: External_Interrupts
 * File Name: Ext_Interrupts.h
 * Description: Header file for the AVR External Interrupts driver
 * Author: Mohamed Sayed Hussein
 *******************************************************************************/

#ifndef MCAL_EXTERNAL_INTERRUPTS_EXT_INTERRUPTS_H_
#define MCAL_EXTERNAL_INTERRUPTS_EXT_INTERRUPTS_H_

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



/*******************************************************************************
 *                              Internal Module Data Types                     *
 *******************************************************************************/

/* Enum data type to choose one of the 3 AVR external interrupt */
typedef enum EN_Ext_Interrupt_Number_t{
	EXT_INT0, EXT_INT1, EXT_INT2
}EN_Ext_Interrupt_Number_t;


/* enum data type to choose AVR Timer Mode */
typedef enum EN_Ext_Int_Modes{
	LowLevel, HighLevel, ChangeLevel, FailingEdge, RisingEdge
}EN_Ext_Int_Modes;


/* Configuration Structure for AVR external interrupt Driver Which configure:
 1- The Ext_Int_ID we want to use (0,1,2)
 2- The Ext_Int_Mode driver modes (Low Level, High Level, any Level Change, Failing Edge, or Rising Edge)
 3- The Ext_Int_Enable want to Enable or Disable (TRUE or FALSE)
*/
typedef struct ST_Ext_Int_Config_t{
	EN_Ext_Interrupt_Number_t	Ext_Int_ID;
	EN_Ext_Int_Modes			Ext_Int_Mode;
	boolean						Ext_Int_Enable;
}ST_Ext_Int_Config_t;


/* Enum type for return type, to handle APIs error */
typedef enum EN_ExtIntError_t{
	 ERROR_EXT_INT0 ,ERROR_EXT_INT1, ERROR_EXT_INT2,
	 ERROR_EXT_INT_ID, ERROR_EXT_INT_MODE, OK_EXT_INT
}EN_ExtIntError_t;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

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
EN_ExtIntError_t Ext_Interrupts_Init(ST_Ext_Int_Config_t *Ext_Int_ConfigPTR);


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
EN_ExtIntError_t Ext_Interrupts_deinit(ST_Ext_Int_Config_t *Ext_Int_ConfigPTR);


/*
 * Description: Function to set the Call Back function address of External interrupt 0.
 */
void Ext_Interrupt0_setCallBack(void(*T0_ptr)(void));


/*
 * Description: Function to set the Call Back function address of External interrupt 1.
 */
void Ext_Interrupt1_setCallBack(void(*T1_ptr)(void));


/*
 * Description: Function to set the Call Back function address of External interrupt 2.
 */
void Ext_Interrupt2_setCallBack(void(*T2_ptr)(void));


#endif /* MCAL_EXTERNAL_INTERRUPTS_EXT_INTERRUPTS_H_ */
