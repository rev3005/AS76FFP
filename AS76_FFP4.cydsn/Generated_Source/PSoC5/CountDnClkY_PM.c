/*******************************************************************************
* File Name: CountDnClkY_PM.c  
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

#include "CountDnClkY.h"

static CountDnClkY_backupStruct CountDnClkY_backup;


/*******************************************************************************
* Function Name: CountDnClkY_SaveConfig
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
*  CountDnClkY_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CountDnClkY_SaveConfig(void) 
{
    #if (!CountDnClkY_UsingFixedFunction)

        CountDnClkY_backup.CounterUdb = CountDnClkY_ReadCounter();

        #if(!CountDnClkY_ControlRegRemoved)
            CountDnClkY_backup.CounterControlRegister = CountDnClkY_ReadControlRegister();
        #endif /* (!CountDnClkY_ControlRegRemoved) */

    #endif /* (!CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_RestoreConfig
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
*  CountDnClkY_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CountDnClkY_RestoreConfig(void) 
{      
    #if (!CountDnClkY_UsingFixedFunction)

       CountDnClkY_WriteCounter(CountDnClkY_backup.CounterUdb);

        #if(!CountDnClkY_ControlRegRemoved)
            CountDnClkY_WriteControlRegister(CountDnClkY_backup.CounterControlRegister);
        #endif /* (!CountDnClkY_ControlRegRemoved) */

    #endif /* (!CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_Sleep
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
*  CountDnClkY_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CountDnClkY_Sleep(void) 
{
    #if(!CountDnClkY_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CountDnClkY_CTRL_ENABLE == (CountDnClkY_CONTROL & CountDnClkY_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CountDnClkY_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CountDnClkY_backup.CounterEnableState = 0u;
        }
    #else
        CountDnClkY_backup.CounterEnableState = 1u;
        if(CountDnClkY_backup.CounterEnableState != 0u)
        {
            CountDnClkY_backup.CounterEnableState = 0u;
        }
    #endif /* (!CountDnClkY_ControlRegRemoved) */
    
    CountDnClkY_Stop();
    CountDnClkY_SaveConfig();
}


/*******************************************************************************
* Function Name: CountDnClkY_Wakeup
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
*  CountDnClkY_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CountDnClkY_Wakeup(void) 
{
    CountDnClkY_RestoreConfig();
    #if(!CountDnClkY_ControlRegRemoved)
        if(CountDnClkY_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CountDnClkY_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CountDnClkY_ControlRegRemoved) */
    
}


/* [] END OF FILE */
