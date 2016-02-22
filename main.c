/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <math.h>
#include "blinky.h"
#include "pid_control.h"

#define MAGNET_NUM           5u       // 5 magnets per wheel.
#define WHEEL_DIAMETER     2.34       // Wheel radius in [m]
#define PI           3.14159265       // pi
#define FEET             0.3048       // F -> m

float fDistanceTravelledPerRev = PI * WHEEL_DIAMETER;    // [m]
float fSpeedMPS;                      // Speed read form hall effect sensor [m]/[s]
float fSpeedFPS;                      // Speed read form hall effect sensor [f]/[s]
float fV_ref = 4.0;                   // [feet]/[s]


char str[16];                         // LCD char array 2x16

float fTimerArray[10];                // 2 * MAGNET_NUM
uint8 uiTimerArrayIndex;              // 0-9
uint32 uiTimeStamp;                   // Timer period - capture
float fTimeStamp;                     // Units of [s]

float fTimePerRevolution;             // Time elapsed until the same magnet passes the H-sensor
float fAvgTimePerRevolution;          // Time average over the last 5 readings (possible bug!)

uint8 uiPWM;                          // PWM compare value
uint8 i;                              // General purpose iterator

/* Function prototype */
//

CY_ISR(hallEffectSensor)
{
    // Get the index from the counter (0-9) for 5 magnets.
    uiTimerArrayIndex = hallTickCounter_ReadCounter();
    // Time elapsed from timer starting and hall effect pulse (units of clock ticks)
    uiTimeStamp = hallTickTimer_ReadPeriod() - hallTickTimer_ReadCapture();
    // Convert clock ticks to seconds (2.4MHz BUS CLK)
    fTimeStamp = uiTimeStamp / 2.4E7;  
    // Populate/update the timer array (2 values for each magnet)
    fTimerArray[uiTimerArrayIndex] = fTimeStamp;
    
    fTimePerRevolution = 0;
    // Average time in takes for a revolution off of each magnet
    for(i = 0; i < 5; i++)
    {
        fTimePerRevolution += fabs(fTimerArray[i+5] - fTimerArray[i]);
        fAvgTimePerRevolution = fTimePerRevolution / 5;
    }
    
    // Calculate speed in [m]/[s]
    fSpeedMPS = fDistanceTravelledPerRev / fAvgTimePerRevolution;
    
    // Speed in [F]/[s]
    fSpeedFPS = fSpeedMPS / FEET;
    
    // Calculate the PWM_out signal and convert it to an int
    uiPWM = floor(pid_control(fSpeedFPS, fV_ref) + 0.5);
    PWM_GateVoltage_WriteCompare(uiPWM);
    
    
    
    
    
    
    
    LCD_ClearDisplay();
    
    LCD_Position(0u,0u);
    sprintf(str, "C: %u", (int)uiTimerArrayIndex);
    LCD_PrintString(str);
   
    LCD_Position(0u,5u);
    sprintf(str, "T: %.3f", fTimeStamp);
    LCD_PrintString(str);
    
    
    LCD_Position(1u,0u);
    sprintf(str, "dT: %.4f", fTimePerRevolution);
    LCD_PrintString(str);
    
    //LCD_Position(1u,0u);
    //sprintf(str,"T: %u",(int)uiTimeStamp);
    //LCD_PrintString(str);
    //LCD_PrintU32Number(uiTimeStamp);
    
   
    
}


int main()
{
    //Blinky();
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Enable the interrupt component connected to hallEffectSensor
    hallEffect_ISR_Start();
    hallEffect_ISR_SetVector(hallEffectSensor);
    
    // Start components
    hallTickCounter_Start();
    hallTickTimer_Start();
    PWM_GateVoltage_Start();
    
    // Start clocks
    deBounce_Start();
    PWM_clock_Start();
    //testClock_Start();
    
    // Start LCD
    LCD_Start();
    LCD_ClearDisplay();

    for(;;)
    {
        /* Place your application code here. */
        /*
        CyDelay(1000);
        Blinky();
        LCD_Position(0u,0u);
        LCD_PrintU32Number(i);
        i++;
        */
        
    }
}

/* [] END OF FILE */
