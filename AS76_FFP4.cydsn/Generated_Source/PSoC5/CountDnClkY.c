/*******************************************************************************
* File Name: CountDnClkY.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 CountDnClkY_initVar = 0u;


/*******************************************************************************
* Function Name: CountDnClkY_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void CountDnClkY_Init(void) 
{
        #if (!CountDnClkY_UsingFixedFunction && !CountDnClkY_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CountDnClkY_UsingFixedFunction && !CountDnClkY_ControlRegRemoved) */
        
        #if(!CountDnClkY_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CountDnClkY_interruptState;
        #endif /* (!CountDnClkY_UsingFixedFunction) */
        
        #if (CountDnClkY_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CountDnClkY_CONTROL &= CountDnClkY_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CountDnClkY_CONTROL2 &= ((uint8)(~CountDnClkY_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CountDnClkY_CONTROL3 &= ((uint8)(~CountDnClkY_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CountDnClkY_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CountDnClkY_CONTROL |= CountDnClkY_ONESHOT;
            #endif /* (CountDnClkY_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CountDnClkY_CONTROL2 |= CountDnClkY_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CountDnClkY_RT1 &= ((uint8)(~CountDnClkY_RT1_MASK));
            CountDnClkY_RT1 |= CountDnClkY_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CountDnClkY_RT1 &= ((uint8)(~CountDnClkY_SYNCDSI_MASK));
            CountDnClkY_RT1 |= CountDnClkY_SYNCDSI_EN;

        #else
            #if(!CountDnClkY_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CountDnClkY_CONTROL & ((uint8)(~CountDnClkY_CTRL_CMPMODE_MASK));
            CountDnClkY_CONTROL = ctrl | CountDnClkY_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CountDnClkY_CONTROL & ((uint8)(~CountDnClkY_CTRL_CAPMODE_MASK));
            
            #if( 0 != CountDnClkY_CAPTURE_MODE_CONF)
                CountDnClkY_CONTROL = ctrl | CountDnClkY_DEFAULT_CAPTURE_MODE;
            #else
                CountDnClkY_CONTROL = ctrl;
            #endif /* 0 != CountDnClkY_CAPTURE_MODE */ 
            
            #endif /* (!CountDnClkY_ControlRegRemoved) */
        #endif /* (CountDnClkY_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CountDnClkY_UsingFixedFunction)
            CountDnClkY_ClearFIFO();
        #endif /* (!CountDnClkY_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CountDnClkY_WritePeriod(CountDnClkY_INIT_PERIOD_VALUE);
        #if (!(CountDnClkY_UsingFixedFunction && (CY_PSOC5A)))
            CountDnClkY_WriteCounter(CountDnClkY_INIT_COUNTER_VALUE);
        #endif /* (!(CountDnClkY_UsingFixedFunction && (CY_PSOC5A))) */
        CountDnClkY_SetInterruptMode(CountDnClkY_INIT_INTERRUPTS_MASK);
        
        #if (!CountDnClkY_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CountDnClkY_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CountDnClkY_WriteCompare(CountDnClkY_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CountDnClkY_interruptState = CyEnterCriticalSection();
            
            CountDnClkY_STATUS_AUX_CTRL |= CountDnClkY_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CountDnClkY_interruptState);
            
        #endif /* (!CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void CountDnClkY_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CountDnClkY_UsingFixedFunction)
        CountDnClkY_GLOBAL_ENABLE |= CountDnClkY_BLOCK_EN_MASK;
        CountDnClkY_GLOBAL_STBY_ENABLE |= CountDnClkY_BLOCK_STBY_EN_MASK;
    #endif /* (CountDnClkY_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CountDnClkY_ControlRegRemoved || CountDnClkY_UsingFixedFunction)
        CountDnClkY_CONTROL |= CountDnClkY_CTRL_ENABLE;                
    #endif /* (!CountDnClkY_ControlRegRemoved || CountDnClkY_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CountDnClkY_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  CountDnClkY_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CountDnClkY_Start(void) 
{
    if(CountDnClkY_initVar == 0u)
    {
        CountDnClkY_Init();
        
        CountDnClkY_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CountDnClkY_Enable();        
}


/*******************************************************************************
* Function Name: CountDnClkY_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void CountDnClkY_Stop(void) 
{
    /* Disable Counter */
    #if(!CountDnClkY_ControlRegRemoved || CountDnClkY_UsingFixedFunction)
        CountDnClkY_CONTROL &= ((uint8)(~CountDnClkY_CTRL_ENABLE));        
    #endif /* (!CountDnClkY_ControlRegRemoved || CountDnClkY_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CountDnClkY_UsingFixedFunction)
        CountDnClkY_GLOBAL_ENABLE &= ((uint8)(~CountDnClkY_BLOCK_EN_MASK));
        CountDnClkY_GLOBAL_STBY_ENABLE &= ((uint8)(~CountDnClkY_BLOCK_STBY_EN_MASK));
    #endif /* (CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void CountDnClkY_SetInterruptMode(uint8 interruptsMask) 
{
    CountDnClkY_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CountDnClkY_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   CountDnClkY_ReadStatusRegister(void) 
{
    return CountDnClkY_STATUS;
}


#if(!CountDnClkY_ControlRegRemoved)
/*******************************************************************************
* Function Name: CountDnClkY_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   CountDnClkY_ReadControlRegister(void) 
{
    return CountDnClkY_CONTROL;
}


/*******************************************************************************
* Function Name: CountDnClkY_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    CountDnClkY_WriteControlRegister(uint8 control) 
{
    CountDnClkY_CONTROL = control;
}

#endif  /* (!CountDnClkY_ControlRegRemoved) */


#if (!(CountDnClkY_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CountDnClkY_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void CountDnClkY_WriteCounter(uint16 counter) \
                                   
{
    #if(CountDnClkY_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CountDnClkY_GLOBAL_ENABLE & CountDnClkY_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CountDnClkY_GLOBAL_ENABLE |= CountDnClkY_BLOCK_EN_MASK;
        CY_SET_REG16(CountDnClkY_COUNTER_LSB_PTR, (uint16)counter);
        CountDnClkY_GLOBAL_ENABLE &= ((uint8)(~CountDnClkY_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(CountDnClkY_COUNTER_LSB_PTR, counter);
    #endif /* (CountDnClkY_UsingFixedFunction) */
}
#endif /* (!(CountDnClkY_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CountDnClkY_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 CountDnClkY_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CountDnClkY_UsingFixedFunction)
		(void)CY_GET_REG16(CountDnClkY_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CountDnClkY_COUNTER_LSB_PTR_8BIT);
	#endif/* (CountDnClkY_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CountDnClkY_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CountDnClkY_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(CountDnClkY_STATICCOUNT_LSB_PTR));
    #endif /* (CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 CountDnClkY_ReadCapture(void) 
{
    #if(CountDnClkY_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CountDnClkY_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(CountDnClkY_STATICCOUNT_LSB_PTR));
    #endif /* (CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void CountDnClkY_WritePeriod(uint16 period) 
{
    #if(CountDnClkY_UsingFixedFunction)
        CY_SET_REG16(CountDnClkY_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(CountDnClkY_PERIOD_LSB_PTR, period);
    #endif /* (CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 CountDnClkY_ReadPeriod(void) 
{
    #if(CountDnClkY_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(CountDnClkY_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(CountDnClkY_PERIOD_LSB_PTR));
    #endif /* (CountDnClkY_UsingFixedFunction) */
}


#if (!CountDnClkY_UsingFixedFunction)
/*******************************************************************************
* Function Name: CountDnClkY_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void CountDnClkY_WriteCompare(uint16 compare) \
                                   
{
    #if(CountDnClkY_UsingFixedFunction)
        CY_SET_REG16(CountDnClkY_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(CountDnClkY_COMPARE_LSB_PTR, compare);
    #endif /* (CountDnClkY_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CountDnClkY_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 CountDnClkY_ReadCompare(void) 
{
    return (CY_GET_REG16(CountDnClkY_COMPARE_LSB_PTR));
}


#if (CountDnClkY_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CountDnClkY_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void CountDnClkY_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CountDnClkY_CONTROL &= ((uint8)(~CountDnClkY_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CountDnClkY_CONTROL |= compareMode;
}
#endif  /* (CountDnClkY_COMPARE_MODE_SOFTWARE) */


#if (CountDnClkY_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CountDnClkY_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void CountDnClkY_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CountDnClkY_CONTROL &= ((uint8)(~CountDnClkY_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CountDnClkY_CONTROL |= ((uint8)((uint8)captureMode << CountDnClkY_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CountDnClkY_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CountDnClkY_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void CountDnClkY_ClearFIFO(void) 
{

    while(0u != (CountDnClkY_ReadStatusRegister() & CountDnClkY_STATUS_FIFONEMP))
    {
        (void)CountDnClkY_ReadCapture();
    }

}
#endif  /* (!CountDnClkY_UsingFixedFunction) */


/* [] END OF FILE */

