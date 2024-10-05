/*******************************************************************************
* File Name: clockCounter.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_clockCounter_H)
#define CY_CLOCK_clockCounter_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void clockCounter_Start(void) ;
void clockCounter_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clockCounter_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clockCounter_StandbyPower(uint8 state) ;
void clockCounter_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clockCounter_GetDividerRegister(void) ;
void clockCounter_SetModeRegister(uint8 modeBitMask) ;
void clockCounter_ClearModeRegister(uint8 modeBitMask) ;
uint8 clockCounter_GetModeRegister(void) ;
void clockCounter_SetSourceRegister(uint8 clkSource) ;
uint8 clockCounter_GetSourceRegister(void) ;
#if defined(clockCounter__CFG3)
void clockCounter_SetPhaseRegister(uint8 clkPhase) ;
uint8 clockCounter_GetPhaseRegister(void) ;
#endif /* defined(clockCounter__CFG3) */

#define clockCounter_Enable()                       clockCounter_Start()
#define clockCounter_Disable()                      clockCounter_Stop()
#define clockCounter_SetDivider(clkDivider)         clockCounter_SetDividerRegister(clkDivider, 1u)
#define clockCounter_SetDividerValue(clkDivider)    clockCounter_SetDividerRegister((clkDivider) - 1u, 1u)
#define clockCounter_SetMode(clkMode)               clockCounter_SetModeRegister(clkMode)
#define clockCounter_SetSource(clkSource)           clockCounter_SetSourceRegister(clkSource)
#if defined(clockCounter__CFG3)
#define clockCounter_SetPhase(clkPhase)             clockCounter_SetPhaseRegister(clkPhase)
#define clockCounter_SetPhaseValue(clkPhase)        clockCounter_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clockCounter__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clockCounter_CLKEN              (* (reg8 *) clockCounter__PM_ACT_CFG)
#define clockCounter_CLKEN_PTR          ((reg8 *) clockCounter__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clockCounter_CLKSTBY            (* (reg8 *) clockCounter__PM_STBY_CFG)
#define clockCounter_CLKSTBY_PTR        ((reg8 *) clockCounter__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clockCounter_DIV_LSB            (* (reg8 *) clockCounter__CFG0)
#define clockCounter_DIV_LSB_PTR        ((reg8 *) clockCounter__CFG0)
#define clockCounter_DIV_PTR            ((reg16 *) clockCounter__CFG0)

/* Clock MSB divider configuration register. */
#define clockCounter_DIV_MSB            (* (reg8 *) clockCounter__CFG1)
#define clockCounter_DIV_MSB_PTR        ((reg8 *) clockCounter__CFG1)

/* Mode and source configuration register */
#define clockCounter_MOD_SRC            (* (reg8 *) clockCounter__CFG2)
#define clockCounter_MOD_SRC_PTR        ((reg8 *) clockCounter__CFG2)

#if defined(clockCounter__CFG3)
/* Analog clock phase configuration register */
#define clockCounter_PHASE              (* (reg8 *) clockCounter__CFG3)
#define clockCounter_PHASE_PTR          ((reg8 *) clockCounter__CFG3)
#endif /* defined(clockCounter__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clockCounter_CLKEN_MASK         clockCounter__PM_ACT_MSK
#define clockCounter_CLKSTBY_MASK       clockCounter__PM_STBY_MSK

/* CFG2 field masks */
#define clockCounter_SRC_SEL_MSK        clockCounter__CFG2_SRC_SEL_MASK
#define clockCounter_MODE_MASK          (~(clockCounter_SRC_SEL_MSK))

#if defined(clockCounter__CFG3)
/* CFG3 phase mask */
#define clockCounter_PHASE_MASK         clockCounter__CFG3_PHASE_DLY_MASK
#endif /* defined(clockCounter__CFG3) */

#endif /* CY_CLOCK_clockCounter_H */


/* [] END OF FILE */
