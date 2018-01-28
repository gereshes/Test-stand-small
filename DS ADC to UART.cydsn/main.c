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
#include "project.h"
#include <stdio.h>

volatile unsigned long _millis=0;

CY_ISR(millis_isr){
    _millis++;
    millis_interrupt_ClearPending();
}

unsigned long millis(){
    return _millis;
}
    
int main(void)
{
    int i=0;
    int reading=0;
    char text[256]="";
    int samp_rate = 46; // How many samples from the adc before they get averaged
    CyGlobalIntEnable; /* Enable global interrupts. */
    millis_interrupt_StartEx(millis_isr);
    UART_Start();
    adc_Start();
    adc_StartConvert();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        reading = 0;
        //high = 0;
        
        for(i=0; i<samp_rate; i++){
            adc_IsEndConversion(adc_WAIT_FOR_RESULT);
            reading += adc_GetResult32();
        }
        reading /= samp_rate;
        //reading = adc_CountsTo_uVolts(reading);
        snprintf(text, 90, "%ld:%d\r\n", millis(), reading);
        UART_PutString(text);
    }
}

/* [] END OF FILE */
