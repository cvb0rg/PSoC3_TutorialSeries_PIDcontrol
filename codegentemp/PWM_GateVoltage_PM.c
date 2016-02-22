/*******************************************************************************
* File Name: PWM_GateVoltage_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_GateVoltage.h"

static PWM_GateVoltage_backupStruct PWM_GateVoltage_backup;


/*******************************************************************************
* Function Name: PWM_GateVoltage_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GateVoltage_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_GateVoltage_SaveConfig(void) 
{

    #if(!PWM_GateVoltage_UsingFixedFunction)
        #if(!PWM_GateVoltage_PWMModeIsCenterAligned)
            PWM_GateVoltage_backup.PWMPeriod = PWM_GateVoltage_ReadPeriod();
        #endif /* (!PWM_GateVoltage_PWMModeIsCenterAligned) */
        PWM_GateVoltage_backup.PWMUdb = PWM_GateVoltage_ReadCounter();
        #if (PWM_GateVoltage_UseStatus)
            PWM_GateVoltage_backup.InterruptMaskValue = PWM_GateVoltage_STATUS_MASK;
        #endif /* (PWM_GateVoltage_UseStatus) */

        #if(PWM_GateVoltage_DeadBandMode == PWM_GateVoltage__B_PWM__DBM_256_CLOCKS || \
            PWM_GateVoltage_DeadBandMode == PWM_GateVoltage__B_PWM__DBM_2_4_CLOCKS)
            PWM_GateVoltage_backup.PWMdeadBandValue = PWM_GateVoltage_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_GateVoltage_KillModeMinTime)
             PWM_GateVoltage_backup.PWMKillCounterPeriod = PWM_GateVoltage_ReadKillTime();
        #endif /* (PWM_GateVoltage_KillModeMinTime) */

        #if(PWM_GateVoltage_UseControl)
            PWM_GateVoltage_backup.PWMControlRegister = PWM_GateVoltage_ReadControlRegister();
        #endif /* (PWM_GateVoltage_UseControl) */
    #endif  /* (!PWM_GateVoltage_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_GateVoltage_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GateVoltage_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GateVoltage_RestoreConfig(void) 
{
        #if(!PWM_GateVoltage_UsingFixedFunction)
            #if(!PWM_GateVoltage_PWMModeIsCenterAligned)
                PWM_GateVoltage_WritePeriod(PWM_GateVoltage_backup.PWMPeriod);
            #endif /* (!PWM_GateVoltage_PWMModeIsCenterAligned) */

            PWM_GateVoltage_WriteCounter(PWM_GateVoltage_backup.PWMUdb);

            #if (PWM_GateVoltage_UseStatus)
                PWM_GateVoltage_STATUS_MASK = PWM_GateVoltage_backup.InterruptMaskValue;
            #endif /* (PWM_GateVoltage_UseStatus) */

            #if(PWM_GateVoltage_DeadBandMode == PWM_GateVoltage__B_PWM__DBM_256_CLOCKS || \
                PWM_GateVoltage_DeadBandMode == PWM_GateVoltage__B_PWM__DBM_2_4_CLOCKS)
                PWM_GateVoltage_WriteDeadTime(PWM_GateVoltage_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_GateVoltage_KillModeMinTime)
                PWM_GateVoltage_WriteKillTime(PWM_GateVoltage_backup.PWMKillCounterPeriod);
            #endif /* (PWM_GateVoltage_KillModeMinTime) */

            #if(PWM_GateVoltage_UseControl)
                PWM_GateVoltage_WriteControlRegister(PWM_GateVoltage_backup.PWMControlRegister);
            #endif /* (PWM_GateVoltage_UseControl) */
        #endif  /* (!PWM_GateVoltage_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_GateVoltage_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GateVoltage_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_GateVoltage_Sleep(void) 
{
    #if(PWM_GateVoltage_UseControl)
        if(PWM_GateVoltage_CTRL_ENABLE == (PWM_GateVoltage_CONTROL & PWM_GateVoltage_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_GateVoltage_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_GateVoltage_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_GateVoltage_UseControl) */

    /* Stop component */
    PWM_GateVoltage_Stop();

    /* Save registers configuration */
    PWM_GateVoltage_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_GateVoltage_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GateVoltage_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GateVoltage_Wakeup(void) 
{
     /* Restore registers values */
    PWM_GateVoltage_RestoreConfig();

    if(PWM_GateVoltage_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_GateVoltage_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
