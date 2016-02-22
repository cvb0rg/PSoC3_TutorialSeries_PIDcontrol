/*******************************************************************************
* File Name: hallTickCounter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "hallTickCounter.h"

static hallTickCounter_backupStruct hallTickCounter_backup;


/*******************************************************************************
* Function Name: hallTickCounter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  hallTickCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void hallTickCounter_SaveConfig(void) 
{
    #if (!hallTickCounter_UsingFixedFunction)

        hallTickCounter_backup.CounterUdb = hallTickCounter_ReadCounter();

        #if(!hallTickCounter_ControlRegRemoved)
            hallTickCounter_backup.CounterControlRegister = hallTickCounter_ReadControlRegister();
        #endif /* (!hallTickCounter_ControlRegRemoved) */

    #endif /* (!hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  hallTickCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void hallTickCounter_RestoreConfig(void) 
{      
    #if (!hallTickCounter_UsingFixedFunction)

       hallTickCounter_WriteCounter(hallTickCounter_backup.CounterUdb);

        #if(!hallTickCounter_ControlRegRemoved)
            hallTickCounter_WriteControlRegister(hallTickCounter_backup.CounterControlRegister);
        #endif /* (!hallTickCounter_ControlRegRemoved) */

    #endif /* (!hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  hallTickCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void hallTickCounter_Sleep(void) 
{
    #if(!hallTickCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(hallTickCounter_CTRL_ENABLE == (hallTickCounter_CONTROL & hallTickCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            hallTickCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            hallTickCounter_backup.CounterEnableState = 0u;
        }
    #else
        hallTickCounter_backup.CounterEnableState = 1u;
        if(hallTickCounter_backup.CounterEnableState != 0u)
        {
            hallTickCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!hallTickCounter_ControlRegRemoved) */
    
    hallTickCounter_Stop();
    hallTickCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: hallTickCounter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  hallTickCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void hallTickCounter_Wakeup(void) 
{
    hallTickCounter_RestoreConfig();
    #if(!hallTickCounter_ControlRegRemoved)
        if(hallTickCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            hallTickCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!hallTickCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
