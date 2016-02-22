/*******************************************************************************
* File Name: SyncOut.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SyncOut_H) /* Pins SyncOut_H */
#define CY_PINS_SyncOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SyncOut_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SyncOut_Write(uint8 value) ;
void    SyncOut_SetDriveMode(uint8 mode) ;
uint8   SyncOut_ReadDataReg(void) ;
uint8   SyncOut_Read(void) ;
void    SyncOut_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   SyncOut_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SyncOut_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define SyncOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define SyncOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define SyncOut_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define SyncOut_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define SyncOut_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define SyncOut_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define SyncOut_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define SyncOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SyncOut_MASK               SyncOut__MASK
#define SyncOut_SHIFT              SyncOut__SHIFT
#define SyncOut_WIDTH              1u

/* Interrupt constants */
#if defined(SyncOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SyncOut_SetInterruptMode() function.
     *  @{
     */
        #define SyncOut_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define SyncOut_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define SyncOut_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define SyncOut_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define SyncOut_INTR_MASK      (0x01u)
#endif /* (SyncOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SyncOut_PS                     (* (reg8 *) SyncOut__PS)
/* Data Register */
#define SyncOut_DR                     (* (reg8 *) SyncOut__DR)
/* Port Number */
#define SyncOut_PRT_NUM                (* (reg8 *) SyncOut__PRT) 
/* Connect to Analog Globals */                                                  
#define SyncOut_AG                     (* (reg8 *) SyncOut__AG)                       
/* Analog MUX bux enable */
#define SyncOut_AMUX                   (* (reg8 *) SyncOut__AMUX) 
/* Bidirectional Enable */                                                        
#define SyncOut_BIE                    (* (reg8 *) SyncOut__BIE)
/* Bit-mask for Aliased Register Access */
#define SyncOut_BIT_MASK               (* (reg8 *) SyncOut__BIT_MASK)
/* Bypass Enable */
#define SyncOut_BYP                    (* (reg8 *) SyncOut__BYP)
/* Port wide control signals */                                                   
#define SyncOut_CTL                    (* (reg8 *) SyncOut__CTL)
/* Drive Modes */
#define SyncOut_DM0                    (* (reg8 *) SyncOut__DM0) 
#define SyncOut_DM1                    (* (reg8 *) SyncOut__DM1)
#define SyncOut_DM2                    (* (reg8 *) SyncOut__DM2) 
/* Input Buffer Disable Override */
#define SyncOut_INP_DIS                (* (reg8 *) SyncOut__INP_DIS)
/* LCD Common or Segment Drive */
#define SyncOut_LCD_COM_SEG            (* (reg8 *) SyncOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define SyncOut_LCD_EN                 (* (reg8 *) SyncOut__LCD_EN)
/* Slew Rate Control */
#define SyncOut_SLW                    (* (reg8 *) SyncOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SyncOut_PRTDSI__CAPS_SEL       (* (reg8 *) SyncOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SyncOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SyncOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SyncOut_PRTDSI__OE_SEL0        (* (reg8 *) SyncOut__PRTDSI__OE_SEL0) 
#define SyncOut_PRTDSI__OE_SEL1        (* (reg8 *) SyncOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SyncOut_PRTDSI__OUT_SEL0       (* (reg8 *) SyncOut__PRTDSI__OUT_SEL0) 
#define SyncOut_PRTDSI__OUT_SEL1       (* (reg8 *) SyncOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SyncOut_PRTDSI__SYNC_OUT       (* (reg8 *) SyncOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SyncOut__SIO_CFG)
    #define SyncOut_SIO_HYST_EN        (* (reg8 *) SyncOut__SIO_HYST_EN)
    #define SyncOut_SIO_REG_HIFREQ     (* (reg8 *) SyncOut__SIO_REG_HIFREQ)
    #define SyncOut_SIO_CFG            (* (reg8 *) SyncOut__SIO_CFG)
    #define SyncOut_SIO_DIFF           (* (reg8 *) SyncOut__SIO_DIFF)
#endif /* (SyncOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(SyncOut__INTSTAT)
    #define SyncOut_INTSTAT             (* (reg8 *) SyncOut__INTSTAT)
    #define SyncOut_SNAP                (* (reg8 *) SyncOut__SNAP)
    
	#define SyncOut_0_INTTYPE_REG 		(* (reg8 *) SyncOut__0__INTTYPE)
#endif /* (SyncOut__INTSTAT) */

#endif /* End Pins SyncOut_H */


/* [] END OF FILE */
