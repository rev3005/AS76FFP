/*******************************************************************************
* File Name: Counter_OptDecUpClkY_PM.c  
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

#include "Counter_OptDecUpClkY.h"

static Counter_OptDecUpClkY_backupStruct Counter_OptDecUpClkY_backup;


/*******************************************************************************
* Function Name: Counter_OptDecUpClkY_SaveConfig
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
*  Counter_OptDecUpClkY_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_OptDecUpClkY_SaveConfig(void) 
{
    #if (!Counter_OptDecUpClkY_UsingFixedFunction)

        Counter_OptDecUpClkY_backup.CounterUdb = Counter_OptDecUpClkY_ReadCounter();

        #if(!Counter_OptDecUpClkY_ControlRegRemoved)
            Counter_OptDecUpClkY_backup.CounterControlRegister = Counter_OptDecUpClkY_ReadControlRegister();
        #endif /* (!Counter_OptDecUpClkY_ControlRegRemoved) */

    #endif /* (!Counter_OptDecUpClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecUpClkY_RestoreConfig
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
*  Counter_OptDecUpClkY_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecUpClkY_RestoreConfig(void) 
{      
    #if (!Counter_OptDecUpClkY_UsingFixedFunction)

       Counter_OptDecUpClkY_WriteCounter(Counter_OptDecUpClkY_backup.CounterUdb);

        #if(!Counter_OptDecUpClkY_ControlRegRemoved)
            Counter_OptDecUpClkY_WriteControlRegister(Counter_OptDecUpClkY_backup.CounterControlRegister);
        #endif /* (!Counter_OptDecUpClkY_ControlRegRemoved) */

    #endif /* (!Counter_OptDecUpClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_OptDecUpClkY_Sleep
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
*  Counter_OptDecUpClkY_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_OptDecUpClkY_Sleep(void) 
{
    #if(!Counter_OptDecUpClkY_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_OptDecUpClkY_CTRL_ENABLE == (Counter_OptDecUpClkY_CONTROL & Counter_OptDecUpClkY_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_OptDecUpClkY_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_OptDecUpClkY_backup.CounterEnableState = 0u;
        }
    #else
        Counter_OptDecUpClkY_backup.CounterEnableState = 1u;
        if(Counter_OptDecUpClkY_backup.CounterEnableState != 0u)
        {
            Counter_OptDecUpClkY_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_OptDecUpClkY_ControlRegRemoved) */
    
    Counter_OptDecUpClkY_Stop();
    Counter_OptDecUpClkY_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_OptDecUpClkY_Wakeup
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
*  Counter_OptDecUpClkY_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_OptDecUpClkY_Wakeup(void) 
{
    Counter_OptDecUpClkY_RestoreConfig();
    #if(!Counter_OptDecUpClkY_ControlRegRemoved)
        if(Counter_OptDecUpClkY_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_OptDecUpClkY_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_OptDecUpClkY_ControlRegRemoved) */
    
}


/* [] END OF FILE */
