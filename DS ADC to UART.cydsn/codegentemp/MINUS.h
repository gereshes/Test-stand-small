/*******************************************************************************
* File Name: MINUS.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MINUS_H) /* Pins MINUS_H */
#define CY_PINS_MINUS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MINUS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MINUS__PORT == 15 && ((MINUS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MINUS_Write(uint8 value);
void    MINUS_SetDriveMode(uint8 mode);
uint8   MINUS_ReadDataReg(void);
uint8   MINUS_Read(void);
void    MINUS_SetInterruptMode(uint16 position, uint16 mode);
uint8   MINUS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MINUS_SetDriveMode() function.
     *  @{
     */
        #define MINUS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MINUS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MINUS_DM_RES_UP          PIN_DM_RES_UP
        #define MINUS_DM_RES_DWN         PIN_DM_RES_DWN
        #define MINUS_DM_OD_LO           PIN_DM_OD_LO
        #define MINUS_DM_OD_HI           PIN_DM_OD_HI
        #define MINUS_DM_STRONG          PIN_DM_STRONG
        #define MINUS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MINUS_MASK               MINUS__MASK
#define MINUS_SHIFT              MINUS__SHIFT
#define MINUS_WIDTH              1u

/* Interrupt constants */
#if defined(MINUS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MINUS_SetInterruptMode() function.
     *  @{
     */
        #define MINUS_INTR_NONE      (uint16)(0x0000u)
        #define MINUS_INTR_RISING    (uint16)(0x0001u)
        #define MINUS_INTR_FALLING   (uint16)(0x0002u)
        #define MINUS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MINUS_INTR_MASK      (0x01u) 
#endif /* (MINUS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MINUS_PS                     (* (reg8 *) MINUS__PS)
/* Data Register */
#define MINUS_DR                     (* (reg8 *) MINUS__DR)
/* Port Number */
#define MINUS_PRT_NUM                (* (reg8 *) MINUS__PRT) 
/* Connect to Analog Globals */                                                  
#define MINUS_AG                     (* (reg8 *) MINUS__AG)                       
/* Analog MUX bux enable */
#define MINUS_AMUX                   (* (reg8 *) MINUS__AMUX) 
/* Bidirectional Enable */                                                        
#define MINUS_BIE                    (* (reg8 *) MINUS__BIE)
/* Bit-mask for Aliased Register Access */
#define MINUS_BIT_MASK               (* (reg8 *) MINUS__BIT_MASK)
/* Bypass Enable */
#define MINUS_BYP                    (* (reg8 *) MINUS__BYP)
/* Port wide control signals */                                                   
#define MINUS_CTL                    (* (reg8 *) MINUS__CTL)
/* Drive Modes */
#define MINUS_DM0                    (* (reg8 *) MINUS__DM0) 
#define MINUS_DM1                    (* (reg8 *) MINUS__DM1)
#define MINUS_DM2                    (* (reg8 *) MINUS__DM2) 
/* Input Buffer Disable Override */
#define MINUS_INP_DIS                (* (reg8 *) MINUS__INP_DIS)
/* LCD Common or Segment Drive */
#define MINUS_LCD_COM_SEG            (* (reg8 *) MINUS__LCD_COM_SEG)
/* Enable Segment LCD */
#define MINUS_LCD_EN                 (* (reg8 *) MINUS__LCD_EN)
/* Slew Rate Control */
#define MINUS_SLW                    (* (reg8 *) MINUS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MINUS_PRTDSI__CAPS_SEL       (* (reg8 *) MINUS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MINUS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MINUS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MINUS_PRTDSI__OE_SEL0        (* (reg8 *) MINUS__PRTDSI__OE_SEL0) 
#define MINUS_PRTDSI__OE_SEL1        (* (reg8 *) MINUS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MINUS_PRTDSI__OUT_SEL0       (* (reg8 *) MINUS__PRTDSI__OUT_SEL0) 
#define MINUS_PRTDSI__OUT_SEL1       (* (reg8 *) MINUS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MINUS_PRTDSI__SYNC_OUT       (* (reg8 *) MINUS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MINUS__SIO_CFG)
    #define MINUS_SIO_HYST_EN        (* (reg8 *) MINUS__SIO_HYST_EN)
    #define MINUS_SIO_REG_HIFREQ     (* (reg8 *) MINUS__SIO_REG_HIFREQ)
    #define MINUS_SIO_CFG            (* (reg8 *) MINUS__SIO_CFG)
    #define MINUS_SIO_DIFF           (* (reg8 *) MINUS__SIO_DIFF)
#endif /* (MINUS__SIO_CFG) */

/* Interrupt Registers */
#if defined(MINUS__INTSTAT)
    #define MINUS_INTSTAT            (* (reg8 *) MINUS__INTSTAT)
    #define MINUS_SNAP               (* (reg8 *) MINUS__SNAP)
    
	#define MINUS_0_INTTYPE_REG 		(* (reg8 *) MINUS__0__INTTYPE)
#endif /* (MINUS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MINUS_H */


/* [] END OF FILE */
