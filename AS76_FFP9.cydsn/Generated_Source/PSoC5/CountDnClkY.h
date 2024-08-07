/*******************************************************************************
* File Name: CountDnClkY.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_CountDnClkY_H)
#define CY_COUNTER_CountDnClkY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CountDnClkY_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed CountDnClkY_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef CountDnClkY_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* CountDnClkY_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define CountDnClkY_Resolution            16u
#define CountDnClkY_UsingFixedFunction    0u
#define CountDnClkY_ControlRegRemoved     0u
#define CountDnClkY_COMPARE_MODE_SOFTWARE 0u
#define CountDnClkY_CAPTURE_MODE_SOFTWARE 0u
#define CountDnClkY_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint16 CounterUdb;         /* Current Counter Value */

    #if (!CountDnClkY_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!CountDnClkY_ControlRegRemoved) */

}CountDnClkY_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    CountDnClkY_Start(void) ;
void    CountDnClkY_Stop(void) ;
void    CountDnClkY_SetInterruptMode(uint8 interruptsMask) ;
uint8   CountDnClkY_ReadStatusRegister(void) ;
#define CountDnClkY_GetInterruptSource() CountDnClkY_ReadStatusRegister()
#if(!CountDnClkY_ControlRegRemoved)
    uint8   CountDnClkY_ReadControlRegister(void) ;
    void    CountDnClkY_WriteControlRegister(uint8 control) \
        ;
#endif /* (!CountDnClkY_ControlRegRemoved) */
#if (!(CountDnClkY_UsingFixedFunction && (CY_PSOC5A)))
    void    CountDnClkY_WriteCounter(uint16 counter) \
            ; 
#endif /* (!(CountDnClkY_UsingFixedFunction && (CY_PSOC5A))) */
uint16  CountDnClkY_ReadCounter(void) ;
uint16  CountDnClkY_ReadCapture(void) ;
void    CountDnClkY_WritePeriod(uint16 period) \
    ;
uint16  CountDnClkY_ReadPeriod( void ) ;
#if (!CountDnClkY_UsingFixedFunction)
    void    CountDnClkY_WriteCompare(uint16 compare) \
        ;
    uint16  CountDnClkY_ReadCompare( void ) \
        ;
#endif /* (!CountDnClkY_UsingFixedFunction) */

#if (CountDnClkY_COMPARE_MODE_SOFTWARE)
    void    CountDnClkY_SetCompareMode(uint8 compareMode) ;
#endif /* (CountDnClkY_COMPARE_MODE_SOFTWARE) */
#if (CountDnClkY_CAPTURE_MODE_SOFTWARE)
    void    CountDnClkY_SetCaptureMode(uint8 captureMode) ;
#endif /* (CountDnClkY_CAPTURE_MODE_SOFTWARE) */
void CountDnClkY_ClearFIFO(void)     ;
void CountDnClkY_Init(void)          ;
void CountDnClkY_Enable(void)        ;
void CountDnClkY_SaveConfig(void)    ;
void CountDnClkY_RestoreConfig(void) ;
void CountDnClkY_Sleep(void)         ;
void CountDnClkY_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define CountDnClkY__B_COUNTER__LESS_THAN 1
#define CountDnClkY__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define CountDnClkY__B_COUNTER__EQUAL 0
#define CountDnClkY__B_COUNTER__GREATER_THAN 3
#define CountDnClkY__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define CountDnClkY__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define CountDnClkY_CMP_MODE_LT 1u
#define CountDnClkY_CMP_MODE_LTE 2u
#define CountDnClkY_CMP_MODE_EQ 0u
#define CountDnClkY_CMP_MODE_GT 3u
#define CountDnClkY_CMP_MODE_GTE 4u
#define CountDnClkY_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define CountDnClkY__B_COUNTER__NONE 0
#define CountDnClkY__B_COUNTER__RISING_EDGE 1
#define CountDnClkY__B_COUNTER__FALLING_EDGE 2
#define CountDnClkY__B_COUNTER__EITHER_EDGE 3
#define CountDnClkY__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define CountDnClkY_CAP_MODE_NONE 0u
#define CountDnClkY_CAP_MODE_RISE 1u
#define CountDnClkY_CAP_MODE_FALL 2u
#define CountDnClkY_CAP_MODE_BOTH 3u
#define CountDnClkY_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define CountDnClkY_CAPTURE_MODE_CONF       0u
#define CountDnClkY_INIT_PERIOD_VALUE       65534u
#define CountDnClkY_INIT_COUNTER_VALUE      0u
#if (CountDnClkY_UsingFixedFunction)
#define CountDnClkY_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << CountDnClkY_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define CountDnClkY_INIT_COMPARE_VALUE      0u
#define CountDnClkY_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << CountDnClkY_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << CountDnClkY_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CountDnClkY_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CountDnClkY_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CountDnClkY_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define CountDnClkY_DEFAULT_COMPARE_MODE    1u

