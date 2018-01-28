/*******************************************************************************
* File Name: PLUS.h  
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

#if !defined(CY_PINS_PLUS_H) /* Pins PLUS_H */
#define CY_PINS_PLUS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PLUS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PLUS__PORT == 15 && ((PLUS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PLUS_Write(uint8 value);
void    PLUS_SetDriveMode(uint8 mode);
uint8   PLUS_ReadDataReg(void);
uint8   PLUS_Read(void);
void    PLUS_SetInterruptMode(uint16 position, uint16 mode);
uint8   PLUS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PLUS_SetDriveMode() function.
     *  @{
     */
        #define PLUS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PLUS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PLUS_DM_RES_UP          PIN_DM_RES_UP
        #define PLUS_DM_RES_DWN         PIN_DM_RES_DWN
        #define PLUS_DM_OD_LO           PIN_DM_OD_LO
        #define PLUS_DM_OD_HI           PIN_DM_OD_HI
        #define PLUS_DM_STRONG          PIN_DM_STRONG
        #define PLUS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PLUS_MASK               PLUS__MASK
#define PLUS_SHIFT              PLUS__SHIFT
#define PLUS_WIDTH              1u

/* Interrupt constants */
#if defined(PLUS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PLUS_SetInterruptMode() function.
     *  @{
     */
        #define PLUS_INTR_NONE      (uint16)(0x0000u)
        #define PLUS_INTR_RISING    (uint16)(0x0001u)
        #define PLUS_INTR_FALLING   (uint16)(0x0002u)
        #define PLUS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PLUS_INTR_MASK      (0x01u) 
#endif /* (PLUS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PLUS_PS                     (* (reg8 *) PLUS__PS)
/* Data Register */
#define PLUS_DR                     (* (reg8 *) PLUS__DR)
/* Port Number */
#define PLUS_PRT_NUM                (* (reg8 *) PLUS__PRT) 
/* Connect to Analog Globals */                                                  
#define PLUS_AG                     (* (reg8 *) PLUS__AG)                       
/* Analog MUX bux enable */
#define PLUS_AMUX                   (* (reg8 *) PLUS__AMUX) 
/* Bidirectional Enable */                                                        
#define PLUS_BIE                    (* (reg8 *) PLUS__BIE)
/* Bit-mask for Aliased Register Access */
#define PLUS_BIT_MASK               (* (reg8 *) PLUS__BIT_MASK)
/* Bypass Enable */
#define PLUS_BYP                    (* (reg8 *) PLUS__BYP)
/* Port wide control signals */                                                   
#define PLUS_CTL                    (* (reg8 *) PLUS__CTL)
/* Drive Modes */
#define PLUS_DM0                    (* (reg8 *) PLUS__DM0) 
#define PLUS_DM1                    (* (reg8 *) PLUS__DM1)
#define PLUS_DM2                    (* (reg8 *) PLUS__DM2) 
/* Input Buffer Disable Override */
#define PLUS_INP_DIS                (* (reg8 *) PLUS__INP_DIS)
/* LCD Common or Segment Drive */
#define PLUS_LCD_COM_SEG            (* (reg8 *) PLUS__LCD_COM_SEG)
/* Enable Segment LCD */
#define PLUS_LCD_EN                 (* (reg8 *) PLUS__LCD_EN)
/* Slew Rate Control */
#define PLUS_SLW                    (* (reg8 *) PLUS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PLUS_PRTDSI__CAPS_SEL       (* (reg8 *) PLUS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PLUS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PLUS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PLUS_PRTDSI__OE_SEL0        (* (reg8 *) PLUS__PRTDSI__OE_SEL0) 
#define PLUS_PRTDSI__OE_SEL1        (* (reg8 *) PLUS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PLUS_PRTDSI__OUT_SEL0       (* (reg8 *) PLUS__PRTDSI__OUT_SEL0) 
#define PLUS_PRTDSI__OUT_SEL1       (* (reg8 *) PLUS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PLUS_PRTDSI__SYNC_OUT       (* (reg8 *) PLUS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PLUS__SIO_CFG)
    #define PLUS_SIO_HYST_EN        (* (reg8 *) PLUS__SIO_HYST_EN)
    #define PLUS_SIO_REG_HIFREQ     (* (reg8 *) PLUS__SIO_REG_HIFREQ)
    #define PLUS_SIO_CFG            (* (reg8 *) PLUS__SIO_CFG)
    #define PLUS_SIO_DIFF           (* (reg8 *) PLUS__SIO_DIFF)
#endif /* (PLUS__SIO_CFG) */

/* Interrupt Registers */
#if defined(PLUS__INTSTAT)
    #define PLUS_INTSTAT            (* (reg8 *) PLUS__INTSTAT)
    #define PLUS_SNAP               (* (reg8 *) PLUS__SNAP)
    
	#define PLUS_0_INTTYPE_REG 		(* (reg8 *) PLUS__0__INTTYPE)
#endif /* (PLUS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PLUS_H */


/* [] END OF FILE */
