/*******************************************************************************
* File Name: CounterUpClkX.h  
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
    
#if !defined(CY_COUNTER_CounterUpClkX_H)
#define CY_COUNTER_CounterUpClkX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 CounterUpClkX_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed CounterUpClkX_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef CounterUpClkX_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* CounterUpClkX_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define CounterUpClkX_Resolution            32u
#define CounterUpClkX_UsingFixedFunction    0u
#define CounterUpClkX_ControlRegRemoved     0u
#define CounterUpClkX_COMPARE_MODE_SOFTWARE 0u
#define CounterUpClkX_CAPTURE_MODE_SOFTWARE 0u
#define CounterUpClkX_RunModeUsed           0u


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
    uint32 CounterUdb;         /* Current Counter Value */

    #if (!CounterUpClkX_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!CounterUpClkX_ControlRegRemoved) */

}CounterUpClkX_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    CounterUpClkX_Start(void) ;
void    CounterUpClkX_Stop(void) ;
void    CounterUpClkX_SetInterruptMode(uint8 interruptsMask) ;
uint8   CounterUpClkX_ReadStatusRegister(void) ;
#define CounterUpClkX_GetInterruptSource() CounterUpClkX_ReadStatusRegister()
#if(!CounterUpClkX_ControlRegRemoved)
    uint8   CounterUpClkX_ReadControlRegister(void) ;
    void    CounterUpClkX_WriteControlRegister(uint8 control) \
        ;
#endif /* (!CounterUpClkX_ControlRegRemoved) */
#if (!(CounterUpClkX_UsingFixedFunction && (CY_PSOC5A)))
    void    CounterUpClkX_WriteCounter(uint32 counter) \
            ; 
#endif /* (!(CounterUpClkX_UsingFixedFunction && (CY_PSOC5A))) */
uint32  CounterUpClkX_ReadCounter(void) ;
uint32  CounterUpClkX_ReadCapture(void) ;
void    CounterUpClkX_WritePeriod(uint32 period) \
    ;
uint32  CounterUpClkX_ReadPeriod( void ) ;
#if (!CounterUpClkX_UsingFixedFunction)
    void    CounterUpClkX_WriteCompare(uint32 compare) \
        ;
    uint32  CounterUpClkX_ReadCompare( void ) \
        ;
#endif /* (!CounterUpClkX_UsingFixedFunction) */

#if (CounterUpClkX_COMPARE_MODE_SOFTWARE)
    void    CounterUpClkX_SetCompareMode(uint8 compareMode) ;
#endif /* (CounterUpClkX_COMPARE_MODE_SOFTWARE) */
#if (CounterUpClkX_CAPTURE_MODE_SOFTWARE)
    void    CounterUpClkX_SetCaptureMode(uint8 captureMode) ;
