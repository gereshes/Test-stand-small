/*******************************************************************************
* File Name: adc_Bypass_P03.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "adc_Bypass_P03.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 adc_Bypass_P03__PORT == 15 && ((adc_Bypass_P03__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: adc_Bypass_P03_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void adc_Bypass_P03_Write(uint8 value) 
{
    uint8 staticBits = (adc_Bypass_P03_DR & (uint8)(~adc_Bypass_P03_MASK));
    adc_Bypass_P03_DR = staticBits | ((uint8)(value << adc_Bypass_P03_SHIFT) & adc_Bypass_P03_MASK);
}


/*******************************************************************************
* Function Name: adc_Bypass_P03_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  adc_Bypass_P03_DM_STRONG     Strong Drive 
*  adc_Bypass_P03_DM_OD_HI      Open Drain, Drives High 
*  adc_Bypass_P03_DM_OD_LO      Open Drain, Drives Low 
*  adc_Bypass_P03_DM_RES_UP     Resistive Pull Up 
*  adc_Bypass_P03_DM_RES_DWN    Resistive Pull Down 
*  adc_Bypass_P03_DM_RES_UPDWN  Resistive Pull Up/Down 
*  adc_Bypass_P03_DM_DIG_HIZ    High Impedance Digital 
*  adc_Bypass_P03_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void adc_Bypass_P03_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(adc_Bypass_P03_0, mode);
}


/*******************************************************************************
* Function Name: adc_Bypass_P03_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro adc_Bypass_P03_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 adc_Bypass_P03_Read(void) 
{
    return (adc_Bypass_P03_PS & adc_Bypass_P03_MASK) >> adc_Bypass_P03_SHIFT;
}


/*******************************************************************************
* Function Name: adc_Bypass_P03_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 adc_Bypass_P03_ReadDataReg(void) 
{
    return (adc_Bypass_P03_DR & adc_Bypass_P03_MASK) >> adc_Bypass_P03_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(adc_Bypass_P03_INTSTAT) 

    /*******************************************************************************
    * Function Name: adc_Bypass_P03_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 adc_Bypass_P03_ClearInterrupt(void) 
    {
        return (adc_Bypass_P03_INTSTAT & adc_Bypass_P03_MASK) >> adc_Bypass_P03_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
