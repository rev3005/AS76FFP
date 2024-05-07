/*******************************************************************************
* File Name: CounterDnClkY_PM.c  
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

#include "CounterDnClkY.h"

static CounterDnClkY_backupStruct CounterDnClkY_backup;


/*******************************************************************************
* Function Name: CounterDnClkY_SaveConfig
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
*  CounterDnClkY_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterDnClkY_SaveConfig(void) 
{
    #if (!CounterDnClkY_UsingFixedFunction)

        CounterDnClkY_backup.CounterUdb = CounterDnClkY_ReadCounter();

        #if(!CounterDnClkY_ControlRegRemoved)
            CounterDnClkY_backup.CounterControlRegister = CounterDnClkY_ReadControlRegister();
        #endif /* (!CounterDnClkY_ControlRegRemoved) */

    #endif /* (!CounterDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkY_RestoreConfig
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
*  CounterDnClkY_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterDnClkY_RestoreConfig(void) 
{      
    #if (!CounterDnClkY_UsingFixedFunction)

       CounterDnClkY_WriteCounter(CounterDnClkY_backup.CounterUdb);

        #if(!CounterDnClkY_ControlRegRemoved)
            CounterDnClkY_WriteControlRegister(CounterDnClkY_backup.CounterControlRegister);
        #endif /* (!CounterDnClkY_ControlRegRemoved) */

    #endif /* (!CounterDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkY_Sleep
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
*  CounterDnClkY_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterDnClkY_Sleep(void) 
{
    #if(!CounterDnClkY_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterDnClkY_CTRL_ENABLE == (CounterDnClkY_CONTROL & CounterDnClkY_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterDnClkY_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterDnClkY_backup.CounterEnableState = 0u;
        }
    #else
        CounterDnClkY_backup.CounterEnableState = 1u;
        if(CounterDnClkY_backup.CounterEnableState != 0u)
        {
            CounterDnClkY_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterDnClkY_ControlRegRemoved) */
    
    CounterDnClkY_Stop();
    CounterDnClkY_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterDnClkY_Wakeup
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
*  CounterDnClkY_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterDnClkY_Wakeup(void) 
{
    CounterDnClkY_RestoreConfig();
    #if(!CounterDnClkY_ControlRegRemoved)
        if(CounterDnClkY_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterDnClkY_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterDnClkY_ControlRegRemoved) */
    
}


/* [] END OF FILE */
