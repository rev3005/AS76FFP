/*******************************************************************************
* File Name: CounterUpClkY_PM.c  
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

#include "CounterUpClkY.h"

static CounterUpClkY_backupStruct CounterUpClkY_backup;


/*******************************************************************************
* Function Name: CounterUpClkY_SaveConfig
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
*  CounterUpClkY_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterUpClkY_SaveConfig(void) 
{
    #if (!CounterUpClkY_UsingFixedFunction)

        CounterUpClkY_backup.CounterUdb = CounterUpClkY_ReadCounter();

        #if(!CounterUpClkY_ControlRegRemoved)
            CounterUpClkY_backup.CounterControlRegister = CounterUpClkY_ReadControlRegister();
        #endif /* (!CounterUpClkY_ControlRegRemoved) */

    #endif /* (!CounterUpClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkY_RestoreConfig
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
*  CounterUpClkY_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterUpClkY_RestoreConfig(void) 
{      
    #if (!CounterUpClkY_UsingFixedFunction)

       CounterUpClkY_WriteCounter(CounterUpClkY_backup.CounterUdb);

        #if(!CounterUpClkY_ControlRegRemoved)
            CounterUpClkY_WriteControlRegister(CounterUpClkY_backup.CounterControlRegister);
        #endif /* (!CounterUpClkY_ControlRegRemoved) */

    #endif /* (!CounterUpClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkY_Sleep
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
*  CounterUpClkY_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterUpClkY_Sleep(void) 
{
    #if(!CounterUpClkY_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterUpClkY_CTRL_ENABLE == (CounterUpClkY_CONTROL & CounterUpClkY_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterUpClkY_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterUpClkY_backup.CounterEnableState = 0u;
        }
    #else
        CounterUpClkY_backup.CounterEnableState = 1u;
        if(CounterUpClkY_backup.CounterEnableState != 0u)
        {
            CounterUpClkY_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterUpClkY_ControlRegRemoved) */
    
    CounterUpClkY_Stop();
    CounterUpClkY_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterUpClkY_Wakeup
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
*  CounterUpClkY_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterUpClkY_Wakeup(void) 
{
    CounterUpClkY_RestoreConfig();
    #if(!CounterUpClkY_ControlRegRemoved)
        if(CounterUpClkY_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterUpClkY_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterUpClkY_ControlRegRemoved) */
    
}


/* [] END OF FILE */
