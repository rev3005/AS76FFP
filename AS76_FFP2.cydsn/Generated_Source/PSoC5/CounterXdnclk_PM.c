/*******************************************************************************
* File Name: CounterXdnclk_PM.c  
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

#include "CounterXdnclk.h"

static CounterXdnclk_backupStruct CounterXdnclk_backup;


/*******************************************************************************
* Function Name: CounterXdnclk_SaveConfig
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
*  CounterXdnclk_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CounterXdnclk_SaveConfig(void) 
{
    #if (!CounterXdnclk_UsingFixedFunction)

        CounterXdnclk_backup.CounterUdb = CounterXdnclk_ReadCounter();

        #if(!CounterXdnclk_ControlRegRemoved)
            CounterXdnclk_backup.CounterControlRegister = CounterXdnclk_ReadControlRegister();
        #endif /* (!CounterXdnclk_ControlRegRemoved) */

    #endif /* (!CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_RestoreConfig
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
*  CounterXdnclk_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CounterXdnclk_RestoreConfig(void) 
{      
    #if (!CounterXdnclk_UsingFixedFunction)

       CounterXdnclk_WriteCounter(CounterXdnclk_backup.CounterUdb);

        #if(!CounterXdnclk_ControlRegRemoved)
            CounterXdnclk_WriteControlRegister(CounterXdnclk_backup.CounterControlRegister);
        #endif /* (!CounterXdnclk_ControlRegRemoved) */

    #endif /* (!CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_Sleep
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
*  CounterXdnclk_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CounterXdnclk_Sleep(void) 
{
    #if(!CounterXdnclk_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CounterXdnclk_CTRL_ENABLE == (CounterXdnclk_CONTROL & CounterXdnclk_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CounterXdnclk_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CounterXdnclk_backup.CounterEnableState = 0u;
        }
    #else
        CounterXdnclk_backup.CounterEnableState = 1u;
        if(CounterXdnclk_backup.CounterEnableState != 0u)
        {
            CounterXdnclk_backup.CounterEnableState = 0u;
        }
    #endif /* (!CounterXdnclk_ControlRegRemoved) */
    
    CounterXdnclk_Stop();
    CounterXdnclk_SaveConfig();
}


/*******************************************************************************
* Function Name: CounterXdnclk_Wakeup
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
*  CounterXdnclk_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CounterXdnclk_Wakeup(void) 
{
    CounterXdnclk_RestoreConfig();
    #if(!CounterXdnclk_ControlRegRemoved)
        if(CounterXdnclk_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CounterXdnclk_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CounterXdnclk_ControlRegRemoved) */
    
}


/* [] END OF FILE */