#endif /* (CounterUpClkX_CAPTURE_MODE_SOFTWARE) */
void CounterUpClkX_ClearFIFO(void)     ;
void CounterUpClkX_Init(void)          ;
void CounterUpClkX_Enable(void)        ;
void CounterUpClkX_SaveConfig(void)    ;
void CounterUpClkX_RestoreConfig(void) ;
void CounterUpClkX_Sleep(void)         ;
void CounterUpClkX_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define CounterUpClkX__B_COUNTER__LESS_THAN 1
#define CounterUpClkX__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define CounterUpClkX__B_COUNTER__EQUAL 0
#define CounterUpClkX__B_COUNTER__GREATER_THAN 3
#define CounterUpClkX__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define CounterUpClkX__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define CounterUpClkX_CMP_MODE_LT 1u
#define CounterUpClkX_CMP_MODE_LTE 2u
#define CounterUpClkX_CMP_MODE_EQ 0u
#define CounterUpClkX_CMP_MODE_GT 3u
#define CounterUpClkX_CMP_MODE_GTE 4u
#define CounterUpClkX_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define CounterUpClkX__B_COUNTER__NONE 0
#define CounterUpClkX__B_COUNTER__RISING_EDGE 1
#define CounterUpClkX__B_COUNTER__FALLING_EDGE 2
#define CounterUpClkX__B_COUNTER__EITHER_EDGE 3
#define CounterUpClkX__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define CounterUpClkX_CAP_MODE_NONE 0u
#define CounterUpClkX_CAP_MODE_RISE 1u
#define CounterUpClkX_CAP_MODE_FALL 2u
#define CounterUpClkX_CAP_MODE_BOTH 3u
#define CounterUpClkX_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define CounterUpClkX_CAPTURE_MODE_CONF       0u
#define CounterUpClkX_INIT_PERIOD_VALUE       4294967294u
#define CounterUpClkX_INIT_COUNTER_VALUE      0u
#if (CounterUpClkX_UsingFixedFunction)
#define CounterUpClkX_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << CounterUpClkX_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define CounterUpClkX_INIT_COMPARE_VALUE      4294967293u
#define CounterUpClkX_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << CounterUpClkX_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << CounterUpClkX_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterUpClkX_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterUpClkX_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << CounterUpClkX_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define CounterUpClkX_DEFAULT_COMPARE_MODE    0u

#if( 0 != CounterUpClkX_CAPTURE_MODE_CONF)
    #define CounterUpClkX_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << CounterUpClkX_CTRL_CAPMODE0_SHIFT))
#else    
    #define CounterUpClkX_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != CounterUpClkX_CAPTURE_MODE_CONF) */

#endif /* (CounterUpClkX_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (CounterUpClkX_UsingFixedFunction)
    #define CounterUpClkX_STATICCOUNT_LSB     (*(reg16 *) CounterUpClkX_CounterHW__CAP0 )
    #define CounterUpClkX_STATICCOUNT_LSB_PTR ( (reg16 *) CounterUpClkX_CounterHW__CAP0 )
    #define CounterUpClkX_PERIOD_LSB          (*(reg16 *) CounterUpClkX_CounterHW__PER0 )
    #define CounterUpClkX_PERIOD_LSB_PTR      ( (reg16 *) CounterUpClkX_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define CounterUpClkX_COMPARE_LSB         (*(reg16 *) CounterUpClkX_CounterHW__CNT_CMP0 )
    #define CounterUpClkX_COMPARE_LSB_PTR     ( (reg16 *) CounterUpClkX_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define CounterUpClkX_COUNTER_LSB         (*(reg16 *) CounterUpClkX_CounterHW__CNT_CMP0 )
    #define CounterUpClkX_COUNTER_LSB_PTR     ( (reg16 *) CounterUpClkX_CounterHW__CNT_CMP0 )
    #define CounterUpClkX_RT1                 (*(reg8 *) CounterUpClkX_CounterHW__RT1)
    #define CounterUpClkX_RT1_PTR             ( (reg8 *) CounterUpClkX_CounterHW__RT1)
