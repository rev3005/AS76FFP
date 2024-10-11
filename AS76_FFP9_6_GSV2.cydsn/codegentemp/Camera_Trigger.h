/*******************************************************************************
* File Name: Camera_Trigger.h  
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

#if !defined(CY_PINS_Camera_Trigger_H) /* Pins Camera_Trigger_H */
#define CY_PINS_Camera_Trigger_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Camera_Trigger_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Camera_Trigger__PORT == 15 && ((Camera_Trigger__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Camera_Trigger_Write(uint8 value);
void    Camera_Trigger_SetDriveMode(uint8 mode);
uint8   Camera_Trigger_ReadDataReg(void);
uint8   Camera_Trigger_Read(void);
void    Camera_Trigger_SetInterruptMode(uint16 position, uint16 mode);
uint8   Camera_Trigger_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Camera_Trigger_SetDriveMode() function.
     *  @{
     */
        #define Camera_Trigger_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Camera_Trigger_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Camera_Trigger_DM_RES_UP          PIN_DM_RES_UP
        #define Camera_Trigger_DM_RES_DWN         PIN_DM_RES_DWN
        #define Camera_Trigger_DM_OD_LO           PIN_DM_OD_LO
        #define Camera_Trigger_DM_OD_HI           PIN_DM_OD_HI
        #define Camera_Trigger_DM_STRONG          PIN_DM_STRONG
        #define Camera_Trigger_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Camera_Trigger_MASK               Camera_Trigger__MASK
#define Camera_Trigger_SHIFT              Camera_Trigger__SHIFT
#define Camera_Trigger_WIDTH              1u

/* Interrupt constants */
#if defined(Camera_Trigger__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Camera_Trigger_SetInterruptMode() function.
     *  @{
     */
        #define Camera_Trigger_INTR_NONE      (uint16)(0x0000u)
        #define Camera_Trigger_INTR_RISING    (uint16)(0x0001u)
        #define Camera_Trigger_INTR_FALLING   (uint16)(0x0002u)
        #define Camera_Trigger_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Camera_Trigger_INTR_MASK      (0x01u) 
#endif /* (Camera_Trigger__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Camera_Trigger_PS                     (* (reg8 *) Camera_Trigger__PS)
/* Data Register */
#define Camera_Trigger_DR                     (* (reg8 *) Camera_Trigger__DR)
/* Port Number */
#define Camera_Trigger_PRT_NUM                (* (reg8 *) Camera_Trigger__PRT) 
/* Connect to Analog Globals */                                                  
#define Camera_Trigger_AG                     (* (reg8 *) Camera_Trigger__AG)                       
/* Analog MUX bux enable */
#define Camera_Trigger_AMUX                   (* (reg8 *) Camera_Trigger__AMUX) 
/* Bidirectional Enable */                                                        
#define Camera_Trigger_BIE                    (* (reg8 *) Camera_Trigger__BIE)
/* Bit-mask for Aliased Register Access */
#define Camera_Trigger_BIT_MASK               (* (reg8 *) Camera_Trigger__BIT_MASK)
/* Bypass Enable */
#define Camera_Trigger_BYP                    (* (reg8 *) Camera_Trigger__BYP)
/* Port wide control signals */                                                   
#define Camera_Trigger_CTL                    (* (reg8 *) Camera_Trigger__CTL)
/* Drive Modes */
#define Camera_Trigger_DM0                    (* (reg8 *) Camera_Trigger__DM0) 
#define Camera_Trigger_DM1                    (* (reg8 *) Camera_Trigger__DM1)
#define Camera_Trigger_DM2                    (* (reg8 *) Camera_Trigger__DM2) 
/* Input Buffer Disable Override */
#define Camera_Trigger_INP_DIS                (* (reg8 *) Camera_Trigger__INP_DIS)
/* LCD Common or Segment Drive */
#define Camera_Trigger_LCD_COM_SEG            (* (reg8 *) Camera_Trigger__LCD_COM_SEG)
/* Enable Segment LCD */
#define Camera_Trigger_LCD_EN                 (* (reg8 *) Camera_Trigger__LCD_EN)
/* Slew Rate Control */
#define Camera_Trigger_SLW                    (* (reg8 *) Camera_Trigger__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Camera_Trigger_PRTDSI__CAPS_SEL       (* (reg8 *) Camera_Trigger__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Camera_Trigger_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Camera_Trigger__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Camera_Trigger_PRTDSI__OE_SEL0        (* (reg8 *) Camera_Trigger__PRTDSI__OE_SEL0) 
#define Camera_Trigger_PRTDSI__OE_SEL1        (* (reg8 *) Camera_Trigger__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Camera_Trigger_PRTDSI__OUT_SEL0       (* (reg8 *) Camera_Trigger__PRTDSI__OUT_SEL0) 
#define Camera_Trigger_PRTDSI__OUT_SEL1       (* (reg8 *) Camera_Trigger__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Camera_Trigger_PRTDSI__SYNC_OUT       (* (reg8 *) Camera_Trigger__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Camera_Trigger__SIO_CFG)
    #define Camera_Trigger_SIO_HYST_EN        (* (reg8 *) Camera_Trigger__SIO_HYST_EN)
    #define Camera_Trigger_SIO_REG_HIFREQ     (* (reg8 *) Camera_Trigger__SIO_REG_HIFREQ)
    #define Camera_Trigger_SIO_CFG            (* (reg8 *) Camera_Trigger__SIO_CFG)
    #define Camera_Trigger_SIO_DIFF           (* (reg8 *) Camera_Trigger__SIO_DIFF)
#endif /* (Camera_Trigger__SIO_CFG) */

/* Interrupt Registers */
#if defined(Camera_Trigger__INTSTAT)
    #define Camera_Trigger_INTSTAT            (* (reg8 *) Camera_Trigger__INTSTAT)
    #define Camera_Trigger_SNAP               (* (reg8 *) Camera_Trigger__SNAP)
    
	#define Camera_Trigger_0_INTTYPE_REG 		(* (reg8 *) Camera_Trigger__0__INTTYPE)
#endif /* (Camera_Trigger__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Camera_Trigger_H */


/* [] END OF FILE */
