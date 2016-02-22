/*******************************************************************************
* File Name: hallEffectSensor.h  
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

#if !defined(CY_PINS_hallEffectSensor_H) /* Pins hallEffectSensor_H */
#define CY_PINS_hallEffectSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "hallEffectSensor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    hallEffectSensor_Write(uint8 value) ;
void    hallEffectSensor_SetDriveMode(uint8 mode) ;
uint8   hallEffectSensor_ReadDataReg(void) ;
uint8   hallEffectSensor_Read(void) ;
void    hallEffectSensor_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   hallEffectSensor_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the hallEffectSensor_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define hallEffectSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define hallEffectSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define hallEffectSensor_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define hallEffectSensor_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define hallEffectSensor_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define hallEffectSensor_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define hallEffectSensor_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define hallEffectSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define hallEffectSensor_MASK               hallEffectSensor__MASK
#define hallEffectSensor_SHIFT              hallEffectSensor__SHIFT
#define hallEffectSensor_WIDTH              1u

/* Interrupt constants */
#if defined(hallEffectSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in hallEffectSensor_SetInterruptMode() function.
     *  @{
     */
        #define hallEffectSensor_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define hallEffectSensor_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define hallEffectSensor_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define hallEffectSensor_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define hallEffectSensor_INTR_MASK      (0x01u)
#endif /* (hallEffectSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define hallEffectSensor_PS                     (* (reg8 *) hallEffectSensor__PS)
/* Data Register */
#define hallEffectSensor_DR                     (* (reg8 *) hallEffectSensor__DR)
/* Port Number */
#define hallEffectSensor_PRT_NUM                (* (reg8 *) hallEffectSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define hallEffectSensor_AG                     (* (reg8 *) hallEffectSensor__AG)                       
/* Analog MUX bux enable */
#define hallEffectSensor_AMUX                   (* (reg8 *) hallEffectSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define hallEffectSensor_BIE                    (* (reg8 *) hallEffectSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define hallEffectSensor_BIT_MASK               (* (reg8 *) hallEffectSensor__BIT_MASK)
/* Bypass Enable */
#define hallEffectSensor_BYP                    (* (reg8 *) hallEffectSensor__BYP)
/* Port wide control signals */                                                   
#define hallEffectSensor_CTL                    (* (reg8 *) hallEffectSensor__CTL)
/* Drive Modes */
#define hallEffectSensor_DM0                    (* (reg8 *) hallEffectSensor__DM0) 
#define hallEffectSensor_DM1                    (* (reg8 *) hallEffectSensor__DM1)
#define hallEffectSensor_DM2                    (* (reg8 *) hallEffectSensor__DM2) 
/* Input Buffer Disable Override */
#define hallEffectSensor_INP_DIS                (* (reg8 *) hallEffectSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define hallEffectSensor_LCD_COM_SEG            (* (reg8 *) hallEffectSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define hallEffectSensor_LCD_EN                 (* (reg8 *) hallEffectSensor__LCD_EN)
/* Slew Rate Control */
#define hallEffectSensor_SLW                    (* (reg8 *) hallEffectSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define hallEffectSensor_PRTDSI__CAPS_SEL       (* (reg8 *) hallEffectSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define hallEffectSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) hallEffectSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define hallEffectSensor_PRTDSI__OE_SEL0        (* (reg8 *) hallEffectSensor__PRTDSI__OE_SEL0) 
#define hallEffectSensor_PRTDSI__OE_SEL1        (* (reg8 *) hallEffectSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define hallEffectSensor_PRTDSI__OUT_SEL0       (* (reg8 *) hallEffectSensor__PRTDSI__OUT_SEL0) 
#define hallEffectSensor_PRTDSI__OUT_SEL1       (* (reg8 *) hallEffectSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define hallEffectSensor_PRTDSI__SYNC_OUT       (* (reg8 *) hallEffectSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(hallEffectSensor__SIO_CFG)
    #define hallEffectSensor_SIO_HYST_EN        (* (reg8 *) hallEffectSensor__SIO_HYST_EN)
    #define hallEffectSensor_SIO_REG_HIFREQ     (* (reg8 *) hallEffectSensor__SIO_REG_HIFREQ)
    #define hallEffectSensor_SIO_CFG            (* (reg8 *) hallEffectSensor__SIO_CFG)
    #define hallEffectSensor_SIO_DIFF           (* (reg8 *) hallEffectSensor__SIO_DIFF)
#endif /* (hallEffectSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(hallEffectSensor__INTSTAT)
    #define hallEffectSensor_INTSTAT             (* (reg8 *) hallEffectSensor__INTSTAT)
    #define hallEffectSensor_SNAP                (* (reg8 *) hallEffectSensor__SNAP)
    
	#define hallEffectSensor_0_INTTYPE_REG 		(* (reg8 *) hallEffectSensor__0__INTTYPE)
#endif /* (hallEffectSensor__INTSTAT) */

#endif /* End Pins hallEffectSensor_H */


/* [] END OF FILE */
