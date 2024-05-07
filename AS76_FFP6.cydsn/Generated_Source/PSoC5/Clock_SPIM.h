/*******************************************************************************
* File Name: Clock_SPIM.h
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

#if !defined(CY_CLOCK_Clock_SPIM_H)
#define CY_CLOCK_Clock_SPIM_H

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

void Clock_SPIM_Start(void) ;
void Clock_SPIM_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clock_SPIM_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Clock_SPIM_StandbyPower(uint8 state) ;
void Clock_SPIM_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Clock_SPIM_GetDividerRegister(void) ;
void Clock_SPIM_SetModeRegister(uint8 modeBitMask) ;
void Clock_SPIM_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clock_SPIM_GetModeRegister(void) ;
void Clock_SPIM_SetSourceRegister(uint8 clkSource) ;
uint8 Clock_SPIM_GetSourceRegister(void) ;
#if defined(Clock_SPIM__CFG3)
void Clock_SPIM_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clock_SPIM_GetPhaseRegister(void) ;
#endif /* defined(Clock_SPIM__CFG3) */

#define Clock_SPIM_Enable()                       Clock_SPIM_Start()
#define Clock_SPIM_Disable()                      Clock_SPIM_Stop()
#define Clock_SPIM_SetDivider(clkDivider)         Clock_SPIM_SetDividerRegister(clkDivider, 1u)
#define Clock_SPIM_SetDividerValue(clkDivider)    Clock_SPIM_SetDividerRegister((clkDivider) - 1u, 1u)
#define Clock_SPIM_SetMode(clkMode)               Clock_SPIM_SetModeRegister(clkMode)
#define Clock_SPIM_SetSource(clkSource)           Clock_SPIM_SetSourceRegister(clkSource)
#if defined(Clock_SPIM__CFG3)
#define Clock_SPIM_SetPhase(clkPhase)             Clock_SPIM_SetPhaseRegister(clkPhase)
#define Clock_SPIM_SetPhaseValue(clkPhase)        Clock_SPIM_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Clock_SPIM__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clock_SPIM_CLKEN              (* (reg8 *) Clock_SPIM__PM_ACT_CFG)
#define Clock_SPIM_CLKEN_PTR          ((reg8 *) Clock_SPIM__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clock_SPIM_CLKSTBY            (* (reg8 *) Clock_SPIM__PM_STBY_CFG)
#define Clock_SPIM_CLKSTBY_PTR        ((reg8 *) Clock_SPIM__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clock_SPIM_DIV_LSB            (* (reg8 *) Clock_SPIM__CFG0)
#define Clock_SPIM_DIV_LSB_PTR        ((reg8 *) Clock_SPIM__CFG0)
#define Clock_SPIM_DIV_PTR            ((reg16 *) Clock_SPIM__CFG0)

/* Clock MSB divider configuration register. */
#define Clock_SPIM_DIV_MSB            (* (reg8 *) Clock_SPIM__CFG1)
#define Clock_SPIM_DIV_MSB_PTR        ((reg8 *) Clock_SPIM__CFG1)

/* Mode and source configuration register */
#define Clock_SPIM_MOD_SRC            (* (reg8 *) Clock_SPIM__CFG2)
#define Clock_SPIM_MOD_SRC_PTR        ((reg8 *) Clock_SPIM__CFG2)

#if defined(Clock_SPIM__CFG3)
/* Analog clock phase configuration register */
#define Clock_SPIM_PHASE              (* (reg8 *) Clock_SPIM__CFG3)
#define Clock_SPIM_PHASE_PTR          ((reg8 *) Clock_SPIM__CFG3)
#endif /* defined(Clock_SPIM__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clock_SPIM_CLKEN_MASK         Clock_SPIM__PM_ACT_MSK
#define Clock_SPIM_CLKSTBY_MASK       Clock_SPIM__PM_STBY_MSK

/* CFG2 field masks */
#define Clock_SPIM_SRC_SEL_MSK        Clock_SPIM__CFG2_SRC_SEL_MASK
#define Clock_SPIM_MODE_MASK          (~(Clock_SPIM_SRC_SEL_MSK))

#if defined(Clock_SPIM__CFG3)
/* CFG3 phase mask */
#define Clock_SPIM_PHASE_MASK         Clock_SPIM__CFG3_PHASE_DLY_MASK
#endif /* defined(Clock_SPIM__CFG3) */

#endif /* CY_CLOCK_Clock_SPIM_H */


/* [] END OF FILE */
