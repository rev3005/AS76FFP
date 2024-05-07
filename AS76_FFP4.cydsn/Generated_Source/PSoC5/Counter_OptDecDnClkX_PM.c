/*******************************************************************************
* File Name: Counter_OptDecDnClkX_PM.c  
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

#include "Counter_OptDecDnClkX.h"

static Counter_OptDecDnClkX_backupStruct Counter_OptDecDnClkX_backup;


/*******************************************************************************
* Function Name: Counter_OptDecDnClkX_SaveConfig
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
*  Counter_OptDecDnClkX_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_OptDecDnClkX_SaveConfig(void) 
{
    #if (!Counter_OptDecDnClkX_UsingFixedFunction)

        Counter_OptDecDnClkX_backup.CounterUdb = Counter_OptDecDnClkX_ReadCounter();

        #if(!Counter_OptDecDnClkX_ControlRegRemoved)
            Counter_OptDecDnClkX_backup.CounterControlRegister = Counter_OptDecDnClkX_ReadControlRegister();
        #endif /* (!Counter_OptDecDnClkX_ControlRegRemoved) */

    #endif /* (!Counter_OptDecDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecDnClkX_RestoreConfig
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
*  Counter_OptDecDnClkX_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecDnClkX_RestoreConfig(void) 
{      
    #if (!Counter_OptDecDnClkX_UsingFixedFunction)

       Counter_OptDecDnClkX_WriteCounter(Counter_OptDecDnClkX_backup.CounterUdb);

        #if(!Counter_OptDecDnClkX_ControlRegRemoved)
            Counter_OptDecDnClkX_WriteControlRegister(Counter_OptDecDnClkX_backup.CounterControlRegister);
        #endif /* (!Counter_OptDecDnClkX_ControlRegRemoved) */

    #endif /* (!Counter_OptDecDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecDnClkX_Sleep
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
*  Counter_OptDecDnClkX_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_OptDecDnClkX_Sleep(void) 
{
    #if(!Counter_OptDecDnClkX_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_OptDecDnClkX_CTRL_ENABLE == (Counter_OptDecDnClkX_CONTROL & Counter_OptDecDnClkX_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_OptDecDnClkX_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_OptDecDnClkX_backup.CounterEnableState = 0u;
        }
    #else
        Counter_OptDecDnClkX_backup.CounterEnableState = 1u;
        if(Counter_OptDecDnClkX_backup.CounterEnableState != 0u)
        {
            Counter_OptDecDnClkX_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_OptDecDnClkX_ControlRegRemoved) */
    
    Counter_OptDecDnClkX_Stop();
    Counter_OptDecDnClkX_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_OptDecDnClkX_Wakeup
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
*  Counter_OptDecDnClkX_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecDnClkX_Wakeup(void) 
{
    Counter_OptDecDnClkX_RestoreConfig();
    #if(!Counter_OptDecDnClkX_ControlRegRemoved)
        if(Counter_OptDecDnClkX_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_OptDecDnClkX_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_OptDecDnClkX_ControlRegRemoved) */
    
}


/* [] END OF FILE */
