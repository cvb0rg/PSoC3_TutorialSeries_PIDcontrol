/*******************************************************************************
* File Name: MOSFET_Gate.h  
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

#if !defined(CY_PINS_MOSFET_Gate_H) /* Pins MOSFET_Gate_H */
#define CY_PINS_MOSFET_Gate_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOSFET_Gate_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MOSFET_Gate_Write(uint8 value) ;
void    MOSFET_Gate_SetDriveMode(uint8 mode) ;
uint8   MOSFET_Gate_ReadDataReg(void) ;
uint8   MOSFET_Gate_Read(void) ;
void    MOSFET_Gate_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   MOSFET_Gate_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MOSFET_Gate_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define MOSFET_Gate_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define MOSFET_Gate_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define MOSFET_Gate_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define MOSFET_Gate_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define MOSFET_Gate_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define MOSFET_Gate_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define MOSFET_Gate_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define MOSFET_Gate_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MOSFET_Gate_MASK               MOSFET_Gate__MASK
#define MOSFET_Gate_SHIFT              MOSFET_Gate__SHIFT
#define MOSFET_Gate_WIDTH              1u

/* Interrupt constants */
#if defined(MOSFET_Gate__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOSFET_Gate_SetInterruptMode() function.
     *  @{
     */
        #define MOSFET_Gate_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define MOSFET_Gate_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define MOSFET_Gate_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define MOSFET_Gate_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define MOSFET_Gate_INTR_MASK      (0x01u)
#endif /* (MOSFET_Gate__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOSFET_Gate_PS                     (* (reg8 *) MOSFET_Gate__PS)
/* Data Register */
#define MOSFET_Gate_DR                     (* (reg8 *) MOSFET_Gate__DR)
/* Port Number */
#define MOSFET_Gate_PRT_NUM                (* (reg8 *) MOSFET_Gate__PRT) 
/* Connect to Analog Globals */                                                  
#define MOSFET_Gate_AG                     (* (reg8 *) MOSFET_Gate__AG)                       
/* Analog MUX bux enable */
#define MOSFET_Gate_AMUX                   (* (reg8 *) MOSFET_Gate__AMUX) 
/* Bidirectional Enable */                                                        
#define MOSFET_Gate_BIE                    (* (reg8 *) MOSFET_Gate__BIE)
/* Bit-mask for Aliased Register Access */
#define MOSFET_Gate_BIT_MASK               (* (reg8 *) MOSFET_Gate__BIT_MASK)
/* Bypass Enable */
#define MOSFET_Gate_BYP                    (* (reg8 *) MOSFET_Gate__BYP)
/* Port wide control signals */                                                   
#define MOSFET_Gate_CTL                    (* (reg8 *) MOSFET_Gate__CTL)
/* Drive Modes */
#define MOSFET_Gate_DM0                    (* (reg8 *) MOSFET_Gate__DM0) 
#define MOSFET_Gate_DM1                    (* (reg8 *) MOSFET_Gate__DM1)
#define MOSFET_Gate_DM2                    (* (reg8 *) MOSFET_Gate__DM2) 
/* Input Buffer Disable Override */
#define MOSFET_Gate_INP_DIS                (* (reg8 *) MOSFET_Gate__INP_DIS)
/* LCD Common or Segment Drive */
#define MOSFET_Gate_LCD_COM_SEG            (* (reg8 *) MOSFET_Gate__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOSFET_Gate_LCD_EN                 (* (reg8 *) MOSFET_Gate__LCD_EN)
/* Slew Rate Control */
#define MOSFET_Gate_SLW                    (* (reg8 *) MOSFET_Gate__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOSFET_Gate_PRTDSI__CAPS_SEL       (* (reg8 *) MOSFET_Gate__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOSFET_Gate_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOSFET_Gate__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOSFET_Gate_PRTDSI__OE_SEL0        (* (reg8 *) MOSFET_Gate__PRTDSI__OE_SEL0) 
#define MOSFET_Gate_PRTDSI__OE_SEL1        (* (reg8 *) MOSFET_Gate__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOSFET_Gate_PRTDSI__OUT_SEL0       (* (reg8 *) MOSFET_Gate__PRTDSI__OUT_SEL0) 
#define MOSFET_Gate_PRTDSI__OUT_SEL1       (* (reg8 *) MOSFET_Gate__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOSFET_Gate_PRTDSI__SYNC_OUT       (* (reg8 *) MOSFET_Gate__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MOSFET_Gate__SIO_CFG)
    #define MOSFET_Gate_SIO_HYST_EN        (* (reg8 *) MOSFET_Gate__SIO_HYST_EN)
    #define MOSFET_Gate_SIO_REG_HIFREQ     (* (reg8 *) MOSFET_Gate__SIO_REG_HIFREQ)
    #define MOSFET_Gate_SIO_CFG            (* (reg8 *) MOSFET_Gate__SIO_CFG)
    #define MOSFET_Gate_SIO_DIFF           (* (reg8 *) MOSFET_Gate__SIO_DIFF)
#endif /* (MOSFET_Gate__SIO_CFG) */

/* Interrupt Registers */
#if defined(MOSFET_Gate__INTSTAT)
    #define MOSFET_Gate_INTSTAT             (* (reg8 *) MOSFET_Gate__INTSTAT)
    #define MOSFET_Gate_SNAP                (* (reg8 *) MOSFET_Gate__SNAP)
    
	#define MOSFET_Gate_0_INTTYPE_REG 		(* (reg8 *) MOSFET_Gate__0__INTTYPE)
#endif /* (MOSFET_Gate__INTSTAT) */

#endif /* End Pins MOSFET_Gate_H */


/* [] END OF FILE */
