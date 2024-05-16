/* ========================================
   Copyright Sigtuple, 2022
   All Rights Reserved
   UNPUBLISHED, LICENSED SOFTWARE.

   CONFIDENTIAL AND PROPRIETARY INFORMATION
   WHICH IS THE PROPERTY OF SIGTUPLE.

   ========================================
*/
#include "project.h"
#include <stdlib.h>
#include <string.h>
#include "AS76.h"
#include "variables.h"


uint8_t status_x =0xFF;
uint8_t status_y =0xFF;
uint8_t status_z =0xFF;
uint8_t status_t =0xFF;



int main(void)
{
    CyGlobalIntEnable;                                  /* Enable global interrupts. */
    wait_timer_Init();
    
    
    
    
    LED3_Write(0xFF);
    LED2_Write(0xFF);
    Initialize_PWM();     
    UART_PCB_LOG_Start();   
    Write_Debug_UART_Char("PCB On/PCB RESET**********  \r\n");
    Initialize_USB();                                   /* Start USB to communicate with motherbord. */
    Initialize_And_Start_All_Opt_Encoder();             /* Start optical decoder. */    
    SPIM_Start();                                       /* SPI communication start for motor driver. */    
    Initialize_Motor(TMC5160_nCS_MotorX);
    CyDelayUs(100);
    Initialize_Motor(TMC5160_nCS_MotorY); 
    CyDelayUs(100);
    Initialize_Motor(TMC5160_nCS_MotorZ); 
    CyDelayUs(100);
    Initialize_Motor(TMC5160_nCS_MotorT); 
    CyDelayUs(100);
    Initialize_Motor(TMC5160_nCS_MotorO); 
    CyDelayUs(100);

 
    // API for Homing X,Y,Z,T
    //TMC5160_MotorZ_EN_Write(0x00);
    CyDelay(100);
    //homeZ(TMC5160_nCS_MotorZ);
    //TMC5160_MotorX_EN_Write(0x00);
    CyDelay(100);
    //homeX(TMC5160_nCS_MotorX);
    //TMC5160_MotorY_EN_Write(0x00);
    CyDelay(100);
    //homeY(TMC5160_nCS_MotorY);
    
    //TMC5160_MotorT_EN_Write(0x00);
    //homeT(TMC5160_nCS_MotorT);
    //TMC5160_MotorT_EN_Write(0xFF); 
    //TMC5160_MotorO_EN_Write(0x00);
    update_max_velocity(6200, TMC5160_nCS_MotorO);
    
    QuadDec_X_SetCounter(0x00) ;
    QuadDec_Y_SetCounter(0x00) ;  
    
    LED3_Write(0x00);
    LED2_Write(0x00);
    
   
        
////////////////////////////////////////// LOOP ///////////////////////////////////////////////////         
        
    for (;;)  
    {    
        Is_USB_Unpluged();                              /* Reset MCU if USB unplugged or plugged. */
        if (0 != USB_DataIsReady())                     /* Check for input data from host. */
        {       
            count = USB_GetAll(USB_received);           /* Read received data and re-enable OUT endpoint. */
            if(count >= 2)                              /* Check if data id more then 2 bytes. */
            {
                Write_Debug_UART_Char("DATA RECEIVED  \r\n");
                LED2_Write(0xFF);
                Process_USB_Data();   
                LED2_Write(0x00);
                  /* Process The USB incoming data. */
                

            }
        }            
    
           
   
        
      
    // Test API for Movement Check with error correction 
    //goTo_XYZ(1656000,556000,0); 
    //goTo_XYZ(2560000,800000,60000);
    //CyDelayUs(50);;
    //goTo_XYZ((51200*40),(51200*6),(51200*7)); 
    //CyDelayUs(50); 
    //goTo_XYZ((51200*60),(51200*15),(51200*10)); 
    //CyDelayUs(50);    
    //goTo_XYZ(0,0,0); 
    //CyDelayUs(50);  

    CyDelayUs(100);

        
        }    
   
}

/* [] END OF FILE *///*************************/
