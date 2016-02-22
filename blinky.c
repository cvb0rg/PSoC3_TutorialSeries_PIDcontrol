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

/* [] END OF FILE */

#include <project.h>
#include "blinky.h"

/*
************************************************************************ 
* File: blinky.c
* verion: 1.0
*
* Description:
*   Blinks the onboard LED (connect to P6_2) twice; used for debugging.
************************************************************************
*/

void Blinky(void)
{
    LED_Status_Write(LED_ON);
    CyDelay(BLINK_DELAY_MS);
    LED_Status_Write(LED_OFF);
    CyDelay(BLINK_DELAY_MS);
    LED_Status_Write(LED_ON);
    CyDelay(BLINK_DELAY_MS);
    LED_Status_Write(LED_OFF);
    CyDelay(BLINK_DELAY_MS);
}