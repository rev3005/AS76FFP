/*******************************************************************************
* File Name: Pin_OptDecDnClkY.h  
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

#if !defined(CY_PINS_Pin_OptDecDnClkY_H) /* Pins Pin_OptDecDnClkY_H */
#define CY_PINS_Pin_OptDecDnClkY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_OptDecDnClkY_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_OptDecDnClkY__PORT == 15 && ((Pin_OptDecDnClkY__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin_OptDecDnClkY_Write(uint8 value);
void    Pin_OptDecDnClkY_SetDriveMode(uint8 mode);
uint8   Pin_OptDecDnClkY_ReadDataReg(void);
uint8   Pin_OptDecDnClkY_Read(void);
void    Pin_OptDecDnClkY_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_OptDecDnClkY_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin_OptDecDnClkY_SetDriveMode() function.
     *  @{
     */
        #define Pin_OptDecDnClkY_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin_OptDecDnClkY_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin_OptDecDnClkY_DM_RES_UP          PIN_DM_RES_UP
        #define Pin_OptDecDnClkY_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin_OptDecDnClkY_DM_OD_LO           PIN_DM_OD_LO
        #define Pin_OptDecDnClkY_DM_OD_HI           PIN_DM_OD_HI
        #define Pin_OptDecDnClkY_DM_STRONG          PIN_DM_STRONG
        #define Pin_OptDecDnClkY_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin_OptDecDnClkY_MASK               Pin_OptDecDnClkY__MASK
#define Pin_OptDecDnClkY_SHIFT              Pin_OptDecDnClkY__SHIFT
#define Pin_OptDecDnClkY_WIDTH              1u

/* Interrupt constants */
#if defined(Pin_OptDecDnClkY__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_OptDecDnClkY_SetInterruptMode() function.
     *  @{
     */
        #define Pin_OptDecDnClkY_INTR_NONE      (uint16)(0x0000u)
        #define Pin_OptDecDnClkY_INTR_RISING    (uint16)(0x0001u)
        #define Pin_OptDecDnClkY_INTR_FALLING   (uint16)(0x0002u)
        #define Pin_OptDecDnClkY_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin_OptDecDnClkY_INTR_MASK      (0x01u) 
#endif /* (Pin_OptDecDnClkY__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_OptDecDnClkY_PS                     (* (reg8 *) Pin_OptDecDnClkY__PS)
/* Data Register */
#define Pin_OptDecDnClkY_DR                     (* (reg8 *) Pin_OptDecDnClkY__DR)
/* Port Number */
#define Pin_OptDecDnClkY_PRT_NUM                (* (reg8 *) Pin_OptDecDnClkY__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_OptDecDnClkY_AG                     (* (reg8 *) Pin_OptDecDnClkY__AG)                       
/* Analog MUX bux enable */
#define Pin_OptDecDnClkY_AMUX                   (* (reg8 *) Pin_OptDecDnClkY__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_OptDecDnClkY_BIE                    (* (reg8 *) Pin_OptDecDnClkY__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_OptDecDnClkY_BIT_MASK               (* (reg8 *) Pin_OptDecDnClkY__BIT_MASK)
/* Bypass Enable */
#define Pin_OptDecDnClkY_BYP                    (* (reg8 *) Pin_OptDecDnClkY__BYP)
/* Port wide control signals */                                                   
#define Pin_OptDecDnClkY_CTL                    (* (reg8 *) Pin_OptDecDnClkY__CTL)
/* Drive Modes */
#define Pin_OptDecDnClkY_DM0                    (* (reg8 *) Pin_OptDecDnClkY__DM0) 
#define Pin_OptDecDnClkY_DM1                    (* (reg8 *) Pin_OptDecDnClkY__DM1)
#define Pin_OptDecDnClkY_DM2                    (* (reg8 *) Pin_OptDecDnClkY__DM2) 
/* Input Buffer Disable Override */
#define Pin_OptDecDnClkY_INP_DIS                (* (reg8 *) Pin_OptDecDnClkY__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_OptDecDnClkY_LCD_COM_SEG            (* (reg8 *) Pin_OptDecDnClkY__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_OptDecDnClkY_LCD_EN                 (* (reg8 *) Pin_OptDecDnClkY__LCD_EN)
/* Slew Rate Control */
#define Pin_OptDecDnClkY_SLW                    (* (reg8 *) Pin_OptDecDnClkY__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_OptDecDnClkY_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_OptDecDnClkY__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_OptDecDnClkY_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_OptDecDnClkY__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_OptDecDnClkY_PRTDSI__OE_SEL0        (* (reg8 *) Pin_OptDecDnClkY__PRTDSI__OE_SEL0) 
#define Pin_OptDecDnClkY_PRTDSI__OE_SEL1        (* (reg8 *) Pin_OptDecDnClkY__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_OptDecDnClkY_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_OptDecDnClkY__PRTDSI__OUT_SEL0) 
#define Pin_OptDecDnClkY_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_OptDecDnClkY__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_OptDecDnClkY_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_OptDecDnClkY__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin_OptDecDnClkY__SIO_CFG)
    #define Pin_OptDecDnClkY_SIO_HYST_EN        (* (reg8 *) Pin_OptDecDnClkY__SIO_HYST_EN)
    #define Pin_OptDecDnClkY_SIO_REG_HIFREQ     (* (reg8 *) Pin_OptDecDnClkY__SIO_REG_HIFREQ)
    #define Pin_OptDecDnClkY_SIO_CFG            (* (reg8 *) Pin_OptDecDnClkY__SIO_CFG)
    #define Pin_OptDecDnClkY_SIO_DIFF           (* (reg8 *) Pin_OptDecDnClkY__SIO_DIFF)
#endif /* (Pin_OptDecDnClkY__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin_OptDecDnClkY__INTSTAT)
    #define Pin_OptDecDnClkY_INTSTAT            (* (reg8 *) Pin_OptDecDnClkY__INTSTAT)
    #define Pin_OptDecDnClkY_SNAP               (* (reg8 *) Pin_OptDecDnClkY__SNAP)
    
	#define Pin_OptDecDnClkY_0_INTTYPE_REG 		(* (reg8 *) Pin_OptDecDnClkY__0__INTTYPE)
#endif /* (Pin_OptDecDnClkY__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_OptDecDnClkY_H */


/* [] END OF FILE */
