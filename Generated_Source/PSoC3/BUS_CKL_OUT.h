/*******************************************************************************
* File Name: BUS_CKL_OUT.h  
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

#if !defined(CY_PINS_BUS_CKL_OUT_H) /* Pins BUS_CKL_OUT_H */
#define CY_PINS_BUS_CKL_OUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BUS_CKL_OUT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BUS_CKL_OUT_Write(uint8 value) ;
void    BUS_CKL_OUT_SetDriveMode(uint8 mode) ;
uint8   BUS_CKL_OUT_ReadDataReg(void) ;
uint8   BUS_CKL_OUT_Read(void) ;
void    BUS_CKL_OUT_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   BUS_CKL_OUT_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BUS_CKL_OUT_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define BUS_CKL_OUT_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define BUS_CKL_OUT_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define BUS_CKL_OUT_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define BUS_CKL_OUT_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define BUS_CKL_OUT_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define BUS_CKL_OUT_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define BUS_CKL_OUT_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define BUS_CKL_OUT_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BUS_CKL_OUT_MASK               BUS_CKL_OUT__MASK
#define BUS_CKL_OUT_SHIFT              BUS_CKL_OUT__SHIFT
#define BUS_CKL_OUT_WIDTH              1u

/* Interrupt constants */
#if defined(BUS_CKL_OUT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BUS_CKL_OUT_SetInterruptMode() function.
     *  @{
     */
        #define BUS_CKL_OUT_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define BUS_CKL_OUT_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define BUS_CKL_OUT_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define BUS_CKL_OUT_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define BUS_CKL_OUT_INTR_MASK      (0x01u)
#endif /* (BUS_CKL_OUT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BUS_CKL_OUT_PS                     (* (reg8 *) BUS_CKL_OUT__PS)
/* Data Register */
#define BUS_CKL_OUT_DR                     (* (reg8 *) BUS_CKL_OUT__DR)
/* Port Number */
#define BUS_CKL_OUT_PRT_NUM                (* (reg8 *) BUS_CKL_OUT__PRT) 
/* Connect to Analog Globals */                                                  
#define BUS_CKL_OUT_AG                     (* (reg8 *) BUS_CKL_OUT__AG)                       
/* Analog MUX bux enable */
#define BUS_CKL_OUT_AMUX                   (* (reg8 *) BUS_CKL_OUT__AMUX) 
/* Bidirectional Enable */                                                        
#define BUS_CKL_OUT_BIE                    (* (reg8 *) BUS_CKL_OUT__BIE)
/* Bit-mask for Aliased Register Access */
#define BUS_CKL_OUT_BIT_MASK               (* (reg8 *) BUS_CKL_OUT__BIT_MASK)
/* Bypass Enable */
#define BUS_CKL_OUT_BYP                    (* (reg8 *) BUS_CKL_OUT__BYP)
/* Port wide control signals */                                                   
#define BUS_CKL_OUT_CTL                    (* (reg8 *) BUS_CKL_OUT__CTL)
/* Drive Modes */
#define BUS_CKL_OUT_DM0                    (* (reg8 *) BUS_CKL_OUT__DM0) 
#define BUS_CKL_OUT_DM1                    (* (reg8 *) BUS_CKL_OUT__DM1)
#define BUS_CKL_OUT_DM2                    (* (reg8 *) BUS_CKL_OUT__DM2) 
/* Input Buffer Disable Override */
#define BUS_CKL_OUT_INP_DIS                (* (reg8 *) BUS_CKL_OUT__INP_DIS)
/* LCD Common or Segment Drive */
#define BUS_CKL_OUT_LCD_COM_SEG            (* (reg8 *) BUS_CKL_OUT__LCD_COM_SEG)
/* Enable Segment LCD */
#define BUS_CKL_OUT_LCD_EN                 (* (reg8 *) BUS_CKL_OUT__LCD_EN)
/* Slew Rate Control */
#define BUS_CKL_OUT_SLW                    (* (reg8 *) BUS_CKL_OUT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BUS_CKL_OUT_PRTDSI__CAPS_SEL       (* (reg8 *) BUS_CKL_OUT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BUS_CKL_OUT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BUS_CKL_OUT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BUS_CKL_OUT_PRTDSI__OE_SEL0        (* (reg8 *) BUS_CKL_OUT__PRTDSI__OE_SEL0) 
#define BUS_CKL_OUT_PRTDSI__OE_SEL1        (* (reg8 *) BUS_CKL_OUT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BUS_CKL_OUT_PRTDSI__OUT_SEL0       (* (reg8 *) BUS_CKL_OUT__PRTDSI__OUT_SEL0) 
#define BUS_CKL_OUT_PRTDSI__OUT_SEL1       (* (reg8 *) BUS_CKL_OUT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BUS_CKL_OUT_PRTDSI__SYNC_OUT       (* (reg8 *) BUS_CKL_OUT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BUS_CKL_OUT__SIO_CFG)
    #define BUS_CKL_OUT_SIO_HYST_EN        (* (reg8 *) BUS_CKL_OUT__SIO_HYST_EN)
    #define BUS_CKL_OUT_SIO_REG_HIFREQ     (* (reg8 *) BUS_CKL_OUT__SIO_REG_HIFREQ)
    #define BUS_CKL_OUT_SIO_CFG            (* (reg8 *) BUS_CKL_OUT__SIO_CFG)
    #define BUS_CKL_OUT_SIO_DIFF           (* (reg8 *) BUS_CKL_OUT__SIO_DIFF)
#endif /* (BUS_CKL_OUT__SIO_CFG) */

/* Interrupt Registers */
#if defined(BUS_CKL_OUT__INTSTAT)
    #define BUS_CKL_OUT_INTSTAT             (* (reg8 *) BUS_CKL_OUT__INTSTAT)
    #define BUS_CKL_OUT_SNAP                (* (reg8 *) BUS_CKL_OUT__SNAP)
    
	#define BUS_CKL_OUT_0_INTTYPE_REG 		(* (reg8 *) BUS_CKL_OUT__0__INTTYPE)
#endif /* (BUS_CKL_OUT__INTSTAT) */

#endif /* End Pins BUS_CKL_OUT_H */


/* [] END OF FILE */
