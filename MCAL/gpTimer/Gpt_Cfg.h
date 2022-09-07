/*
 * Gpt_Cfg.h
 *
 *  Created on: Aug 19, 2022
 *      Author: msh20
 */

#ifndef MCAL_GPTIMER_GPT_CFG_H_
#define MCAL_GPTIMER_GPT_CFG_H_

#include "Gpt.h"

/* Global variable to hold the configuration For Timer 0*/
ST_Timer_Config_t g_Timer0_Config = {
		Timer0,			/* Timer_ID */
		Compare_Mode,	/* Timer_mode */
		F_CPU_1024,		/* Prescalar */
		no_clock,		/* timer2_prescalar */
		0, 				/* Timer_Initial_value */
		244				/* Timer_Compare_value */
};


/* Global variable to hold the configuration For Timer 2 */
ST_Timer_Config_t g_Timer2_Config = {
		Timer2,			/* Timer_ID */
		Compare_Mode,	/* Timer_mode */
		No_Clock,		/* Prescalar */
		f_Cpu_1024,		/* timer2_prescalar */
		0, 				/* Timer_Initial_value */
		240				/* Timer_Compare_value */
};

#endif /* MCAL_GPTIMER_GPT_CFG_H_ */
