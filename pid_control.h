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
#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#define PWM_Period    99.0       // PWM period, set before run
#define PWM_REF       45.0       // Value of PWM duty cycle corresponding to fV_ref
#define EPSILON        0.2       // Tolerance on the error signal fDeltaV
    
float pid_control(float fCurSpeed, float fRefSpeed);

#endif

/* [] END OF FILE */
