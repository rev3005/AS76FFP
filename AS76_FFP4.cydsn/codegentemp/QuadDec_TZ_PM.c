/*******************************************************************************
* File Name: QuadDec_TZ_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec_TZ.h"

static QuadDec_TZ_BACKUP_STRUCT QuadDec_TZ_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec_TZ_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_TZ_SaveConfig(void) 
{
    #if (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_8_BIT)
        QuadDec_TZ_Cnt8_SaveConfig();
    #else 
        /* (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_32_BIT)
         */
        QuadDec_TZ_Cnt16_SaveConfig();
    #endif /* (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_TZ_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_TZ_RestoreConfig(void) 
{
    #if (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_8_BIT)
        QuadDec_TZ_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_32_BIT) 
         */
        QuadDec_TZ_Cnt16_RestoreConfig();
    #endif /* (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_TZ_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_TZ_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_TZ_Sleep(void) 
{
    if (0u != (QuadDec_TZ_SR_AUX_CONTROL & QuadDec_TZ_INTERRUPTS_ENABLE))
    {
        QuadDec_TZ_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec_TZ_backup.enableState = 0u;
    }

    QuadDec_TZ_Stop();
    QuadDec_TZ_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_TZ_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_TZ_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec_TZ_Wakeup(void) 
{
    QuadDec_TZ_RestoreConfig();

    if (QuadDec_TZ_backup.enableState != 0u)
    {
        #if (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_8_BIT)
            QuadDec_TZ_Cnt8_Enable();
        #else 
            /* (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_32_BIT) 
            */
            QuadDec_TZ_Cnt16_Enable();
        #endif /* (QuadDec_TZ_COUNTER_SIZE == QuadDec_TZ_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec_TZ_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

