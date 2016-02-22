/*******************************************************************************
* File Name: pushButton.h  
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

#if !defined(CY_PINS_pushButton_H) /* Pins pushButton_H */
#define CY_PINS_pushButton_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pushButton_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pushButton_Write(uint8 value) ;
void    pushButton_SetDriveMode(uint8 mode) ;
uint8   pushButton_ReadDataReg(void) ;
uint8   pushButton_Read(void) ;
void    pushButton_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   pushButton_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pushButton_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define pushButton_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define pushButton_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define pushButton_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define pushButton_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define pushButton_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define pushButton_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define pushButton_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define pushButton_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pushButton_MASK               pushButton__MASK
#define pushButton_SHIFT              pushButton__SHIFT
#define pushButton_WIDTH              1u

/* Interrupt constants */
#if defined(pushButton__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pushButton_SetInterruptMode() function.
     *  @{
     */
        #define pushButton_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define pushButton_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define pushButton_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define pushButton_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define pushButton_INTR_MASK      (0x01u)
#endif /* (pushButton__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pushButton_PS                     (* (reg8 *) pushButton__PS)
/* Data Register */
#define pushButton_DR                     (* (reg8 *) pushButton__DR)
/* Port Number */
#define pushButton_PRT_NUM                (* (reg8 *) pushButton__PRT) 
/* Connect to Analog Globals */                                                  
#define pushButton_AG                     (* (reg8 *) pushButton__AG)                       
/* Analog MUX bux enable */
#define pushButton_AMUX                   (* (reg8 *) pushButton__AMUX) 
/* Bidirectional Enable */                                                        
#define pushButton_BIE                    (* (reg8 *) pushButton__BIE)
/* Bit-mask for Aliased Register Access */
#define pushButton_BIT_MASK               (* (reg8 *) pushButton__BIT_MASK)
/* Bypass Enable */
#define pushButton_BYP                    (* (reg8 *) pushButton__BYP)
/* Port wide control signals */                                                   
#define pushButton_CTL                    (* (reg8 *) pushButton__CTL)
/* Drive Modes */
#define pushButton_DM0                    (* (reg8 *) pushButton__DM0) 
#define pushButton_DM1                    (* (reg8 *) pushButton__DM1)
#define pushButton_DM2                    (* (reg8 *) pushButton__DM2) 
/* Input Buffer Disable Override */
#define pushButton_INP_DIS                (* (reg8 *) pushButton__INP_DIS)
/* LCD Common or Segment Drive */
#define pushButton_LCD_COM_SEG            (* (reg8 *) pushButton__LCD_COM_SEG)
/* Enable Segment LCD */
#define pushButton_LCD_EN                 (* (reg8 *) pushButton__LCD_EN)
/* Slew Rate Control */
#define pushButton_SLW                    (* (reg8 *) pushButton__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pushButton_PRTDSI__CAPS_SEL       (* (reg8 *) pushButton__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pushButton_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pushButton__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pushButton_PRTDSI__OE_SEL0        (* (reg8 *) pushButton__PRTDSI__OE_SEL0) 
#define pushButton_PRTDSI__OE_SEL1        (* (reg8 *) pushButton__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pushButton_PRTDSI__OUT_SEL0       (* (reg8 *) pushButton__PRTDSI__OUT_SEL0) 
#define pushButton_PRTDSI__OUT_SEL1       (* (reg8 *) pushButton__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pushButton_PRTDSI__SYNC_OUT       (* (reg8 *) pushButton__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pushButton__SIO_CFG)
    #define pushButton_SIO_HYST_EN        (* (reg8 *) pushButton__SIO_HYST_EN)
    #define pushButton_SIO_REG_HIFREQ     (* (reg8 *) pushButton__SIO_REG_HIFREQ)
    #define pushButton_SIO_CFG            (* (reg8 *) pushButton__SIO_CFG)
    #define pushButton_SIO_DIFF           (* (reg8 *) pushButton__SIO_DIFF)
#endif /* (pushButton__SIO_CFG) */

/* Interrupt Registers */
#if defined(pushButton__INTSTAT)
    #define pushButton_INTSTAT             (* (reg8 *) pushButton__INTSTAT)
    #define pushButton_SNAP                (* (reg8 *) pushButton__SNAP)
    
	#define pushButton_0_INTTYPE_REG 		(* (reg8 *) pushButton__0__INTTYPE)
#endif /* (pushButton__INTSTAT) */

#endif /* End Pins pushButton_H */


/* [] END OF FILE */