#if( 0 != CountDnClkY_CAPTURE_MODE_CONF)
    #define CountDnClkY_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << CountDnClkY_CTRL_CAPMODE0_SHIFT))
#else    
    #define CountDnClkY_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != CountDnClkY_CAPTURE_MODE_CONF) */

#endif /* (CountDnClkY_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (CountDnClkY_UsingFixedFunction)
    #define CountDnClkY_STATICCOUNT_LSB     (*(reg16 *) CountDnClkY_CounterHW__CAP0 )
    #define CountDnClkY_STATICCOUNT_LSB_PTR ( (reg16 *) CountDnClkY_CounterHW__CAP0 )
    #define CountDnClkY_PERIOD_LSB          (*(reg16 *) CountDnClkY_CounterHW__PER0 )
    #define CountDnClkY_PERIOD_LSB_PTR      ( (reg16 *) CountDnClkY_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define CountDnClkY_COMPARE_LSB         (*(reg16 *) CountDnClkY_CounterHW__CNT_CMP0 )
    #define CountDnClkY_COMPARE_LSB_PTR     ( (reg16 *) CountDnClkY_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define CountDnClkY_COUNTER_LSB         (*(reg16 *) CountDnClkY_CounterHW__CNT_CMP0 )
    #define CountDnClkY_COUNTER_LSB_PTR     ( (reg16 *) CountDnClkY_CounterHW__CNT_CMP0 )
    #define CountDnClkY_RT1                 (*(reg8 *) CountDnClkY_CounterHW__RT1)
    #define CountDnClkY_RT1_PTR             ( (reg8 *) CountDnClkY_CounterHW__RT1)
