/*******************************************************************************
* File Name: PWM_CondenserLED_PM.c
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

#include "PWM_CondenserLED.h"

static PWM_CondenserLED_backupStruct PWM_CondenserLED_backup;


/*******************************************************************************
* Function Name: PWM_CondenserLED_SaveConfig
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
*  PWM_CondenserLED_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_CondenserLED_SaveConfig(void) 
{

    #if(!PWM_CondenserLED_UsingFixedFunction)
        #if(!PWM_CondenserLED_PWMModeIsCenterAligned)
            PWM_CondenserLED_backup.PWMPeriod = PWM_CondenserLED_ReadPeriod();
        #endif /* (!PWM_CondenserLED_PWMModeIsCenterAligned) */
        PWM_CondenserLED_backup.PWMUdb = PWM_CondenserLED_ReadCounter();
        #if (PWM_CondenserLED_UseStatus)
            PWM_CondenserLED_backup.InterruptMaskValue = PWM_CondenserLED_STATUS_MASK;
        #endif /* (PWM_CondenserLED_UseStatus) */

        #if(PWM_CondenserLED_DeadBandMode == PWM_CondenserLED__B_PWM__DBM_256_CLOCKS || \
            PWM_CondenserLED_DeadBandMode == PWM_CondenserLED__B_PWM__DBM_2_4_CLOCKS)
            PWM_CondenserLED_backup.PWMdeadBandValue = PWM_CondenserLED_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_CondenserLED_KillModeMinTime)
             PWM_CondenserLED_backup.PWMKillCounterPeriod = PWM_CondenserLED_ReadKillTime();
        #endif /* (PWM_CondenserLED_KillModeMinTime) */

        #if(PWM_CondenserLED_UseControl)
            PWM_CondenserLED_backup.PWMControlRegister = PWM_CondenserLED_ReadControlRegister();
        #endif /* (PWM_CondenserLED_UseControl) */
    #endif  /* (!PWM_CondenserLED_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_CondenserLED_RestoreConfig
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
*  PWM_CondenserLED_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_CondenserLED_RestoreConfig(void) 
{
        #if(!PWM_CondenserLED_UsingFixedFunction)
            #if(!PWM_CondenserLED_PWMModeIsCenterAligned)
                PWM_CondenserLED_WritePeriod(PWM_CondenserLED_backup.PWMPeriod);
            #endif /* (!PWM_CondenserLED_PWMModeIsCenterAligned) */

            PWM_CondenserLED_WriteCounter(PWM_CondenserLED_backup.PWMUdb);

            #if (PWM_CondenserLED_UseStatus)
                PWM_CondenserLED_STATUS_MASK = PWM_CondenserLED_backup.InterruptMaskValue;
            #endif /* (PWM_CondenserLED_UseStatus) */

            #if(PWM_CondenserLED_DeadBandMode == PWM_CondenserLED__B_PWM__DBM_256_CLOCKS || \
                PWM_CondenserLED_DeadBandMode == PWM_CondenserLED__B_PWM__DBM_2_4_CLOCKS)
                PWM_CondenserLED_WriteDeadTime(PWM_CondenserLED_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_CondenserLED_KillModeMinTime)
                PWM_CondenserLED_WriteKillTime(PWM_CondenserLED_backup.PWMKillCounterPeriod);
            #endif /* (PWM_CondenserLED_KillModeMinTime) */

            #if(PWM_CondenserLED_UseControl)
                PWM_CondenserLED_WriteControlRegister(PWM_CondenserLED_backup.PWMControlRegister);
            #endif /* (PWM_CondenserLED_UseControl) */
        #endif  /* (!PWM_CondenserLED_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_CondenserLED_Sleep
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
*  PWM_CondenserLED_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_CondenserLED_Sleep(void) 
{
    #if(PWM_CondenserLED_UseControl)
        if(PWM_CondenserLED_CTRL_ENABLE == (PWM_CondenserLED_CONTROL & PWM_CondenserLED_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_CondenserLED_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_CondenserLED_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_CondenserLED_UseControl) */

    /* Stop component */
    PWM_CondenserLED_Stop();

    /* Save registers configuration */
    PWM_CondenserLED_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_CondenserLED_Wakeup
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
*  PWM_CondenserLED_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_CondenserLED_Wakeup(void) 
{
     /* Restore registers values */
    PWM_CondenserLED_RestoreConfig();

    if(PWM_CondenserLED_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_CondenserLED_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
