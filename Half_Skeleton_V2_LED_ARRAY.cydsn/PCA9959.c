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
#include "PCA9959.h"

/*Variables*/

uint16_t RX = 0;
uint16_t TX = 0;
uint8_t  RegAddr = 0x00;
uint8_t  Data = 0x00;
_Bool Op =1;
uint8_t PgSl = 0;

///////////////////////////////////////////////////////////////////////////////////////

void PageSel_1(_Bool Sel)
{
    if(Sel == 0)
    {
        RegAddr = 0x0B;
        Data    = 0x00;                                 //Page 0, i.e Grid Registers selected
        PCA9959_Write_1(RegAddr, Data);
    }
    else
    {
        RegAddr = 0X0B;
        Data    = 0x80;                                 //Page 1, i.e Channel Registers selected 
        PCA9959_Write_1(RegAddr, Data);
    }
}

void PageSel_2(_Bool Sel)
{
    if(Sel == 0)
    {
        RegAddr = 0x0B;
        Data    = 0x00;                                 //Page 0, i.e Grid Registers selected
        PCA9959_Write_2(RegAddr, Data);
    }
    else
    {
        RegAddr = 0X0B;
        Data    = 0x80;                                 //Page 1, i.e Channel Registers selected 
        PCA9959_Write_2(RegAddr, Data);
    }
}

void PageSel_3(_Bool Sel)
{
    if(Sel == 0)
    {
        RegAddr = 0x0B;
        Data    = 0x00;                                 //Page 0, i.e Grid Registers selected
        PCA9959_Write_3(RegAddr, Data);
    }
    else
    {
        RegAddr = 0X0B;
        Data    = 0x80;                                 //Page 1, i.e Channel Registers selected 
        PCA9959_Write_3(RegAddr, Data);
    }
}

