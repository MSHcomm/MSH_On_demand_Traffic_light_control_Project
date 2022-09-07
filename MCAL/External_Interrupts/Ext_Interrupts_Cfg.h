/*
 * Ext_Interrupts_Cfg.h
 *
 *  Created on: Aug 21, 2022
 *      Author: msh20
 */

#ifndef MCAL_EXTERNAL_INTERRUPTS_EXT_INTERRUPTS_CFG_H_
#define MCAL_EXTERNAL_INTERRUPTS_EXT_INTERRUPTS_CFG_H_

#include "Ext_Interrupts.h"

ST_Ext_Int_Config_t g_Ext_Int0_Config ={
		EXT_INT0,		/* Ext_Int_ID */
		FailingEdge,	/* Ext_Int_Mode */
		TRUE			/* Ext_Int_Enable (TRUE or FALSE)*/
};

#endif /* MCAL_EXTERNAL_INTERRUPTS_EXT_INTERRUPTS_CFG_H_ */
