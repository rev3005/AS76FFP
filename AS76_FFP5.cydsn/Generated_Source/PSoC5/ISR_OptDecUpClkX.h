/*******************************************************************************
* File Name: ISR_OptDecUpClkX.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ISR_OptDecUpClkX_H)
#define CY_ISR_ISR_OptDecUpClkX_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_OptDecUpClkX_Start(void);
void ISR_OptDecUpClkX_StartEx(cyisraddress address);
void ISR_OptDecUpClkX_Stop(void);

CY_ISR_PROTO(ISR_OptDecUpClkX_Interrupt);

void ISR_OptDecUpClkX_SetVector(cyisraddress address);
cyisraddress ISR_OptDecUpClkX_GetVector(void);

void ISR_OptDecUpClkX_SetPriority(uint8 priority);
uint8 ISR_OptDecUpClkX_GetPriority(void);

void ISR_OptDecUpClkX_Enable(void);
uint8 ISR_OptDecUpClkX_GetState(void);
void ISR_OptDecUpClkX_Disable(void);

void ISR_OptDecUpClkX_SetPending(void);
void ISR_OptDecUpClkX_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_OptDecUpClkX ISR. */
#define ISR_OptDecUpClkX_INTC_VECTOR            ((reg32 *) ISR_OptDecUpClkX__INTC_VECT)

/* Address of the ISR_OptDecUpClkX ISR priority. */
#define ISR_OptDecUpClkX_INTC_PRIOR             ((reg8 *) ISR_OptDecUpClkX__INTC_PRIOR_REG)

/* Priority of the ISR_OptDecUpClkX interrupt. */
#define ISR_OptDecUpClkX_INTC_PRIOR_NUMBER      ISR_OptDecUpClkX__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_OptDecUpClkX interrupt. */
#define ISR_OptDecUpClkX_INTC_SET_EN            ((reg32 *) ISR_OptDecUpClkX__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_OptDecUpClkX interrupt. */
#define ISR_OptDecUpClkX_INTC_CLR_EN            ((reg32 *) ISR_OptDecUpClkX__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_OptDecUpClkX interrupt state to pending. */
#define ISR_OptDecUpClkX_INTC_SET_PD            ((reg32 *) ISR_OptDecUpClkX__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_OptDecUpClkX interrupt. */
#define ISR_OptDecUpClkX_INTC_CLR_PD            ((reg32 *) ISR_OptDecUpClkX__INTC_CLR_PD_REG)


#endif /* CY_ISR_ISR_OptDecUpClkX_H */


/* [] END OF FILE */
