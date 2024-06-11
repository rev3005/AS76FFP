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



#endif
