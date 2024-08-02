/* ========================================
 *
 * Copyright Sigtuple, 2022
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF SIGTUPLE.
 *
 * ========================================
*/

#include <stdint.h>
#include <stdbool.h>
#include "project.h"
#include <stdio.h>
#include <math.h>
#include "configuration.h"
#include <stdlib.h>


bool Is_Slide_On_Gripper;
uint16 count;
uint8 USB_received[64];
int8  USB_transmit[47];
extern bool Time_Out_Error;
#define OneRotation   51200

//Function Decleration

void Initialize_Motor(uint8_t Motor);
void Initialize_And_Start_All_Opt_Encoder();
// Go to Function asks motor to go to particular position
int goTo_X(int32 Position_X_Requested);
int goTo_Y(int32 Position_Y_Requested);
int goTo_Z(int32 Position_Z_Requested);
int goTo_T(int32 Position_Z_Requested);
int goTo_XYZ(int32 Position_X_Requested,int32 Position_Y_Requested,int32 Position_Z_Requested);


bool if_all_homing_done(); // checks if all homing actions were performed or not

void Initialize_PWM();
int set_CondenserLED();
int set_BarcodeCondenser_LED();
int Beep_Once();
int Beep_Twice();
int Long_Beep();
void Set_Backlight_LED(uint8_t value);



void Read_All_Optical_Encoder();
void Process_USB_Data();
void Send_Feedback_to_USB(int Error);
void Is_USB_Unpluged();
void Reset_If_USB_Hanged();
void Initialize_USB();
void IS_USB_Unpluged();
void Clear_USB_RX_Buffer();
void Clear_Pending_USB_Data();
void Write_Debug_UART_Char(char Str[]);
void Write_Debug_UART_Int(int32 num);
void Reset_All_L6470_Motor();
void Configure_All_XYZ_L6470_Motor();
void Configure_L6470_For_X_Motor();
void Configure_L6470_For_Y_Motor();
void Configure_L6470_For_Z_Motor();
void Set_Speed();
void set_no_of_execution();
int check_If_Home_XYZ_done();
int check_Error(char Axis, char command_in_progress );
unsigned long FSCalc(float stepsPerSec);
unsigned long MaxSpdCalc(float stepsPerSec);
uint8_t Data_To_Transfer(uint8_t data);
void SetParam(uint8_t param, unsigned long value);
void Move(uint8_t dir, unsigned long n_step);
void Error_Check();
void disconnect_all_motor();
void Enable_Encoder_X(int steps);
void Enable_Encoder_Y(int steps);
void Enable_Encoder_Z(int steps);
void Enable_Encoder_T(int steps);
void UART_print_all_values();

// SPI nCS Pin
#define TMC5160_nCS_MotorX  0x00
#define TMC5160_nCS_MotorY  0x01
#define TMC5160_nCS_MotorZ  0x02
#define TMC5160_nCS_MotorT  0x03
#define TMC5160_nCS_MotorO  0x04


// Command status, code and data for USB
#define HomeX                              0x007A
#define HomeY                              0x007B
#define HomeZ                              0x007C 
#define HomeT                              0x007D
#define GotoX                              0x07A0  
#define GotoY                              0x07B0  
#define GotoXYZ                            0x07C0 
#define GotoZ                              0x07D0
#define GotoT                              0x07E0
#define GotoZ_Vs                           0x07D1
#define GotoO_Vs                           0x07D2
#define GotoXYZ_Vs                         0x07C1
#define Set_LED_voltage                    0x7A00 
#define Set_Backlight                      0x7E00
#define Set_BarClight                      0x7F00
#define Set_OilDispenser                   0x007E
#define Status                             0x00FE
#define SetSpeed                           0x7B00 
#define SetNoOfExecution                   0x7C00 
#define SetMaxError                        0x7D00
#define S_LED_On                           0x006E
#define S_LED_Off                          0x006F
#define Get_Status                         0x00FE
#define PCB_Reset                          0x00FF
#define Stop_All_Motor                     0x0080
#define Pause                              0x0081
#define Resume                             0x0082
#define GSV2                               0x7383
#define GSV2_1                             0x8383
#define GSV2_3                             0x7373
#define GSV2LR                             0x9393




//Error Codes
#define Error_Code                                      0x0F0F// Error Code 
#define No_Error                                        0xFA00// Error No:- 0
#define X_Motor_Not_Working                             0xFA01// Error No:- 1
#define X_Encoder_Not_Working                           0xFA02// Error No:- 2
#define X_Switch_Not_Working                            0xFA17// Error No:- 3
#define X_Motor_Driver_Fault                            0xFA07// Error No:- 4
#define Requested_X_Step_Exceeding_The_Limit            0xFA11// Error No:- 5
#define X_Homing_Not_Done_Yet                           0xFA1D// Error No:- 5
#define Y_Motor_Not_Working                             0xFA03// Error No:- 7
#define Y_Encoder_Not_Working                           0xFA04// Error No:- 8
#define Y_Switch_Not_Working                            0xFA18// Error No:- 9
#define Y_Motor_Driver_Fault                            0xFA08// Error No:- 10 
#define Requested_Y_Step_Exceeding_The_Limit            0xFA12// Error No:- 11
#define Y_Homing_Not_Done_Yet                           0xFA1E// Error No:- 12
#define Z_Motor_Not_Working                             0xFA05// Error No:- 13
#define Z_Encoder_Not_Working                           0xFA06// Error No:- 14
#define Z_Switch_Not_Working                            0xFA19// Error No:- 15          
#define Z_Motor_Driver_Fault                            0xFA09// Error No:- 16 
#define Requested_Z_Step_Exceeding_The_Limit            0xFA13// Error No:- 17
#define Z_Homing_Not_Done_Yet                           0xFA1F// Error No:- 18
#define Wrong_Command_Received                          0xFA22// Error No:- 19
#define PCB_Paused                                      0xFA23// Error No:- 20
#define PCB_Busy                                        0xFA24// Error No:- 21
#define X_Motor_Busy                                    0xFA25// Error No:- 22
#define Y_Motor_Busy                                    0xFA26// Error No:- 23
#define Z_Motor_Busy                                    0xFA27// Error No:- 24
#define T_Motor_Busy                                    0xFA28// Error No:- 24
#define All_Homing_Not_Done_Yet                         0xFA29// Error No:- 5
#define T_Motor_Not_Working                             0xFA2B// Error No:- 1
#define T_Encoder_Not_Working                           0xFA2C// Error No:- 2
#define T_Switch_Not_Working                            0xFA2D// Error No:- 3
#define T_Motor_Driver_Fault                            0xFA2E// Error No:- 4
#define Requested_T_Step_Exceeding_The_Limit            0xFA2A// Error No:- 5
#define T_Homing_Not_Done_Yet                           0xFA2F// Error No:- 5
#define All_Motors_Homing_Not_Done                      0xFA29
#define O_Motor_Not_Working                             0xFA30// Error No:- 3

/* The USB_received Buffer size Inter_Stage equal to the maximum packet size of the IN and OUT bulk endpoints.

The USB_received Buffer size is equal to the maximum packet size of the IN and OUT bulk endpoints.

[] END OF FILE */
