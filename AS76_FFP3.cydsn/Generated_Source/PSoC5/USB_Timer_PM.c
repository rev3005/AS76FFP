/*******************************************************************************
* File Name: USB_Timer_PM.c
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

#include "USB_Timer.h"

static USB_Timer_backupStruct USB_Timer_backup;


/*******************************************************************************
* Function Name: USB_Timer_SaveConfig
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
*  USB_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void USB_Timer_SaveConfig(void) 
{
    #if (!USB_Timer_UsingFixedFunction)
        USB_Timer_backup.TimerUdb = USB_Timer_ReadCounter();
        USB_Timer_backup.InterruptMaskValue = USB_Timer_STATUS_MASK;
        #if (USB_Timer_UsingHWCaptureCounter)
            USB_Timer_backup.TimerCaptureCounter = USB_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!USB_Timer_UDB_CONTROL_REG_REMOVED)
            USB_Timer_backup.TimerControlRegister = USB_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: USB_Timer_RestoreConfig
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
*  USB_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void USB_Timer_RestoreConfig(void) 
{   
    #if (!USB_Timer_UsingFixedFunction)

        USB_Timer_WriteCounter(USB_Timer_backup.TimerUdb);
        USB_Timer_STATUS_MASK =USB_Timer_backup.InterruptMaskValue;
        #if (USB_Timer_UsingHWCaptureCounter)
            USB_Timer_SetCaptureCount(USB_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!USB_Timer_UDB_CONTROL_REG_REMOVED)
            USB_Timer_WriteControlRegister(USB_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: USB_Timer_Sleep
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
*  USB_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void USB_Timer_Sleep(void) 
{
    #if(!USB_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(USB_Timer_CTRL_ENABLE == (USB_Timer_CONTROL & USB_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            USB_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            USB_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    USB_Timer_Stop();
    USB_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: USB_Timer_Wakeup
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
*  USB_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void USB_Timer_Wakeup(void) 
{
    USB_Timer_RestoreConfig();
    #if(!USB_Timer_UDB_CONTROL_REG_REMOVED)
        if(USB_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                USB_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
