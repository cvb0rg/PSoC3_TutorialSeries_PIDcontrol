/*******************************************************************************
* File Name: PWM_GateVoltage.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "PWM_GateVoltage.h"

/* Error message for removed <resource> through optimization */
#ifdef PWM_GateVoltage_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* PWM_GateVoltage_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 PWM_GateVoltage_initVar = 0u;


/*******************************************************************************
* Function Name: PWM_GateVoltage_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GateVoltage_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PWM_GateVoltage_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PWM_GateVoltage_initVar == 0u)
    {
        PWM_GateVoltage_Init();
        PWM_GateVoltage_initVar = 1u;
    }
    PWM_GateVoltage_Enable();

}


/*******************************************************************************
* Function Name: PWM_GateVoltage_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  PWM_GateVoltage_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_GateVoltage_Init(void) 
{
    #if (PWM_GateVoltage_UsingFixedFunction || PWM_GateVoltage_UseControl)
        uint8 ctrl;
    #endif /* (PWM_GateVoltage_UsingFixedFunction || PWM_GateVoltage_UseControl) */

    #if(!PWM_GateVoltage_UsingFixedFunction)
        #if(PWM_GateVoltage_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PWM_GateVoltage_interruptState;
        #endif /* (PWM_GateVoltage_UseStatus) */
    #endif /* (!PWM_GateVoltage_UsingFixedFunction) */

    #if (PWM_GateVoltage_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PWM_GateVoltage_CONTROL |= PWM_GateVoltage_CFG0_MODE;
        #if (PWM_GateVoltage_DeadBand2_4)
            PWM_GateVoltage_CONTROL |= PWM_GateVoltage_CFG0_DB;
        #endif /* (PWM_GateVoltage_DeadBand2_4) */

        ctrl = PWM_GateVoltage_CONTROL3 & ((uint8 )(~PWM_GateVoltage_CTRL_CMPMODE1_MASK));
        PWM_GateVoltage_CONTROL3 = ctrl | PWM_GateVoltage_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PWM_GateVoltage_RT1 &= ((uint8)(~PWM_GateVoltage_RT1_MASK));
        PWM_GateVoltage_RT1 |= PWM_GateVoltage_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        PWM_GateVoltage_RT1 &= ((uint8)(~PWM_GateVoltage_SYNCDSI_MASK));
        PWM_GateVoltage_RT1 |= PWM_GateVoltage_SYNCDSI_EN;

    #elif (PWM_GateVoltage_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PWM_GateVoltage_CONTROL & ((uint8)(~PWM_GateVoltage_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~PWM_GateVoltage_CTRL_CMPMODE1_MASK));
        PWM_GateVoltage_CONTROL = ctrl | PWM_GateVoltage_DEFAULT_COMPARE2_MODE |
                                   PWM_GateVoltage_DEFAULT_COMPARE1_MODE;
    #endif /* (PWM_GateVoltage_UsingFixedFunction) */

    #if (!PWM_GateVoltage_UsingFixedFunction)
        #if (PWM_GateVoltage_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PWM_GateVoltage_AUX_CONTROLDP0 |= (PWM_GateVoltage_AUX_CTRL_FIFO0_CLR);
        #else /* (PWM_GateVoltage_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PWM_GateVoltage_AUX_CONTROLDP0 |= (PWM_GateVoltage_AUX_CTRL_FIFO0_CLR);
            PWM_GateVoltage_AUX_CONTROLDP1 |= (PWM_GateVoltage_AUX_CTRL_FIFO0_CLR);
        #endif /* (PWM_GateVoltage_Resolution == 8) */

        PWM_GateVoltage_WriteCounter(PWM_GateVoltage_INIT_PERIOD_VALUE);
    #endif /* (!PWM_GateVoltage_UsingFixedFunction) */

    PWM_GateVoltage_WritePeriod(PWM_GateVoltage_INIT_PERIOD_VALUE);

        #if (PWM_GateVoltage_UseOneCompareMode)
            PWM_GateVoltage_WriteCompare(PWM_GateVoltage_INIT_COMPARE_VALUE1);
        #else
            PWM_GateVoltage_WriteCompare1(PWM_GateVoltage_INIT_COMPARE_VALUE1);
            PWM_GateVoltage_WriteCompare2(PWM_GateVoltage_INIT_COMPARE_VALUE2);
        #endif /* (PWM_GateVoltage_UseOneCompareMode) */

        #if (PWM_GateVoltage_KillModeMinTime)
            PWM_GateVoltage_WriteKillTime(PWM_GateVoltage_MinimumKillTime);
        #endif /* (PWM_GateVoltage_KillModeMinTime) */

        #if (PWM_GateVoltage_DeadBandUsed)
            PWM_GateVoltage_WriteDeadTime(PWM_GateVoltage_INIT_DEAD_TIME);
        #endif /* (PWM_GateVoltage_DeadBandUsed) */

    #if (PWM_GateVoltage_UseStatus || PWM_GateVoltage_UsingFixedFunction)
        PWM_GateVoltage_SetInterruptMode(PWM_GateVoltage_INIT_INTERRUPTS_MODE);
    #endif /* (PWM_GateVoltage_UseStatus || PWM_GateVoltage_UsingFixedFunction) */

    #if (PWM_GateVoltage_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PWM_GateVoltage_GLOBAL_ENABLE |= PWM_GateVoltage_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PWM_GateVoltage_CONTROL2 |= PWM_GateVoltage_CTRL2_IRQ_SEL;
    #else
        #if(PWM_GateVoltage_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PWM_GateVoltage_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PWM_GateVoltage_STATUS_AUX_CTRL |= PWM_GateVoltage_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(PWM_GateVoltage_interruptState);

            /* Clear the FIFO to enable the PWM_GateVoltage_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PWM_GateVoltage_ClearFIFO();
        #endif /* (PWM_GateVoltage_UseStatus) */
    #endif /* (PWM_GateVoltage_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_GateVoltage_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void PWM_GateVoltage_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PWM_GateVoltage_UsingFixedFunction)
        PWM_GateVoltage_GLOBAL_ENABLE |= PWM_GateVoltage_BLOCK_EN_MASK;
        PWM_GateVoltage_GLOBAL_STBY_ENABLE |= PWM_GateVoltage_BLOCK_STBY_EN_MASK;
    #endif /* (PWM_GateVoltage_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (PWM_GateVoltage_UseControl || PWM_GateVoltage_UsingFixedFunction)
        PWM_GateVoltage_CONTROL |= PWM_GateVoltage_CTRL_ENABLE;
    #endif /* (PWM_GateVoltage_UseControl || PWM_GateVoltage_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_GateVoltage_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void PWM_GateVoltage_Stop(void) 
{
    #if (PWM_GateVoltage_UseControl || PWM_GateVoltage_UsingFixedFunction)
        PWM_GateVoltage_CONTROL &= ((uint8)(~PWM_GateVoltage_CTRL_ENABLE));
    #endif /* (PWM_GateVoltage_UseControl || PWM_GateVoltage_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (PWM_GateVoltage_UsingFixedFunction)
        PWM_GateVoltage_GLOBAL_ENABLE &= ((uint8)(~PWM_GateVoltage_BLOCK_EN_MASK));
        PWM_GateVoltage_GLOBAL_STBY_ENABLE &= ((uint8)(~PWM_GateVoltage_BLOCK_STBY_EN_MASK));
    #endif /* (PWM_GateVoltage_UsingFixedFunction) */
}

