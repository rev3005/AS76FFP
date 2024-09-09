/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
#include "project.h"

#ifndef PCA9959_H
#define PCA9959_H


/*Grid Config and Control,Dur Reg*/
#define Grd0_Cf 0x20                                        //Grid0 Config Register Address
#define Grd_Ctl 0x09
#define Grd_Dur 0x08 


/*Channel Address Reg Begin*/

#define Ch0_Cf1 0x20                                        //Channel '0' Config-1, Channel Group Assignment and Channel enable  Register's Address
#define Ch0_Cf2 0x21                                        //Channel '0' Config-2, Channel Present '1' current setting Registers's Address
#define Ch0_Cf3 0x22                                        //Channel '0' Config-3, Channel Present '2' current setting Registers's Address
#define Ch0_Cf4 0x23                                        //Channel '0' Config-4, Channel Present '3' current setting Registers's Address

#define Ch1_Cf1 0x24
#define Ch1_Cf2 0x25
    
#define Ch2_Cf1 0x28
#define Ch2_Cf2 0x29
    
#define Ch3_Cf1 0x2C
#define Ch3_Cf2 0x2D

#define Ch4_Cf1 0x30
#define Ch4_Cf2 0x31

#define Ch5_Cf1 0x34
#define Ch5_Cf2 0x35    

#define Ch6_Cf1 0x38
#define Ch6_Cf2 0x39

#define Ch7_Cf1 0x3C
#define Ch7_Cf2 0x3D

#define Ch8_Cf1 0x40
#define Ch8_Cf2 0x41

#define Ch9_Cf1 0x44
#define Ch9_Cf2 0x45

#define Ch10_Cf1 0x48
#define Ch10_Cf2 0x49

#define Ch11_Cf1 0x4C
#define Ch11_Cf2 0x4D

#define Ch12_Cf1 0x50
#define Ch12_Cf2 0x51
#define Ch12_Cf3 0x52
#define Ch12_Cf4 0x53

#define Ch13_Cf1 0x54
#define Ch13_Cf2 0x55

#define Ch14_Cf1 0x58
#define Ch14_Cf2 0x59

#define Ch15_Cf1 0x5C
#define Ch15_Cf2 0x5D

#define Ch16_Cf1 0x60
#define Ch16_Cf2 0x61

#define Ch17_Cf1 0x64
#define Ch17_Cf2 0x65

#define Ch18_Cf1 0x68
#define Ch18_Cf2 0x69

#define Ch19_Cf1 0x6C
#define Ch19_Cf2 0x6D

#define Ch20_Cf1 0x70
#define Ch20_Cf2 0x71

#define Ch21_Cf1 0x74
#define Ch21_Cf2 0x75

#define Ch22_Cf1 0x78
#define Ch22_Cf2 0x79

#define Ch23_Cf1 0x7C
#define Ch23_Cf2 0x7D

/*Channel Address Reg End*/

/*Mode Regs*/
#define Mode1    0x00
#define Mode2    0x01

/*LED Error Flag Regs*/
#define EFLAG0   0x02
#define EFLAG1   0x03
#define EFLAG2   0x04
#define EFLAG3   0x05
#define EFLAG4   0x06
#define EFLAG5   0x07

/*Page Sel and Side Ctl Reg*/
#define Pg_Sl   0x0B                                        //Page Select Register Address
#define GdSel   0b0
#define ChSel   0b1
#define Side_Ctl 0x0A

/*SPI R/W Boolean*/
#define Read    0b1
#define Write   0b0


/*Function Declaration*/

void Reset_Driver(void);

void PageSel(_Bool);
void PageSel_1(_Bool);
void PageSel_2(_Bool);
void PageSel_3(_Bool);
void PageSel_4(_Bool);

void PCA9959_Write(uint8_t, uint8_t);
void PCA9959_Write_1(uint8_t, uint8_t);
void PCA9959_Write_2(uint8_t, uint8_t);
void PCA9959_Write_3(uint8_t, uint8_t);
void PCA9959_Write_4(uint8_t, uint8_t);

void PCA9959_Read(uint8_t);
void Buffer_Clear(void);

void PCA9959_Init(void);
void PCA9959_Init_1(void);
void PCA9959_Init_2(void);
void PCA9959_Init_3(void);
void PCA9959_Init_4(void);
void PCA9959_Init_all(void);


void PCA_16Bit_TxOp(uint16_t);
void PCA_16Bit_TxOp_1(uint16_t);
void PCA_16Bit_TxOp_2(uint16_t);
void PCA_16Bit_TxOp_3(uint16_t);
void PCA_16Bit_TxOp_4(uint16_t);


void PCA9959_ChnEn(uint8_t, uint8_t);
void PCA9959_ChnEn_1(uint8_t, uint8_t);
void PCA9959_ChnEn_2(uint8_t, uint8_t);
void PCA9959_ChnEn_3(uint8_t, uint8_t);
void PCA9959_ChnEn_4(uint8_t, uint8_t);

void PCA9959_clear(void);

void PCA9959_dummy(void);




#endif