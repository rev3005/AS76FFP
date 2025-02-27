/*******************************************************************************
* File Name: ISR_Encoder_X_B.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <ISR_Encoder_X_B.h>
#include "cyapicallbacks.h"

#if !defined(ISR_Encoder_X_B__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ISR_Encoder_X_B_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_Start(void)
{
    /* For all we know the interrupt is active. */
    ISR_Encoder_X_B_Disable();

    /* Set the ISR to point to the ISR_Encoder_X_B Interrupt. */
    ISR_Encoder_X_B_SetVector(&ISR_Encoder_X_B_Interrupt);

    /* Set the priority. */
    ISR_Encoder_X_B_SetPriority((uint8)ISR_Encoder_X_B_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_Encoder_X_B_Enable();
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    ISR_Encoder_X_B_Disable();

    /* Set the ISR to point to the ISR_Encoder_X_B Interrupt. */
    ISR_Encoder_X_B_SetVector(address);

    /* Set the priority. */
    ISR_Encoder_X_B_SetPriority((uint8)ISR_Encoder_X_B_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_Encoder_X_B_Enable();
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_Stop(void)
{
    /* Disable this interrupt. */
    ISR_Encoder_X_B_Disable();

    /* Set the ISR to point to the passive one. */
    ISR_Encoder_X_B_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for ISR_Encoder_X_B.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(ISR_Encoder_X_B_Interrupt)
{
    #ifdef ISR_Encoder_X_B_INTERRUPT_INTERRUPT_CALLBACK
        ISR_Encoder_X_B_Interrupt_InterruptCallback();
    #endif /* ISR_Encoder_X_B_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START ISR_Encoder_X_B_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ISR_Encoder_X_B_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use ISR_Encoder_X_B_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)ISR_Encoder_X_B__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress ISR_Encoder_X_B_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)ISR_Encoder_X_B__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling ISR_Encoder_X_B_Start or ISR_Encoder_X_B_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after ISR_Encoder_X_B_Start or ISR_Encoder_X_B_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_SetPriority(uint8 priority)
{
    *ISR_Encoder_X_B_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 ISR_Encoder_X_B_GetPriority(void)
{
    uint8 priority;


    priority = *ISR_Encoder_X_B_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_Enable(void)
{
    /* Enable the general interrupt. */
    *ISR_Encoder_X_B_INTC_SET_EN = ISR_Encoder_X_B__INTC_MASK;
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 ISR_Encoder_X_B_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*ISR_Encoder_X_B_INTC_SET_EN & (uint32)ISR_Encoder_X_B__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_Disable(void)
{
    /* Disable the general interrupt. */
    *ISR_Encoder_X_B_INTC_CLR_EN = ISR_Encoder_X_B__INTC_MASK;
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void ISR_Encoder_X_B_SetPending(void)
{
    *ISR_Encoder_X_B_INTC_SET_PD = ISR_Encoder_X_B__INTC_MASK;
}


/*******************************************************************************
* Function Name: ISR_Encoder_X_B_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ISR_Encoder_X_B_ClearPending(void)
{
    *ISR_Encoder_X_B_INTC_CLR_PD = ISR_Encoder_X_B__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
