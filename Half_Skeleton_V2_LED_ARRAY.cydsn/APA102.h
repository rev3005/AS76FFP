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

#ifndef APA102_H
#define APA102_H

//uint8 revfggfghfg =0;

    
 void RGB_Byte_TxOp(uint8_t);



//#define StartFrame SPIM_WriteTxData(0x00);SPIM_WriteTxData(0x00);SPIM_WriteTxData(0x00);SPIM_WriteTxData(0x00);
//#define EndFrame   SPIM_WriteTxData(0xFF);SPIM_WriteTxData(0xFF);SPIM_WriteTxData(0xFF);SPIM_WriteTxData(0xFF);

#define StartFrame RGB_Byte_TxOp(0x00);RGB_Byte_TxOp(0x00);RGB_Byte_TxOp(0x00);RGB_Byte_TxOp(0x00);
#define EndFrame   RGB_Byte_TxOp(0xFF);RGB_Byte_TxOp(0xFF);RGB_Byte_TxOp(0xFF);RGB_Byte_TxOp(0xFF);



void LedFrame(uint8_t,uint8_t,uint8_t,uint8_t);
void BF(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
void BF2(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
void Ring(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
void BF22(uint8_t R1,uint8_t G1,uint8_t B1,uint8_t MaxB1,uint8_t R2,uint8_t G2,uint8_t B2,uint8_t MaxB2,uint8_t R3,uint8_t G3,uint8_t B3,uint8_t MaxB3,uint8_t R4,uint8_t G4,uint8_t B4,uint8_t MaxB4,uint8_t R5,uint8_t G5,uint8_t B5,uint8_t MaxB5,uint8_t R6,uint8_t G6,uint8_t B6,uint8_t MaxB6);



#endif