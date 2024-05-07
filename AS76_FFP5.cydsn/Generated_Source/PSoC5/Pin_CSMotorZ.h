/*******************************************************************************
* File Name: Pin_CSMotorZ.h  
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

#if !defined(CY_PINS_Pin_CSMotorZ_H) /* Pins Pin_CSMotorZ_H */
#define CY_PINS_Pin_CSMotorZ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_CSMotorZ_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_CSMotorZ__PORT == 15 && ((Pin_CSMotorZ__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin_CSMotorZ_Write(uint8 value);
void    Pin_CSMotorZ_SetDriveMode(uint8 mode);
uint8   Pin_CSMotorZ_ReadDataReg(void);
uint8   Pin_CSMotorZ_Read(void);
void    Pin_CSMotorZ_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_CSMotorZ_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin_CSMotorZ_SetDriveMode() function.
     *  @{
     */
        #define Pin_CSMotorZ_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin_CSMotorZ_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin_CSMotorZ_DM_RES_UP          PIN_DM_RES_UP
        #define Pin_CSMotorZ_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin_CSMotorZ_DM_OD_LO           PIN_DM_OD_LO
        #define Pin_CSMotorZ_DM_OD_HI           PIN_DM_OD_HI
        #define Pin_CSMotorZ_DM_STRONG          PIN_DM_STRONG
        #define Pin_CSMotorZ_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin_CSMotorZ_MASK               Pin_CSMotorZ__MASK
#define Pin_CSMotorZ_SHIFT              Pin_CSMotorZ__SHIFT
#define Pin_CSMotorZ_WIDTH              1u

/* Interrupt constants */
#if defined(Pin_CSMotorZ__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_CSMotorZ_SetInterruptMode() function.
     *  @{
     */
        #define Pin_CSMotorZ_INTR_NONE      (uint16)(0x0000u)
        #define Pin_CSMotorZ_INTR_RISING    (uint16)(0x0001u)
        #define Pin_CSMotorZ_INTR_FALLING   (uint16)(0x0002u)
        #define Pin_CSMotorZ_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin_CSMotorZ_INTR_MASK      (0x01u) 
#endif /* (Pin_CSMotorZ__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_CSMotorZ_PS                     (* (reg8 *) Pin_CSMotorZ__PS)
/* Data Register */
#define Pin_CSMotorZ_DR                     (* (reg8 *) Pin_CSMotorZ__DR)
/* Port Number */
#define Pin_CSMotorZ_PRT_NUM                (* (reg8 *) Pin_CSMotorZ__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_CSMotorZ_AG                     (* (reg8 *) Pin_CSMotorZ__AG)                       
/* Analog MUX bux enable */
#define Pin_CSMotorZ_AMUX                   (* (reg8 *) Pin_CSMotorZ__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_CSMotorZ_BIE                    (* (reg8 *) Pin_CSMotorZ__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_CSMotorZ_BIT_MASK               (* (reg8 *) Pin_CSMotorZ__BIT_MASK)
/* Bypass Enable */
#define Pin_CSMotorZ_BYP                    (* (reg8 *) Pin_CSMotorZ__BYP)
/* Port wide control signals */                                                   
#define Pin_CSMotorZ_CTL                    (* (reg8 *) Pin_CSMotorZ__CTL)
/* Drive Modes */
#define Pin_CSMotorZ_DM0                    (* (reg8 *) Pin_CSMotorZ__DM0) 
#define Pin_CSMotorZ_DM1                    (* (reg8 *) Pin_CSMotorZ__DM1)
#define Pin_CSMotorZ_DM2                    (* (reg8 *) Pin_CSMotorZ__DM2) 
/* Input Buffer Disable Override */
#define Pin_CSMotorZ_INP_DIS                (* (reg8 *) Pin_CSMotorZ__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_CSMotorZ_LCD_COM_SEG            (* (reg8 *) Pin_CSMotorZ__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_CSMotorZ_LCD_EN                 (* (reg8 *) Pin_CSMotorZ__LCD_EN)
/* Slew Rate Control */
#define Pin_CSMotorZ_SLW                    (* (reg8 *) Pin_CSMotorZ__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_CSMotorZ_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_CSMotorZ__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_CSMotorZ_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_CSMotorZ__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_CSMotorZ_PRTDSI__OE_SEL0        (* (reg8 *) Pin_CSMotorZ__PRTDSI__OE_SEL0) 
#define Pin_CSMotorZ_PRTDSI__OE_SEL1        (* (reg8 *) Pin_CSMotorZ__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_CSMotorZ_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_CSMotorZ__PRTDSI__OUT_SEL0) 
#define Pin_CSMotorZ_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_CSMotorZ__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_CSMotorZ_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_CSMotorZ__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin_CSMotorZ__SIO_CFG)
    #define Pin_CSMotorZ_SIO_HYST_EN        (* (reg8 *) Pin_CSMotorZ__SIO_HYST_EN)
    #define Pin_CSMotorZ_SIO_REG_HIFREQ     (* (reg8 *) Pin_CSMotorZ__SIO_REG_HIFREQ)
    #define Pin_CSMotorZ_SIO_CFG            (* (reg8 *) Pin_CSMotorZ__SIO_CFG)
    #define Pin_CSMotorZ_SIO_DIFF           (* (reg8 *) Pin_CSMotorZ__SIO_DIFF)
#endif /* (Pin_CSMotorZ__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin_CSMotorZ__INTSTAT)
    #define Pin_CSMotorZ_INTSTAT            (* (reg8 *) Pin_CSMotorZ__INTSTAT)
    #define Pin_CSMotorZ_SNAP               (* (reg8 *) Pin_CSMotorZ__SNAP)
    
	#define Pin_CSMotorZ_0_INTTYPE_REG 		(* (reg8 *) Pin_CSMotorZ__0__INTTYPE)
#endif /* (Pin_CSMotorZ__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_CSMotorZ_H */


/* [] END OF FILE */
