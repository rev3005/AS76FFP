/*******************************************************************************
* File Name: CounterUpClkX_PM.c  
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

#include "CounterUpClkX.h"

static CounterUpClkX_backupStruct CounterUpClkX_backup;


/*******************************************************************************
* Function Name: CounterUpClkX_SaveConfig
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
*  CounterUpClkX_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterUpClkX_SaveConfig(void) 
{
    #if (!CounterUpClkX_UsingFixedFunction)

        CounterUpClkX_backup.CounterUdb = CounterUpClkX_ReadCounter();

        #if(!CounterUpClkX_ControlRegRemoved)
            CounterUpClkX_backup.CounterControlRegister = CounterUpClkX_ReadControlRegister();
        #endif /* (!CounterUpClkX_ControlRegRemoved) */

    #endif /* (!CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_RestoreConfig
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
*  CounterUpClkX_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterUpClkX_RestoreConfig(void) 
{      
    #if (!CounterUpClkX_UsingFixedFunction)

       CounterUpClkX_WriteCounter(CounterUpClkX_backup.CounterUdb);

        #if(!CounterUpClkX_ControlRegRemoved)
            CounterUpClkX_WriteControlRegister(CounterUpClkX_backup.CounterControlRegister);
        #endif /* (!CounterUpClkX_ControlRegRemoved) */

    #endif /* (!CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_Sleep
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
*  CounterUpClkX_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterUpClkX_Sleep(void) 
{
    #if(!CounterUpClkX_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterUpClkX_CTRL_ENABLE == (CounterUpClkX_CONTROL & CounterUpClkX_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterUpClkX_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterUpClkX_backup.CounterEnableState = 0u;
        }
    #else
        CounterUpClkX_backup.CounterEnableState = 1u;
        if(CounterUpClkX_backup.CounterEnableState != 0u)
        {
            CounterUpClkX_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterUpClkX_ControlRegRemoved) */
    
    CounterUpClkX_Stop();
    CounterUpClkX_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterUpClkX_Wakeup
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
*  CounterUpClkX_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterUpClkX_Wakeup(void) 
{
    CounterUpClkX_RestoreConfig();
    #if(!CounterUpClkX_ControlRegRemoved)
        if(CounterUpClkX_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterUpClkX_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterUpClkX_ControlRegRemoved) */
    
}


/* [] END OF FILE */
