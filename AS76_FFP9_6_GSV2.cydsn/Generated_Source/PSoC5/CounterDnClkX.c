/*******************************************************************************
* File Name: CounterDnClkX.c  
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

#include "CounterDnClkX.h"

uint8 CounterDnClkX_initVar = 0u;


/*******************************************************************************
* Function Name: CounterDnClkX_Init
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
void CounterDnClkX_Init(void) 
{
        #if (!CounterDnClkX_UsingFixedFunction && !CounterDnClkX_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterDnClkX_UsingFixedFunction && !CounterDnClkX_ControlRegRemoved) */
        
        #if(!CounterDnClkX_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterDnClkX_interruptState;
        #endif /* (!CounterDnClkX_UsingFixedFunction) */
        
        #if (CounterDnClkX_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterDnClkX_CONTROL &= CounterDnClkX_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterDnClkX_CONTROL2 &= ((uint8)(~CounterDnClkX_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterDnClkX_CONTROL3 &= ((uint8)(~CounterDnClkX_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterDnClkX_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterDnClkX_CONTROL |= CounterDnClkX_ONESHOT;
            #endif /* (CounterDnClkX_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterDnClkX_CONTROL2 |= CounterDnClkX_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterDnClkX_RT1 &= ((uint8)(~CounterDnClkX_RT1_MASK));
            CounterDnClkX_RT1 |= CounterDnClkX_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterDnClkX_RT1 &= ((uint8)(~CounterDnClkX_SYNCDSI_MASK));
            CounterDnClkX_RT1 |= CounterDnClkX_SYNCDSI_EN;

        #else
            #if(!CounterDnClkX_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterDnClkX_CONTROL & ((uint8)(~CounterDnClkX_CTRL_CMPMODE_MASK));
            CounterDnClkX_CONTROL = ctrl | CounterDnClkX_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterDnClkX_CONTROL & ((uint8)(~CounterDnClkX_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterDnClkX_CAPTURE_MODE_CONF)
                CounterDnClkX_CONTROL = ctrl | CounterDnClkX_DEFAULT_CAPTURE_MODE;
            #else
                CounterDnClkX_CONTROL = ctrl;
            #endif /* 0 != CounterDnClkX_CAPTURE_MODE */ 
            
            #endif /* (!CounterDnClkX_ControlRegRemoved) */
        #endif /* (CounterDnClkX_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterDnClkX_UsingFixedFunction)
            CounterDnClkX_ClearFIFO();
        #endif /* (!CounterDnClkX_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterDnClkX_WritePeriod(CounterDnClkX_INIT_PERIOD_VALUE);
        #if (!(CounterDnClkX_UsingFixedFunction && (CY_PSOC5A)))
            CounterDnClkX_WriteCounter(CounterDnClkX_INIT_COUNTER_VALUE);
        #endif /* (!(CounterDnClkX_UsingFixedFunction && (CY_PSOC5A))) */
        CounterDnClkX_SetInterruptMode(CounterDnClkX_INIT_INTERRUPTS_MASK);
        
        #if (!CounterDnClkX_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterDnClkX_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterDnClkX_WriteCompare(CounterDnClkX_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterDnClkX_interruptState = CyEnterCriticalSection();
            
            CounterDnClkX_STATUS_AUX_CTRL |= CounterDnClkX_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterDnClkX_interruptState);
            
        #endif /* (!CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_Enable
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
void CounterDnClkX_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterDnClkX_UsingFixedFunction)
        CounterDnClkX_GLOBAL_ENABLE |= CounterDnClkX_BLOCK_EN_MASK;
        CounterDnClkX_GLOBAL_STBY_ENABLE |= CounterDnClkX_BLOCK_STBY_EN_MASK;
    #endif /* (CounterDnClkX_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterDnClkX_ControlRegRemoved || CounterDnClkX_UsingFixedFunction)
        CounterDnClkX_CONTROL |= CounterDnClkX_CTRL_ENABLE;                
    #endif /* (!CounterDnClkX_ControlRegRemoved || CounterDnClkX_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterDnClkX_Start
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
*  CounterDnClkX_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterDnClkX_Start(void) 
{
    if(CounterDnClkX_initVar == 0u)
    {
        CounterDnClkX_Init();
        
        CounterDnClkX_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterDnClkX_Enable();        
}


/*******************************************************************************
* Function Name: CounterDnClkX_Stop
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
void CounterDnClkX_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterDnClkX_ControlRegRemoved || CounterDnClkX_UsingFixedFunction)
        CounterDnClkX_CONTROL &= ((uint8)(~CounterDnClkX_CTRL_ENABLE));        
    #endif /* (!CounterDnClkX_ControlRegRemoved || CounterDnClkX_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterDnClkX_UsingFixedFunction)
        CounterDnClkX_GLOBAL_ENABLE &= ((uint8)(~CounterDnClkX_BLOCK_EN_MASK));
        CounterDnClkX_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterDnClkX_BLOCK_STBY_EN_MASK));
    #endif /* (CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_SetInterruptMode
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
void CounterDnClkX_SetInterruptMode(uint8 interruptsMask) 
{
    CounterDnClkX_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterDnClkX_ReadStatusRegister
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
uint8   CounterDnClkX_ReadStatusRegister(void) 
{
    return CounterDnClkX_STATUS;
}


#if(!CounterDnClkX_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterDnClkX_ReadControlRegister
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
uint8   CounterDnClkX_ReadControlRegister(void) 
{
    return CounterDnClkX_CONTROL;
}


/*******************************************************************************
* Function Name: CounterDnClkX_WriteControlRegister
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
void    CounterDnClkX_WriteControlRegister(uint8 control) 
{
    CounterDnClkX_CONTROL = control;
}

#endif  /* (!CounterDnClkX_ControlRegRemoved) */


#if (!(CounterDnClkX_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterDnClkX_WriteCounter
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
void CounterDnClkX_WriteCounter(uint32 counter) \
                                   
{
    #if(CounterDnClkX_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterDnClkX_GLOBAL_ENABLE & CounterDnClkX_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterDnClkX_GLOBAL_ENABLE |= CounterDnClkX_BLOCK_EN_MASK;
        CY_SET_REG16(CounterDnClkX_COUNTER_LSB_PTR, (uint16)counter);
        CounterDnClkX_GLOBAL_ENABLE &= ((uint8)(~CounterDnClkX_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(CounterDnClkX_COUNTER_LSB_PTR, counter);
    #endif /* (CounterDnClkX_UsingFixedFunction) */
}
#endif /* (!(CounterDnClkX_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterDnClkX_ReadCounter
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
uint32 CounterDnClkX_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterDnClkX_UsingFixedFunction)
		(void)CY_GET_REG16(CounterDnClkX_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterDnClkX_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterDnClkX_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterDnClkX_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterDnClkX_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterDnClkX_STATICCOUNT_LSB_PTR));
    #endif /* (CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_ReadCapture
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
uint32 CounterDnClkX_ReadCapture(void) 
{
    #if(CounterDnClkX_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterDnClkX_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterDnClkX_STATICCOUNT_LSB_PTR));
    #endif /* (CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_WritePeriod
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
void CounterDnClkX_WritePeriod(uint32 period) 
{
    #if(CounterDnClkX_UsingFixedFunction)
        CY_SET_REG16(CounterDnClkX_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(CounterDnClkX_PERIOD_LSB_PTR, period);
    #endif /* (CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_ReadPeriod
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
uint32 CounterDnClkX_ReadPeriod(void) 
{
    #if(CounterDnClkX_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterDnClkX_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterDnClkX_PERIOD_LSB_PTR));
    #endif /* (CounterDnClkX_UsingFixedFunction) */
}


#if (!CounterDnClkX_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterDnClkX_WriteCompare
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
void CounterDnClkX_WriteCompare(uint32 compare) \
                                   
{
    #if(CounterDnClkX_UsingFixedFunction)
        CY_SET_REG16(CounterDnClkX_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(CounterDnClkX_COMPARE_LSB_PTR, compare);
    #endif /* (CounterDnClkX_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterDnClkX_ReadCompare
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
uint32 CounterDnClkX_ReadCompare(void) 
{
    return (CY_GET_REG32(CounterDnClkX_COMPARE_LSB_PTR));
}


#if (CounterDnClkX_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterDnClkX_SetCompareMode
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
void CounterDnClkX_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterDnClkX_CONTROL &= ((uint8)(~CounterDnClkX_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterDnClkX_CONTROL |= compareMode;
}
#endif  /* (CounterDnClkX_COMPARE_MODE_SOFTWARE) */


#if (CounterDnClkX_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterDnClkX_SetCaptureMode
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
void CounterDnClkX_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterDnClkX_CONTROL &= ((uint8)(~CounterDnClkX_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterDnClkX_CONTROL |= ((uint8)((uint8)captureMode << CounterDnClkX_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterDnClkX_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterDnClkX_ClearFIFO
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
void CounterDnClkX_ClearFIFO(void) 
{

    while(0u != (CounterDnClkX_ReadStatusRegister() & CounterDnClkX_STATUS_FIFONEMP))
    {
        (void)CounterDnClkX_ReadCapture();
    }

}
#endif  /* (!CounterDnClkX_UsingFixedFunction) */


/* [] END OF FILE */

