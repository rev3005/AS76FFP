/*******************************************************************************
* File Name: CounterDnClkX_PM.c  
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

#include "CounterDnClkX.h"

static CounterDnClkX_backupStruct CounterDnClkX_backup;


/*******************************************************************************
* Function Name: CounterDnClkX_SaveConfig
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
*  CounterDnClkX_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterDnClkX_SaveConfig(void) 
{
    #if (!CounterDnClkX_UsingFixedFunction)

        CounterDnClkX_backup.CounterUdb = CounterDnClkX_ReadCounter();

        #if(!CounterDnClkX_ControlRegRemoved)
            CounterDnClkX_backup.CounterControlRegister = CounterDnClkX_ReadControlRegister();
        #endif /* (!CounterDnClkX_ControlRegRemoved) */

    #endif /* (!CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_RestoreConfig
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
*  CounterDnClkX_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterDnClkX_RestoreConfig(void) 
{      
    #if (!CounterDnClkX_UsingFixedFunction)

       CounterDnClkX_WriteCounter(CounterDnClkX_backup.CounterUdb);

        #if(!CounterDnClkX_ControlRegRemoved)
            CounterDnClkX_WriteControlRegister(CounterDnClkX_backup.CounterControlRegister);
        #endif /* (!CounterDnClkX_ControlRegRemoved) */

    #endif /* (!CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_Sleep
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
*  CounterDnClkX_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterDnClkX_Sleep(void) 
{
    #if(!CounterDnClkX_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterDnClkX_CTRL_ENABLE == (CounterDnClkX_CONTROL & CounterDnClkX_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterDnClkX_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterDnClkX_backup.CounterEnableState = 0u;
        }
    #else
        CounterDnClkX_backup.CounterEnableState = 1u;
        if(CounterDnClkX_backup.CounterEnableState != 0u)
        {
            CounterDnClkX_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterDnClkX_ControlRegRemoved) */
    
    CounterDnClkX_Stop();
    CounterDnClkX_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterDnClkX_Wakeup
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
*  CounterDnClkX_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterDnClkX_Wakeup(void) 
{
    CounterDnClkX_RestoreConfig();
    #if(!CounterDnClkX_ControlRegRemoved)
        if(CounterDnClkX_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterDnClkX_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterDnClkX_ControlRegRemoved) */
    
}


/* [] END OF FILE */
