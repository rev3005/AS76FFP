/*******************************************************************************
* File Name: QuadDec_TZ_INT.c
* Version 3.0
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec_TZ.h"
#include "QuadDec_TZ_PVT.h"
#include "cyapicallbacks.h"

volatile int32 QuadDec_TZ_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QuadDec_TZ_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for Quadrature Decoder Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QuadDec_TZ_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QuadDec_TZ_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QuadDec_TZ_ISR )
{
   uint8 QuadDec_TZ_swStatus;

   QuadDec_TZ_swStatus = QuadDec_TZ_STATUS_REG;

    #ifdef QuadDec_TZ_ISR_ENTRY_CALLBACK
        QuadDec_TZ_ISR_EntryCallback();
    #endif /* QuadDec_TZ_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START QuadDec_TZ_ISR_START` */

    /* `#END` */

    if (0u != (QuadDec_TZ_swStatus & QuadDec_TZ_COUNTER_OVERFLOW))
    {
        QuadDec_TZ_count32SoftPart += (int32) QuadDec_TZ_COUNTER_MAX_VALUE;
    }
    else if (0u != (QuadDec_TZ_swStatus & QuadDec_TZ_COUNTER_UNDERFLOW))
    {
        QuadDec_TZ_count32SoftPart -= (int32) QuadDec_TZ_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QuadDec_TZ_swStatus & QuadDec_TZ_COUNTER_RESET))
    {
        QuadDec_TZ_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QuadDec_TZ_ISR_END` */

    /* `#END` */

    #ifdef QuadDec_TZ_ISR_EXIT_CALLBACK
        QuadDec_TZ_ISR_ExitCallback();
    #endif /* QuadDec_TZ_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