#else
    
    #if (CounterUpClkX_Resolution <= 8u) /* 8-bit Counter */
    
        #define CounterUpClkX_STATICCOUNT_LSB     (*(reg8 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define CounterUpClkX_STATICCOUNT_LSB_PTR ( (reg8 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define CounterUpClkX_PERIOD_LSB          (*(reg8 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define CounterUpClkX_PERIOD_LSB_PTR      ( (reg8 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define CounterUpClkX_COMPARE_LSB         (*(reg8 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define CounterUpClkX_COMPARE_LSB_PTR     ( (reg8 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define CounterUpClkX_COUNTER_LSB         (*(reg8 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )  
        #define CounterUpClkX_COUNTER_LSB_PTR     ( (reg8 *)\
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )
    
    #elif(CounterUpClkX_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define CounterUpClkX_STATICCOUNT_LSB     (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define CounterUpClkX_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define CounterUpClkX_PERIOD_LSB          (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define CounterUpClkX_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define CounterUpClkX_COMPARE_LSB         (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define CounterUpClkX_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define CounterUpClkX_COUNTER_LSB         (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )  
            #define CounterUpClkX_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define CounterUpClkX_STATICCOUNT_LSB     (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_F0_REG )
            #define CounterUpClkX_STATICCOUNT_LSB_PTR ( (reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_F0_REG )
            #define CounterUpClkX_PERIOD_LSB          (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_D0_REG )
            #define CounterUpClkX_PERIOD_LSB_PTR      ( (reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_D0_REG )
            #define CounterUpClkX_COMPARE_LSB         (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_D1_REG )
            #define CounterUpClkX_COMPARE_LSB_PTR     ( (reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_D1_REG )
            #define CounterUpClkX_COUNTER_LSB         (*(reg16 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_A0_REG )  
            #define CounterUpClkX_COUNTER_LSB_PTR     ( (reg16 *)\
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(CounterUpClkX_Resolution <= 24u) /* 24-bit Counter */
        
        #define CounterUpClkX_STATICCOUNT_LSB     (*(reg32 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define CounterUpClkX_STATICCOUNT_LSB_PTR ( (reg32 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define CounterUpClkX_PERIOD_LSB          (*(reg32 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define CounterUpClkX_PERIOD_LSB_PTR      ( (reg32 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define CounterUpClkX_COMPARE_LSB         (*(reg32 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define CounterUpClkX_COMPARE_LSB_PTR     ( (reg32 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define CounterUpClkX_COUNTER_LSB         (*(reg32 *) \
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )  
        #define CounterUpClkX_COUNTER_LSB_PTR     ( (reg32 *)\
            CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define CounterUpClkX_STATICCOUNT_LSB     (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define CounterUpClkX_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define CounterUpClkX_PERIOD_LSB          (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define CounterUpClkX_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define CounterUpClkX_COMPARE_LSB         (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define CounterUpClkX_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define CounterUpClkX_COUNTER_LSB         (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )  
            #define CounterUpClkX_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define CounterUpClkX_STATICCOUNT_LSB     (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_F0_REG )
            #define CounterUpClkX_STATICCOUNT_LSB_PTR ( (reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_F0_REG )
            #define CounterUpClkX_PERIOD_LSB          (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_D0_REG )
            #define CounterUpClkX_PERIOD_LSB_PTR      ( (reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_D0_REG )
            #define CounterUpClkX_COMPARE_LSB         (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_D1_REG )
            #define CounterUpClkX_COMPARE_LSB_PTR     ( (reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_D1_REG )
            #define CounterUpClkX_COUNTER_LSB         (*(reg32 *) \
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_A0_REG )  
            #define CounterUpClkX_COUNTER_LSB_PTR     ( (reg32 *)\
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define CounterUpClkX_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                CounterUpClkX_CounterUDB_sC32_counterdp_u0__A0_REG )
				
    #define CounterUpClkX_AUX_CONTROLDP0 \
        (*(reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u0__DP_AUX_CTL_REG)
    
    #define CounterUpClkX_AUX_CONTROLDP0_PTR \
        ( (reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (CounterUpClkX_Resolution == 16 || CounterUpClkX_Resolution == 24 || CounterUpClkX_Resolution == 32)
       #define CounterUpClkX_AUX_CONTROLDP1 \
           (*(reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u1__DP_AUX_CTL_REG)
       #define CounterUpClkX_AUX_CONTROLDP1_PTR \
           ( (reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (CounterUpClkX_Resolution == 16 || CounterUpClkX_Resolution == 24 || CounterUpClkX_Resolution == 32) */
    
    #if (CounterUpClkX_Resolution == 24 || CounterUpClkX_Resolution == 32)
       #define CounterUpClkX_AUX_CONTROLDP2 \
           (*(reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u2__DP_AUX_CTL_REG)
       #define CounterUpClkX_AUX_CONTROLDP2_PTR \
           ( (reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (CounterUpClkX_Resolution == 24 || CounterUpClkX_Resolution == 32) */
    
    #if (CounterUpClkX_Resolution == 32)
       #define CounterUpClkX_AUX_CONTROLDP3 \
           (*(reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u3__DP_AUX_CTL_REG)
       #define CounterUpClkX_AUX_CONTROLDP3_PTR \
           ( (reg8 *) CounterUpClkX_CounterUDB_sC32_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (CounterUpClkX_Resolution == 32) */

#endif  /* (CounterUpClkX_UsingFixedFunction) */

#if (CounterUpClkX_UsingFixedFunction)
    #define CounterUpClkX_STATUS         (*(reg8 *) CounterUpClkX_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define CounterUpClkX_STATUS_MASK             (*(reg8 *) CounterUpClkX_CounterHW__SR0 )
    #define CounterUpClkX_STATUS_MASK_PTR         ( (reg8 *) CounterUpClkX_CounterHW__SR0 )
    #define CounterUpClkX_CONTROL                 (*(reg8 *) CounterUpClkX_CounterHW__CFG0)
    #define CounterUpClkX_CONTROL_PTR             ( (reg8 *) CounterUpClkX_CounterHW__CFG0)
    #define CounterUpClkX_CONTROL2                (*(reg8 *) CounterUpClkX_CounterHW__CFG1)
    #define CounterUpClkX_CONTROL2_PTR            ( (reg8 *) CounterUpClkX_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define CounterUpClkX_CONTROL3       (*(reg8 *) CounterUpClkX_CounterHW__CFG2)
        #define CounterUpClkX_CONTROL3_PTR   ( (reg8 *) CounterUpClkX_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define CounterUpClkX_GLOBAL_ENABLE           (*(reg8 *) CounterUpClkX_CounterHW__PM_ACT_CFG)
    #define CounterUpClkX_GLOBAL_ENABLE_PTR       ( (reg8 *) CounterUpClkX_CounterHW__PM_ACT_CFG)
    #define CounterUpClkX_GLOBAL_STBY_ENABLE      (*(reg8 *) CounterUpClkX_CounterHW__PM_STBY_CFG)
    #define CounterUpClkX_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) CounterUpClkX_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define CounterUpClkX_BLOCK_EN_MASK          CounterUpClkX_CounterHW__PM_ACT_MSK
    #define CounterUpClkX_BLOCK_STBY_EN_MASK     CounterUpClkX_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define CounterUpClkX_CTRL_ENABLE_SHIFT      0x00u
    #define CounterUpClkX_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define CounterUpClkX_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterUpClkX_CTRL_ENABLE_SHIFT))         
    #define CounterUpClkX_ONESHOT                ((uint8)((uint8)0x01u << CounterUpClkX_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define CounterUpClkX_CTRL_MODE_SHIFT        0x01u    
        #define CounterUpClkX_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << CounterUpClkX_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define CounterUpClkX_CTRL_MODE_SHIFT        0x00u    
        #define CounterUpClkX_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << CounterUpClkX_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define CounterUpClkX_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define CounterUpClkX_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << CounterUpClkX_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define CounterUpClkX_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define CounterUpClkX_STATUS_ZERO_INT_EN_MASK_SHIFT      (CounterUpClkX_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define CounterUpClkX_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define CounterUpClkX_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)CounterUpClkX_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define CounterUpClkX_RT1_SHIFT            0x04u
    #define CounterUpClkX_RT1_MASK             ((uint8)((uint8)0x03u << CounterUpClkX_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define CounterUpClkX_SYNC                 ((uint8)((uint8)0x03u << CounterUpClkX_RT1_SHIFT))
    #define CounterUpClkX_SYNCDSI_SHIFT        0x00u
    #define CounterUpClkX_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << CounterUpClkX_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define CounterUpClkX_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << CounterUpClkX_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !CounterUpClkX_UsingFixedFunction */
    #define CounterUpClkX_STATUS               (* (reg8 *) CounterUpClkX_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define CounterUpClkX_STATUS_PTR           (  (reg8 *) CounterUpClkX_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define CounterUpClkX_STATUS_MASK          (* (reg8 *) CounterUpClkX_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define CounterUpClkX_STATUS_MASK_PTR      (  (reg8 *) CounterUpClkX_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define CounterUpClkX_STATUS_AUX_CTRL      (*(reg8 *) CounterUpClkX_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define CounterUpClkX_STATUS_AUX_CTRL_PTR  ( (reg8 *) CounterUpClkX_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define CounterUpClkX_CONTROL              (* (reg8 *) CounterUpClkX_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define CounterUpClkX_CONTROL_PTR          (  (reg8 *) CounterUpClkX_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define CounterUpClkX_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define CounterUpClkX_CTRL_CMPMODE_MASK      0x07u 
    #define CounterUpClkX_CTRL_CAPMODE_MASK      0x03u  
    #define CounterUpClkX_CTRL_RESET             ((uint8)((uint8)0x01u << CounterUpClkX_CTRL_RESET_SHIFT))  
    #define CounterUpClkX_CTRL_ENABLE            ((uint8)((uint8)0x01u << CounterUpClkX_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define CounterUpClkX_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define CounterUpClkX_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define CounterUpClkX_STATUS_CMP_INT_EN_MASK_SHIFT       CounterUpClkX_STATUS_CMP_SHIFT       
    #define CounterUpClkX_STATUS_ZERO_INT_EN_MASK_SHIFT      CounterUpClkX_STATUS_ZERO_SHIFT      
    #define CounterUpClkX_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  CounterUpClkX_STATUS_OVERFLOW_SHIFT  
    #define CounterUpClkX_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT CounterUpClkX_STATUS_UNDERFLOW_SHIFT 
    #define CounterUpClkX_STATUS_CAPTURE_INT_EN_MASK_SHIFT   CounterUpClkX_STATUS_CAPTURE_SHIFT   
    #define CounterUpClkX_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  CounterUpClkX_STATUS_FIFOFULL_SHIFT  
    #define CounterUpClkX_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  CounterUpClkX_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define CounterUpClkX_STATUS_CMP             ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_CMP_SHIFT))  
    #define CounterUpClkX_STATUS_ZERO            ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_ZERO_SHIFT)) 
    #define CounterUpClkX_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_OVERFLOW_SHIFT)) 
    #define CounterUpClkX_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_UNDERFLOW_SHIFT)) 
    #define CounterUpClkX_STATUS_CAPTURE         ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_CAPTURE_SHIFT)) 
    #define CounterUpClkX_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_FIFOFULL_SHIFT))
    #define CounterUpClkX_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << CounterUpClkX_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define CounterUpClkX_STATUS_CMP_INT_EN_MASK            CounterUpClkX_STATUS_CMP                    
    #define CounterUpClkX_STATUS_ZERO_INT_EN_MASK           CounterUpClkX_STATUS_ZERO            
    #define CounterUpClkX_STATUS_OVERFLOW_INT_EN_MASK       CounterUpClkX_STATUS_OVERFLOW        
    #define CounterUpClkX_STATUS_UNDERFLOW_INT_EN_MASK      CounterUpClkX_STATUS_UNDERFLOW       
    #define CounterUpClkX_STATUS_CAPTURE_INT_EN_MASK        CounterUpClkX_STATUS_CAPTURE         
    #define CounterUpClkX_STATUS_FIFOFULL_INT_EN_MASK       CounterUpClkX_STATUS_FIFOFULL        
    #define CounterUpClkX_STATUS_FIFONEMP_INT_EN_MASK       CounterUpClkX_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define CounterUpClkX_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define CounterUpClkX_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define CounterUpClkX_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define CounterUpClkX_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define CounterUpClkX_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define CounterUpClkX_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* CounterUpClkX_UsingFixedFunction */

#endif  /* CY_COUNTER_CounterUpClkX_H */


/* [] END OF FILE */

