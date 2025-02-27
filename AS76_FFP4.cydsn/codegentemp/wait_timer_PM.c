/*******************************************************************************
* File Name: wait_timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "wait_timer.h"

static wait_timer_backupStruct wait_timer_backup;


/*******************************************************************************
* Function Name: wait_timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  wait_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void wait_timer_SaveConfig(void) 
{
    #if (!wait_timer_UsingFixedFunction)
        wait_timer_backup.TimerUdb = wait_timer_ReadCounter();
        wait_timer_backup.InterruptMaskValue = wait_timer_STATUS_MASK;
        #if (wait_timer_UsingHWCaptureCounter)
            wait_timer_backup.TimerCaptureCounter = wait_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!wait_timer_UDB_CONTROL_REG_REMOVED)
            wait_timer_backup.TimerControlRegister = wait_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: wait_timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  wait_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void wait_timer_RestoreConfig(void) 
{   
    #if (!wait_timer_UsingFixedFunction)

        wait_timer_WriteCounter(wait_timer_backup.TimerUdb);
        wait_timer_STATUS_MASK =wait_timer_backup.InterruptMaskValue;
        #if (wait_timer_UsingHWCaptureCounter)
            wait_timer_SetCaptureCount(wait_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!wait_timer_UDB_CONTROL_REG_REMOVED)
            wait_timer_WriteControlRegister(wait_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: wait_timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  wait_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void wait_timer_Sleep(void) 
{
    #if(!wait_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(wait_timer_CTRL_ENABLE == (wait_timer_CONTROL & wait_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            wait_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            wait_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    wait_timer_Stop();
    wait_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: wait_timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  wait_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void wait_timer_Wakeup(void) 
{
    wait_timer_RestoreConfig();
    #if(!wait_timer_UDB_CONTROL_REG_REMOVED)
        if(wait_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                wait_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
