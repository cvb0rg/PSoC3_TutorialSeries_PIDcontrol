/*******************************************************************************
* File Name: hallEffect_ISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_hallEffect_ISR_H)
#define CY_ISR_hallEffect_ISR_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void hallEffect_ISR_Start(void) ;
void hallEffect_ISR_StartEx(cyisraddress address) ;
void hallEffect_ISR_Stop(void) ;

CY_ISR_PROTO(hallEffect_ISR_Interrupt);

void hallEffect_ISR_SetVector(cyisraddress address) ;
cyisraddress hallEffect_ISR_GetVector(void) ;

void hallEffect_ISR_SetPriority(uint8 priority) ;
uint8 hallEffect_ISR_GetPriority(void) ;

void hallEffect_ISR_Enable(void) ;
uint8 hallEffect_ISR_GetState(void) ;
void hallEffect_ISR_Disable(void) ;

void hallEffect_ISR_SetPending(void) ;
void hallEffect_ISR_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the hallEffect_ISR ISR. */
#define hallEffect_ISR_INTC_VECTOR            ((reg16 *) hallEffect_ISR__INTC_VECT)

/* Address of the hallEffect_ISR ISR priority. */
#define hallEffect_ISR_INTC_PRIOR             ((reg8 *) hallEffect_ISR__INTC_PRIOR_REG)

/* Priority of the hallEffect_ISR interrupt. */
#define hallEffect_ISR_INTC_PRIOR_NUMBER      hallEffect_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable hallEffect_ISR interrupt. */
#define hallEffect_ISR_INTC_SET_EN            ((reg8 *) hallEffect_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the hallEffect_ISR interrupt. */
#define hallEffect_ISR_INTC_CLR_EN            ((reg8 *) hallEffect_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the hallEffect_ISR interrupt state to pending. */
#define hallEffect_ISR_INTC_SET_PD            ((reg8 *) hallEffect_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the hallEffect_ISR interrupt. */
#define hallEffect_ISR_INTC_CLR_PD            ((reg8 *) hallEffect_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_hallEffect_ISR_H */


/* [] END OF FILE */
