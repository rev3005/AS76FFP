/*******************************************************************************
* File Name: PWM_BarcodeCondenser_LED_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_BarcodeCondenser_LED.h"

static PWM_BarcodeCondenser_LED_backupStruct PWM_BarcodeCondenser_LED_backup;


/*******************************************************************************
* Function Name: PWM_BarcodeCondenser_LED_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_BarcodeCondenser_LED_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_BarcodeCondenser_LED_SaveConfig(void) 
{

    #if(!PWM_BarcodeCondenser_LED_UsingFixedFunction)
        #if(!PWM_BarcodeCondenser_LED_PWMModeIsCenterAligned)
            PWM_BarcodeCondenser_LED_backup.PWMPeriod = PWM_BarcodeCondenser_LED_ReadPeriod();
        #endif /* (!PWM_BarcodeCondenser_LED_PWMModeIsCenterAligned) */
        PWM_BarcodeCondenser_LED_backup.PWMUdb = PWM_BarcodeCondenser_LED_ReadCounter();
        #if (PWM_BarcodeCondenser_LED_UseStatus)
            PWM_BarcodeCondenser_LED_backup.InterruptMaskValue = PWM_BarcodeCondenser_LED_STATUS_MASK;
        #endif /* (PWM_BarcodeCondenser_LED_UseStatus) */

        #if(PWM_BarcodeCondenser_LED_DeadBandMode == PWM_BarcodeCondenser_LED__B_PWM__DBM_256_CLOCKS || \
            PWM_BarcodeCondenser_LED_DeadBandMode == PWM_BarcodeCondenser_LED__B_PWM__DBM_2_4_CLOCKS)
            PWM_BarcodeCondenser_LED_backup.PWMdeadBandValue = PWM_BarcodeCondenser_LED_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_BarcodeCondenser_LED_KillModeMinTime)
             PWM_BarcodeCondenser_LED_backup.PWMKillCounterPeriod = PWM_BarcodeCondenser_LED_ReadKillTime();
        #endif /* (PWM_BarcodeCondenser_LED_KillModeMinTime) */

        #if(PWM_BarcodeCondenser_LED_UseControl)
            PWM_BarcodeCondenser_LED_backup.PWMControlRegister = PWM_BarcodeCondenser_LED_ReadControlRegister();
        #endif /* (PWM_BarcodeCondenser_LED_UseControl) */
    #endif  /* (!PWM_BarcodeCondenser_LED_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_BarcodeCondenser_LED_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_BarcodeCondenser_LED_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_BarcodeCondenser_LED_RestoreConfig(void) 
{
        #if(!PWM_BarcodeCondenser_LED_UsingFixedFunction)
            #if(!PWM_BarcodeCondenser_LED_PWMModeIsCenterAligned)
                PWM_BarcodeCondenser_LED_WritePeriod(PWM_BarcodeCondenser_LED_backup.PWMPeriod);
            #endif /* (!PWM_BarcodeCondenser_LED_PWMModeIsCenterAligned) */

            PWM_BarcodeCondenser_LED_WriteCounter(PWM_BarcodeCondenser_LED_backup.PWMUdb);

            #if (PWM_BarcodeCondenser_LED_UseStatus)
                PWM_BarcodeCondenser_LED_STATUS_MASK = PWM_BarcodeCondenser_LED_backup.InterruptMaskValue;
            #endif /* (PWM_BarcodeCondenser_LED_UseStatus) */

            #if(PWM_BarcodeCondenser_LED_DeadBandMode == PWM_BarcodeCondenser_LED__B_PWM__DBM_256_CLOCKS || \
                PWM_BarcodeCondenser_LED_DeadBandMode == PWM_BarcodeCondenser_LED__B_PWM__DBM_2_4_CLOCKS)
                PWM_BarcodeCondenser_LED_WriteDeadTime(PWM_BarcodeCondenser_LED_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_BarcodeCondenser_LED_KillModeMinTime)
                PWM_BarcodeCondenser_LED_WriteKillTime(PWM_BarcodeCondenser_LED_backup.PWMKillCounterPeriod);
            #endif /* (PWM_BarcodeCondenser_LED_KillModeMinTime) */

            #if(PWM_BarcodeCondenser_LED_UseControl)
                PWM_BarcodeCondenser_LED_WriteControlRegister(PWM_BarcodeCondenser_LED_backup.PWMControlRegister);
            #endif /* (PWM_BarcodeCondenser_LED_UseControl) */
        #endif  /* (!PWM_BarcodeCondenser_LED_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_BarcodeCondenser_LED_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_BarcodeCondenser_LED_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_BarcodeCondenser_LED_Sleep(void) 
{
    #if(PWM_BarcodeCondenser_LED_UseControl)
        if(PWM_BarcodeCondenser_LED_CTRL_ENABLE == (PWM_BarcodeCondenser_LED_CONTROL & PWM_BarcodeCondenser_LED_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_BarcodeCondenser_LED_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_BarcodeCondenser_LED_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_BarcodeCondenser_LED_UseControl) */

    /* Stop component */
    PWM_BarcodeCondenser_LED_Stop();

    /* Save registers configuration */
    PWM_BarcodeCondenser_LED_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_BarcodeCondenser_LED_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_BarcodeCondenser_LED_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_BarcodeCondenser_LED_Wakeup(void) 
{
     /* Restore registers values */
    PWM_BarcodeCondenser_LED_RestoreConfig();

    if(PWM_BarcodeCondenser_LED_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_BarcodeCondenser_LED_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
