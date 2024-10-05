/*******************************************************************************
* File Name: CounterXdnclk.c  
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

#include "CounterXdnclk.h"

uint8 CounterXdnclk_initVar = 0u;


/*******************************************************************************
* Function Name: CounterXdnclk_Init
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
void CounterXdnclk_Init(void) 
{
        #if (!CounterXdnclk_UsingFixedFunction && !CounterXdnclk_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CounterXdnclk_UsingFixedFunction && !CounterXdnclk_ControlRegRemoved) */
        
        #if(!CounterXdnclk_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CounterXdnclk_interruptState;
        #endif /* (!CounterXdnclk_UsingFixedFunction) */
        
        #if (CounterXdnclk_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CounterXdnclk_CONTROL &= CounterXdnclk_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CounterXdnclk_CONTROL2 &= ((uint8)(~CounterXdnclk_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CounterXdnclk_CONTROL3 &= ((uint8)(~CounterXdnclk_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CounterXdnclk_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CounterXdnclk_CONTROL |= CounterXdnclk_ONESHOT;
            #endif /* (CounterXdnclk_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CounterXdnclk_CONTROL2 |= CounterXdnclk_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CounterXdnclk_RT1 &= ((uint8)(~CounterXdnclk_RT1_MASK));
            CounterXdnclk_RT1 |= CounterXdnclk_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CounterXdnclk_RT1 &= ((uint8)(~CounterXdnclk_SYNCDSI_MASK));
            CounterXdnclk_RT1 |= CounterXdnclk_SYNCDSI_EN;

        #else
            #if(!CounterXdnclk_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CounterXdnclk_CONTROL & ((uint8)(~CounterXdnclk_CTRL_CMPMODE_MASK));
            CounterXdnclk_CONTROL = ctrl | CounterXdnclk_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CounterXdnclk_CONTROL & ((uint8)(~CounterXdnclk_CTRL_CAPMODE_MASK));
            
            #if( 0 != CounterXdnclk_CAPTURE_MODE_CONF)
                CounterXdnclk_CONTROL = ctrl | CounterXdnclk_DEFAULT_CAPTURE_MODE;
            #else
                CounterXdnclk_CONTROL = ctrl;
            #endif /* 0 != CounterXdnclk_CAPTURE_MODE */ 
            
            #endif /* (!CounterXdnclk_ControlRegRemoved) */
        #endif /* (CounterXdnclk_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CounterXdnclk_UsingFixedFunction)
            CounterXdnclk_ClearFIFO();
        #endif /* (!CounterXdnclk_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CounterXdnclk_WritePeriod(CounterXdnclk_INIT_PERIOD_VALUE);
        #if (!(CounterXdnclk_UsingFixedFunction && (CY_PSOC5A)))
            CounterXdnclk_WriteCounter(CounterXdnclk_INIT_COUNTER_VALUE);
        #endif /* (!(CounterXdnclk_UsingFixedFunction && (CY_PSOC5A))) */
        CounterXdnclk_SetInterruptMode(CounterXdnclk_INIT_INTERRUPTS_MASK);
        
        #if (!CounterXdnclk_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)CounterXdnclk_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CounterXdnclk_WriteCompare(CounterXdnclk_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CounterXdnclk_interruptState = CyEnterCriticalSection();
            
            CounterXdnclk_STATUS_AUX_CTRL |= CounterXdnclk_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CounterXdnclk_interruptState);
            
        #endif /* (!CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_Enable
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
void CounterXdnclk_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CounterXdnclk_UsingFixedFunction)
        CounterXdnclk_GLOBAL_ENABLE |= CounterXdnclk_BLOCK_EN_MASK;
        CounterXdnclk_GLOBAL_STBY_ENABLE |= CounterXdnclk_BLOCK_STBY_EN_MASK;
    #endif /* (CounterXdnclk_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CounterXdnclk_ControlRegRemoved || CounterXdnclk_UsingFixedFunction)
        CounterXdnclk_CONTROL |= CounterXdnclk_CTRL_ENABLE;                
    #endif /* (!CounterXdnclk_ControlRegRemoved || CounterXdnclk_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CounterXdnclk_Start
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
*  CounterXdnclk_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CounterXdnclk_Start(void) 
{
    if(CounterXdnclk_initVar == 0u)
    {
        CounterXdnclk_Init();
        
        CounterXdnclk_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CounterXdnclk_Enable();        
}


/*******************************************************************************
* Function Name: CounterXdnclk_Stop
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
void CounterXdnclk_Stop(void) 
{
    /* Disable Counter */
    #if(!CounterXdnclk_ControlRegRemoved || CounterXdnclk_UsingFixedFunction)
        CounterXdnclk_CONTROL &= ((uint8)(~CounterXdnclk_CTRL_ENABLE));        
    #endif /* (!CounterXdnclk_ControlRegRemoved || CounterXdnclk_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CounterXdnclk_UsingFixedFunction)
        CounterXdnclk_GLOBAL_ENABLE &= ((uint8)(~CounterXdnclk_BLOCK_EN_MASK));
        CounterXdnclk_GLOBAL_STBY_ENABLE &= ((uint8)(~CounterXdnclk_BLOCK_STBY_EN_MASK));
    #endif /* (CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_SetInterruptMode
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
void CounterXdnclk_SetInterruptMode(uint8 interruptsMask) 
{
    CounterXdnclk_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CounterXdnclk_ReadStatusRegister
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
uint8   CounterXdnclk_ReadStatusRegister(void) 
{
    return CounterXdnclk_STATUS;
}


#if(!CounterXdnclk_ControlRegRemoved)
/*******************************************************************************
* Function Name: CounterXdnclk_ReadControlRegister
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
uint8   CounterXdnclk_ReadControlRegister(void) 
{
    return CounterXdnclk_CONTROL;
}


/*******************************************************************************
* Function Name: CounterXdnclk_WriteControlRegister
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
void    CounterXdnclk_WriteControlRegister(uint8 control) 
{
    CounterXdnclk_CONTROL = control;
}

#endif  /* (!CounterXdnclk_ControlRegRemoved) */


#if (!(CounterXdnclk_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CounterXdnclk_WriteCounter
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
void CounterXdnclk_WriteCounter(uint32 counter) \
                                   
{
    #if(CounterXdnclk_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (CounterXdnclk_GLOBAL_ENABLE & CounterXdnclk_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CounterXdnclk_GLOBAL_ENABLE |= CounterXdnclk_BLOCK_EN_MASK;
        CY_SET_REG16(CounterXdnclk_COUNTER_LSB_PTR, (uint16)counter);
        CounterXdnclk_GLOBAL_ENABLE &= ((uint8)(~CounterXdnclk_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(CounterXdnclk_COUNTER_LSB_PTR, counter);
    #endif /* (CounterXdnclk_UsingFixedFunction) */
}
#endif /* (!(CounterXdnclk_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CounterXdnclk_ReadCounter
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
uint32 CounterXdnclk_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(CounterXdnclk_UsingFixedFunction)
		(void)CY_GET_REG16(CounterXdnclk_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(CounterXdnclk_COUNTER_LSB_PTR_8BIT);
	#endif/* (CounterXdnclk_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(CounterXdnclk_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterXdnclk_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterXdnclk_STATICCOUNT_LSB_PTR));
    #endif /* (CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_ReadCapture
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
uint32 CounterXdnclk_ReadCapture(void) 
{
    #if(CounterXdnclk_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterXdnclk_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterXdnclk_STATICCOUNT_LSB_PTR));
    #endif /* (CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_WritePeriod
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
void CounterXdnclk_WritePeriod(uint32 period) 
{
    #if(CounterXdnclk_UsingFixedFunction)
        CY_SET_REG16(CounterXdnclk_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(CounterXdnclk_PERIOD_LSB_PTR, period);
    #endif /* (CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_ReadPeriod
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
uint32 CounterXdnclk_ReadPeriod(void) 
{
    #if(CounterXdnclk_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(CounterXdnclk_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(CounterXdnclk_PERIOD_LSB_PTR));
    #endif /* (CounterXdnclk_UsingFixedFunction) */
}


#if (!CounterXdnclk_UsingFixedFunction)
/*******************************************************************************
* Function Name: CounterXdnclk_WriteCompare
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
void CounterXdnclk_WriteCompare(uint32 compare) \
                                   
{
    #if(CounterXdnclk_UsingFixedFunction)
        CY_SET_REG16(CounterXdnclk_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(CounterXdnclk_COMPARE_LSB_PTR, compare);
    #endif /* (CounterXdnclk_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CounterXdnclk_ReadCompare
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
uint32 CounterXdnclk_ReadCompare(void) 
{
    return (CY_GET_REG32(CounterXdnclk_COMPARE_LSB_PTR));
}


#if (CounterXdnclk_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterXdnclk_SetCompareMode
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
void CounterXdnclk_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CounterXdnclk_CONTROL &= ((uint8)(~CounterXdnclk_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    CounterXdnclk_CONTROL |= compareMode;
}
#endif  /* (CounterXdnclk_COMPARE_MODE_SOFTWARE) */


#if (CounterXdnclk_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CounterXdnclk_SetCaptureMode
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
void CounterXdnclk_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CounterXdnclk_CONTROL &= ((uint8)(~CounterXdnclk_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    CounterXdnclk_CONTROL |= ((uint8)((uint8)captureMode << CounterXdnclk_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (CounterXdnclk_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CounterXdnclk_ClearFIFO
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
void CounterXdnclk_ClearFIFO(void) 
{

    while(0u != (CounterXdnclk_ReadStatusRegister() & CounterXdnclk_STATUS_FIFONEMP))
    {
        (void)CounterXdnclk_ReadCapture();
    }

}
#endif  /* (!CounterXdnclk_UsingFixedFunction) */


/* [] END OF FILE */

