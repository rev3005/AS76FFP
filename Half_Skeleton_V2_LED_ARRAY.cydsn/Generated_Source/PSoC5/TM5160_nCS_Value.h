/*******************************************************************************
* File Name: TM5160_nCS_Value.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_TM5160_nCS_Value_H) /* CY_CONTROL_REG_TM5160_nCS_Value_H */
#define CY_CONTROL_REG_TM5160_nCS_Value_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} TM5160_nCS_Value_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    TM5160_nCS_Value_Write(uint8 control) ;
uint8   TM5160_nCS_Value_Read(void) ;

void TM5160_nCS_Value_SaveConfig(void) ;
void TM5160_nCS_Value_RestoreConfig(void) ;
void TM5160_nCS_Value_Sleep(void) ; 
void TM5160_nCS_Value_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define TM5160_nCS_Value_Control        (* (reg8 *) TM5160_nCS_Value_Sync_ctrl_reg__CONTROL_REG )
#define TM5160_nCS_Value_Control_PTR    (  (reg8 *) TM5160_nCS_Value_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_TM5160_nCS_Value_H */


/* [] END OF FILE */
