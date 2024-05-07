/*******************************************************************************
* File Name: TM5160_nCS_Value_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TM5160_nCS_Value.h"

/* Check for removal by optimization */
#if !defined(TM5160_nCS_Value_Sync_ctrl_reg__REMOVED)

static TM5160_nCS_Value_BACKUP_STRUCT  TM5160_nCS_Value_backup = {0u};

    
/*******************************************************************************
* Function Name: TM5160_nCS_Value_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TM5160_nCS_Value_SaveConfig(void) 
{
    TM5160_nCS_Value_backup.controlState = TM5160_nCS_Value_Control;
}


/*******************************************************************************
* Function Name: TM5160_nCS_Value_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void TM5160_nCS_Value_RestoreConfig(void) 
{
     TM5160_nCS_Value_Control = TM5160_nCS_Value_backup.controlState;
}


/*******************************************************************************
* Function Name: TM5160_nCS_Value_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TM5160_nCS_Value_Sleep(void) 
{
    TM5160_nCS_Value_SaveConfig();
}


/*******************************************************************************
* Function Name: TM5160_nCS_Value_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TM5160_nCS_Value_Wakeup(void)  
{
    TM5160_nCS_Value_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