void PageSel_4(_Bool Sel)
{
    if(Sel == 0)
    {
        RegAddr = 0x0B;
        Data    = 0x00;                                 //Page 0, i.e Grid Registers selected
        PCA9959_Write_4(RegAddr, Data);
    }
    else
    {
        RegAddr = 0X0B;
        Data    = 0x80;                                 //Page 1, i.e Channel Registers selected 
        PCA9959_Write_4(RegAddr, Data);
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void PCA9959_Init_1(void)
{

    PCA9959_Write_1(Mode2, 0x18);
    Pin_OE_PCA9959_1_Write(1);                                      /*Disable all channels. */
    PCA9959_Write_1(Side_Ctl, 0x00);                       //Side 0 to be written to and executed
    PageSel_1(GdSel);
    PCA9959_Write_1(Grd0_Cf, 0x01);                       //LED Channels mapped to Group O use the preset Current set in thier respective CHx_CFG2 Register while Grid0 is activated
//    CyDelay(100);

}

void PCA9959_Init_2(void)
{
    PCA9959_Write_2(Mode2, 0x18);
    Pin_OE_PCA9959_2_Write(1);                                      /*Disable all channels. */
    PCA9959_Write_2(Side_Ctl, 0x00);                       //Side 0 to be written to and executed
    PageSel_2(GdSel);
    PCA9959_Write_2(Grd0_Cf, 0x01);                       //LED Channels mapped to Group O use the preset Current set in thier respective CHx_CFG2 Register while Grid0 is activated
//    CyDelay(100);

}

void PCA9959_Init_3(void)
{
    PCA9959_Write_3(Mode2, 0x18);
    Pin_OE_PCA9959_3_Write(1);                                      /*Disable all channels. */
    PCA9959_Write_3(Side_Ctl, 0x00);                       //Side 0 to be written to and executed
    PageSel_3(GdSel);
    PCA9959_Write_3(Grd0_Cf, 0x01);                       //LED Channels mapped to Group O use the preset Current set in thier respective CHx_CFG2 Register while Grid0 is activated
//    CyDelay(100);

}

void PCA9959_Init_4(void)
{
    PCA9959_Write_4(Mode2, 0x18);
    Pin_OE_PCA9959_4_Write(1);                                      /*Disable all channels. */
    PCA9959_Write_4(Side_Ctl, 0x00);                       //Side 0 to be written to and executed
    PageSel_4(GdSel);
    PCA9959_Write_4(Grd0_Cf, 0x01);                       //LED Channels mapped to Group O use the preset Current set in thier respective CHx_CFG2 Register while Grid0 is activated
//    CyDelay(100);

}

void PCA9959_Init_all(void)
{
   Reset_Driver();
   PCA9959_Init_1();
   PCA9959_Init_2();
   PCA9959_Init_3();
   PCA9959_Init_4();
}

///////////////////////////////////////////////////////////////////////////////////////

void PCA9959_Write_1(uint8_t regaddr_w, uint8_t data_w)
{
    Op = Write;   
    TX = ((((regaddr_w << 1) | Op) << 8) | data_w );    //Evaluate TX so that Write operation can be performed on the register
    PCA_16Bit_TxOp_1(TX);                                 //Send Write command with register address and new data to be written to the register
//    CyDelayUs(1);
    
}

void PCA9959_Write_2(uint8_t regaddr_w, uint8_t data_w)
{
    Op = Write;   
    TX = ((((regaddr_w << 1) | Op) << 8) | data_w );    //Evaluate TX so that Write operation can be performed on the register
    PCA_16Bit_TxOp_2(TX);                                 //Send Write command with register address and new data to be written to the register
//    CyDelayUs(1);
    
}

void PCA9959_Write_3(uint8_t regaddr_w, uint8_t data_w)
{
    Op = Write;   
    TX = ((((regaddr_w << 1) | Op) << 8) | data_w );    //Evaluate TX so that Write operation can be performed on the register
    PCA_16Bit_TxOp_3(TX);                                 //Send Write command with register address and new data to be written to the register
//    CyDelayUs(1);
    
}

void PCA9959_Write_4(uint8_t regaddr_w, uint8_t data_w)
{
    Op = Write;   
    TX = ((((regaddr_w << 1) | Op) << 8) | data_w );    //Evaluate TX so that Write operation can be performed on the register
    PCA_16Bit_TxOp_4(TX);                                 //Send Write command with register address and new data to be written to the register
//    CyDelayUs(1);
    
}

///////////////////////////////////////////////////////////////////////////////////////

void PCA_16Bit_TxOp_1(uint16_t PCA_Tx16Bit)
{
    uint8_t i=0;
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(0);
    CyDelayUs(1);
    
    PCA9959_dummy();
    
    for(i=16;i>0;i--)
    {
      Pin_MOSI_PCA9959_Write((uint8)((PCA_Tx16Bit >> (i-1))&0x01));
      Pin_SCK_PCA9959_Write(0);
      CyDelayUs(1);
      Pin_SCK_PCA9959_Write(1);
      CyDelayUs(1);
    }
    
    PCA9959_dummy();
    PCA9959_dummy();
    
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(1);
    
}

void PCA_16Bit_TxOp_2(uint16_t PCA_Tx16Bit)
{
    uint8_t i=0;
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(0);
    CyDelayUs(1);
    
    PCA9959_dummy();
    PCA9959_dummy();
    PCA9959_dummy();
    
    for(i=16;i>0;i--)
    {
      Pin_MOSI_PCA9959_Write((uint8)((PCA_Tx16Bit >> (i-1))&0x01));
      Pin_SCK_PCA9959_Write(0);
      CyDelayUs(1);
      Pin_SCK_PCA9959_Write(1);
      CyDelayUs(1);
    }
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(1);
    
}

void PCA_16Bit_TxOp_3(uint16_t PCA_Tx16Bit)
{
    uint8_t i=0;
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(0);
    CyDelayUs(1);
    
    for(i=16;i>0;i--)
    {
      Pin_MOSI_PCA9959_Write((uint8)((PCA_Tx16Bit >> (i-1))&0x01));
      Pin_SCK_PCA9959_Write(0);
      CyDelayUs(1);
      Pin_SCK_PCA9959_Write(1);
      CyDelayUs(1);
    }
    
    PCA9959_dummy();
    PCA9959_dummy();
    PCA9959_dummy();
    
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(1);
    
}

void PCA_16Bit_TxOp_4(uint16_t PCA_Tx16Bit)
{
    uint8_t i=0;
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(0);
    CyDelayUs(1);
    
    PCA9959_dummy();
    PCA9959_dummy();
    
    for(i=16;i>0;i--)
    {
      Pin_MOSI_PCA9959_Write((uint8)((PCA_Tx16Bit >> (i-1))&0x01));
      Pin_SCK_PCA9959_Write(0);
      CyDelayUs(1);
      Pin_SCK_PCA9959_Write(1);
      CyDelayUs(1);
    }
    
    PCA9959_dummy();
    
    Pin_SCK_PCA9959_Write(0);
    Pin_SS_PCA9959_Write(1);
    
}

///////////////////////////////////////////////////////////////////////////////////////

void PCA9959_ChnEn(uint8_t Brg, uint8_t Sel)
{

    PCA9959_Init_all();
    CyDelayUs(1);
    if(Brg <= 255)
    {
        
        
        if(Sel == 1)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x00);                       //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x00);
            PCA9959_Write_1(Ch2_Cf1, 0x00); 
            PCA9959_Write_1(Ch3_Cf1, 0x00); 
            PCA9959_Write_1(Ch4_Cf1, 0x00); 
            PCA9959_Write_1(Ch5_Cf1, 0x00); 
            PCA9959_Write_1(Ch6_Cf1, 0x00); 
            PCA9959_Write_1(Ch7_Cf1, 0x00); 
            PCA9959_Write_1(Ch8_Cf1, 0x00); 
            PCA9959_Write_1(Ch9_Cf1, 0x00); 
            PCA9959_Write_1(Ch10_Cf1, 0x01);  //
            PCA9959_Write_1(Ch11_Cf1, 0x00);
            
            PCA9959_Write_1(Ch12_Cf1, 0x00);
            PCA9959_Write_1(Ch13_Cf1, 0x00);
            PCA9959_Write_1(Ch14_Cf1, 0x00);
            PCA9959_Write_1(Ch15_Cf1, 0x00);
            PCA9959_Write_1(Ch16_Cf1, 0x00);
            PCA9959_Write_1(Ch17_Cf1, 0x00);
            PCA9959_Write_1(Ch18_Cf1, 0x00);
            PCA9959_Write_1(Ch19_Cf1, 0x00);
            PCA9959_Write_1(Ch20_Cf1, 0x00);
            PCA9959_Write_1(Ch21_Cf1, 0x00);
            PCA9959_Write_1(Ch22_Cf1, 0x00);
            PCA9959_Write_1(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, 0x00);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, 0x00);
            PCA9959_Write_1(Ch2_Cf2, 0x00);
            PCA9959_Write_1(Ch3_Cf2, 0x00);
            PCA9959_Write_1(Ch4_Cf2, 0x00);
            PCA9959_Write_1(Ch5_Cf2, 0x00);
            PCA9959_Write_1(Ch6_Cf2, 0x00);
            PCA9959_Write_1(Ch7_Cf2, 0x00);
            PCA9959_Write_1(Ch8_Cf2, 0x00);
            PCA9959_Write_1(Ch9_Cf2, 0x00);
            PCA9959_Write_1(Ch10_Cf2, Brg);
            PCA9959_Write_1(Ch11_Cf2, 0x00);
            
            PCA9959_Write_1(Ch12_Cf2, 0x00);
            PCA9959_Write_1(Ch13_Cf2, 0x00);
            PCA9959_Write_1(Ch14_Cf2, 0x00);
            PCA9959_Write_1(Ch15_Cf2, 0x00);
            PCA9959_Write_1(Ch16_Cf2, 0x00);
            PCA9959_Write_1(Ch17_Cf2, 0x00);
            PCA9959_Write_1(Ch18_Cf2, 0x00);
            PCA9959_Write_1(Ch19_Cf2, 0x00);
            PCA9959_Write_1(Ch20_Cf2, 0x00);
            PCA9959_Write_1(Ch21_Cf2, 0x00);
            PCA9959_Write_1(Ch22_Cf2, 0x00);
            PCA9959_Write_1(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_1_Write(0);
        }

        else if(Sel == 2)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x00);                       //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x00);
            PCA9959_Write_1(Ch2_Cf1, 0x00); 
            PCA9959_Write_1(Ch3_Cf1, 0x00); 
            PCA9959_Write_1(Ch4_Cf1, 0x00); 
            PCA9959_Write_1(Ch5_Cf1, 0x00); 
            PCA9959_Write_1(Ch6_Cf1, 0x01);  //
            PCA9959_Write_1(Ch7_Cf1, 0x00); 
            PCA9959_Write_1(Ch8_Cf1, 0x00); 
            PCA9959_Write_1(Ch9_Cf1, 0x01);  //
            PCA9959_Write_1(Ch10_Cf1, 0x00); 
            PCA9959_Write_1(Ch11_Cf1, 0x00);
            
            PCA9959_Write_1(Ch12_Cf1, 0x00);
            PCA9959_Write_1(Ch13_Cf1, 0x01); //
            PCA9959_Write_1(Ch14_Cf1, 0x00);
            PCA9959_Write_1(Ch15_Cf1, 0x00);
            PCA9959_Write_1(Ch16_Cf1, 0x00);
            PCA9959_Write_1(Ch17_Cf1, 0x00);
            PCA9959_Write_1(Ch18_Cf1, 0x00);
            PCA9959_Write_1(Ch19_Cf1, 0x00);
            PCA9959_Write_1(Ch20_Cf1, 0x00);
            PCA9959_Write_1(Ch21_Cf1, 0x00);
            PCA9959_Write_1(Ch22_Cf1, 0x00);
            PCA9959_Write_1(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, 0x00);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, 0x00);
            PCA9959_Write_1(Ch2_Cf2, 0x00);
            PCA9959_Write_1(Ch3_Cf2, 0x00);
            PCA9959_Write_1(Ch4_Cf2, 0x00);
            PCA9959_Write_1(Ch5_Cf2, 0x00);
            PCA9959_Write_1(Ch6_Cf2, Brg); //
            PCA9959_Write_1(Ch7_Cf2, 0x00);
            PCA9959_Write_1(Ch8_Cf2, 0x00);
            PCA9959_Write_1(Ch9_Cf2, Brg);   //
            PCA9959_Write_1(Ch10_Cf2, 0x00);
            PCA9959_Write_1(Ch11_Cf2, 0x00);
            
            PCA9959_Write_1(Ch12_Cf2, 0x00);
            PCA9959_Write_1(Ch13_Cf2, Brg); //
            PCA9959_Write_1(Ch14_Cf2, 0x00);
            PCA9959_Write_1(Ch15_Cf2, 0x00);
            PCA9959_Write_1(Ch16_Cf2, 0x00);
            PCA9959_Write_1(Ch17_Cf2, 0x00);
            PCA9959_Write_1(Ch18_Cf2, 0x00);
            PCA9959_Write_1(Ch19_Cf2, 0x00);
            PCA9959_Write_1(Ch20_Cf2, 0x00);
            PCA9959_Write_1(Ch21_Cf2, 0x00);
            PCA9959_Write_1(Ch22_Cf2, 0x00);
            PCA9959_Write_1(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_1_Write(0);
        }
        
        else if(Sel == 3)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x00);                       //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x00);
            PCA9959_Write_1(Ch2_Cf1, 0x00); 
            PCA9959_Write_1(Ch3_Cf1, 0x00); 
            PCA9959_Write_1(Ch4_Cf1, 0x00); 
            PCA9959_Write_1(Ch5_Cf1, 0x00); 
            PCA9959_Write_1(Ch6_Cf1, 0x00);  
            PCA9959_Write_1(Ch7_Cf1, 0x01); //
            PCA9959_Write_1(Ch8_Cf1, 0x00); 
            PCA9959_Write_1(Ch9_Cf1, 0x00);  
            PCA9959_Write_1(Ch10_Cf1, 0x00); 
            PCA9959_Write_1(Ch11_Cf1, 0x01); //
            
            PCA9959_Write_1(Ch12_Cf1, 0x00);
            PCA9959_Write_1(Ch13_Cf1, 0x00); 
            PCA9959_Write_1(Ch14_Cf1, 0x01); //
            PCA9959_Write_1(Ch15_Cf1, 0x00);
            PCA9959_Write_1(Ch16_Cf1, 0x00);
            PCA9959_Write_1(Ch17_Cf1, 0x00);
            PCA9959_Write_1(Ch18_Cf1, 0x00);
            PCA9959_Write_1(Ch19_Cf1, 0x00);
            PCA9959_Write_1(Ch20_Cf1, 0x00);
            PCA9959_Write_1(Ch21_Cf1, 0x00);
            PCA9959_Write_1(Ch22_Cf1, 0x00);
            PCA9959_Write_1(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, 0x00);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, 0x00);
            PCA9959_Write_1(Ch2_Cf2, 0x00);
            PCA9959_Write_1(Ch3_Cf2, 0x00);
            PCA9959_Write_1(Ch4_Cf2, 0x00);
            PCA9959_Write_1(Ch5_Cf2, 0x00);
            PCA9959_Write_1(Ch6_Cf2, 0x00); 
            PCA9959_Write_1(Ch7_Cf2, Brg);   //
            PCA9959_Write_1(Ch8_Cf2, 0x00);
            PCA9959_Write_1(Ch9_Cf2, 0x00);   
            PCA9959_Write_1(Ch10_Cf2, 0x00);
            PCA9959_Write_1(Ch11_Cf2, Brg);  //
            
            PCA9959_Write_1(Ch12_Cf2, 0x00);
            PCA9959_Write_1(Ch13_Cf2, 0x00); 
            PCA9959_Write_1(Ch14_Cf2, Brg);  //
            PCA9959_Write_1(Ch15_Cf2, 0x00);
            PCA9959_Write_1(Ch16_Cf2, 0x00);
            PCA9959_Write_1(Ch17_Cf2, 0x00);
            PCA9959_Write_1(Ch18_Cf2, 0x00);
            PCA9959_Write_1(Ch19_Cf2, 0x00);
            PCA9959_Write_1(Ch20_Cf2, 0x00);
            PCA9959_Write_1(Ch21_Cf2, 0x00);
            PCA9959_Write_1(Ch22_Cf2, 0x00);
            PCA9959_Write_1(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_1_Write(0);
        }
        
        else if(Sel == 4)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x00);                       //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x00);
            PCA9959_Write_1(Ch2_Cf1, 0x00); 
            PCA9959_Write_1(Ch3_Cf1, 0x00); 
            PCA9959_Write_1(Ch4_Cf1, 0x00); 
            PCA9959_Write_1(Ch5_Cf1, 0x00); 
            PCA9959_Write_1(Ch6_Cf1, 0x01);  //
            PCA9959_Write_1(Ch7_Cf1, 0x01); //
            PCA9959_Write_1(Ch8_Cf1, 0x00); 
            PCA9959_Write_1(Ch9_Cf1, 0x01); // 
            PCA9959_Write_1(Ch10_Cf1, 0x01); 
            PCA9959_Write_1(Ch11_Cf1, 0x01); //
            
            PCA9959_Write_1(Ch12_Cf1, 0x00);
            PCA9959_Write_1(Ch13_Cf1, 0x01); //
            PCA9959_Write_1(Ch14_Cf1, 0x01); //
            PCA9959_Write_1(Ch15_Cf1, 0x00);
            PCA9959_Write_1(Ch16_Cf1, 0x00);
            PCA9959_Write_1(Ch17_Cf1, 0x00);
            PCA9959_Write_1(Ch18_Cf1, 0x00);
            PCA9959_Write_1(Ch19_Cf1, 0x00);
            PCA9959_Write_1(Ch20_Cf1, 0x00);
            PCA9959_Write_1(Ch21_Cf1, 0x00);
            PCA9959_Write_1(Ch22_Cf1, 0x00);
            PCA9959_Write_1(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, 0x00);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, 0x00);
            PCA9959_Write_1(Ch2_Cf2, 0x00);
            PCA9959_Write_1(Ch3_Cf2, 0x00);
            PCA9959_Write_1(Ch4_Cf2, 0x00);
            PCA9959_Write_1(Ch5_Cf2, 0x00);
            PCA9959_Write_1(Ch6_Cf2, Brg); //
            PCA9959_Write_1(Ch7_Cf2, Brg); //
            PCA9959_Write_1(Ch8_Cf2, 0x00);
            PCA9959_Write_1(Ch9_Cf2, Brg);   //
            PCA9959_Write_1(Ch10_Cf2, Brg);
            PCA9959_Write_1(Ch11_Cf2, Brg);//
            
            PCA9959_Write_1(Ch12_Cf2, 0x00);
            PCA9959_Write_1(Ch13_Cf2, Brg); //
            PCA9959_Write_1(Ch14_Cf2, Brg);//
            PCA9959_Write_1(Ch15_Cf2, 0x00);
            PCA9959_Write_1(Ch16_Cf2, 0x00);
            PCA9959_Write_1(Ch17_Cf2, 0x00);
            PCA9959_Write_1(Ch18_Cf2, 0x00);
            PCA9959_Write_1(Ch19_Cf2, 0x00);
            PCA9959_Write_1(Ch20_Cf2, 0x00);
            PCA9959_Write_1(Ch21_Cf2, 0x00);
            PCA9959_Write_1(Ch22_Cf2, 0x00);
            PCA9959_Write_1(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_1_Write(0);
        }
        
        else if(Sel == 5)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x00);                       //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x01); //
            PCA9959_Write_1(Ch2_Cf1, 0x00); 
            PCA9959_Write_1(Ch3_Cf1, 0x01); //
            PCA9959_Write_1(Ch4_Cf1, 0x00); 
            PCA9959_Write_1(Ch5_Cf1, 0x01); //
            PCA9959_Write_1(Ch6_Cf1, 0x00);  
            PCA9959_Write_1(Ch7_Cf1, 0x00); 
            PCA9959_Write_1(Ch8_Cf1, 0x00); 
            PCA9959_Write_1(Ch9_Cf1, 0x00);  
            PCA9959_Write_1(Ch10_Cf1, 0x00); 
            PCA9959_Write_1(Ch11_Cf1, 0x00);
            
            PCA9959_Write_1(Ch12_Cf1, 0x01); //
            PCA9959_Write_1(Ch13_Cf1, 0x00); 
            PCA9959_Write_1(Ch14_Cf1, 0x00);
            PCA9959_Write_1(Ch15_Cf1, 0x00);
            PCA9959_Write_1(Ch16_Cf1, 0x01); //
            PCA9959_Write_1(Ch17_Cf1, 0x00);
            PCA9959_Write_1(Ch18_Cf1, 0x01); //
            PCA9959_Write_1(Ch19_Cf1, 0x00);
            PCA9959_Write_1(Ch20_Cf1, 0x00);
            PCA9959_Write_1(Ch21_Cf1, 0x00);
            PCA9959_Write_1(Ch22_Cf1, 0x00);
            PCA9959_Write_1(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, 0x00);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, Brg);  //
            PCA9959_Write_1(Ch2_Cf2, 0x00);
            PCA9959_Write_1(Ch3_Cf2, Brg);  //
            PCA9959_Write_1(Ch4_Cf2, 0x00);
            PCA9959_Write_1(Ch5_Cf2, Brg); //
            PCA9959_Write_1(Ch6_Cf2, 0x00); 
            PCA9959_Write_1(Ch7_Cf2, 0x00);
            PCA9959_Write_1(Ch8_Cf2, 0x00);
            PCA9959_Write_1(Ch9_Cf2, 0x00);   
            PCA9959_Write_1(Ch10_Cf2, 0x00);
            PCA9959_Write_1(Ch11_Cf2, 0x00);
            
            PCA9959_Write_1(Ch12_Cf2, Brg); //
            PCA9959_Write_1(Ch13_Cf2, 0x00); 
            PCA9959_Write_1(Ch14_Cf2, 0x00);
            PCA9959_Write_1(Ch15_Cf2, 0x00);
            PCA9959_Write_1(Ch16_Cf2, Brg); //
            PCA9959_Write_1(Ch17_Cf2, 0x00);
            PCA9959_Write_1(Ch18_Cf2, Brg); //
            PCA9959_Write_1(Ch19_Cf2, 0x00);
            PCA9959_Write_1(Ch20_Cf2, 0x00);
            PCA9959_Write_1(Ch21_Cf2, 0x00);
            PCA9959_Write_1(Ch22_Cf2, 0x00);
            PCA9959_Write_1(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_1_Write(0);
        }
        
        else if(Sel == 6)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x01);    //                 //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x00); 
            PCA9959_Write_1(Ch2_Cf1, 0x01);  //
            PCA9959_Write_1(Ch3_Cf1, 0x00); 
            PCA9959_Write_1(Ch4_Cf1, 0x01); //
            PCA9959_Write_1(Ch5_Cf1, 0x00); 
            PCA9959_Write_1(Ch6_Cf1, 0x00);  
            PCA9959_Write_1(Ch7_Cf1, 0x00); 
            PCA9959_Write_1(Ch8_Cf1, 0x01); //
            PCA9959_Write_1(Ch9_Cf1, 0x00);  
            PCA9959_Write_1(Ch10_Cf1, 0x00); 
            PCA9959_Write_1(Ch11_Cf1, 0x00);
            
            PCA9959_Write_1(Ch12_Cf1, 0x00);
            PCA9959_Write_1(Ch13_Cf1, 0x00); 
            PCA9959_Write_1(Ch14_Cf1, 0x00);
            PCA9959_Write_1(Ch15_Cf1, 0x01); //
            PCA9959_Write_1(Ch16_Cf1, 0x00); 
            PCA9959_Write_1(Ch17_Cf1, 0x01); //
            PCA9959_Write_1(Ch18_Cf1, 0x00); 
            PCA9959_Write_1(Ch19_Cf1, 0x00);
            PCA9959_Write_1(Ch20_Cf1, 0x00);
            PCA9959_Write_1(Ch21_Cf1, 0x00);
            PCA9959_Write_1(Ch22_Cf1, 0x00);
            PCA9959_Write_1(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, Brg);        //            //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, 0x00);  
            PCA9959_Write_1(Ch2_Cf2, Brg);  //
            PCA9959_Write_1(Ch3_Cf2, 0x00); 
            PCA9959_Write_1(Ch4_Cf2, Brg); //
            PCA9959_Write_1(Ch5_Cf2, 0x00); 
            PCA9959_Write_1(Ch6_Cf2, 0x00); 
            PCA9959_Write_1(Ch7_Cf2, 0x00);
            PCA9959_Write_1(Ch8_Cf2, Brg);  //
            PCA9959_Write_1(Ch9_Cf2, 0x00);   
            PCA9959_Write_1(Ch10_Cf2, 0x00);
            PCA9959_Write_1(Ch11_Cf2, 0x00);
            
            PCA9959_Write_1(Ch12_Cf2, 0x00); 
            PCA9959_Write_1(Ch13_Cf2, 0x00); 
            PCA9959_Write_1(Ch14_Cf2, 0x00);
            PCA9959_Write_1(Ch15_Cf2, Brg);  //
            PCA9959_Write_1(Ch16_Cf2, 0x00); 
            PCA9959_Write_1(Ch17_Cf2, Brg);  //
            PCA9959_Write_1(Ch18_Cf2, 0x00);  
            PCA9959_Write_1(Ch19_Cf2, 0x00);
            PCA9959_Write_1(Ch20_Cf2, 0x00);
            PCA9959_Write_1(Ch21_Cf2, 0x00);
            PCA9959_Write_1(Ch22_Cf2, 0x00);
            PCA9959_Write_1(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_1_Write(0);
        }
        
        else if(Sel == 7)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x01);  //                     //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x01); //
            PCA9959_Write_1(Ch2_Cf1, 0x01); //
            PCA9959_Write_1(Ch3_Cf1, 0x01); //
            PCA9959_Write_1(Ch4_Cf1, 0x01); //
            PCA9959_Write_1(Ch5_Cf1, 0x01); //
            PCA9959_Write_1(Ch6_Cf1, 0x00);  
            PCA9959_Write_1(Ch7_Cf1, 0x00); 
            PCA9959_Write_1(Ch8_Cf1, 0x01); //
            PCA9959_Write_1(Ch9_Cf1, 0x00);  
            PCA9959_Write_1(Ch10_Cf1, 0x00); 
            PCA9959_Write_1(Ch11_Cf1, 0x00);
            
            PCA9959_Write_1(Ch12_Cf1, 0x01); //
            PCA9959_Write_1(Ch13_Cf1, 0x00); 
            PCA9959_Write_1(Ch14_Cf1, 0x00);
            PCA9959_Write_1(Ch15_Cf1, 0x01); //
            PCA9959_Write_1(Ch16_Cf1, 0x01); // 
            PCA9959_Write_1(Ch17_Cf1, 0x01); //
            PCA9959_Write_1(Ch18_Cf1, 0x01); //
            PCA9959_Write_1(Ch19_Cf1, 0x00);
            PCA9959_Write_1(Ch20_Cf1, 0x00);
            PCA9959_Write_1(Ch21_Cf1, 0x00);
            PCA9959_Write_1(Ch22_Cf1, 0x00);
            PCA9959_Write_1(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, Brg);    //                   //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, Brg);  //
            PCA9959_Write_1(Ch2_Cf2, Brg);  //
            PCA9959_Write_1(Ch3_Cf2, Brg); // 
            PCA9959_Write_1(Ch4_Cf2, Brg); //
            PCA9959_Write_1(Ch5_Cf2, Brg); //
            PCA9959_Write_1(Ch6_Cf2, 0x00); 
            PCA9959_Write_1(Ch7_Cf2, 0x00);
            PCA9959_Write_1(Ch8_Cf2, Brg);  //
            PCA9959_Write_1(Ch9_Cf2, 0x00);   
            PCA9959_Write_1(Ch10_Cf2, 0x00);
            PCA9959_Write_1(Ch11_Cf2, 0x00);
            
            PCA9959_Write_1(Ch12_Cf2, Brg); //
            PCA9959_Write_1(Ch13_Cf2, 0x00); 
            PCA9959_Write_1(Ch14_Cf2, 0x00);
            PCA9959_Write_1(Ch15_Cf2, Brg);  //
            PCA9959_Write_1(Ch16_Cf2, Brg); //
            PCA9959_Write_1(Ch17_Cf2, Brg);  //
            PCA9959_Write_1(Ch18_Cf2, Brg);  //
            PCA9959_Write_1(Ch19_Cf2, 0x00);
            PCA9959_Write_1(Ch20_Cf2, 0x00);
            PCA9959_Write_1(Ch21_Cf2, 0x00);
            PCA9959_Write_1(Ch22_Cf2, 0x00);
            PCA9959_Write_1(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_1_Write(0);
        }
        
        else if(Sel == 8)
        {
            Pin_OE_PCA9959_1_Write(1);
            PageSel_1(ChSel);
            PCA9959_Write_1(Ch0_Cf1, 0x01);  //                     //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_1(Ch1_Cf1, 0x01); //
            PCA9959_Write_1(Ch2_Cf1, 0x01); //
            PCA9959_Write_1(Ch3_Cf1, 0x01); //
            PCA9959_Write_1(Ch4_Cf1, 0x01); //
            PCA9959_Write_1(Ch5_Cf1, 0x01); //
            PCA9959_Write_1(Ch6_Cf1, 0x01);  
            PCA9959_Write_1(Ch7_Cf1, 0x01); 
            PCA9959_Write_1(Ch8_Cf1, 0x01); //
            PCA9959_Write_1(Ch9_Cf1, 0x01);  
            PCA9959_Write_1(Ch10_Cf1, 0x01); 
            PCA9959_Write_1(Ch11_Cf1, 0x01);
            
            PCA9959_Write_1(Ch12_Cf1, 0x01); //
            PCA9959_Write_1(Ch13_Cf1, 0x01); 
            PCA9959_Write_1(Ch14_Cf1, 0x01);
            PCA9959_Write_1(Ch15_Cf1, 0x01); //
            PCA9959_Write_1(Ch16_Cf1, 0x01); // 
            PCA9959_Write_1(Ch17_Cf1, 0x01); //
            PCA9959_Write_1(Ch18_Cf1, 0x01); //
            PCA9959_Write_1(Ch19_Cf1, 0x01);
            PCA9959_Write_1(Ch20_Cf1, 0x01);
            PCA9959_Write_1(Ch21_Cf1, 0x01);
            PCA9959_Write_1(Ch22_Cf1, 0x01);
            PCA9959_Write_1(Ch23_Cf1, 0x01);
            
            
            
            PCA9959_Write_1(Ch0_Cf2, Brg);    //                   //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_1(Ch1_Cf2, Brg);  //
            PCA9959_Write_1(Ch2_Cf2, Brg);  //
            PCA9959_Write_1(Ch3_Cf2, Brg); // 
            PCA9959_Write_1(Ch4_Cf2, Brg); //
            PCA9959_Write_1(Ch5_Cf2, Brg); //
            PCA9959_Write_1(Ch6_Cf2, Brg); 
            PCA9959_Write_1(Ch7_Cf2, Brg);
            PCA9959_Write_1(Ch8_Cf2, Brg);  //
            PCA9959_Write_1(Ch9_Cf2, Brg);   
            PCA9959_Write_1(Ch10_Cf2, Brg);
            PCA9959_Write_1(Ch11_Cf2, Brg);
            
            PCA9959_Write_1(Ch12_Cf2, Brg); //
            PCA9959_Write_1(Ch13_Cf2, Brg); 
            PCA9959_Write_1(Ch14_Cf2, Brg);
            PCA9959_Write_1(Ch15_Cf2, Brg);  //
            PCA9959_Write_1(Ch16_Cf2, Brg); //
            PCA9959_Write_1(Ch17_Cf2, Brg);  //
            PCA9959_Write_1(Ch18_Cf2, Brg);  //
            PCA9959_Write_1(Ch19_Cf2, Brg);
            PCA9959_Write_1(Ch20_Cf2, Brg);
            PCA9959_Write_1(Ch21_Cf2, Brg);
            PCA9959_Write_1(Ch22_Cf2, Brg);
            PCA9959_Write_1(Ch23_Cf2, Brg);
            Pin_OE_PCA9959_1_Write(0);
        }
            
        else if(Sel == 9)
        {
            Pin_OE_PCA9959_4_Write(1);
            PageSel_4(ChSel);
            PCA9959_Write_4(Ch0_Cf1, 0x01);   //                    //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_4(Ch1_Cf1, 0x00);
            PCA9959_Write_4(Ch2_Cf1, 0x01); //
            PCA9959_Write_4(Ch3_Cf1, 0x00); 
            PCA9959_Write_4(Ch4_Cf1, 0x01); //
            PCA9959_Write_4(Ch5_Cf1, 0x00); 
            PCA9959_Write_4(Ch6_Cf1, 0x01); //
            PCA9959_Write_4(Ch7_Cf1, 0x00); 
            PCA9959_Write_4(Ch8_Cf1, 0x01); //
            PCA9959_Write_4(Ch9_Cf1, 0x00); 
            PCA9959_Write_4(Ch10_Cf1, 0x01);  //
            PCA9959_Write_4(Ch11_Cf1, 0x00);
            
            PCA9959_Write_4(Ch12_Cf1, 0x01); //
            PCA9959_Write_4(Ch13_Cf1, 0x00);
            PCA9959_Write_4(Ch14_Cf1, 0x01); //
            PCA9959_Write_4(Ch15_Cf1, 0x00);
            PCA9959_Write_4(Ch16_Cf1, 0x01); //
            PCA9959_Write_4(Ch17_Cf1, 0x00);
            PCA9959_Write_4(Ch18_Cf1, 0x01); //
            PCA9959_Write_4(Ch19_Cf1, 0x00);
            PCA9959_Write_4(Ch20_Cf1, 0x01); //
            PCA9959_Write_4(Ch21_Cf1, 0x00);
            PCA9959_Write_4(Ch22_Cf1, 0x01); //
            PCA9959_Write_4(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_4(Ch0_Cf2, Brg);       //                //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_4(Ch1_Cf2, 0x00);
            PCA9959_Write_4(Ch2_Cf2, Brg); //
            PCA9959_Write_4(Ch3_Cf2, 0x00);
            PCA9959_Write_4(Ch4_Cf2, Brg); //
            PCA9959_Write_4(Ch5_Cf2, 0x00);
            PCA9959_Write_4(Ch6_Cf2, Brg); //
            PCA9959_Write_4(Ch7_Cf2, 0x00);
            PCA9959_Write_4(Ch8_Cf2, Brg); //
            PCA9959_Write_4(Ch9_Cf2, 0x00);
            PCA9959_Write_4(Ch10_Cf2, Brg); //
            PCA9959_Write_4(Ch11_Cf2, 0x00);
            
            PCA9959_Write_4(Ch12_Cf2, Brg); //
            PCA9959_Write_4(Ch13_Cf2, 0x00);
            PCA9959_Write_4(Ch14_Cf2, Brg); //
            PCA9959_Write_4(Ch15_Cf2, 0x00);
            PCA9959_Write_4(Ch16_Cf2, Brg); //
            PCA9959_Write_4(Ch17_Cf2, 0x00);
            PCA9959_Write_4(Ch18_Cf2, Brg); //
            PCA9959_Write_4(Ch19_Cf2, 0x00);
            PCA9959_Write_4(Ch20_Cf2, Brg); //
            PCA9959_Write_4(Ch21_Cf2, 0x00);
            PCA9959_Write_4(Ch22_Cf2, Brg); //
            PCA9959_Write_4(Ch23_Cf2, 0x00);
            Pin_OE_PCA9959_4_Write(0);
        }
        
        else if(Sel == 10)
        {
            Pin_OE_PCA9959_4_Write(1);
            PageSel_4(ChSel);
            PCA9959_Write_4(Ch0_Cf1, 0x00);                     //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_4(Ch1_Cf1, 0x01); //
            PCA9959_Write_4(Ch2_Cf1, 0x00); 
            PCA9959_Write_4(Ch3_Cf1, 0x01); //
            PCA9959_Write_4(Ch4_Cf1, 0x00); 
            PCA9959_Write_4(Ch5_Cf1, 0x01); //
            PCA9959_Write_4(Ch6_Cf1, 0x00); 
            PCA9959_Write_4(Ch7_Cf1, 0x01); //
            PCA9959_Write_4(Ch8_Cf1, 0x00); 
            PCA9959_Write_4(Ch9_Cf1, 0x01); //
            PCA9959_Write_4(Ch10_Cf1, 0x00);  
            PCA9959_Write_4(Ch11_Cf1, 0x01); //
            
            PCA9959_Write_4(Ch12_Cf1, 0x00);
            PCA9959_Write_4(Ch13_Cf1, 0x01); //
            PCA9959_Write_4(Ch14_Cf1, 0x00);
            PCA9959_Write_4(Ch15_Cf1, 0x01); //
            PCA9959_Write_4(Ch16_Cf1, 0x00);
            PCA9959_Write_4(Ch17_Cf1, 0x01); //
            PCA9959_Write_4(Ch18_Cf1, 0x00);
            PCA9959_Write_4(Ch19_Cf1, 0x01); //
            PCA9959_Write_4(Ch20_Cf1, 0x00);
            PCA9959_Write_4(Ch21_Cf1, 0x01); //
            PCA9959_Write_4(Ch22_Cf1, 0x00);
            PCA9959_Write_4(Ch23_Cf1, 0x01); //
            
            
            
            PCA9959_Write_4(Ch0_Cf2, 0x00);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_4(Ch1_Cf2, Brg); //
            PCA9959_Write_4(Ch2_Cf2, 0x00);
            PCA9959_Write_4(Ch3_Cf2, Brg); //
            PCA9959_Write_4(Ch4_Cf2, 0x00); 
            PCA9959_Write_4(Ch5_Cf2, Brg); //
            PCA9959_Write_4(Ch6_Cf2, 0x00);
            PCA9959_Write_4(Ch7_Cf2, Brg); //
            PCA9959_Write_4(Ch8_Cf2, 0x00);
            PCA9959_Write_4(Ch9_Cf2, Brg); //
            PCA9959_Write_4(Ch10_Cf2, 0x00);
            PCA9959_Write_4(Ch11_Cf2, Brg); //
            
            PCA9959_Write_4(Ch12_Cf2, 0x00);
            PCA9959_Write_4(Ch13_Cf2, Brg); //
            PCA9959_Write_4(Ch14_Cf2, 0x00);
            PCA9959_Write_4(Ch15_Cf2, Brg); //
            PCA9959_Write_4(Ch16_Cf2, 0x00);
            PCA9959_Write_4(Ch17_Cf2, Brg); //
            PCA9959_Write_4(Ch18_Cf2, 0x00);
            PCA9959_Write_4(Ch19_Cf2, Brg); //
            PCA9959_Write_4(Ch20_Cf2, 0x00);
            PCA9959_Write_4(Ch21_Cf2, Brg); //
            PCA9959_Write_4(Ch22_Cf2, 0x00);
            PCA9959_Write_4(Ch23_Cf2, Brg); //
            Pin_OE_PCA9959_4_Write(0);
        }
        
        else if(Sel == 11)
        {
            Pin_OE_PCA9959_4_Write(1);
            PageSel_4(ChSel);
            PCA9959_Write_4(Ch0_Cf1, 0x01);                       //LED Channel 0 is assigned to Group 0 and enabled
            PCA9959_Write_4(Ch1_Cf1, 0x01);
            PCA9959_Write_4(Ch2_Cf1, 0x01); 
            PCA9959_Write_4(Ch3_Cf1, 0x01); 
            
            
            PCA9959_Write_4(Ch4_Cf1, 0x01); 
            PCA9959_Write_4(Ch5_Cf1, 0x01); 
            PCA9959_Write_4(Ch6_Cf1, 0x01); 
            PCA9959_Write_4(Ch7_Cf1, 0x01); 
            PCA9959_Write_4(Ch8_Cf1, 0x01); 
            PCA9959_Write_4(Ch9_Cf1, 0x01); 
            PCA9959_Write_4(Ch10_Cf1, 0x01); 
            PCA9959_Write_4(Ch11_Cf1, 0x01);
            
            PCA9959_Write_4(Ch12_Cf1, 0x01);
            PCA9959_Write_4(Ch13_Cf1, 0x01);
            PCA9959_Write_4(Ch14_Cf1, 0x01);
            PCA9959_Write_4(Ch15_Cf1, 0x01);
            PCA9959_Write_4(Ch16_Cf1, 0x01);
            PCA9959_Write_4(Ch17_Cf1, 0x01);
            PCA9959_Write_4(Ch18_Cf1, 0x01);
            PCA9959_Write_4(Ch19_Cf1, 0x01);
            PCA9959_Write_4(Ch20_Cf1, 0x01);
            PCA9959_Write_4(Ch21_Cf1, 0x01);
            PCA9959_Write_4(Ch22_Cf1, 0x01);
            PCA9959_Write_4(Ch23_Cf1, 0x01);
            
            
            
            PCA9959_Write_4(Ch0_Cf2, Brg);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_4(Ch1_Cf2, Brg);
            PCA9959_Write_4(Ch2_Cf2, Brg);
            PCA9959_Write_4(Ch3_Cf2, Brg);
            PCA9959_Write_4(Ch4_Cf2, Brg);
            PCA9959_Write_4(Ch5_Cf2, Brg);
            PCA9959_Write_4(Ch6_Cf2, Brg);
            PCA9959_Write_4(Ch7_Cf2, Brg);
            PCA9959_Write_4(Ch8_Cf2, Brg);
            PCA9959_Write_4(Ch9_Cf2, Brg);
            PCA9959_Write_4(Ch10_Cf2, Brg);
            PCA9959_Write_4(Ch11_Cf2, Brg);
            
            PCA9959_Write_4(Ch12_Cf2, Brg);
            PCA9959_Write_4(Ch13_Cf2, Brg);
            PCA9959_Write_4(Ch14_Cf2, Brg);
            PCA9959_Write_4(Ch15_Cf2, Brg);
            PCA9959_Write_4(Ch16_Cf2, Brg);
            PCA9959_Write_4(Ch17_Cf2, Brg);
            PCA9959_Write_4(Ch18_Cf2, Brg);
            PCA9959_Write_4(Ch19_Cf2, Brg);
            PCA9959_Write_4(Ch20_Cf2, Brg);
            PCA9959_Write_4(Ch21_Cf2, Brg);
            PCA9959_Write_4(Ch22_Cf2, Brg);
            PCA9959_Write_4(Ch23_Cf2, Brg); 
            CyDelay(100);
            Pin_OE_PCA9959_4_Write(0);
        }
        
        else if(Sel == 12)
        {
            Pin_OE_PCA9959_3_Write(1);
            PageSel_3(ChSel);
            PCA9959_Write_3(Ch0_Cf1, 0x01);                       //LED Channel 0 is assigned to Group 0 and enabled U2
            PCA9959_Write_3(Ch1_Cf1, 0x01);
            PCA9959_Write_3(Ch2_Cf1, 0x01); 
            PCA9959_Write_3(Ch3_Cf1, 0x01); 
            
            
            PCA9959_Write_3(Ch4_Cf1, 0x01); 
            PCA9959_Write_3(Ch5_Cf1, 0x01); 
            PCA9959_Write_3(Ch6_Cf1, 0x01); 
            PCA9959_Write_3(Ch7_Cf1, 0x01); 
            PCA9959_Write_3(Ch8_Cf1, 0x01); 
            PCA9959_Write_3(Ch9_Cf1, 0x01); 
            PCA9959_Write_3(Ch10_Cf1, 0x01); 
            PCA9959_Write_3(Ch11_Cf1, 0x01);
            
            PCA9959_Write_3(Ch12_Cf1, 0x01);
            PCA9959_Write_3(Ch13_Cf1, 0x01);
            PCA9959_Write_3(Ch14_Cf1, 0x01);
            PCA9959_Write_3(Ch15_Cf1, 0x00);
            PCA9959_Write_3(Ch16_Cf1, 0x00);
            PCA9959_Write_3(Ch17_Cf1, 0x00);
            PCA9959_Write_3(Ch18_Cf1, 0x00);
            PCA9959_Write_3(Ch19_Cf1, 0x00);
            PCA9959_Write_3(Ch20_Cf1, 0x00);
            PCA9959_Write_3(Ch21_Cf1, 0x00);
            PCA9959_Write_3(Ch22_Cf1, 0x00);
            PCA9959_Write_3(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_3(Ch0_Cf2, Brg);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_3(Ch1_Cf2, Brg);
            PCA9959_Write_3(Ch2_Cf2, Brg);
            PCA9959_Write_3(Ch3_Cf2, Brg);
            PCA9959_Write_3(Ch4_Cf2, Brg);
            PCA9959_Write_3(Ch5_Cf2, Brg);
            PCA9959_Write_3(Ch6_Cf2, Brg);
            PCA9959_Write_3(Ch7_Cf2, Brg);
            PCA9959_Write_3(Ch8_Cf2, Brg);
            PCA9959_Write_3(Ch9_Cf2, Brg);
            PCA9959_Write_3(Ch10_Cf2, Brg);
            PCA9959_Write_3(Ch11_Cf2, Brg);
            
            PCA9959_Write_3(Ch12_Cf2, Brg);
            PCA9959_Write_3(Ch13_Cf2, Brg);
            PCA9959_Write_3(Ch14_Cf2, Brg);
            PCA9959_Write_3(Ch15_Cf2, 0x00);
            PCA9959_Write_3(Ch16_Cf2, 0x00);
            PCA9959_Write_3(Ch17_Cf2, 0x00);
            PCA9959_Write_3(Ch18_Cf2, 0x00);
            PCA9959_Write_3(Ch19_Cf2, 0x00);
            PCA9959_Write_3(Ch20_Cf2, 0x00);
            PCA9959_Write_3(Ch21_Cf2, 0x00);
            PCA9959_Write_3(Ch22_Cf2, 0x00);
            PCA9959_Write_3(Ch23_Cf2, 0x00); 
            //CyDelay(50);
            Pin_OE_PCA9959_3_Write(0);
            
            Pin_OE_PCA9959_2_Write(1);
            PageSel_2(ChSel);
            PCA9959_Write_2(Ch0_Cf1, 0x01);                       //LED Channel 0 is assigned to Group 0 and enabled U3
            PCA9959_Write_2(Ch1_Cf1, 0x01);
            PCA9959_Write_2(Ch2_Cf1, 0x01); 
            PCA9959_Write_2(Ch3_Cf1, 0x01); 
            
            
            PCA9959_Write_2(Ch4_Cf1, 0x01); 
            PCA9959_Write_2(Ch5_Cf1, 0x01); 
            PCA9959_Write_2(Ch6_Cf1, 0x01); 
            PCA9959_Write_2(Ch7_Cf1, 0x01); 
            PCA9959_Write_2(Ch8_Cf1, 0x01); 
            PCA9959_Write_2(Ch9_Cf1, 0x01); 
            PCA9959_Write_2(Ch10_Cf1, 0x01); 
            PCA9959_Write_2(Ch11_Cf1, 0x01);
            
            PCA9959_Write_2(Ch12_Cf1, 0x01);
            PCA9959_Write_2(Ch13_Cf1, 0x01);
            PCA9959_Write_2(Ch14_Cf1, 0x01);
            PCA9959_Write_2(Ch15_Cf1, 0x00);
            PCA9959_Write_2(Ch16_Cf1, 0x00);
            PCA9959_Write_2(Ch17_Cf1, 0x00);
            PCA9959_Write_2(Ch18_Cf1, 0x00);
            PCA9959_Write_2(Ch19_Cf1, 0x00);
            PCA9959_Write_2(Ch20_Cf1, 0x00);
            PCA9959_Write_2(Ch21_Cf1, 0x00);
            PCA9959_Write_2(Ch22_Cf1, 0x00);
            PCA9959_Write_2(Ch23_Cf1, 0x00);
            
            
            
            PCA9959_Write_2(Ch0_Cf2, Brg);                       //Preset Current in CH0_CF2 register has been set to 20mA
            PCA9959_Write_2(Ch1_Cf2, Brg);
            PCA9959_Write_2(Ch2_Cf2, Brg);
            PCA9959_Write_2(Ch3_Cf2, Brg);
            PCA9959_Write_2(Ch4_Cf2, Brg);
            PCA9959_Write_2(Ch5_Cf2, Brg);
            PCA9959_Write_2(Ch6_Cf2, Brg);
            PCA9959_Write_2(Ch7_Cf2, Brg);
            PCA9959_Write_2(Ch8_Cf2, Brg);
            PCA9959_Write_2(Ch9_Cf2, Brg);
            PCA9959_Write_2(Ch10_Cf2, Brg);
            PCA9959_Write_2(Ch11_Cf2, Brg);
            
            PCA9959_Write_2(Ch12_Cf2, Brg);
            PCA9959_Write_2(Ch13_Cf2, Brg);
            PCA9959_Write_2(Ch14_Cf2, Brg);
            PCA9959_Write_2(Ch15_Cf2, 0x00);
            PCA9959_Write_2(Ch16_Cf2, 0x00);
            PCA9959_Write_2(Ch17_Cf2, 0x00);
            PCA9959_Write_2(Ch18_Cf2, 0x00);
            PCA9959_Write_2(Ch19_Cf2, 0x00);
            PCA9959_Write_2(Ch20_Cf2, 0x00);
            PCA9959_Write_2(Ch21_Cf2, 0x00);
            PCA9959_Write_2(Ch22_Cf2, 0x00);
            PCA9959_Write_2(Ch23_Cf2, 0x00); 
            
            Pin_OE_PCA9959_2_Write(0);
        }
        
        else
        {
            
            PCA9959_clear();
        }
    }
}



