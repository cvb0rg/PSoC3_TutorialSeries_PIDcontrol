/*******************************************************************************
* File Name: hallTickTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "hallTickTimer.h"

static hallTickTimer_backupStruct hallTickTimer_backup;


/*******************************************************************************
* Function Name: hallTickTimer_SaveConfig
********************************************************************************
*
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
*  hallTickTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void hallTickTimer_SaveConfig(void) 
{
    #if (!hallTickTimer_UsingFixedFunction)
        hallTickTimer_backup.TimerUdb = hallTickTimer_ReadCounter();
        hallTickTimer_backup.InterruptMaskValue = hallTickTimer_STATUS_MASK;
        #if (hallTickTimer_UsingHWCaptureCounter)
            hallTickTimer_backup.TimerCaptureCounter = hallTickTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!hallTickTimer_UDB_CONTROL_REG_REMOVED)
            hallTickTimer_backup.TimerControlRegister = hallTickTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: hallTickTimer_RestoreConfig
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
*  hallTickTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void hallTickTimer_RestoreConfig(void) 
{   
    #if (!hallTickTimer_UsingFixedFunction)

        hallTickTimer_WriteCounter(hallTickTimer_backup.TimerUdb);
        hallTickTimer_STATUS_MASK =hallTickTimer_backup.InterruptMaskValue;
        #if (hallTickTimer_UsingHWCaptureCounter)
            hallTickTimer_SetCaptureCount(hallTickTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!hallTickTimer_UDB_CONTROL_REG_REMOVED)
            hallTickTimer_WriteControlRegister(hallTickTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: hallTickTimer_Sleep
********************************************************************************
*
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
*  hallTickTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void hallTickTimer_Sleep(void) 
{
    #if(!hallTickTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(hallTickTimer_CTRL_ENABLE == (hallTickTimer_CONTROL & hallTickTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            hallTickTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            hallTickTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    hallTickTimer_Stop();
    hallTickTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: hallTickTimer_Wakeup
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
*  hallTickTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void hallTickTimer_Wakeup(void) 
{
    hallTickTimer_RestoreConfig();
    #if(!hallTickTimer_UDB_CONTROL_REG_REMOVED)
        if(hallTickTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                hallTickTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