#if (PWM_GateVoltage_UseOneCompareMode)
    #if (PWM_GateVoltage_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PWM_GateVoltage_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWM_GateVoltage_SetCompareMode(uint8 comparemode) 
        {
            #if(PWM_GateVoltage_UsingFixedFunction)

                #if(0 != PWM_GateVoltage_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWM_GateVoltage_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != PWM_GateVoltage_CTRL_CMPMODE1_SHIFT) */

                PWM_GateVoltage_CONTROL3 &= ((uint8)(~PWM_GateVoltage_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                PWM_GateVoltage_CONTROL3 |= comparemodemasked;

            #elif (PWM_GateVoltage_UseControl)

                #if(0 != PWM_GateVoltage_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << PWM_GateVoltage_CTRL_CMPMODE1_SHIFT)) &
                                                PWM_GateVoltage_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & PWM_GateVoltage_CTRL_CMPMODE1_MASK;
                #endif /* (0 != PWM_GateVoltage_CTRL_CMPMODE1_SHIFT) */

                #if(0 != PWM_GateVoltage_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << PWM_GateVoltage_CTRL_CMPMODE2_SHIFT)) &
                                               PWM_GateVoltage_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & PWM_GateVoltage_CTRL_CMPMODE2_MASK;
                #endif /* (0 != PWM_GateVoltage_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                PWM_GateVoltage_CONTROL &= ((uint8)(~(PWM_GateVoltage_CTRL_CMPMODE1_MASK |
                                            PWM_GateVoltage_CTRL_CMPMODE2_MASK)));
                PWM_GateVoltage_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (PWM_GateVoltage_UsingFixedFunction) */
        }
    #endif /* PWM_GateVoltage_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (PWM_GateVoltage_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PWM_GateVoltage_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWM_GateVoltage_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != PWM_GateVoltage_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWM_GateVoltage_CTRL_CMPMODE1_SHIFT)) &
                                           PWM_GateVoltage_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & PWM_GateVoltage_CTRL_CMPMODE1_MASK;
            #endif /* (0 != PWM_GateVoltage_CTRL_CMPMODE1_SHIFT) */

            #if (PWM_GateVoltage_UseControl)
                PWM_GateVoltage_CONTROL &= ((uint8)(~PWM_GateVoltage_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                PWM_GateVoltage_CONTROL |= comparemodemasked;
            #endif /* (PWM_GateVoltage_UseControl) */
        }
    #endif /* PWM_GateVoltage_CompareMode1SW */

#if (PWM_GateVoltage_CompareMode2SW)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWM_GateVoltage_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != PWM_GateVoltage_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWM_GateVoltage_CTRL_CMPMODE2_SHIFT)) &
                                                 PWM_GateVoltage_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & PWM_GateVoltage_CTRL_CMPMODE2_MASK;
        #endif /* (0 != PWM_GateVoltage_CTRL_CMPMODE2_SHIFT) */

        #if (PWM_GateVoltage_UseControl)
            PWM_GateVoltage_CONTROL &= ((uint8)(~PWM_GateVoltage_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            PWM_GateVoltage_CONTROL |= comparemodemasked;
        #endif /* (PWM_GateVoltage_UseControl) */
    }
    #endif /*PWM_GateVoltage_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!PWM_GateVoltage_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void PWM_GateVoltage_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(PWM_GateVoltage_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(PWM_GateVoltage_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(PWM_GateVoltage_CAPTURE_LSB_PTR));
    }

    #if (PWM_GateVoltage_UseStatus)


        /*******************************************************************************
        * Function Name: PWM_GateVoltage_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWM_GateVoltage_ClearFIFO(void) 
        {
            while(0u != (PWM_GateVoltage_ReadStatusRegister() & PWM_GateVoltage_STATUS_FIFONEMPTY))
            {
                (void)PWM_GateVoltage_ReadCapture();
            }
        }

    #endif /* PWM_GateVoltage_UseStatus */

#endif /* !PWM_GateVoltage_UsingFixedFunction */


/*******************************************************************************
* Function Name: PWM_GateVoltage_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void PWM_GateVoltage_WritePeriod(uint8 period) 
{
    #if(PWM_GateVoltage_UsingFixedFunction)
        CY_SET_REG16(PWM_GateVoltage_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(PWM_GateVoltage_PERIOD_LSB_PTR, period);
    #endif /* (PWM_GateVoltage_UsingFixedFunction) */
}