void PCA9959_clear(void)
{
    Pin_SS_PCA9959_Write(1);
    Pin_OE_PCA9959_1_Write(1);
    PageSel_1(ChSel);
    PCA9959_Write_1(Ch0_Cf1, 0x00);                       
    PCA9959_Write_1(Ch1_Cf1, 0x00);
    PCA9959_Write_1(Ch2_Cf1, 0x00); 
    PCA9959_Write_1(Ch3_Cf1, 0x00); 
    PCA9959_Write_1(Ch4_Cf1, 0x00); 
    PCA9959_Write_1(Ch5_Cf1, 0x00); 
    PCA9959_Write_1(Ch6_Cf1, 0x00); 
    PCA9959_Write_1(Ch7_Cf1, 0x00); 
    PCA9959_Write_1(Ch8_Cf1, 0x00); 
    PCA9959_Write_1(Ch9_Cf1, 0x00); 
    PCA9959_Write_1(Ch10_Cf1, 0x00); 
    PCA9959_Write_1(Ch11_Cf1, 0x00);
    
    PCA9959_Write_1(Ch12_Cf1, 0x00);
    PCA9959_Write_1(Ch13_Cf1, 0x00);
    PCA9959_Write_1(Ch14_Cf1, 0x00);
    PCA9959_Write_1(Ch15_Cf1, 0x00);
    PCA9959_Write_1(Ch16_Cf1, 0x00);
    PCA9959_Write_1(Ch17_Cf1, 0x00);
    PCA9959_Write_1(Ch18_Cf1, 0x00);
    PCA9959_Write_1(Ch19_Cf1, 0x00);
    PCA9959_Write_1(Ch20_Cf1, 0x00);
    PCA9959_Write_1(Ch21_Cf1, 0x00);
    PCA9959_Write_1(Ch22_Cf1, 0x00);
    PCA9959_Write_1(Ch23_Cf1, 0x00);
    
    
    
    PCA9959_Write_1(Ch0_Cf2, 0x00);                       
    PCA9959_Write_1(Ch1_Cf2, 0x00);
    PCA9959_Write_1(Ch2_Cf2, 0x00);
    PCA9959_Write_1(Ch3_Cf2, 0x00);
    PCA9959_Write_1(Ch4_Cf2, 0x00);
    PCA9959_Write_1(Ch5_Cf2, 0x00);
    PCA9959_Write_1(Ch6_Cf2, 0x00);
    PCA9959_Write_1(Ch7_Cf2, 0x00);
    PCA9959_Write_1(Ch8_Cf2, 0x00);
    PCA9959_Write_1(Ch9_Cf2, 0x00);
    PCA9959_Write_1(Ch10_Cf2, 0x00);
    PCA9959_Write_1(Ch11_Cf2, 0x00);
    
    PCA9959_Write_1(Ch12_Cf2, 0x00);
    PCA9959_Write_1(Ch13_Cf2, 0x00);
    PCA9959_Write_1(Ch14_Cf2, 0x00);
    PCA9959_Write_1(Ch15_Cf2, 0x00);
    PCA9959_Write_1(Ch16_Cf2, 0x00);
    PCA9959_Write_1(Ch17_Cf2, 0x00);
    PCA9959_Write_1(Ch18_Cf2, 0x00);
    PCA9959_Write_1(Ch19_Cf2, 0x00);
    PCA9959_Write_1(Ch20_Cf2, 0x00);
    PCA9959_Write_1(Ch21_Cf2, 0x00);
    PCA9959_Write_1(Ch22_Cf2, 0x00);
    PCA9959_Write_1(Ch23_Cf2, 0x00);
    Pin_OE_PCA9959_1_Write(1);
    
    Pin_OE_PCA9959_2_Write(1);
    PageSel_2(ChSel);
    PCA9959_Write_2(Ch0_Cf1, 0x00);                       
    PCA9959_Write_2(Ch1_Cf1, 0x00);
    PCA9959_Write_2(Ch2_Cf1, 0x00); 
    PCA9959_Write_2(Ch3_Cf1, 0x00); 
    PCA9959_Write_2(Ch4_Cf1, 0x00); 
    PCA9959_Write_2(Ch5_Cf1, 0x00); 
    PCA9959_Write_2(Ch6_Cf1, 0x00); 
    PCA9959_Write_2(Ch7_Cf1, 0x00); 
    PCA9959_Write_2(Ch8_Cf1, 0x00); 
    PCA9959_Write_2(Ch9_Cf1, 0x00); 
    PCA9959_Write_2(Ch10_Cf1, 0x00);  
    PCA9959_Write_2(Ch11_Cf1, 0x00);
    
    PCA9959_Write_2(Ch12_Cf1, 0x00);
    PCA9959_Write_2(Ch13_Cf1, 0x00);
    PCA9959_Write_2(Ch14_Cf1, 0x00);
    PCA9959_Write_2(Ch15_Cf1, 0x00);
    PCA9959_Write_2(Ch16_Cf1, 0x00);
    PCA9959_Write_2(Ch17_Cf1, 0x00);
    PCA9959_Write_2(Ch18_Cf1, 0x00);
    PCA9959_Write_2(Ch19_Cf1, 0x00);
    PCA9959_Write_2(Ch20_Cf1, 0x00);
    PCA9959_Write_2(Ch21_Cf1, 0x00);
    PCA9959_Write_2(Ch22_Cf1, 0x00);
    PCA9959_Write_2(Ch23_Cf1, 0x00);
    
    
    
    PCA9959_Write_2(Ch0_Cf2, 0x00);                       
    PCA9959_Write_2(Ch1_Cf2, 0x00);
    PCA9959_Write_2(Ch2_Cf2, 0x00);
    PCA9959_Write_2(Ch3_Cf2, 0x00);
    PCA9959_Write_2(Ch4_Cf2, 0x00);
    PCA9959_Write_2(Ch5_Cf2, 0x00);
    PCA9959_Write_2(Ch6_Cf2, 0x00);
    PCA9959_Write_2(Ch7_Cf2, 0x00);
    PCA9959_Write_2(Ch8_Cf2, 0x00);
    PCA9959_Write_2(Ch9_Cf2, 0x00);
    PCA9959_Write_2(Ch10_Cf2, 0x00);
    PCA9959_Write_2(Ch11_Cf2, 0x00);
    
    PCA9959_Write_2(Ch12_Cf2, 0x00);
    PCA9959_Write_2(Ch13_Cf2, 0x00);
    PCA9959_Write_2(Ch14_Cf2, 0x00);
    PCA9959_Write_2(Ch15_Cf2, 0x00);
    PCA9959_Write_2(Ch16_Cf2, 0x00);
    PCA9959_Write_2(Ch17_Cf2, 0x00);
    PCA9959_Write_2(Ch18_Cf2, 0x00);
    PCA9959_Write_2(Ch19_Cf2, 0x00);
    PCA9959_Write_2(Ch20_Cf2, 0x00);
    PCA9959_Write_2(Ch21_Cf2, 0x00);
    PCA9959_Write_2(Ch22_Cf2, 0x00);
    PCA9959_Write_2(Ch23_Cf2, 0x00);
    Pin_OE_PCA9959_2_Write(1);
    
    Pin_OE_PCA9959_3_Write(1);
    PageSel_3(ChSel);
    PCA9959_Write_3(Ch0_Cf1, 0x00);                       
    PCA9959_Write_3(Ch1_Cf1, 0x00);
    PCA9959_Write_3(Ch2_Cf1, 0x00); 
    PCA9959_Write_3(Ch3_Cf1, 0x00); 
    PCA9959_Write_3(Ch4_Cf1, 0x00); 
    PCA9959_Write_3(Ch5_Cf1, 0x00); 
    PCA9959_Write_3(Ch6_Cf1, 0x00); 
    PCA9959_Write_3(Ch7_Cf1, 0x00); 
    PCA9959_Write_3(Ch8_Cf1, 0x00); 
    PCA9959_Write_3(Ch9_Cf1, 0x00); 
    PCA9959_Write_3(Ch10_Cf1, 0x00); 
    PCA9959_Write_3(Ch11_Cf1, 0x00);
    
    PCA9959_Write_3(Ch12_Cf1, 0x00);
    PCA9959_Write_3(Ch13_Cf1, 0x00);
    PCA9959_Write_3(Ch14_Cf1, 0x00);
    PCA9959_Write_3(Ch15_Cf1, 0x00);
    PCA9959_Write_3(Ch16_Cf1, 0x00);
    PCA9959_Write_3(Ch17_Cf1, 0x00);
    PCA9959_Write_3(Ch18_Cf1, 0x00);
    PCA9959_Write_3(Ch19_Cf1, 0x00);
    PCA9959_Write_3(Ch20_Cf1, 0x00);
    PCA9959_Write_3(Ch21_Cf1, 0x00);
    PCA9959_Write_3(Ch22_Cf1, 0x00);
    PCA9959_Write_3(Ch23_Cf1, 0x00);
    
    
    
    PCA9959_Write_3(Ch0_Cf2, 0x00);                      
    PCA9959_Write_3(Ch1_Cf2, 0x00);
    PCA9959_Write_3(Ch2_Cf2, 0x00);
    PCA9959_Write_3(Ch3_Cf2, 0x00);
    PCA9959_Write_3(Ch4_Cf2, 0x00);
    PCA9959_Write_3(Ch5_Cf2, 0x00);
    PCA9959_Write_3(Ch6_Cf2, 0x00);
    PCA9959_Write_3(Ch7_Cf2, 0x00);
    PCA9959_Write_3(Ch8_Cf2, 0x00);
    PCA9959_Write_3(Ch9_Cf2, 0x00);
    PCA9959_Write_3(Ch10_Cf2, 0x00);
    PCA9959_Write_3(Ch11_Cf2, 0x00);
    
    PCA9959_Write_3(Ch12_Cf2, 0x00);
    PCA9959_Write_3(Ch13_Cf2, 0x00);
    PCA9959_Write_3(Ch14_Cf2, 0x00);
    PCA9959_Write_3(Ch15_Cf2, 0x00);
    PCA9959_Write_3(Ch16_Cf2, 0x00);
    PCA9959_Write_3(Ch17_Cf2, 0x00);
    PCA9959_Write_3(Ch18_Cf2, 0x00);
    PCA9959_Write_3(Ch19_Cf2, 0x00);
    PCA9959_Write_3(Ch20_Cf2, 0x00);
    PCA9959_Write_3(Ch21_Cf2, 0x00);
    PCA9959_Write_3(Ch22_Cf2, 0x00);
    PCA9959_Write_3(Ch23_Cf2, 0x00);
    Pin_OE_PCA9959_3_Write(1);
    
    Pin_OE_PCA9959_4_Write(1);
    PageSel_4(ChSel);
    PCA9959_Write_4(Ch0_Cf1, 0x00);                    
    PCA9959_Write_4(Ch1_Cf1, 0x00);
    PCA9959_Write_4(Ch2_Cf1, 0x00); 
    PCA9959_Write_4(Ch3_Cf1, 0x00); 
    PCA9959_Write_4(Ch4_Cf1, 0x00); 
    PCA9959_Write_4(Ch5_Cf1, 0x00); 
    PCA9959_Write_4(Ch6_Cf1, 0x00); 
    PCA9959_Write_4(Ch7_Cf1, 0x00); 
    PCA9959_Write_4(Ch8_Cf1, 0x00); 
    PCA9959_Write_4(Ch9_Cf1, 0x00); 
    PCA9959_Write_4(Ch10_Cf1, 0x00); 
    PCA9959_Write_4(Ch11_Cf1, 0x00);
    
    PCA9959_Write_4(Ch12_Cf1, 0x00);
    PCA9959_Write_4(Ch13_Cf1, 0x00);
    PCA9959_Write_4(Ch14_Cf1, 0x00);
    PCA9959_Write_4(Ch15_Cf1, 0x00);
    PCA9959_Write_4(Ch16_Cf1, 0x00);
    PCA9959_Write_4(Ch17_Cf1, 0x00);
    PCA9959_Write_4(Ch18_Cf1, 0x00);
    PCA9959_Write_4(Ch19_Cf1, 0x00);
    PCA9959_Write_4(Ch20_Cf1, 0x00);
    PCA9959_Write_4(Ch21_Cf1, 0x00);
    PCA9959_Write_4(Ch22_Cf1, 0x00);
    PCA9959_Write_4(Ch23_Cf1, 0x00);
    
    
    
    PCA9959_Write_4(Ch0_Cf2, 0x00);                       
    PCA9959_Write_4(Ch1_Cf2, 0x00);
    PCA9959_Write_4(Ch2_Cf2, 0x00);
    PCA9959_Write_4(Ch3_Cf2, 0x00);
    PCA9959_Write_4(Ch4_Cf2, 0x00);
    PCA9959_Write_4(Ch5_Cf2, 0x00);
    PCA9959_Write_4(Ch6_Cf2, 0x00);
    PCA9959_Write_4(Ch7_Cf2, 0x00);
    PCA9959_Write_4(Ch8_Cf2, 0x00);
    PCA9959_Write_4(Ch9_Cf2, 0x00);
    PCA9959_Write_4(Ch10_Cf2, 0x00);
    PCA9959_Write_4(Ch11_Cf2, 0x00);
    
    PCA9959_Write_4(Ch12_Cf2, 0x00);
    PCA9959_Write_4(Ch13_Cf2, 0x00);
    PCA9959_Write_4(Ch14_Cf2, 0x00);
    PCA9959_Write_4(Ch15_Cf2, 0x00);
    PCA9959_Write_4(Ch16_Cf2, 0x00);
    PCA9959_Write_4(Ch17_Cf2, 0x00);
    PCA9959_Write_4(Ch18_Cf2, 0x00);
    PCA9959_Write_4(Ch19_Cf2, 0x00);
    PCA9959_Write_4(Ch20_Cf2, 0x00);
    PCA9959_Write_4(Ch21_Cf2, 0x00);
    PCA9959_Write_4(Ch22_Cf2, 0x00);
    PCA9959_Write_4(Ch23_Cf2, 0x00);
    Pin_OE_PCA9959_4_Write(0);
    
}

void PCA9959_dummy(void)
{
    uint8_t i=0;
    for(i=16;i>0;i--)
    {
      Pin_MOSI_PCA9959_Write((uint8)(((Side_Ctl << 1) | 1) << 8) | 0x00);
      Pin_SCK_PCA9959_Write(0);
      CyDelayUs(1);
      Pin_SCK_PCA9959_Write(1);
      CyDelayUs(1);
    } 
}

void Reset_Driver(void) 
{
    Pin_RST_PCA9959_Write(0);
    CyDelayUs(1);
    Pin_RST_PCA9959_Write(1);
    CyDelayUs(1);
}

///////////////////////////////****************************////////////////////////////