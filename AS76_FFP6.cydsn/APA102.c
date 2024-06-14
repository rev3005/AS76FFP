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

#include "APA102.h"

uint8 i,j =0;
uint8_t R,G,B = 0;
uint8_t MaxB = 0;
uint16_t BnB = 0;
uint16_t GnR = 0;
uint8_t LedCnt = 0;


uint8_t STFB[4] = {0x00,0x00,0x00,0x00};
uint8_t ENFB[4] = {0xFF,0xFF,0xFF,0xFF};


uint8_t SPI_RGB_DATA[4];

void BF(uint8_t LedCnt, uint8_t R,uint8_t G,uint8_t B,uint8_t MaxB)
{
    
    StartFrame
    for(i=1;i<=170;i++ )
    {    

        RGB_Byte_TxOp(0xE0);
        RGB_Byte_TxOp(0x00);
        RGB_Byte_TxOp(0x00);
        RGB_Byte_TxOp(0x00);
              
    }
    EndFrame
    
    LedFrame(MaxB,R,G,B);
    StartFrame
    for(i=1;i<=LedCnt;i++ )
    {    
//        SPIM_WriteTxData((BnB >> 8)&0xff);
//        SPIM_WriteTxData(BnB&0xff);
//        SPIM_WriteTxData((GnR >> 8)&0xff);
//        SPIM_WriteTxData(GnR&0xff);
        
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
              
        //SPIM_WriteTxData(BnB);
        //SPIM_WriteTxData(GnR);
         //SPIM_PutArray(SPI_RGB_DATA,4);
    }
    EndFrame
    i=0;
}

void LedFrame(uint8_t MB,uint8_t r,uint8_t g,uint8_t b)
{
    //SPI_RGB_DATA[0] = (((MB & 0b00011111)| 0b11100000)<<8);
    //SPI_RGB_DATA[1] = b;
    //SPI_RGB_DATA[2] = g;
    //SPI_RGB_DATA[3] = r;
    BnB = ((((MB & 0b00011111)| 0b11100000)<<8) | b);
    GnR = ((g<<8) | r); 
}

void Ring(uint8_t RngCnt,uint8_t RngR,uint8_t RngG,uint8_t RngB,uint8_t RngMB)
{   
    StartFrame
    for(i=1;i<=45;i++ )
    {    

        RGB_Byte_TxOp(0xE0);
        RGB_Byte_TxOp(0x00);
        RGB_Byte_TxOp(0x00);
        RGB_Byte_TxOp(0x00);
              
    }
    EndFrame

    switch (RngCnt)  
    {
        case 0:
            StartFrame
            BF2(45,0,0,0,0);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;
        case 1:
            StartFrame
            BF2(45,RngR,RngG,RngB,RngMB);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;
                
        case 2:
            StartFrame        
            //BF2(45,0,0,0,0xE0);
            BF2(7,RngR,RngG,RngB,RngMB);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;
            
        case 3:    
            StartFrame        
            //BF2(45,0,0,0,0xE0);
            BF2(15,RngR,RngG,RngB,RngMB);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;
        
        case 4:    
             StartFrame        
            //BF2(14,0,0,0,0xE0);
            BF2(23,RngR,RngG,RngB,RngMB);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;
        
        case 5:    
             StartFrame        
            //BF2(14,0,0,0,0xE0);
            BF2(30,RngR,RngG,RngB,RngMB);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;
            
        case 6:    
             StartFrame        
            //BF2(14,0,0,0,0xE0);
            BF2(38,RngR,RngG,RngB,RngMB);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;   
        case 7:    
             StartFrame        
            //BF2(14,0,0,0,0xE0);
            BF2(45,RngR,RngG,RngB,RngMB);
            BF2(0,0,0,0,0xE0);
            EndFrame
            break;     
    }
}

void BF2(uint8_t LedCnt, uint8_t R,uint8_t G,uint8_t B,uint8_t MaxB)
{
    LedFrame(MaxB,R,G,B);
    for(i=1;i<=LedCnt;i++ )
    {
         
//        SPIM_WriteTxData((BnB >> 8)&0xff);
//        SPIM_WriteTxData(BnB&0xff);
//        SPIM_WriteTxData((GnR >> 8)&0xff);
//        SPIM_WriteTxData(GnR&0xff);
        
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
        
       
        
        //SPIM_WriteTxData(BnB);
        //SPIM_WriteTxData(GnR);
        //SPIM_PutArray(SPI_RGB_DATA,4);
    }
    i=0;
}

void BF22(uint8_t R1,uint8_t G1,uint8_t B1,uint8_t MaxB1,uint8_t R2,uint8_t G2,uint8_t B2,uint8_t MaxB2,uint8_t R3,uint8_t G3,uint8_t B3,uint8_t MaxB3,uint8_t R4,uint8_t G4,uint8_t B4,uint8_t MaxB4,uint8_t R5,uint8_t G5,uint8_t B5,uint8_t MaxB5,uint8_t R6,uint8_t G6,uint8_t B6,uint8_t MaxB6)
{
    
    StartFrame
    for(i=1;i<=45;i++ )
    {    

        RGB_Byte_TxOp(0xE0);
        RGB_Byte_TxOp(0x00);
        RGB_Byte_TxOp(0x00);
        RGB_Byte_TxOp(0x00);
              
    }
    EndFrame
    
    
    StartFrame
    
    LedFrame(MaxB1,R1,G1,B1);
    for(i=1;i<=45;i++ )
    {
         
//        SPIM_WriteTxData((BnB >> 8)&0xff);
//        SPIM_WriteTxData(BnB&0xff);
//        SPIM_WriteTxData((GnR >> 8)&0xff);
//        SPIM_WriteTxData(GnR&0xff);
       if(i<8)
    {
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
    } 
    
    
     if(i<16 && i>7)
    {
        if(i==8)
        {
        LedFrame(MaxB2,R2,G2,B2);
        }
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
    } 
    
    if(i<24 && i>15)
    {
        if(i==16)
        {
        LedFrame(MaxB3,R3,G3,B3);
        }
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
    }
    
    if(i<31 && i>23)
    {
        if(i==24)
        {
        LedFrame(MaxB4,R4,G4,B4);
        }
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
    }
    
        if(i<39 && i>30)
    {
        if(i==31)
        {
        LedFrame(MaxB5,R5,G5,B5);
        }
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
    }
    
    if(i<46 && i>38)
    {
        if(i==39)
        {
        LedFrame(MaxB6,R6,G6,B6);
        }
        RGB_Byte_TxOp((BnB >> 8)&0xff);
        RGB_Byte_TxOp(BnB&0xff);
        RGB_Byte_TxOp((GnR >> 8)&0xff);
        RGB_Byte_TxOp(GnR&0xff);
    }
       
        
        //SPIM_WriteTxData(BnB);
        //SPIM_WriteTxData(GnR);
        //SPIM_PutArray(SPI_RGB_DATA,4);
    }
    i=0;
    
    BF2(0,0,0,0,0xE0);
    EndFrame
}



void RGB_Byte_TxOp(uint8_t RGB_TxByte)
{
  uint8_t i=0;
    for(i=8;i>0;i--)
    {
      
      Pin_SDO_RGB_Write((RGB_TxByte >> (i-1))&0x01);
      Pin_Clock_RGB_Write(0);
      CyDelayUs(1);
      Pin_Clock_RGB_Write(1);
      CyDelayUs(1);
      
    }

}