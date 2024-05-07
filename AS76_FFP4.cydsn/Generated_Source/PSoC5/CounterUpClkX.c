/*******************************************************************************
* File Name: CounterUpClkX.c  
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

#include "CounterUpClkX.h"

uint8 CounterUpClkX_initVar = 0u;


/*******************************************************************************
* Function Name: CounterUpClkX_Init
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
void CounterUpClkX_Init(void) 
{
        #if (!CounterUpClkX_UsingFixedFunction && !CounterUpClkX_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterUpClkX_UsingFixedFunction && !CounterUpClkX_ControlRegRemoved) */
        
        #if(!CounterUpClkX_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterUpClkX_interruptState;
        #endif /* (!CounterUpClkX_UsingFixedFunction) */
        
        #if (CounterUpClkX_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterUpClkX_CONTROL &= CounterUpClkX_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterUpClkX_CONTROL2 &= ((uint8)(~CounterUpClkX_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterUpClkX_CONTROL3 &= ((uint8)(~CounterUpClkX_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterUpClkX_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterUpClkX_CONTROL |= CounterUpClkX_ONESHOT;
            #endif /* (CounterUpClkX_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterUpClkX_CONTROL2 |= CounterUpClkX_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterUpClkX_RT1 &= ((uint8)(~CounterUpClkX_RT1_MASK));
            CounterUpClkX_RT1 |= CounterUpClkX_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterUpClkX_RT1 &= ((uint8)(~CounterUpClkX_SYNCDSI_MASK));
            CounterUpClkX_RT1 |= CounterUpClkX_SYNCDSI_EN;

        #else
            #if(!CounterUpClkX_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterUpClkX_CONTROL & ((uint8)(~CounterUpClkX_CTRL_CMPMODE_MASK));
            CounterUpClkX_CONTROL = ctrl | CounterUpClkX_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterUpClkX_CONTROL & ((uint8)(~CounterUpClkX_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterUpClkX_CAPTURE_MODE_CONF)
                CounterUpClkX_CONTROL = ctrl | CounterUpClkX_DEFAULT_CAPTURE_MODE;
            #else
                CounterUpClkX_CONTROL = ctrl;
            #endif /* 0 != CounterUpClkX_CAPTURE_MODE */ 
            
            #endif /* (!CounterUpClkX_ControlRegRemoved) */
        #endif /* (CounterUpClkX_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterUpClkX_UsingFixedFunction)
            CounterUpClkX_ClearFIFO();
        #endif /* (!CounterUpClkX_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterUpClkX_WritePeriod(CounterUpClkX_INIT_PERIOD_VALUE);
        #if (!(CounterUpClkX_UsingFixedFunction && (CY_PSOC5A)))
            CounterUpClkX_WriteCounter(CounterUpClkX_INIT_COUNTER_VALUE);
        #endif /* (!(CounterUpClkX_UsingFixedFunction && (CY_PSOC5A))) */
        CounterUpClkX_SetInterruptMode(CounterUpClkX_INIT_INTERRUPTS_MASK);
        
        #if (!CounterUpClkX_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterUpClkX_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterUpClkX_WriteCompare(CounterUpClkX_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterUpClkX_interruptState = CyEnterCriticalSection();
            
            CounterUpClkX_STATUS_AUX_CTRL |= CounterUpClkX_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterUpClkX_interruptState);
            
        #endif /* (!CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_Enable
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
void CounterUpClkX_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterUpClkX_UsingFixedFunction)
        CounterUpClkX_GLOBAL_ENABLE |= CounterUpClkX_BLOCK_EN_MASK;
        CounterUpClkX_GLOBAL_STBY_ENABLE |= CounterUpClkX_BLOCK_STBY_EN_MASK;
    #endif /* (CounterUpClkX_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterUpClkX_ControlRegRemoved || CounterUpClkX_UsingFixedFunction)
        CounterUpClkX_CONTROL |= CounterUpClkX_CTRL_ENABLE;                
    #endif /* (!CounterUpClkX_ControlRegRemoved || CounterUpClkX_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterUpClkX_Start
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
*  CounterUpClkX_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterUpClkX_Start(void) 
{
    if(CounterUpClkX_initVar == 0u)
    {
        CounterUpClkX_Init();
        
        CounterUpClkX_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterUpClkX_Enable();        
}


/*******************************************************************************
* Function Name: CounterUpClkX_Stop
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
void CounterUpClkX_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterUpClkX_ControlRegRemoved || CounterUpClkX_UsingFixedFunction)
        CounterUpClkX_CONTROL &= ((uint8)(~CounterUpClkX_CTRL_ENABLE));        
    #endif /* (!CounterUpClkX_ControlRegRemoved || CounterUpClkX_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterUpClkX_UsingFixedFunction)
        CounterUpClkX_GLOBAL_ENABLE &= ((uint8)(~CounterUpClkX_BLOCK_EN_MASK));
        CounterUpClkX_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterUpClkX_BLOCK_STBY_EN_MASK));
    #endif /* (CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_SetInterruptMode
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
void CounterUpClkX_SetInterruptMode(uint8 interruptsMask) 
{
    CounterUpClkX_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterUpClkX_ReadStatusRegister
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
uint8   CounterUpClkX_ReadStatusRegister(void) 
{
    return CounterUpClkX_STATUS;
}


#if(!CounterUpClkX_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterUpClkX_ReadControlRegister
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
uint8   CounterUpClkX_ReadControlRegister(void) 
{
    return CounterUpClkX_CONTROL;
}


/*******************************************************************************
* Function Name: CounterUpClkX_WriteControlRegister
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
void    CounterUpClkX_WriteControlRegister(uint8 control) 
{
    CounterUpClkX_CONTROL = control;
}

#endif  /* (!CounterUpClkX_ControlRegRemoved) */


#if (!(CounterUpClkX_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterUpClkX_WriteCounter
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
void CounterUpClkX_WriteCounter(uint32 counter) \
                                   
{
    #if(CounterUpClkX_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterUpClkX_GLOBAL_ENABLE & CounterUpClkX_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterUpClkX_GLOBAL_ENABLE |= CounterUpClkX_BLOCK_EN_MASK;
        CY_SET_REG16(CounterUpClkX_COUNTER_LSB_PTR, (uint16)counter);
        CounterUpClkX_GLOBAL_ENABLE &= ((uint8)(~CounterUpClkX_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(CounterUpClkX_COUNTER_LSB_PTR, counter);
    #endif /* (CounterUpClkX_UsingFixedFunction) */
}
#endif /* (!(CounterUpClkX_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterUpClkX_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 CounterUpClkX_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterUpClkX_UsingFixedFunction)
		(void)CY_GET_REG16(CounterUpClkX_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterUpClkX_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterUpClkX_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterUpClkX_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterUpClkX_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterUpClkX_STATICCOUNT_LSB_PTR));
    #endif /* (CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 CounterUpClkX_ReadCapture(void) 
{
    #if(CounterUpClkX_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterUpClkX_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterUpClkX_STATICCOUNT_LSB_PTR));
    #endif /* (CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void CounterUpClkX_WritePeriod(uint32 period) 
{
    #if(CounterUpClkX_UsingFixedFunction)
        CY_SET_REG16(CounterUpClkX_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(CounterUpClkX_PERIOD_LSB_PTR, period);
    #endif /* (CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 CounterUpClkX_ReadPeriod(void) 
{
    #if(CounterUpClkX_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterUpClkX_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterUpClkX_PERIOD_LSB_PTR));
    #endif /* (CounterUpClkX_UsingFixedFunction) */
}


#if (!CounterUpClkX_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterUpClkX_WriteCompare
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
void CounterUpClkX_WriteCompare(uint32 compare) \
                                   
{
    #if(CounterUpClkX_UsingFixedFunction)
        CY_SET_REG16(CounterUpClkX_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(CounterUpClkX_COMPARE_LSB_PTR, compare);
    #endif /* (CounterUpClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterUpClkX_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 CounterUpClkX_ReadCompare(void) 
{
    return (CY_GET_REG32(CounterUpClkX_COMPARE_LSB_PTR));
}


#if (CounterUpClkX_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterUpClkX_SetCompareMode
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
void CounterUpClkX_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterUpClkX_CONTROL &= ((uint8)(~CounterUpClkX_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterUpClkX_CONTROL |= compareMode;
}
#endif  /* (CounterUpClkX_COMPARE_MODE_SOFTWARE) */


#if (CounterUpClkX_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterUpClkX_SetCaptureMode
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
void CounterUpClkX_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterUpClkX_CONTROL &= ((uint8)(~CounterUpClkX_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterUpClkX_CONTROL |= ((uint8)((uint8)captureMode << CounterUpClkX_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterUpClkX_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterUpClkX_ClearFIFO
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
void CounterUpClkX_ClearFIFO(void) 
{

    while(0u != (CounterUpClkX_ReadStatusRegister() & CounterUpClkX_STATUS_FIFONEMP))
    {
        (void)CounterUpClkX_ReadCapture();
    }

}
#endif  /* (!CounterUpClkX_UsingFixedFunction) */


/* [] END OF FILE */

