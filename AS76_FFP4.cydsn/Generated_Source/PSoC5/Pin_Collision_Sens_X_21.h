/*******************************************************************************
* File Name: Pin_Collision_Sens_X_21.h  
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

#if !defined(CY_PINS_Pin_Collision_Sens_X_21_H) /* Pins Pin_Collision_Sens_X_21_H */
#define CY_PINS_Pin_Collision_Sens_X_21_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_Collision_Sens_X_21_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_Collision_Sens_X_21__PORT == 15 && ((Pin_Collision_Sens_X_21__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin_Collision_Sens_X_21_Write(uint8 value);
void    Pin_Collision_Sens_X_21_SetDriveMode(uint8 mode);
uint8   Pin_Collision_Sens_X_21_ReadDataReg(void);
uint8   Pin_Collision_Sens_X_21_Read(void);
void    Pin_Collision_Sens_X_21_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_Collision_Sens_X_21_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin_Collision_Sens_X_21_SetDriveMode() function.
     *  @{
     */
        #define Pin_Collision_Sens_X_21_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin_Collision_Sens_X_21_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin_Collision_Sens_X_21_DM_RES_UP          PIN_DM_RES_UP
        #define Pin_Collision_Sens_X_21_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin_Collision_Sens_X_21_DM_OD_LO           PIN_DM_OD_LO
        #define Pin_Collision_Sens_X_21_DM_OD_HI           PIN_DM_OD_HI
        #define Pin_Collision_Sens_X_21_DM_STRONG          PIN_DM_STRONG
        #define Pin_Collision_Sens_X_21_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin_Collision_Sens_X_21_MASK               Pin_Collision_Sens_X_21__MASK
#define Pin_Collision_Sens_X_21_SHIFT              Pin_Collision_Sens_X_21__SHIFT
#define Pin_Collision_Sens_X_21_WIDTH              1u

/* Interrupt constants */
#if defined(Pin_Collision_Sens_X_21__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_Collision_Sens_X_21_SetInterruptMode() function.
     *  @{
     */
        #define Pin_Collision_Sens_X_21_INTR_NONE      (uint16)(0x0000u)
        #define Pin_Collision_Sens_X_21_INTR_RISING    (uint16)(0x0001u)
        #define Pin_Collision_Sens_X_21_INTR_FALLING   (uint16)(0x0002u)
        #define Pin_Collision_Sens_X_21_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin_Collision_Sens_X_21_INTR_MASK      (0x01u) 
#endif /* (Pin_Collision_Sens_X_21__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_Collision_Sens_X_21_PS                     (* (reg8 *) Pin_Collision_Sens_X_21__PS)
/* Data Register */
#define Pin_Collision_Sens_X_21_DR                     (* (reg8 *) Pin_Collision_Sens_X_21__DR)
/* Port Number */
#define Pin_Collision_Sens_X_21_PRT_NUM                (* (reg8 *) Pin_Collision_Sens_X_21__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_Collision_Sens_X_21_AG                     (* (reg8 *) Pin_Collision_Sens_X_21__AG)                       
/* Analog MUX bux enable */
#define Pin_Collision_Sens_X_21_AMUX                   (* (reg8 *) Pin_Collision_Sens_X_21__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_Collision_Sens_X_21_BIE                    (* (reg8 *) Pin_Collision_Sens_X_21__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_Collision_Sens_X_21_BIT_MASK               (* (reg8 *) Pin_Collision_Sens_X_21__BIT_MASK)
/* Bypass Enable */
#define Pin_Collision_Sens_X_21_BYP                    (* (reg8 *) Pin_Collision_Sens_X_21__BYP)
/* Port wide control signals */                                                   
#define Pin_Collision_Sens_X_21_CTL                    (* (reg8 *) Pin_Collision_Sens_X_21__CTL)
/* Drive Modes */
#define Pin_Collision_Sens_X_21_DM0                    (* (reg8 *) Pin_Collision_Sens_X_21__DM0) 
#define Pin_Collision_Sens_X_21_DM1                    (* (reg8 *) Pin_Collision_Sens_X_21__DM1)
#define Pin_Collision_Sens_X_21_DM2                    (* (reg8 *) Pin_Collision_Sens_X_21__DM2) 
/* Input Buffer Disable Override */
#define Pin_Collision_Sens_X_21_INP_DIS                (* (reg8 *) Pin_Collision_Sens_X_21__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_Collision_Sens_X_21_LCD_COM_SEG            (* (reg8 *) Pin_Collision_Sens_X_21__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_Collision_Sens_X_21_LCD_EN                 (* (reg8 *) Pin_Collision_Sens_X_21__LCD_EN)
/* Slew Rate Control */
#define Pin_Collision_Sens_X_21_SLW                    (* (reg8 *) Pin_Collision_Sens_X_21__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_Collision_Sens_X_21_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_Collision_Sens_X_21__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_Collision_Sens_X_21_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_Collision_Sens_X_21__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_Collision_Sens_X_21_PRTDSI__OE_SEL0        (* (reg8 *) Pin_Collision_Sens_X_21__PRTDSI__OE_SEL0) 
#define Pin_Collision_Sens_X_21_PRTDSI__OE_SEL1        (* (reg8 *) Pin_Collision_Sens_X_21__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_Collision_Sens_X_21_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_Collision_Sens_X_21__PRTDSI__OUT_SEL0) 
#define Pin_Collision_Sens_X_21_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_Collision_Sens_X_21__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_Collision_Sens_X_21_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_Collision_Sens_X_21__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin_Collision_Sens_X_21__SIO_CFG)
    #define Pin_Collision_Sens_X_21_SIO_HYST_EN        (* (reg8 *) Pin_Collision_Sens_X_21__SIO_HYST_EN)
    #define Pin_Collision_Sens_X_21_SIO_REG_HIFREQ     (* (reg8 *) Pin_Collision_Sens_X_21__SIO_REG_HIFREQ)
    #define Pin_Collision_Sens_X_21_SIO_CFG            (* (reg8 *) Pin_Collision_Sens_X_21__SIO_CFG)
    #define Pin_Collision_Sens_X_21_SIO_DIFF           (* (reg8 *) Pin_Collision_Sens_X_21__SIO_DIFF)
#endif /* (Pin_Collision_Sens_X_21__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin_Collision_Sens_X_21__INTSTAT)
    #define Pin_Collision_Sens_X_21_INTSTAT            (* (reg8 *) Pin_Collision_Sens_X_21__INTSTAT)
    #define Pin_Collision_Sens_X_21_SNAP               (* (reg8 *) Pin_Collision_Sens_X_21__SNAP)
    
	#define Pin_Collision_Sens_X_21_0_INTTYPE_REG 		(* (reg8 *) Pin_Collision_Sens_X_21__0__INTTYPE)
#endif /* (Pin_Collision_Sens_X_21__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_Collision_Sens_X_21_H */


/* [] END OF FILE */
