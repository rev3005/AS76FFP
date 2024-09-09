/*******************************************************************************
* File Name: Encoder_T_Z_Select.h  
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

#if !defined(CY_CONTROL_REG_Encoder_T_Z_Select_H) /* CY_CONTROL_REG_Encoder_T_Z_Select_H */
#define CY_CONTROL_REG_Encoder_T_Z_Select_H

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

} Encoder_T_Z_Select_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Encoder_T_Z_Select_Write(uint8 control) ;
uint8   Encoder_T_Z_Select_Read(void) ;

void Encoder_T_Z_Select_SaveConfig(void) ;
void Encoder_T_Z_Select_RestoreConfig(void) ;
void Encoder_T_Z_Select_Sleep(void) ; 
void Encoder_T_Z_Select_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Encoder_T_Z_Select_Control        (* (reg8 *) Encoder_T_Z_Select_Sync_ctrl_reg__CONTROL_REG )
#define Encoder_T_Z_Select_Control_PTR    (  (reg8 *) Encoder_T_Z_Select_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Encoder_T_Z_Select_H */


/* [] END OF FILE */
