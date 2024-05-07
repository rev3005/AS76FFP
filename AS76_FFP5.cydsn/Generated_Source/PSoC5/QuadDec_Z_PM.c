/*******************************************************************************
* File Name: QuadDec_Z_PM.c
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

#include "QuadDec_Z.h"

static QuadDec_Z_BACKUP_STRUCT QuadDec_Z_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec_Z_SaveConfig
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
void QuadDec_Z_SaveConfig(void) 
{
    #if (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_8_BIT)
        QuadDec_Z_Cnt8_SaveConfig();
    #else 
        /* (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_32_BIT)
         */
        QuadDec_Z_Cnt16_SaveConfig();
    #endif /* (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_Z_RestoreConfig
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
void QuadDec_Z_RestoreConfig(void) 
{
    #if (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_8_BIT)
        QuadDec_Z_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_32_BIT) 
         */
        QuadDec_Z_Cnt16_RestoreConfig();
    #endif /* (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_Z_Sleep
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
*  QuadDec_Z_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_Z_Sleep(void) 
{
    if (0u != (QuadDec_Z_SR_AUX_CONTROL & QuadDec_Z_INTERRUPTS_ENABLE))
    {
        QuadDec_Z_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec_Z_backup.enableState = 0u;
    }

    QuadDec_Z_Stop();
    QuadDec_Z_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_Z_Wakeup
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
*  QuadDec_Z_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec_Z_Wakeup(void) 
{
    QuadDec_Z_RestoreConfig();

    if (QuadDec_Z_backup.enableState != 0u)
    {
        #if (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_8_BIT)
            QuadDec_Z_Cnt8_Enable();
        #else 
            /* (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_32_BIT) 
            */
            QuadDec_Z_Cnt16_Enable();
        #endif /* (QuadDec_Z_COUNTER_SIZE == QuadDec_Z_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec_Z_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