#else
    
    #if (CountDnClkY_Resolution <= 8u) /* 8-bit Counter */
    
        #define CountDnClkY_STATICCOUNT_LSB     (*(reg8 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CountDnClkY_STATICCOUNT_LSB_PTR ( (reg8 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CountDnClkY_PERIOD_LSB          (*(reg8 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CountDnClkY_PERIOD_LSB_PTR      ( (reg8 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CountDnClkY_COMPARE_LSB         (*(reg8 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CountDnClkY_COMPARE_LSB_PTR     ( (reg8 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CountDnClkY_COUNTER_LSB         (*(reg8 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define CountDnClkY_COUNTER_LSB_PTR     ( (reg8 *)\
            CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #elif(CountDnClkY_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define CountDnClkY_STATICCOUNT_LSB     (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CountDnClkY_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CountDnClkY_PERIOD_LSB          (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CountDnClkY_PERIOD_LSB_PTR      ( (reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CountDnClkY_COMPARE_LSB         (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CountDnClkY_COMPARE_LSB_PTR     ( (reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CountDnClkY_COUNTER_LSB         (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define CountDnClkY_COUNTER_LSB_PTR     ( (reg16 *)\
                CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CountDnClkY_STATICCOUNT_LSB     (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define CountDnClkY_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define CountDnClkY_PERIOD_LSB          (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define CountDnClkY_PERIOD_LSB_PTR      ( (reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define CountDnClkY_COMPARE_LSB         (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define CountDnClkY_COMPARE_LSB_PTR     ( (reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define CountDnClkY_COUNTER_LSB         (*(reg16 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )  
            #define CountDnClkY_COUNTER_LSB_PTR     ( (reg16 *)\
                CountDnClkY_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(CountDnClkY_Resolution <= 24u) /* 24-bit Counter */
        
        #define CountDnClkY_STATICCOUNT_LSB     (*(reg32 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CountDnClkY_STATICCOUNT_LSB_PTR ( (reg32 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define CountDnClkY_PERIOD_LSB          (*(reg32 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CountDnClkY_PERIOD_LSB_PTR      ( (reg32 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define CountDnClkY_COMPARE_LSB         (*(reg32 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CountDnClkY_COMPARE_LSB_PTR     ( (reg32 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define CountDnClkY_COUNTER_LSB         (*(reg32 *) \
            CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define CountDnClkY_COUNTER_LSB_PTR     ( (reg32 *)\
            CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CountDnClkY_STATICCOUNT_LSB     (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CountDnClkY_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define CountDnClkY_PERIOD_LSB          (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CountDnClkY_PERIOD_LSB_PTR      ( (reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define CountDnClkY_COMPARE_LSB         (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CountDnClkY_COMPARE_LSB_PTR     ( (reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define CountDnClkY_COUNTER_LSB         (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define CountDnClkY_COUNTER_LSB_PTR     ( (reg32 *)\
                CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CountDnClkY_STATICCOUNT_LSB     (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define CountDnClkY_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define CountDnClkY_PERIOD_LSB          (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define CountDnClkY_PERIOD_LSB_PTR      ( (reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define CountDnClkY_COMPARE_LSB         (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define CountDnClkY_COMPARE_LSB_PTR     ( (reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define CountDnClkY_COUNTER_LSB         (*(reg32 *) \
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )  
            #define CountDnClkY_COUNTER_LSB_PTR     ( (reg32 *)\
                CountDnClkY_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define CountDnClkY_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                CountDnClkY_CounterUDB_sC16_counterdp_u0__A0_REG )
				
    #define CountDnClkY_AUX_CONTROLDP0 \
        (*(reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #define CountDnClkY_AUX_CONTROLDP0_PTR \
        ( (reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (CountDnClkY_Resolution == 16 || CountDnClkY_Resolution == 24 || CountDnClkY_Resolution == 32)
       #define CountDnClkY_AUX_CONTROLDP1 \
           (*(reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
       #define CountDnClkY_AUX_CONTROLDP1_PTR \
           ( (reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (CountDnClkY_Resolution == 16 || CountDnClkY_Resolution == 24 || CountDnClkY_Resolution == 32) */
    
    #if (CountDnClkY_Resolution == 24 || CountDnClkY_Resolution == 32)
       #define CountDnClkY_AUX_CONTROLDP2 \
           (*(reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
       #define CountDnClkY_AUX_CONTROLDP2_PTR \
           ( (reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (CountDnClkY_Resolution == 24 || CountDnClkY_Resolution == 32) */
    
    #if (CountDnClkY_Resolution == 32)
       #define CountDnClkY_AUX_CONTROLDP3 \
           (*(reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
       #define CountDnClkY_AUX_CONTROLDP3_PTR \
           ( (reg8 *) CountDnClkY_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (CountDnClkY_Resolution == 32) */

#endif  /* (CountDnClkY_UsingFixedFunction) */

#if (CountDnClkY_UsingFixedFunction)
    #define CountDnClkY_STATUS         (*(reg8 *) CountDnClkY_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CountDnClkY_STATUS_MASK             (*(reg8 *) CountDnClkY_CounterHW__SR0 )
    #define CountDnClkY_STATUS_MASK_PTR         ( (reg8 *) CountDnClkY_CounterHW__SR0 )
    #define CountDnClkY_CONTROL                 (*(reg8 *) CountDnClkY_CounterHW__CFG0)
    #define CountDnClkY_CONTROL_PTR             ( (reg8 *) CountDnClkY_CounterHW__CFG0)
    #define CountDnClkY_CONTROL2                (*(reg8 *) CountDnClkY_CounterHW__CFG1)
    #define CountDnClkY_CONTROL2_PTR            ( (reg8 *) CountDnClkY_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CountDnClkY_CONTROL3       (*(reg8 *) CountDnClkY_CounterHW__CFG2)
        #define CountDnClkY_CONTROL3_PTR   ( (reg8 *) CountDnClkY_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CountDnClkY_GLOBAL_ENABLE           (*(reg8 *) CountDnClkY_CounterHW__PM_ACT_CFG)
    #define CountDnClkY_GLOBAL_ENABLE_PTR       ( (reg8 *) CountDnClkY_CounterHW__PM_ACT_CFG)
    #define CountDnClkY_GLOBAL_STBY_ENABLE      (*(reg8 *) CountDnClkY_CounterHW__PM_STBY_CFG)
    #define CountDnClkY_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) CountDnClkY_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define CountDnClkY_BLOCK_EN_MASK          CountDnClkY_CounterHW__PM_ACT_MSK
    #define CountDnClkY_BLOCK_STBY_EN_MASK     CountDnClkY_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define CountDnClkY_CTRL_ENABLE_SHIFT      0x00u
    #define CountDnClkY_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define CountDnClkY_CTRL_ENABLE            ((uint8)((uint8)0x01u << CountDnClkY_CTRL_ENABLE_SHIFT))         
    #define CountDnClkY_ONESHOT                ((uint8)((uint8)0x01u << CountDnClkY_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define CountDnClkY_CTRL_MODE_SHIFT        0x01u    
        #define CountDnClkY_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << CountDnClkY_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define CountDnClkY_CTRL_MODE_SHIFT        0x00u    
        #define CountDnClkY_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << CountDnClkY_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define CountDnClkY_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define CountDnClkY_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << CountDnClkY_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define CountDnClkY_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define CountDnClkY_STATUS_ZERO_INT_EN_MASK_SHIFT      (CountDnClkY_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define CountDnClkY_STATUS_ZERO            ((uint8)((uint8)0x01u << CountDnClkY_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define CountDnClkY_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)CountDnClkY_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CountDnClkY_RT1_SHIFT            0x04u
    #define CountDnClkY_RT1_MASK             ((uint8)((uint8)0x03u << CountDnClkY_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define CountDnClkY_SYNC                 ((uint8)((uint8)0x03u << CountDnClkY_RT1_SHIFT))
    #define CountDnClkY_SYNCDSI_SHIFT        0x00u
    #define CountDnClkY_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << CountDnClkY_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define CountDnClkY_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << CountDnClkY_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !CountDnClkY_UsingFixedFunction */
    #define CountDnClkY_STATUS               (* (reg8 *) CountDnClkY_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define CountDnClkY_STATUS_PTR           (  (reg8 *) CountDnClkY_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define CountDnClkY_STATUS_MASK          (* (reg8 *) CountDnClkY_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define CountDnClkY_STATUS_MASK_PTR      (  (reg8 *) CountDnClkY_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define CountDnClkY_STATUS_AUX_CTRL      (*(reg8 *) CountDnClkY_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define CountDnClkY_STATUS_AUX_CTRL_PTR  ( (reg8 *) CountDnClkY_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define CountDnClkY_CONTROL              (* (reg8 *) CountDnClkY_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define CountDnClkY_CONTROL_PTR          (  (reg8 *) CountDnClkY_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define CountDnClkY_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define CountDnClkY_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define CountDnClkY_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define CountDnClkY_CTRL_CMPMODE_MASK      0x07u 
    #define CountDnClkY_CTRL_CAPMODE_MASK      0x03u  
    #define CountDnClkY_CTRL_RESET             ((uint8)((uint8)0x01u << CountDnClkY_CTRL_RESET_SHIFT))  
    #define CountDnClkY_CTRL_ENABLE            ((uint8)((uint8)0x01u << CountDnClkY_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define CountDnClkY_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define CountDnClkY_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define CountDnClkY_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define CountDnClkY_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define CountDnClkY_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define CountDnClkY_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define CountDnClkY_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define CountDnClkY_STATUS_CMP_INT_EN_MASK_SHIFT       CountDnClkY_STATUS_CMP_SHIFT       
    #define CountDnClkY_STATUS_ZERO_INT_EN_MASK_SHIFT      CountDnClkY_STATUS_ZERO_SHIFT      
    #define CountDnClkY_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  CountDnClkY_STATUS_OVERFLOW_SHIFT  
    #define CountDnClkY_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT CountDnClkY_STATUS_UNDERFLOW_SHIFT 
    #define CountDnClkY_STATUS_CAPTURE_INT_EN_MASK_SHIFT   CountDnClkY_STATUS_CAPTURE_SHIFT   
    #define CountDnClkY_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  CountDnClkY_STATUS_FIFOFULL_SHIFT  
    #define CountDnClkY_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  CountDnClkY_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define CountDnClkY_STATUS_CMP             ((uint8)((uint8)0x01u << CountDnClkY_STATUS_CMP_SHIFT))  
    #define CountDnClkY_STATUS_ZERO            ((uint8)((uint8)0x01u << CountDnClkY_STATUS_ZERO_SHIFT)) 
    #define CountDnClkY_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << CountDnClkY_STATUS_OVERFLOW_SHIFT)) 
    #define CountDnClkY_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << CountDnClkY_STATUS_UNDERFLOW_SHIFT)) 
    #define CountDnClkY_STATUS_CAPTURE         ((uint8)((uint8)0x01u << CountDnClkY_STATUS_CAPTURE_SHIFT)) 
    #define CountDnClkY_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << CountDnClkY_STATUS_FIFOFULL_SHIFT))
    #define CountDnClkY_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << CountDnClkY_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define CountDnClkY_STATUS_CMP_INT_EN_MASK            CountDnClkY_STATUS_CMP                    
    #define CountDnClkY_STATUS_ZERO_INT_EN_MASK           CountDnClkY_STATUS_ZERO            
    #define CountDnClkY_STATUS_OVERFLOW_INT_EN_MASK       CountDnClkY_STATUS_OVERFLOW        
    #define CountDnClkY_STATUS_UNDERFLOW_INT_EN_MASK      CountDnClkY_STATUS_UNDERFLOW       
    #define CountDnClkY_STATUS_CAPTURE_INT_EN_MASK        CountDnClkY_STATUS_CAPTURE         
    #define CountDnClkY_STATUS_FIFOFULL_INT_EN_MASK       CountDnClkY_STATUS_FIFOFULL        
    #define CountDnClkY_STATUS_FIFONEMP_INT_EN_MASK       CountDnClkY_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define CountDnClkY_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define CountDnClkY_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define CountDnClkY_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define CountDnClkY_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define CountDnClkY_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define CountDnClkY_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* CountDnClkY_UsingFixedFunction */

#endif  /* CY_COUNTER_CountDnClkY_H */


/* [] END OF FILE */

