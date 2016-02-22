/*******************************************************************************
* File Name: hallTickCounter.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 hallTickCounter_initVar = 0u;


/*******************************************************************************
* Function Name: hallTickCounter_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void hallTickCounter_Init(void) 
{
        #if (!hallTickCounter_UsingFixedFunction && !hallTickCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!hallTickCounter_UsingFixedFunction && !hallTickCounter_ControlRegRemoved) */
        
        #if(!hallTickCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 hallTickCounter_interruptState;
        #endif /* (!hallTickCounter_UsingFixedFunction) */
        
        #if (hallTickCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            hallTickCounter_CONTROL &= hallTickCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                hallTickCounter_CONTROL2 &= ((uint8)(~hallTickCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                hallTickCounter_CONTROL3 &= ((uint8)(~hallTickCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (hallTickCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                hallTickCounter_CONTROL |= hallTickCounter_ONESHOT;
            #endif /* (hallTickCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            hallTickCounter_CONTROL2 |= hallTickCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            hallTickCounter_RT1 &= ((uint8)(~hallTickCounter_RT1_MASK));
            hallTickCounter_RT1 |= hallTickCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            hallTickCounter_RT1 &= ((uint8)(~hallTickCounter_SYNCDSI_MASK));
            hallTickCounter_RT1 |= hallTickCounter_SYNCDSI_EN;

        #else
            #if(!hallTickCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = hallTickCounter_CONTROL & ((uint8)(~hallTickCounter_CTRL_CMPMODE_MASK));
            hallTickCounter_CONTROL = ctrl | hallTickCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = hallTickCounter_CONTROL & ((uint8)(~hallTickCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != hallTickCounter_CAPTURE_MODE_CONF)
                hallTickCounter_CONTROL = ctrl | hallTickCounter_DEFAULT_CAPTURE_MODE;
            #else
                hallTickCounter_CONTROL = ctrl;
            #endif /* 0 != hallTickCounter_CAPTURE_MODE */ 
            
            #endif /* (!hallTickCounter_ControlRegRemoved) */
        #endif /* (hallTickCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!hallTickCounter_UsingFixedFunction)
            hallTickCounter_ClearFIFO();
        #endif /* (!hallTickCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        hallTickCounter_WritePeriod(hallTickCounter_INIT_PERIOD_VALUE);
        #if (!(hallTickCounter_UsingFixedFunction && (CY_PSOC5A)))
            hallTickCounter_WriteCounter(hallTickCounter_INIT_COUNTER_VALUE);
        #endif /* (!(hallTickCounter_UsingFixedFunction && (CY_PSOC5A))) */
        hallTickCounter_SetInterruptMode(hallTickCounter_INIT_INTERRUPTS_MASK);
        
        #if (!hallTickCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)hallTickCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            hallTickCounter_WriteCompare(hallTickCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            hallTickCounter_interruptState = CyEnterCriticalSection();
            
            hallTickCounter_STATUS_AUX_CTRL |= hallTickCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(hallTickCounter_interruptState);
            
        #endif /* (!hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void hallTickCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (hallTickCounter_UsingFixedFunction)
        hallTickCounter_GLOBAL_ENABLE |= hallTickCounter_BLOCK_EN_MASK;
        hallTickCounter_GLOBAL_STBY_ENABLE |= hallTickCounter_BLOCK_STBY_EN_MASK;
    #endif /* (hallTickCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!hallTickCounter_ControlRegRemoved || hallTickCounter_UsingFixedFunction)
        hallTickCounter_CONTROL |= hallTickCounter_CTRL_ENABLE;                
    #endif /* (!hallTickCounter_ControlRegRemoved || hallTickCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: hallTickCounter_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  hallTickCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void hallTickCounter_Start(void) 
{
    if(hallTickCounter_initVar == 0u)
    {
        hallTickCounter_Init();
        
        hallTickCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    hallTickCounter_Enable();        
}


/*******************************************************************************
* Function Name: hallTickCounter_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void hallTickCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!hallTickCounter_ControlRegRemoved || hallTickCounter_UsingFixedFunction)
        hallTickCounter_CONTROL &= ((uint8)(~hallTickCounter_CTRL_ENABLE));        
    #endif /* (!hallTickCounter_ControlRegRemoved || hallTickCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (hallTickCounter_UsingFixedFunction)
        hallTickCounter_GLOBAL_ENABLE &= ((uint8)(~hallTickCounter_BLOCK_EN_MASK));
        hallTickCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~hallTickCounter_BLOCK_STBY_EN_MASK));
    #endif /* (hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void hallTickCounter_SetInterruptMode(uint8 interruptsMask) 
{
    hallTickCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: hallTickCounter_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   hallTickCounter_ReadStatusRegister(void) 
{
    return hallTickCounter_STATUS;
}


#if(!hallTickCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: hallTickCounter_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   hallTickCounter_ReadControlRegister(void) 
{
    return hallTickCounter_CONTROL;
}


/*******************************************************************************
* Function Name: hallTickCounter_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    hallTickCounter_WriteControlRegister(uint8 control) 
{
    hallTickCounter_CONTROL = control;
}

#endif  /* (!hallTickCounter_ControlRegRemoved) */


#if (!(hallTickCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: hallTickCounter_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void hallTickCounter_WriteCounter(uint8 counter) \
                                   
{
    #if(hallTickCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (hallTickCounter_GLOBAL_ENABLE & hallTickCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        hallTickCounter_GLOBAL_ENABLE |= hallTickCounter_BLOCK_EN_MASK;
        CY_SET_REG16(hallTickCounter_COUNTER_LSB_PTR, (uint16)counter);
        hallTickCounter_GLOBAL_ENABLE &= ((uint8)(~hallTickCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(hallTickCounter_COUNTER_LSB_PTR, counter);
    #endif /* (hallTickCounter_UsingFixedFunction) */
}
#endif /* (!(hallTickCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: hallTickCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 hallTickCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(hallTickCounter_UsingFixedFunction)
		(void)CY_GET_REG16(hallTickCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(hallTickCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (hallTickCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(hallTickCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(hallTickCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(hallTickCounter_STATICCOUNT_LSB_PTR));
    #endif /* (hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 hallTickCounter_ReadCapture(void) 
{
    #if(hallTickCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(hallTickCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(hallTickCounter_STATICCOUNT_LSB_PTR));
    #endif /* (hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void hallTickCounter_WritePeriod(uint8 period) 
{
    #if(hallTickCounter_UsingFixedFunction)
        CY_SET_REG16(hallTickCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(hallTickCounter_PERIOD_LSB_PTR, period);
    #endif /* (hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 hallTickCounter_ReadPeriod(void) 
{
    #if(hallTickCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(hallTickCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(hallTickCounter_PERIOD_LSB_PTR));
    #endif /* (hallTickCounter_UsingFixedFunction) */
}


#if (!hallTickCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: hallTickCounter_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void hallTickCounter_WriteCompare(uint8 compare) \
                                   
{
    #if(hallTickCounter_UsingFixedFunction)
        CY_SET_REG16(hallTickCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(hallTickCounter_COMPARE_LSB_PTR, compare);
    #endif /* (hallTickCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: hallTickCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 hallTickCounter_ReadCompare(void) 
{
    return (CY_GET_REG8(hallTickCounter_COMPARE_LSB_PTR));
}


#if (hallTickCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: hallTickCounter_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void hallTickCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    hallTickCounter_CONTROL &= ((uint8)(~hallTickCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    hallTickCounter_CONTROL |= compareMode;
}
#endif  /* (hallTickCounter_COMPARE_MODE_SOFTWARE) */


#if (hallTickCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: hallTickCounter_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void hallTickCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    hallTickCounter_CONTROL &= ((uint8)(~hallTickCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    hallTickCounter_CONTROL |= ((uint8)((uint8)captureMode << hallTickCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (hallTickCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: hallTickCounter_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void hallTickCounter_ClearFIFO(void) 
{

    while(0u != (hallTickCounter_ReadStatusRegister() & hallTickCounter_STATUS_FIFONEMP))
    {
        (void)hallTickCounter_ReadCapture();
    }

}
#endif  /* (!hallTickCounter_UsingFixedFunction) */


/* [] END OF FILE */

