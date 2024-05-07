/*******************************************************************************
* File Name: Counter_OptDecDnClkY_PM.c  
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

#include "Counter_OptDecDnClkY.h"

static Counter_OptDecDnClkY_backupStruct Counter_OptDecDnClkY_backup;


/*******************************************************************************
* Function Name: Counter_OptDecDnClkY_SaveConfig
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
*  Counter_OptDecDnClkY_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_OptDecDnClkY_SaveConfig(void) 
{
    #if (!Counter_OptDecDnClkY_UsingFixedFunction)

        Counter_OptDecDnClkY_backup.CounterUdb = Counter_OptDecDnClkY_ReadCounter();

        #if(!Counter_OptDecDnClkY_ControlRegRemoved)
            Counter_OptDecDnClkY_backup.CounterControlRegister = Counter_OptDecDnClkY_ReadControlRegister();
        #endif /* (!Counter_OptDecDnClkY_ControlRegRemoved) */

    #endif /* (!Counter_OptDecDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecDnClkY_RestoreConfig
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
*  Counter_OptDecDnClkY_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecDnClkY_RestoreConfig(void) 
{      
    #if (!Counter_OptDecDnClkY_UsingFixedFunction)

       Counter_OptDecDnClkY_WriteCounter(Counter_OptDecDnClkY_backup.CounterUdb);

        #if(!Counter_OptDecDnClkY_ControlRegRemoved)
            Counter_OptDecDnClkY_WriteControlRegister(Counter_OptDecDnClkY_backup.CounterControlRegister);
        #endif /* (!Counter_OptDecDnClkY_ControlRegRemoved) */

    #endif /* (!Counter_OptDecDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecDnClkY_Sleep
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
*  Counter_OptDecDnClkY_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_OptDecDnClkY_Sleep(void) 
{
    #if(!Counter_OptDecDnClkY_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_OptDecDnClkY_CTRL_ENABLE == (Counter_OptDecDnClkY_CONTROL & Counter_OptDecDnClkY_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_OptDecDnClkY_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_OptDecDnClkY_backup.CounterEnableState = 0u;
        }
    #else
        Counter_OptDecDnClkY_backup.CounterEnableState = 1u;
        if(Counter_OptDecDnClkY_backup.CounterEnableState != 0u)
        {
            Counter_OptDecDnClkY_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_OptDecDnClkY_ControlRegRemoved) */
    
    Counter_OptDecDnClkY_Stop();
    Counter_OptDecDnClkY_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_OptDecDnClkY_Wakeup
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
*  Counter_OptDecDnClkY_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecDnClkY_Wakeup(void) 
{
    Counter_OptDecDnClkY_RestoreConfig();
    #if(!Counter_OptDecDnClkY_ControlRegRemoved)
        if(Counter_OptDecDnClkY_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_OptDecDnClkY_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_OptDecDnClkY_ControlRegRemoved) */
    
}


/* [] END OF FILE */
