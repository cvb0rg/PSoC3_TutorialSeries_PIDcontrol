/*******************************************************************************
* File Name: deBounce.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_deBounce_H)
#define CY_CLOCK_deBounce_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void deBounce_Start(void) ;
void deBounce_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void deBounce_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void deBounce_StandbyPower(uint8 state) ;
void deBounce_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 deBounce_GetDividerRegister(void) ;
void deBounce_SetModeRegister(uint8 modeBitMask) ;
void deBounce_ClearModeRegister(uint8 modeBitMask) ;
uint8 deBounce_GetModeRegister(void) ;
void deBounce_SetSourceRegister(uint8 clkSource) ;
uint8 deBounce_GetSourceRegister(void) ;
#if defined(deBounce__CFG3)
void deBounce_SetPhaseRegister(uint8 clkPhase) ;
uint8 deBounce_GetPhaseRegister(void) ;
#endif /* defined(deBounce__CFG3) */

#define deBounce_Enable()                       deBounce_Start()
#define deBounce_Disable()                      deBounce_Stop()
#define deBounce_SetDivider(clkDivider)         deBounce_SetDividerRegister(clkDivider, 1u)
#define deBounce_SetDividerValue(clkDivider)    deBounce_SetDividerRegister((clkDivider) - 1u, 1u)
#define deBounce_SetMode(clkMode)               deBounce_SetModeRegister(clkMode)
#define deBounce_SetSource(clkSource)           deBounce_SetSourceRegister(clkSource)
#if defined(deBounce__CFG3)
#define deBounce_SetPhase(clkPhase)             deBounce_SetPhaseRegister(clkPhase)
#define deBounce_SetPhaseValue(clkPhase)        deBounce_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(deBounce__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define deBounce_CLKEN              (* (reg8 *) deBounce__PM_ACT_CFG)
#define deBounce_CLKEN_PTR          ((reg8 *) deBounce__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define deBounce_CLKSTBY            (* (reg8 *) deBounce__PM_STBY_CFG)
#define deBounce_CLKSTBY_PTR        ((reg8 *) deBounce__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define deBounce_DIV_LSB            (* (reg8 *) deBounce__CFG0)
#define deBounce_DIV_LSB_PTR        ((reg8 *) deBounce__CFG0)
#define deBounce_DIV_PTR            ((reg16 *) deBounce__CFG0)

/* Clock MSB divider configuration register. */
#define deBounce_DIV_MSB            (* (reg8 *) deBounce__CFG1)
#define deBounce_DIV_MSB_PTR        ((reg8 *) deBounce__CFG1)

/* Mode and source configuration register */
#define deBounce_MOD_SRC            (* (reg8 *) deBounce__CFG2)
#define deBounce_MOD_SRC_PTR        ((reg8 *) deBounce__CFG2)

#if defined(deBounce__CFG3)
/* Analog clock phase configuration register */
#define deBounce_PHASE              (* (reg8 *) deBounce__CFG3)
#define deBounce_PHASE_PTR          ((reg8 *) deBounce__CFG3)
#endif /* defined(deBounce__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define deBounce_CLKEN_MASK         deBounce__PM_ACT_MSK
#define deBounce_CLKSTBY_MASK       deBounce__PM_STBY_MSK

/* CFG2 field masks */
#define deBounce_SRC_SEL_MSK        deBounce__CFG2_SRC_SEL_MASK
#define deBounce_MODE_MASK          (~(deBounce_SRC_SEL_MSK))

#if defined(deBounce__CFG3)
/* CFG3 phase mask */
#define deBounce_PHASE_MASK         deBounce__CFG3_PHASE_DLY_MASK
#endif /* defined(deBounce__CFG3) */

#endif /* CY_CLOCK_deBounce_H */


/* [] END OF FILE */
