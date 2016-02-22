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
#include <math.h>
#include "pid_control.h"
#include "blinky.h"

/*
************************************************************************ 
* File: pid_control.c
* verion: 1.0
*
* Description:
*   ---
************************************************************************
*/

float fDeltaV;                   // Difference between instantaneous speed and ref speed 
float fPWM_out;                  // Value written to the MOSFET gate

float pid_control(float fCurSpeed, float fRefSpeed)
{
    Blinky();
    
    fDeltaV = (fCurSpeed - fRefSpeed);
    
    if (fDeltaV <= EPSILON)
    {
        fPWM_out = PWM_REF;
    } else {
        fPWM_out = ( - tanh(fDeltaV) + 1 ) * PWM_Period/2;
    }
    
    return fPWM_out;
}



/* [] END OF FILE */