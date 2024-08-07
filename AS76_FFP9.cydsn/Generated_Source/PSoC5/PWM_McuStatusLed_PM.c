/*******************************************************************************
* File Name: PWM_McuStatusLed_PM.c
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

#include "PWM_McuStatusLed.h"

static PWM_McuStatusLed_backupStruct PWM_McuStatusLed_backup;


/*******************************************************************************
* Function Name: PWM_McuStatusLed_SaveConfig
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
*  PWM_McuStatusLed_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_McuStatusLed_SaveConfig(void) 
{

    #if(!PWM_McuStatusLed_UsingFixedFunction)
        #if(!PWM_McuStatusLed_PWMModeIsCenterAligned)
            PWM_McuStatusLed_backup.PWMPeriod = PWM_McuStatusLed_ReadPeriod();
        #endif /* (!PWM_McuStatusLed_PWMModeIsCenterAligned) */
        PWM_McuStatusLed_backup.PWMUdb = PWM_McuStatusLed_ReadCounter();
        #if (PWM_McuStatusLed_UseStatus)
            PWM_McuStatusLed_backup.InterruptMaskValue = PWM_McuStatusLed_STATUS_MASK;
        #endif /* (PWM_McuStatusLed_UseStatus) */

        #if(PWM_McuStatusLed_DeadBandMode == PWM_McuStatusLed__B_PWM__DBM_256_CLOCKS || \
            PWM_McuStatusLed_DeadBandMode == PWM_McuStatusLed__B_PWM__DBM_2_4_CLOCKS)
            PWM_McuStatusLed_backup.PWMdeadBandValue = PWM_McuStatusLed_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_McuStatusLed_KillModeMinTime)
             PWM_McuStatusLed_backup.PWMKillCounterPeriod = PWM_McuStatusLed_ReadKillTime();
        #endif /* (PWM_McuStatusLed_KillModeMinTime) */

        #if(PWM_McuStatusLed_UseControl)
            PWM_McuStatusLed_backup.PWMControlRegister = PWM_McuStatusLed_ReadControlRegister();
        #endif /* (PWM_McuStatusLed_UseControl) */
    #endif  /* (!PWM_McuStatusLed_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_McuStatusLed_RestoreConfig
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
*  PWM_McuStatusLed_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_McuStatusLed_RestoreConfig(void) 
{
        #if(!PWM_McuStatusLed_UsingFixedFunction)
            #if(!PWM_McuStatusLed_PWMModeIsCenterAligned)
                PWM_McuStatusLed_WritePeriod(PWM_McuStatusLed_backup.PWMPeriod);
            #endif /* (!PWM_McuStatusLed_PWMModeIsCenterAligned) */

            PWM_McuStatusLed_WriteCounter(PWM_McuStatusLed_backup.PWMUdb);

            #if (PWM_McuStatusLed_UseStatus)
                PWM_McuStatusLed_STATUS_MASK = PWM_McuStatusLed_backup.InterruptMaskValue;
            #endif /* (PWM_McuStatusLed_UseStatus) */

            #if(PWM_McuStatusLed_DeadBandMode == PWM_McuStatusLed__B_PWM__DBM_256_CLOCKS || \
                PWM_McuStatusLed_DeadBandMode == PWM_McuStatusLed__B_PWM__DBM_2_4_CLOCKS)
                PWM_McuStatusLed_WriteDeadTime(PWM_McuStatusLed_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_McuStatusLed_KillModeMinTime)
                PWM_McuStatusLed_WriteKillTime(PWM_McuStatusLed_backup.PWMKillCounterPeriod);
            #endif /* (PWM_McuStatusLed_KillModeMinTime) */

            #if(PWM_McuStatusLed_UseControl)
                PWM_McuStatusLed_WriteControlRegister(PWM_McuStatusLed_backup.PWMControlRegister);
            #endif /* (PWM_McuStatusLed_UseControl) */
        #endif  /* (!PWM_McuStatusLed_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_McuStatusLed_Sleep
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
*  PWM_McuStatusLed_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_McuStatusLed_Sleep(void) 
{
    #if(PWM_McuStatusLed_UseControl)
        if(PWM_McuStatusLed_CTRL_ENABLE == (PWM_McuStatusLed_CONTROL & PWM_McuStatusLed_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_McuStatusLed_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_McuStatusLed_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_McuStatusLed_UseControl) */

    /* Stop component */
    PWM_McuStatusLed_Stop();

    /* Save registers configuration */
    PWM_McuStatusLed_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_McuStatusLed_Wakeup
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
*  PWM_McuStatusLed_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_McuStatusLed_Wakeup(void) 
{
     /* Restore registers values */
    PWM_McuStatusLed_RestoreConfig();

    if(PWM_McuStatusLed_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_McuStatusLed_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