#if (PWM_GateVoltage_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void PWM_GateVoltage_WriteCompare(uint8 compare) \
                                       
    {
        #if(PWM_GateVoltage_UsingFixedFunction)
            CY_SET_REG16(PWM_GateVoltage_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PWM_GateVoltage_COMPARE1_LSB_PTR, compare);
        #endif /* (PWM_GateVoltage_UsingFixedFunction) */

        #if (PWM_GateVoltage_PWMMode == PWM_GateVoltage__B_PWM__DITHER)
            #if(PWM_GateVoltage_UsingFixedFunction)
                CY_SET_REG16(PWM_GateVoltage_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(PWM_GateVoltage_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (PWM_GateVoltage_UsingFixedFunction) */
        #endif /* (PWM_GateVoltage_PWMMode == PWM_GateVoltage__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWM_GateVoltage_WriteCompare1(uint8 compare) \
                                        
    {
        #if(PWM_GateVoltage_UsingFixedFunction)
            CY_SET_REG16(PWM_GateVoltage_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(PWM_GateVoltage_COMPARE1_LSB_PTR, compare);
        #endif /* (PWM_GateVoltage_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWM_GateVoltage_WriteCompare2(uint8 compare) \
                                        
    {
        #if(PWM_GateVoltage_UsingFixedFunction)
            CY_SET_REG16(PWM_GateVoltage_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(PWM_GateVoltage_COMPARE2_LSB_PTR, compare);
        #endif /* (PWM_GateVoltage_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (PWM_GateVoltage_DeadBandUsed)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWM_GateVoltage_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!PWM_GateVoltage_DeadBand2_4)
            CY_SET_REG8(PWM_GateVoltage_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            PWM_GateVoltage_DEADBAND_COUNT &= ((uint8)(~PWM_GateVoltage_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(PWM_GateVoltage_DEADBAND_COUNT_SHIFT)
                PWM_GateVoltage_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << PWM_GateVoltage_DEADBAND_COUNT_SHIFT)) &
                                                    PWM_GateVoltage_DEADBAND_COUNT_MASK;
            #else
                PWM_GateVoltage_DEADBAND_COUNT |= deadtime & PWM_GateVoltage_DEADBAND_COUNT_MASK;
            #endif /* (PWM_GateVoltage_DEADBAND_COUNT_SHIFT) */

        #endif /* (!PWM_GateVoltage_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!PWM_GateVoltage_DeadBand2_4)
            return (CY_GET_REG8(PWM_GateVoltage_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(PWM_GateVoltage_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(PWM_GateVoltage_DEADBAND_COUNT & PWM_GateVoltage_DEADBAND_COUNT_MASK)) >>
                                                                           PWM_GateVoltage_DEADBAND_COUNT_SHIFT));
            #else
                return (PWM_GateVoltage_DEADBAND_COUNT & PWM_GateVoltage_DEADBAND_COUNT_MASK);
            #endif /* (PWM_GateVoltage_DEADBAND_COUNT_SHIFT) */
        #endif /* (!PWM_GateVoltage_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (PWM_GateVoltage_UseStatus || PWM_GateVoltage_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWM_GateVoltage_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(PWM_GateVoltage_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(PWM_GateVoltage_STATUS_PTR));
    }

#endif /* (PWM_GateVoltage_UseStatus || PWM_GateVoltage_UsingFixedFunction) */


#if (PWM_GateVoltage_UseControl)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(PWM_GateVoltage_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWM_GateVoltage_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(PWM_GateVoltage_CONTROL_PTR, control);
    }

#endif /* (PWM_GateVoltage_UseControl) */


#if (!PWM_GateVoltage_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadCapture(void) 
    {
        return (CY_GET_REG8(PWM_GateVoltage_CAPTURE_LSB_PTR));
    }

#endif /* (!PWM_GateVoltage_UsingFixedFunction) */


#if (PWM_GateVoltage_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadCompare(void) 
    {
        #if(PWM_GateVoltage_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(PWM_GateVoltage_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(PWM_GateVoltage_COMPARE1_LSB_PTR));
        #endif /* (PWM_GateVoltage_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadCompare1(void) 
    {
        return (CY_GET_REG8(PWM_GateVoltage_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadCompare2(void) 
    {
        return (CY_GET_REG8(PWM_GateVoltage_COMPARE2_LSB_PTR));
    }

#endif /* (PWM_GateVoltage_UseOneCompareMode) */


/*******************************************************************************
* Function Name: PWM_GateVoltage_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 PWM_GateVoltage_ReadPeriod(void) 
{
    #if(PWM_GateVoltage_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PWM_GateVoltage_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PWM_GateVoltage_PERIOD_LSB_PTR));
    #endif /* (PWM_GateVoltage_UsingFixedFunction) */
}

#if ( PWM_GateVoltage_KillModeMinTime)


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWM_GateVoltage_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(PWM_GateVoltage_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: PWM_GateVoltage_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 PWM_GateVoltage_ReadKillTime(void) 
    {
        return (CY_GET_REG8(PWM_GateVoltage_KILLMODEMINTIME_PTR));
    }

#endif /* ( PWM_GateVoltage_KillModeMinTime) */

/* [] END OF FILE */
