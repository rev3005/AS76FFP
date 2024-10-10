/*******************************************************************************
* File Name: Counter_OptDecUpClkX_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Counter_OptDecUpClkX.h"

static Counter_OptDecUpClkX_backupStruct Counter_OptDecUpClkX_backup;


/*******************************************************************************
* Function Name: Counter_OptDecUpClkX_SaveConfig
********************************************************************************
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
*  Counter_OptDecUpClkX_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_OptDecUpClkX_SaveConfig(void) 
{
    #if (!Counter_OptDecUpClkX_UsingFixedFunction)

        Counter_OptDecUpClkX_backup.CounterUdb = Counter_OptDecUpClkX_ReadCounter();

        #if(!Counter_OptDecUpClkX_ControlRegRemoved)
            Counter_OptDecUpClkX_backup.CounterControlRegister = Counter_OptDecUpClkX_ReadControlRegister();
        #endif /* (!Counter_OptDecUpClkX_ControlRegRemoved) */

    #endif /* (!Counter_OptDecUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecUpClkX_RestoreConfig
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
*  Counter_OptDecUpClkX_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecUpClkX_RestoreConfig(void) 
{      
    #if (!Counter_OptDecUpClkX_UsingFixedFunction)

       Counter_OptDecUpClkX_WriteCounter(Counter_OptDecUpClkX_backup.CounterUdb);

        #if(!Counter_OptDecUpClkX_ControlRegRemoved)
            Counter_OptDecUpClkX_WriteControlRegister(Counter_OptDecUpClkX_backup.CounterControlRegister);
        #endif /* (!Counter_OptDecUpClkX_ControlRegRemoved) */

    #endif /* (!Counter_OptDecUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecUpClkX_Sleep
********************************************************************************
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
*  Counter_OptDecUpClkX_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_OptDecUpClkX_Sleep(void) 
{
    #if(!Counter_OptDecUpClkX_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_OptDecUpClkX_CTRL_ENABLE == (Counter_OptDecUpClkX_CONTROL & Counter_OptDecUpClkX_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_OptDecUpClkX_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_OptDecUpClkX_backup.CounterEnableState = 0u;
        }
    #else
        Counter_OptDecUpClkX_backup.CounterEnableState = 1u;
        if(Counter_OptDecUpClkX_backup.CounterEnableState != 0u)
        {
            Counter_OptDecUpClkX_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_OptDecUpClkX_ControlRegRemoved) */
    
    Counter_OptDecUpClkX_Stop();
    Counter_OptDecUpClkX_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_OptDecUpClkX_Wakeup
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
*  Counter_OptDecUpClkX_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecUpClkX_Wakeup(void) 
{
    Counter_OptDecUpClkX_RestoreConfig();
    #if(!Counter_OptDecUpClkX_ControlRegRemoved)
        if(Counter_OptDecUpClkX_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_OptDecUpClkX_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_OptDecUpClkX_ControlRegRemoved) */
    
}


/* [] END OF FILE */
