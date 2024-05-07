
/* ========================================

   Copyright Sigtuple, 2022
   All Rights Reserved
   UNPUBLISHED, LICENSED SOFTWARE.

   CONFIDENTIAL AND PROPRIETARY INFORMATION
   WHICH IS THE PROPERTY OF SIGTUPLE.

   ========================================
*/
#include "AS76.h"
#include "variables.h"
#include "project.h"
#include "math.h"
#include "configuration.h"
#include <stdlib.h>

bool Time_Out_Error = true;
unsigned int command;
int Error = 0;

int32 Position_Y_Requested = 0; // Variable to hold position of Motor X in uSteps 51200 uSteps = 1 rotation of the motor
int32 Position_X_Requested = 0; // Variable to hold position of Motor X in uSteps 51200 uSteps = 1 rotation of the motor
int32 Position_Z_Requested = 0; // Variable to hold position of Motor X in uSteps 51200 uSteps = 1 rotation of the motor
int32 Position_T_Requested = 0; // Variable to hold position of Motor X in uSteps 51200 uSteps = 1 rotation of the motor

int32 time_ms   = 0;
int32 oil_speed = 0;
int32 oil_dir   = 0;

volatile int32 X_QuadPosition = 0; // Variable to hold position of Motor X in encoder steps, this variable multiplied by the X Motor Pitch factor gives the uSteps, (Quadposition * X_Pitchfactor = X_Position in uSteps)
volatile int32 Y_QuadPosition = 0; // Variable to hold position of Motor Y in encoder steps, this variable multiplied by the Y Motor Pitch factor gives the uSteps, (Quadposition * Y_Pitchfactor = Y_Position in uSteps)
volatile int32 Z_QuadPosition = 0; // Variable to hold position of Motor Z in encoder steps, this variable multiplied by the Z Motor Pitch factor gives the uSteps, (Quadposition * Z_Pitchfactor = Z_Position in uSteps)
volatile int32 T_QuadPosition = 0; // Variable to hold position of Motor T in encoder steps, this variable multiplied by the T Motor Pitch factor gives the uSteps, (Quadposition * T_Pitchfactor = T_Position in uSteps)
int EncoderTZSelect = 0; //Variable to indicate which encoder is being currently selected Z or T
int Buffer_Z_QuadPosition = 0; //Buffer variable to store Z Encoder value when T Encoder channel is been used
int Buffer_T_QuadPosition = 0; //Buffer variable to store T Encoder value when Z Encoder channel is been used

float X_Pitchfactor = 12.8; //Pitchfactor = 51200/(Encoder CPR * 4), where 51200 is the uStep required to make 1 rotation, 4 is the multiplication(Interpolation) factor used in the firmware design schematic, and encoder CPR is the number of pulses generated from encoder for 1 rotation
float Y_Pitchfactor = 12.8; //Pitchfactor = 51200/(Encoder CPR * 4), where 51200 is the uStep required to make 1 rotation, 4 is the multiplication(Interpolation) factor used in the firmware design schematic, and encoder CPR is the number of pulses generated from encoder for 1 rotation
float Z_Pitchfactor = 3.2;  //Pitchfactor = 51200/(Encoder CPR * 4), where 51200 is the uStep required to make 1 rotation, 4 is the multiplication(Interpolation) factor used in the firmware design schematic, and encoder CPR is the number of pulses generated from encoder for 1 rotation
float T_Pitchfactor = 3.2;  //Pitchfactor = 51200/(Encoder CPR * 4), where 51200 is the uStep required to make 1 rotation, 4 is the multiplication(Interpolation) factor used in the firmware design schematic, and encoder CPR is the number of pulses generated from encoder for 1 rotation

unsigned int Motor_Speed_X = (51200*6); //Default_X_Motor_Speed - 6 Rotations per second;
unsigned int Motor_Speed_Y = (51200*6); //Default_Y_Motor_Speed - 6 Rotations per second;
unsigned int Motor_Speed_Z = (51200*6); //Default_Z_Motor_Speed - 3 Rotations per second;

bool HomeX_done = true; //Variable to indicate if Homing procedure done  or not in X Motor, intial value is set true for algorithm logic
bool HomeY_done = true; //Variable to indicate if Homing procedure done  or not in Y Motor, intial value is set true for algorithm logic
bool HomeZ_done = true; //Variable to indicate if Homing procedure done  or not in Z Motor, intial value is set true for algorithm logic
bool HomeT_done = true; //Variable to indicate if Homing procedure done  or not in T Motor, intial value is set true for algorithm logic

bool HomeX_done_Buffer = false; //Variable to indicate if Homing procedure done  or not in X Motor, intial value is set true for algorithm logic
bool HomeY_done_Buffer = false; //Variable to indicate if Homing procedure done  or not in Y Motor, intial value is set true for algorithm logic
bool HomeZ_done_Buffer = false; //Variable to indicate if Homing procedure done  or not in Z Motor, intial value is set true for algorithm logic
bool HomeT_done_Buffer = false; //Variable to indicate if Homing procedure done  or not in T Motor, intial value is set true for algorithm logic

// PWM Value for Condenser LED and Barcode LED
int PWM_Condenser_comare_value = 200;
int PWM_barcode_comare_value = 0;

// Variable to store the status byte of the corresponding motor driver
extern uint8_t status_x;
extern uint8_t status_y;
extern uint8_t status_z;
extern uint8_t status_t;


uint16_t ms_count = 0;
bool exit_loop =0;
CY_ISR(wait_interrupt_Handler) {
    ms_count++;
     
    if(ms_count == 11000) 
    { // ~30 second
        
        exit_loop = 1;
        ms_count = 0; // reset ms counter
    }
}

//Motor Movment Functions Start-------------------------------------------------------

/* --------------------------------------------------------------------------------------------
Function Name        : GotoPos

Prerequist Knowledge : TMC5160 Register Sets, Stepper Motor

Function Description : This Function is used to move the stepper motor to a desired position in the
                       provided axis

Return Type & Data   : Void

Variable Updation:   : Nil

Numnber of Arguments : 2

-----Argument 1-----
Name                 : Pos
Tupe                 : int
Description          : This Argument Represents the Target postion in 1/256 microsteps to which the 
                       stepper should move
Condition            : Nil                       
--------------------

-----Argument 2-----
Name                 : Motor
Tupe                 : uint8_t
Description          : This Argument Represents the driver channel
Condition            : This Value must range from 0x00 to 0x04 since there are only 5 channels
                       available in AS76 System Configuration, condition to be checked in 
                       SPI_MOTOR_CHIP_SELECT Function                       
--------------------



---------------------------------------------------------------------------------------------*/
void GotoPos(int Pos, uint8_t Motor)
{
    Write_32bitSPI_DATA (0x20  , (int) 0x00000000, Motor );
    Write_32bitSPI_DATA (0x05  , Pos, Motor );
    Write_32bitSPI_DATA (0x2D  , Pos, Motor );   

}

///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////Homing X//////////////////////////////////////////

/* --------------------------------------------------------------------------------------------
Function Name        : homeX

Prerequist Knowledge : Homing of stepper motor system, TM5160 Datasheet, Encoders

Function Description : This Function is used to home the motor X, where motor moves at specific
                       Low speed towards left until it hits the limit switch on the left side then 
                       motor rotates 1 rotation next the motor moves at specific Low speed towards 
                       left until it hits the limit switch then motor gain moves 1 rotaion with step
                       loss correction and that point TMC5160 marks as position 0 and resets the X 
                       Channel encoder.

Return Type & Data   :Void

Variable Updation: status_x, Error, X_QuadPosition

Numnber of Arguments : 1

-----Argument 1-----
Name                 : Motor
Tupe                 : uint8_t
Description          : This Argument Represents the driver channel
Condition            : This Value must range from 0x00 to 0x04 since there are only 5 channels
                       available in AS76 System Configuration, condition to be checked in 
                       SPI_MOTOR_CHIP_SELECT Function                       
--------------------



---------------------------------------------------------------------------------------------*/

void homeX(uint8_t Motor)
{
    update_max_velocity((307200), Motor); // Set Motor to low speed
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor ); // Move the motor to Left continuously
    CyDelayUs(200);
    Read_32bitSPI_DATA(0x04, Motor, &status_x); // Read the status register of TMC5160
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_x); // Read the status register of TMC5160
    while ( (status_x & 0x40) == 0x00) // Condition to check if the Left limit switch is pressed or not
    {
       wait_timer_Start();
       wait_interrupt_StartEx(wait_interrupt_Handler);
       Read_32bitSPI_DATA(0x04, Motor, &status_x); // Read the status register of TMC5160
       CyDelayUs(100);
       if(exit_loop == 1)
       {
        Error = 1;
        Send_Feedback_to_USB(Error);
        wait_timer_Stop();
        Write_32bitSPI_DATA (0x20  , (int) 0x00000000, Motor );
        Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); // Mark the current postion as 0
        Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor ); // Set thye target position as 0
        exit_loop = 0;
        Error =0;
        return;        
    }
    }    
    wait_timer_Stop();
    exit_loop =0;
    
    
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); //Write the X_Actual Register of TMC5160 to 0, which makes the current position as 0
    CyDelayUs(10);
    /*
    GotoPos(((256*200)*2), Motor); // Move the motor 2 rotations (102400 uSteps)
    CyDelayUs(500);
    // Read the status byte register to whther the required position is reached by the motor or not, read it atleast twice before checking the codition to avoid any false raeding
    Read_32bitSPI_DATA(0x04, Motor, &status_x); // Read the status register of TMC5160
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_x); // Read the status register of TMC5160
    while ( (status_x & 0x20) == 0x00) // Check if target position is reached or not
    {
        Read_32bitSPI_DATA(0x04, Motor, &status_x); // Read the status register of TMC5160
        CyDelayUs(100);
       
    }
    
    // Till the above point of code 1st homing is done repeat the same procedure at lower speed to be more accurate with error correction mechanism
    Write_32bitSPI_DATA (0x0B  , (int) 127, Motor );
    Write_32bitSPI_DATA (0x11  , (int) 0x00070103, Motor );
    update_max_velocity((53687), Motor); // Update motor speed to 1 rotation/second
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor ); // // Move the motor to Left continuously
    CyDelayUs(200);
    Read_32bitSPI_DATA(0x04, Motor, &status_x);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_x);
    while ( (status_x & 0x40) == 0x00)
    {
       Read_32bitSPI_DATA(0x04, Motor, &status_x);
       CyDelayUs(100);
    }
*/
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor);
    //X_last_position = 0;
    QuadDec_X_SetCounter(0);
    HomeX_done = true;
    HomeY_done = true;
    HomeZ_done = true;
    HomeT_done = true;
    CyDelayUs(100);
    goTo_X((256*200)*1); // Move the motor 1 rotation with error corrction mechanism based on encoder feedback
    HomeX_done = HomeX_done_Buffer;
    HomeY_done = HomeY_done_Buffer;
    HomeZ_done = HomeZ_done_Buffer;
    HomeT_done = HomeT_done_Buffer;
    CyDelayUs(100);
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); // Mark the current postion as 0
    Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor ); // Set thye target position as 0
    update_max_velocity(381178, Motor); // update the motor speed to to 10 rotations per second 53687
    Write_32bitSPI_DATA (0x0B  , (int) 150, Motor );
    Write_32bitSPI_DATA (0x10  , (int) 0x00070101, Motor );
    //Write_32bitSPI_DATA (0x25  , (51200*5)-100, Motor );


    QuadDec_X_SetCounter(0); //set the encoder counter value as 0
    X_QuadPosition =0 ; // set the encoder variable to 0
    HomeX_done = true;
    HomeX_done_Buffer = true;
    Write_Debug_UART_Char("HomeX executed  \r\n");

}

///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////Homing Y//////////////////////////////////////////

/* --------------------------------------------------------------------------------------------
Function Name        : homeY

Prerequist Knowledge : Homing of stepper motor system, TM5160 Datasheet, Encoders

Function Description : This Function is used to home the motor Y, where motor moves at specific
                       Low speed towards left until it hits the limit switch on the left side then 
                       motor rotates 1 rotation next the motor moves at specific Low speed towards 
                       left until it hits the limit switch then motor gain moves 1 rotaion with step
                       loss correction and that point TMC5160 marks as position 0 and resets the Y 
                       Channel encoder.

Return Type & Data   :Void

Variable Updation: status_y, Error, Y_QuadPosition

Numnber of Arguments : 1

-----Argument 1-----
Name                 : Motor
Tupe                 : uint8_t
Description          : This Argument Represents the driver channel
Condition            : This Value must range from 0x00 to 0x04 since there are only 5 channels
                       available in AS76 System Configuration, condition to be checked in 
                       SPI_MOTOR_CHIP_SELECT Function                       
--------------------



---------------------------------------------------------------------------------------------*/

void homeY(uint8_t Motor)
{
    update_max_velocity((307200), Motor);
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor );
    CyDelayUs(50);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    while ( (status_y & 0x40) == 0x00)
    {
        wait_timer_Start();
        wait_interrupt_StartEx(wait_interrupt_Handler);
        Read_32bitSPI_DATA(0x04, Motor, &status_y);
       
        if(exit_loop == 1)
        {
        Error = 8;
        Send_Feedback_to_USB(Error);
        wait_timer_Stop();
        Write_32bitSPI_DATA (0x20  , (int) 0x00000000, Motor );
        Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); // Mark the current postion as 0
        Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor ); // Set thye target position as 0
        exit_loop = 0;
        Error = 0;
        return;
        }
    CyDelayUs(100);
    }
    wait_timer_Stop();
    exit_loop =0;
    
    
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor);
    CyDelayUs(10);
    /*
    GotoPos(((256*200)*1), Motor);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    while ( (status_y & 0x20) == 0x00)
    {
       Read_32bitSPI_DATA(0x04, Motor, &status_y);
        CyDelayUs(100);
       
    }
    Write_32bitSPI_DATA (0x0B  , (int) 180, Motor );
    Write_32bitSPI_DATA (0x10  , (int) 0x00070103, Motor );
    update_max_velocity(53687, Motor);
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor );
    CyDelayUs(200);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    while ( (status_y & 0x40) == 0x00)
    {
       Read_32bitSPI_DATA(0x04, Motor, &status_y);
       CyDelayUs(100);
    }
    */

    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor);
    //Y_last_position = 0;
    QuadDec_Y_SetCounter(0);
    HomeX_done = true;
    HomeY_done = true;
    HomeZ_done = true;
    HomeT_done = true;
    CyDelayUs(100);
    //goTo_Y((256*200)*1);
    goTo_Y(19200);
    HomeX_done = HomeX_done_Buffer;
    HomeY_done = HomeY_done_Buffer;
    HomeZ_done = HomeZ_done_Buffer;
    HomeT_done = HomeT_done_Buffer;
    CyDelayUs(100);
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); 
    Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor );
    update_max_velocity(381178, Motor);
    Write_32bitSPI_DATA (0x0B  , 0, Motor );
    Write_32bitSPI_DATA (0x10  , (int) 0x00070101, Motor );
    //Write_32bitSPI_DATA (0x25  , (51200*5)-100, Motor );

    //Y_last_position = 0;
    QuadDec_Y_SetCounter(0);
    X_QuadPosition =0 ;
    HomeY_done = true;
    HomeY_done_Buffer = true;
    Write_Debug_UART_Char("HomeY executed  \r\n");

}

////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////Homing Z//////////////////////////////////////////

/* --------------------------------------------------------------------------------------------
Function Name        : homeZ

Prerequist Knowledge : Homing of stepper motor system, TM5160 Datasheet, Encoders

Function Description : This Function is used to home the motor Z, where motor moves at specific
                       Low speed towards left until it hits the limit switch on the left side then 
                       motor rotates 1 rotation next the motor moves at specific Low speed towards 
                       left until it hits the limit switch then motor gain moves 1 rotaion with step
                       loss correction and that point TMC5160 marks as position 0 and resets the Z 
                       Channel encoder.

Return Type & Data   :Void

Variable Updation: status_z, Error, Z_QuadPosition

Numnber of Arguments : 1

-----Argument 1-----
Name                 : Motor
Tupe                 : uint8_t
Description          : This Argument Represents the driver channel
Condition            : This Value must range from 0x00 to 0x04 since there are only 5 channels
                       available in AS76 System Configuration, condition to be checked in 
                       SPI_MOTOR_CHIP_SELECT Function                       
--------------------



---------------------------------------------------------------------------------------------*/

void homeZ(uint8_t Motor)
{
    update_max_velocity((53687*2), Motor);
    Enable_Encoder_Z(-Buffer_Z_QuadPosition);
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor );
    CyDelayUs(50);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    while ( (status_z & 0x40) == 0x00)
    {
       wait_timer_Start();
       wait_interrupt_StartEx(wait_interrupt_Handler);
       Read_32bitSPI_DATA(0x04, Motor, &status_z);
       if(exit_loop == 1)
            {
            Error = 15;
            Send_Feedback_to_USB(Error);
            wait_timer_Stop();
            Write_32bitSPI_DATA (0x20  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); // Mark the current postion as 0
            Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor ); // Set thye target position as 0
            exit_loop = 0;
            return;
            //break;
            }
       CyDelayUs(100);
    }
    wait_timer_Stop();
    exit_loop =0;
    
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor);
    //Z_last_position = 0;
    Enable_Encoder_Z(0);
    Buffer_Z_QuadPosition=0;
    CyDelayUs(10);
    /*
    GotoPos(((256*200)*1), Motor);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    while ( (status_z & 0x20) == 0x00)
    {
       Read_32bitSPI_DATA(0x04, Motor, &status_z);
        CyDelayUs(100);
       
    }
    update_max_velocity(53687, Motor);
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor );
    CyDelayUs(200);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    while ( (status_z & 0x40) == 0x00)
    {
       Read_32bitSPI_DATA(0x04, Motor, &status_z);
       CyDelayUs(100);
    }
    */

    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor);
    //Z_last_position = 0;
    Enable_Encoder_Z(0);
    Buffer_Z_QuadPosition=0;
    HomeX_done = true;
    HomeY_done = true;
    HomeZ_done = true;
    HomeT_done = true;
    CyDelayUs(100);
    goTo_Z(((256*200)*1));
    HomeX_done = HomeX_done_Buffer;
    HomeY_done = HomeY_done_Buffer;
    HomeZ_done = HomeZ_done_Buffer;
    HomeT_done = HomeT_done_Buffer;
    CyDelayUs(100);
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); 
    Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor );
    update_max_velocity(53687*2, Motor);

    //Z_last_position = 0;
    Enable_Encoder_Z(0);
    Buffer_Z_QuadPosition=0;
    HomeZ_done = true;
    HomeZ_done_Buffer = true;
    Write_Debug_UART_Char("HomeZ executed  \r\n");

}

///////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////Homing T//////////////////////////////////////////

void homeT(uint8_t Motor)
{
    TMC5160_MotorT_EN_Write(0x00);
    CyDelayUs(100);
    update_max_velocity(12800, Motor);
    Enable_Encoder_T(-Buffer_T_QuadPosition);
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor );
    CyDelayUs(50);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    while ( (status_z & 0x40) == 0x00)
    {
       wait_timer_Start();
       wait_interrupt_StartEx(wait_interrupt_Handler);
       Read_32bitSPI_DATA(0x04, Motor, &status_z);
       if(exit_loop == 1)
            {
            Error = 22;
            Send_Feedback_to_USB(Error);
            wait_timer_Stop();
            Write_32bitSPI_DATA (0x20  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); // Mark the current postion as 0
            Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor ); // Set thye target position as 0
            exit_loop = 0;
            Error =0;
            return;
            //break;
            }
       CyDelayUs(100);
    }
    wait_timer_Stop();
    exit_loop =0;
    
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor);
    CyDelayUs(10);
    /*
    GotoPos((12800), Motor);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    CyDelayUs(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_z);
    while ( (status_z & 0x20) == 0x00)
    {
       Read_32bitSPI_DATA(0x04, Motor, &status_z);
        CyDelayUs(100);
       
    }
    update_max_velocity(12800, Motor);
    Write_32bitSPI_DATA (0x20  , (int) 0x00000002, Motor );
    CyDelayUs(200);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    CyDelay0Us(500);
    Read_32bitSPI_DATA(0x04, Motor, &status_y);
    while ( (status_y & 0x40) == 0x00)
    {
       Read_32bitSPI_DATA(0x04, Motor, &status_y);
       CyDelayUs(100);
    }
    */
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor);
    //T_last_position = 0;
    Enable_Encoder_T(0);
    Buffer_T_QuadPosition=0;
    HomeX_done = true;
    HomeY_done = true;
    HomeZ_done = true;
    HomeT_done = true;
    CyDelayUs(100); 
    goTo_T(3800);
    HomeX_done = HomeX_done_Buffer;
    HomeY_done = HomeY_done_Buffer;
    HomeZ_done = HomeZ_done_Buffer;
    HomeT_done = HomeT_done_Buffer;
    CyDelayUs(100);
    Write_32bitSPI_DATA (0x21  , (int) 0x0000000, Motor); 
    Write_32bitSPI_DATA (0x2D  , 0x00000000, Motor );
    update_max_velocity(12800, Motor);

    //T_last_position = 0;
    Enable_Encoder_T(0);
    Buffer_T_QuadPosition=0;
    HomeT_done = true;
    HomeT_done_Buffer = true;
    Write_Debug_UART_Char("HomeT executed  \r\n");
    TMC5160_MotorT_EN_Write(0xFF);
    CyDelayUs(100);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Go to Position in X Axis//////////////////////////////////////////

int goTo_X(int32 Position_X_Requested)
{
      
    if(if_all_homing_done())
    
    {
        Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorY );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorZ );
        Write_32bitSPI_DATA (0x10  , (int) 0x0007030A, TMC5160_nCS_MotorX );
        //Position_X_Move = Position_X_Move + Position_X_Requested;
        Error = 0;
        Read_All_Optical_Encoder();
        //X_last_position = X_QuadPosition;
        Write_Debug_UART_Char("GotoX Command Recived--->");
        GotoPos(Position_X_Requested, TMC5160_nCS_MotorX); // If provided value is position and not the steps to move
        WaitTillPositionReached (TMC5160_nCS_MotorX);
        CyDelayUs(50);
        //GotoPos(Position_X_Move, TMC5160_nCS_MotorX); // If provided value is steps to move and not the actual position
        Write_Debug_UART_Int(Position_X_Requested);
        Write_Debug_UART_Char("  \r\n");
        Step_correction_x(Position_X_Requested);
        return Error;
    }
    else
    {
        Write_Debug_UART_Char("Homing Not Done");
        Error = 32;
        return Error;
    }
    
}

int Step_correction_x(int32 steps)
{  
    int32 Encoder_Position_X_Requested =0;
    uint8_t temp;
    int32 new_step=0;
    //int32 diff_encoder_value=0;
    int32 encoder_error_value = 0;
    Encoder_Position_X_Requested = steps/X_Pitchfactor;
    
    for(temp=0; temp<=5; temp++)
    {
    Read_All_Optical_Encoder();
    
    encoder_error_value = Encoder_Position_X_Requested - X_QuadPosition;
    if(encoder_error_value >= 2000)
    {
        Error=  2;
        return Error;
    }
    new_step= encoder_error_value* X_Pitchfactor ;
    
       
    if((abs(encoder_error_value))>= X_max_error_After_Correction )
    {
      new_step = new_step+steps;     
      GotoPos(new_step, TMC5160_nCS_MotorX);
      WaitTillPositionReached (TMC5160_nCS_MotorX);
      CyDelayUs(50);
      Write_32bitSPI_DATA (0x21  , steps, TMC5160_nCS_MotorX );
    }
    }
    Read_All_Optical_Encoder();
    encoder_error_value = Encoder_Position_X_Requested - X_QuadPosition;
    if((temp>5))
    {
     if(((abs(encoder_error_value))>= X_max_error_After_Correction ) && ((abs(encoder_error_value))<2000))
     {
        Write_Debug_UART_Char("Fail to reach X position \r\n");
        LED3_Write(0xFF);
        Error=  1;
     }
    
     else if ( ((abs(encoder_error_value))>2000))
     {
       Write_Debug_UART_Char("X Encoder or X Motor Might Not be Working \r\n");
       Error=  2;
     }
    
     else
     {
        Write_Debug_UART_Char("X position Reached");
        Error = 0;
        Write_32bitSPI_DATA (0x21  , steps, TMC5160_nCS_MotorX );
        CyDelayUs(500);
        
     }
    
    }
    
    return Error;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Go to Position in Y Axis//////////////////////////////////////////

int goTo_Y(int32 Position_Y_Requested)
{   
    if(if_all_homing_done())
    {
        Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorX );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorZ );
        Write_32bitSPI_DATA (0x10  , (int) 0x0007010A, TMC5160_nCS_MotorY );
        
        //Position_Y_Move = Position_Y_Move + Position_Y_Requested;
        Error = 0;
        Read_All_Optical_Encoder();
        //Y_last_position = Y_QuadPosition;
        Write_Debug_UART_Char("GotoX Command Recived--->");
        GotoPos(Position_Y_Requested, TMC5160_nCS_MotorY); // If provided value is position and not the steps to move
        WaitTillPositionReached (TMC5160_nCS_MotorY);
        CyDelayUs(50);
        //GotoPos(Position_X_Move, TMC5160_nCS_MotorX); // If provided value is steps to move and not the actual position
        Write_Debug_UART_Int(Position_Y_Requested);
        Write_Debug_UART_Char("  \r\n");
        Step_correction_y(Position_Y_Requested);
        return Error;
    }
    else
    {
        Write_Debug_UART_Char("Homing Not Done");
        Error = 32;
        return Error;
    }
}

int Step_correction_y(int32 steps)
{  
    uint8_t temp=0;
    int32 new_step=0;
    int32 Encoder_Position_Y_Requested =0;
    //int32 diff_encoder_value=0;
    int32 encoder_error_value = 0;
    Encoder_Position_Y_Requested = steps/12.8;
    
    for(temp=0; temp<=3; temp++)
    {
    Read_All_Optical_Encoder();
    //diff_encoder_value = (X_QuadPosition - X_last_position);
    encoder_error_value = Encoder_Position_Y_Requested - Y_QuadPosition;
    new_step= encoder_error_value*12.8;
    if(encoder_error_value >= 4000)
    {
        Error=  9;
        break;
    }
    if((abs(encoder_error_value))>=3)
    {
      new_step = new_step+steps;     
      GotoPos(new_step, TMC5160_nCS_MotorY);
      WaitTillPositionReached (TMC5160_nCS_MotorY);
      CyDelayUs(50);
      Write_32bitSPI_DATA (0x21  , steps, TMC5160_nCS_MotorY );
    }
    
    }
    
    
    Read_All_Optical_Encoder();
    encoder_error_value = Encoder_Position_Y_Requested - Y_QuadPosition;
    
    if(temp>=4)
    {
     if(((abs(encoder_error_value))>=3) && ((abs(encoder_error_value))<2000) )
     {
        Write_Debug_UART_Char("Fail to reach Y position \r\n");
        LED3_Write(0xFF);
        Error=  8;
     }
    
     else if ( ((abs(encoder_error_value))>2000))
     {
       Write_Debug_UART_Char("Y Encoder or Y Motor Might Not be Working \r\n"); 
       Error=  9;
     }
    
     else
     {
        Write_Debug_UART_Char("Y position Reached");
        Error = 0;
        
     }
    
    }
    
    return Error;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Go to Position in Z Axis/////////////////////////////////////////////


int goTo_Z(int32 Position_Z_Requested)
{
    Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorY );
    Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorX );
    Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorZ );
    Position_Z_Requested =  Position_Z_Requested;
    Enable_Encoder_Z(-Buffer_Z_QuadPosition);
    if(if_all_homing_done())
    {
        Error = 0;
        Read_All_Optical_Encoder();
        //Z_last_position = Z_QuadPosition;
        Write_Debug_UART_Char("GotoZ Command Recived--->");
        GotoPos(Position_Z_Requested, TMC5160_nCS_MotorZ); // If provided value is position and not the steps to move
        WaitTillPositionReached (TMC5160_nCS_MotorZ);
        CyDelayUs(50);
        //GotoPos(Position_X_Move, TMC5160_nCS_MotorX); // If provided value is steps to move and not the actual position
        Write_Debug_UART_Int(Position_Z_Requested);
        Write_Debug_UART_Char("  \r\n");
        Step_correction_z(Position_Z_Requested);
        Read_All_Optical_Encoder();
        Buffer_Z_QuadPosition = Z_QuadPosition;
        return Error;
    }
    else
    {
        Write_Debug_UART_Char("Homing Not Done");
        Error = 32;
        return Error;
    }

}

int Step_correction_z(int32 steps)
{  
    uint8_t temp=0;
    int32 new_step=0;
    int32 Encoder_Position_Z_Requested =0;
    //int32 diff_encoder_value=0;
    int32 encoder_error_value = 0;
    Encoder_Position_Z_Requested = steps/3.2;
    
    for(temp=0; temp<=5; temp++)
    {
    
    Read_All_Optical_Encoder();
    //diff_encoder_value = (X_QuadPosition - X_last_position);
    encoder_error_value = Encoder_Position_Z_Requested - Z_QuadPosition;
    new_step= encoder_error_value*3.2;
    if(encoder_error_value >= 4000)
    {
        Error=  16;
        break;
    }
    if((abs(encoder_error_value))>=3)
    {
      new_step = new_step+steps;     
      GotoPos(new_step, TMC5160_nCS_MotorZ);
      WaitTillPositionReached (TMC5160_nCS_MotorZ);
      CyDelayUs(50);
      Write_32bitSPI_DATA (0x21  , steps, TMC5160_nCS_MotorZ );
    }
    
    }
    
    
    Read_All_Optical_Encoder();
    encoder_error_value = Encoder_Position_Z_Requested - Z_QuadPosition;
    
    if(temp>=4)
    {
     if(((abs(encoder_error_value))>=5) && ((abs(encoder_error_value))<4000) )
     {
        Write_Debug_UART_Char("Fail to reach Z position \r\n");
        LED2_Write(0xFF);
        Error = 15;
     }
    
     else if ( ((abs(encoder_error_value))>4000))
     {
       Write_Debug_UART_Char("Z Encoder or Z Motor Might Not be Working \r\n"); 
       Error = 16;
     }
    
     else
     {
       Write_Debug_UART_Char("Z position Reached");
       Error = 0;
        
     }
    
    }
    
    return Error;
}

/////////////////////////////////////Go to Position in T Axis//////////////////////////////////////////

int goTo_T(int32 Position_T_Requested)
{
    TMC5160_MotorT_EN_Write(0x00);
    CyDelayUs(100);
    Enable_Encoder_T(-Buffer_T_QuadPosition);
    if(if_all_homing_done())
    {
        Error = 0;
        Read_All_Optical_Encoder();        
        Write_Debug_UART_Char("GotoT Command Recived--->");
        GotoPos(Position_T_Requested, TMC5160_nCS_MotorT); // If provided value is position and not the steps to move
        WaitTillPositionReached (TMC5160_nCS_MotorT);
        CyDelayUs(50);
        //GotoPos(Position_X_Move, TMC5160_nCS_MotorX); // If provided value is steps to move and not the actual position
        Write_Debug_UART_Int(Position_T_Requested);
        Write_Debug_UART_Char("  \r\n");
        Step_correction_t(Position_T_Requested);
        Read_All_Optical_Encoder();
        Buffer_T_QuadPosition = T_QuadPosition;
        TMC5160_MotorT_EN_Write(0xFF);
        CyDelayUs (100);
        return Error;
    }
    else
    {
        Write_Debug_UART_Char("Homing Not Done");
        Error = 32;
         TMC5160_MotorT_EN_Write(0xFF);
        CyDelayUs(100);
        return Error;
    }
    //Buffer_T_QuadPosition = T_QuadPosition;
}

int Step_correction_t(int32 steps)
{  
    uint8_t temp=0;
    int32 new_step=0;
    int32 Encoder_Position_T_Requested =0;
    //int32 diff_encoder_value=0;
    int32 encoder_error_value = 0;
    Encoder_Position_T_Requested = steps/3.2;
    
    for(temp=0; temp<=3; temp++)
    {
    Read_All_Optical_Encoder();
    //diff_encoder_value = (X_QuadPosition - X_last_position);
    encoder_error_value = Encoder_Position_T_Requested - T_QuadPosition;
    new_step= encoder_error_value*3.2;
    if(encoder_error_value >= 4000)
    {
        Error=  23;
        break;
    }
    
    if((abs(encoder_error_value))>=5)
    {
      new_step = new_step+steps;     
      GotoPos(new_step, TMC5160_nCS_MotorT);
      WaitTillPositionReached (TMC5160_nCS_MotorT);
      CyDelayUs(50);
      Write_32bitSPI_DATA (0x21  , steps, TMC5160_nCS_MotorT );
    }
    
    }
    
    Read_All_Optical_Encoder();
    encoder_error_value = Encoder_Position_T_Requested - T_QuadPosition;
    
    if(temp>=4)
    {
     if(((abs(encoder_error_value))>=5) && ((abs(encoder_error_value))<4000) )
     {
        Write_Debug_UART_Char("Fail to reach T position \r\n");
        Error = 22;
     }
    
     else if ( ((abs(encoder_error_value))>4000))
     {
       Write_Debug_UART_Char("T Encoder or T Motor Might Not be Working \r\n"); 
       Error = 23;
     }
    
     else
     {
        Write_Debug_UART_Char("T position Reached");
        Error = 0;
        
     }
    
    }
    
    return Error;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Go to Position in XYZ Axis//////////////////////////////////////////////

int goTo_XYZ(int32 Position_X_Requested,int32 Position_Y_Requested,int32 Position_Z_Requested)
{
    Read_All_Optical_Encoder();
    //X_last_position = X_QuadPosition;
    Write_Debug_UART_Char("GotoX Command Recived--->");
    if(Position_X_Requested >= 0)
    { 
    GotoPos(Position_X_Requested, TMC5160_nCS_MotorX); // If provided value is position and not the steps to move
    }
    if(Position_Y_Requested >= 0)
    { 
    GotoPos(Position_Y_Requested, TMC5160_nCS_MotorY);
    }
    if(Position_Z_Requested >= 0)
    { 
    Enable_Encoder_Z(-Buffer_Z_QuadPosition);
    GotoPos(Position_Z_Requested, TMC5160_nCS_MotorZ);
    }
    
    if(Position_X_Requested >= 0)
    {
    WaitTillPositionReached (TMC5160_nCS_MotorX);
    }
    if(Position_Y_Requested >= 0)
    {
    WaitTillPositionReached (TMC5160_nCS_MotorY);
    }
    if(Position_Z_Requested >= 0)
    {
    WaitTillPositionReached (TMC5160_nCS_MotorZ);
    }
    
    if(Position_X_Requested >= 0)
    {
    Step_correction_x(Position_X_Requested);
    //Read_All_Optical_Encoder();
    }
    //Send_Feedback_to_USB(Error);
    if(Position_Y_Requested >= 0)
    {
    Step_correction_y(Position_Y_Requested);
    //Read_All_Optical_Encoder();
    }
    //Send_Feedback_to_USB(Error);
    if(Position_Z_Requested >= 0)
    {
    Step_correction_z(Position_Z_Requested);    
    Read_All_Optical_Encoder();
    Buffer_Z_QuadPosition = Z_QuadPosition;
    }
    Read_All_Optical_Encoder();
    Send_Feedback_to_USB(Error);
    
    CyDelayUs(50);
    return 0;  
        
}


bool if_all_homing_done()
{
    if((HomeY_done == false)&&(Error == 0))
    {
        Error = 12;//Y_Homing_Not_Done_Yet
        Write_Debug_UART_Char("Y_Homing_Not_Done_Yet***********[x12]  \r\n");
        UART_print_all_values();
        return false;
    }
    else if((HomeX_done == false)&&(Error == 0))
    {
        Error = 6;//X_Homing_Not_Done_Yet
        Write_Debug_UART_Char("X_Homing_Not_Done_Yet***********  \r\n");
        UART_print_all_values();
        return false;
    }
    else if((HomeZ_done == false)&&(Error == 0))
    {
        Error = 18;//Z_Homing_Not_Done_Yet
        Write_Debug_UART_Char("Z_Homing_Not_Done_Yet***********  \r\n");
        UART_print_all_values();
        return false;
    } 
   /* else if((HomeT_done == false)&&(Error == 0))
    {
        Error = 27;//T_Homing_Not_Done_Yet
        Write_Debug_UART_Char("Z_Homing_Not_Done_Yet***********  \r\n");
        UART_print_all_values();
        return false;
    } */
    else
    {
        return true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//PWM Functions Start-------------------------------------------------------
void Initialize_PWM()
{
    PWM_CondenserLED_Start();
    PWM_CondenserLED_WriteCompare(PWM_Condenser_comare_value); 
    
    PWM_BarcodeCondenser_LED_Start();
    PWM_BarcodeCondenser_LED_WriteCompare(2);
    
    PWM_Buzzer_Start();
    PWM_Buzzer_WriteCompare(2500);
    CyDelay(200);
    PWM_Buzzer_WriteCompare(0);
    CyDelay(200);
    PWM_Buzzer_WriteCompare(2500);
    CyDelay(200);
    PWM_Buzzer_WriteCompare(0);
}
int set_BarcodeCondenser_LED()//Set Barcode Condenser LED light intensity
{
    PWM_barcode_comare_value = ((unsigned int)USB_received[3] << 8) + USB_received[2];  //Read LED intensity value from USB
    PWM_BarcodeCondenser_LED_WriteCompare((PWM_barcode_comare_value*0.6)/10);    //Writing LED value in to PWM maximum limit is 1200
    Write_Debug_UART_Char("LED Barcode Value Recived--->");
    Write_Debug_UART_Int(PWM_barcode_comare_value);
    Write_Debug_UART_Char("\r\n");
    Write_Debug_UART_Char("Set Barcode LED Command Executed  \r\n");
    return 0;
}

int set_CondenserLED()//Set Condenser LED light intensity
{
    PWM_Condenser_comare_value = ((unsigned int)USB_received[3] << 8) + USB_received[2];  //Read LED intensity value from USB
    PWM_CondenserLED_WriteCompare((PWM_Condenser_comare_value*0.6)/10);    //Writing LED value in to PWM maximum limit is 1200
    Write_Debug_UART_Char(" LED Value Recived--->");
    Write_Debug_UART_Int(PWM_Condenser_comare_value);
    Write_Debug_UART_Char("\r\n");
    Write_Debug_UART_Char("Set LED Command Executed  \r\n");
    return 0;
}

int Beep_Once()//Set Condenser LED light intensity
{
    PWM_Buzzer_WriteCompare(2500);
    CyDelay(200);
    PWM_Buzzer_WriteCompare(0);
    Write_Debug_UART_Char("Beeped Once  \r\n");
    return 0;
}

int Beep_Twice()//Set Condenser LED light intensity
{
    PWM_Buzzer_WriteCompare(2500);
    CyDelay(200);
    PWM_Buzzer_WriteCompare(0);
    CyDelay(200);
    PWM_Buzzer_WriteCompare(2500);
    CyDelay(200);
    PWM_Buzzer_WriteCompare(0);
    Write_Debug_UART_Char("Beeped Twice  \r\n");
    return 0;
}

int Long_Beep()//Set Condenser LED light intensity
{
    PWM_Buzzer_WriteCompare(2500);
    CyDelay(2000);
    PWM_Buzzer_WriteCompare(0);
    CyDelay(200);
    
    Write_Debug_UART_Char("Beeped Long  \r\n");
    return 0;
}

//PWM Functions Stop-------------------------------------------------------

void Set_Backlight_LED(uint8_t value)
{
    Pin_Backlight_Write(value);
}

//Optical Decoder Functions Start-------------------------------------------------------
void Initialize_And_Start_All_Opt_Encoder()//Initialize and start Interrupt for XY encoder count and Z QPRC
{   
    X_QuadPosition = 0;
    Y_QuadPosition = 0;
    Z_QuadPosition =0 ;
    T_QuadPosition=0;
    QuadDec_TZ_Start();
    QuadDec_Y_Start();
    QuadDec_X_Start();

    Enable_Encoder_Z(0);
    Enable_Encoder_T(0);
}


void Enable_Encoder_T(int steps)
{
    EncoderTZSelect = 0; // 0 for T and 1 for Z
    QuadDec_TZ_SetCounter(steps);      
    Encoder_T_Z_Select_Write(0);
}

void Enable_Encoder_Z(int steps)
{
    EncoderTZSelect = 1; // 0 for T and 1 for Z
    QuadDec_TZ_SetCounter(steps);
    Encoder_T_Z_Select_Write(1);
}

void Read_All_Optical_Encoder()//Read all optical encoder value and update XYZ value
{
    if(EncoderTZSelect == 0)
    {
        T_QuadPosition = -QuadDec_TZ_GetCounter();
        Z_QuadPosition = Buffer_Z_QuadPosition;
    }
    if(EncoderTZSelect == 1)
    {
        T_QuadPosition = Buffer_T_QuadPosition;
        Z_QuadPosition = -QuadDec_TZ_GetCounter();
    }
    X_QuadPosition = -QuadDec_X_GetCounter();
    Y_QuadPosition = -QuadDec_Y_GetCounter();
}    
//Optical Decoder Functions Stop-------------------------------------------------------


//USB Functions Start-------------------------------------------------------
void Process_USB_Data()/* Process USB incoming data command. */
{
    //Pin_USB_RX_TX_Indicator_LED_Write(1); /* turn ON LED as a indicator to start process the command. */
    Error = 0;
    command = ((unsigned int)USB_received[1] << 8) + USB_received[0];   /* Reading USB data. */
    /*Compare USB data and execute the command*/

    if (command == HomeX)                                          
    {
        update_max_velocity(381178, TMC5160_nCS_MotorX);
        CyDelay(1);
        goTo_X(0);
        homeX(TMC5160_nCS_MotorX);   
        Send_Feedback_to_USB(Error);
    
    }
    else if (command == HomeY)                           
    {
        update_max_velocity(381178, TMC5160_nCS_MotorY);
        CyDelay(1);
        goTo_Y(0);
        homeY(TMC5160_nCS_MotorY);
        Send_Feedback_to_USB(Error);
        
    }
    else if (command == HomeZ)                           
    {
        update_max_velocity(53687*2, TMC5160_nCS_MotorZ);
        CyDelayUs(100);
        goTo_Z(0);
        homeZ(TMC5160_nCS_MotorZ);
        Send_Feedback_to_USB(Error);
    }
    else if (command == HomeT)                           
    {
        Write_32bitSPI_DATA (0x10  , (int) 0x00070503, TMC5160_nCS_MotorT ); 
        CyDelay(10);
        goTo_T(0);
        homeT(TMC5160_nCS_MotorT);
        Send_Feedback_to_USB(Error);
    }
    else if (command == GotoX)                           
    {
        Position_X_Requested = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2]; //Decode USB Steps
        
        {
            Position_X_Requested = (int)(Position_X_Requested / 4);
            Position_X_Requested = (int)Position_X_Requested * 12.8;
            Error = goTo_X(Position_X_Requested);
        }
        
        
        
        
        Write_32bitSPI_DATA (0x10  , (int) 0x0007010A, TMC5160_nCS_MotorX );
        CyDelay(10);
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorY );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorZ );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorX );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorT ); 
        Send_Feedback_to_USB(Error);
        
        
    }
    else if (command == GotoY)          
    {
        Position_Y_Requested = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2]; //Decode USB Steps
        Position_Y_Requested = (int)(Position_Y_Requested / 4);
        Position_Y_Requested = (int)(Position_Y_Requested * 12.8);
        Error = goTo_Y(Position_Y_Requested);
               
        Write_32bitSPI_DATA (0x10  , (int) 0x0007010A, TMC5160_nCS_MotorY );
        CyDelay(10);        
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorY );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorZ );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorX );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070102, TMC5160_nCS_MotorT ); 
        Send_Feedback_to_USB(Error);
    }
    else if (command == GotoZ)        
    {
        Position_Z_Requested = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2]; //Decode USB Steps
        Position_Z_Requested = (Position_Z_Requested / 16);
        Position_Z_Requested = Position_Z_Requested * 51.2;
        Error = goTo_Z(Position_Z_Requested);
        Send_Feedback_to_USB(Error);
    }
    else if (command == GotoT)        
    {
        Write_32bitSPI_DATA (0x10  , (int) 0x00070503, TMC5160_nCS_MotorT ); 
        Position_T_Requested = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2]; //Decode USB Steps
        Position_T_Requested = (Position_T_Requested / 1);
        Position_T_Requested = Position_T_Requested * 1;
        Error = goTo_T(Position_T_Requested);
        Send_Feedback_to_USB(Error);
        Write_32bitSPI_DATA (0x10  , (int) 0x00070303, TMC5160_nCS_MotorT );
   
    }
    else if ( command == Set_OilDispenser )
    {
        int time_ms=0;
        uint8_t direction=0;
        time_ms = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2];
        if((USB_received[6] == 0x00) || (USB_received[6] == 0x01))
        {
            CyDelayUs(10);
        }
        else
        {
          USB_received[6] = 0x00;
        }
        
        direction = USB_received[6];
        run_pump (time_ms, direction);
        Send_Feedback_to_USB(Error);
    }
    
    else if (command == GotoXYZ)
    {
        Position_X_Requested = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2];
        Position_Y_Requested = ((int32)USB_received[9] << 24) + ((int32)USB_received[8] << 16) + ((int32)USB_received[7] << 8) + (int32)USB_received[6];
        Position_Z_Requested = ((int32)USB_received[13] << 24) + ((int32)USB_received[12] << 16) + ((int32)USB_received[11] << 8) + (int32)USB_received[10];
        
        if(Position_X_Requested >= 0)
        {        
        Position_X_Requested = (Position_X_Requested / 4);
        Position_X_Requested = Position_X_Requested * 12.8;
        }
        if(Position_Y_Requested >= 0)
        { 
        Position_Y_Requested = (Position_Y_Requested / 4);
        Position_Y_Requested = Position_Y_Requested * 12.8;
        }
        if(Position_Z_Requested >= 0)
        { 
        Position_Z_Requested = (Position_Z_Requested / 16);
        Position_Z_Requested = Position_Z_Requested * 51.2;
        }
        
        Error = goTo_XYZ(Position_X_Requested, Position_Y_Requested, Position_Z_Requested);
        CyDelay(10);
        Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorY );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorZ );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorX );
        Write_32bitSPI_DATA (0x10  , (int) 0x00070103, TMC5160_nCS_MotorT );
        Send_Feedback_to_USB(Error);
    }
    
    else if (command == Set_LED_voltage)
    { 
        set_CondenserLED();
        CyDelay(100);
        Send_Feedback_to_USB(Error);  
    }
    
    else if (command == Set_BarClight)
    {
        set_BarcodeCondenser_LED();
        CyDelay(100);
        Send_Feedback_to_USB(Error);  
    }
    
    else if (command == Set_Backlight)
    {
        uint8_t value=0;
        value = USB_received[2];
        if(value == 0)
        {
        value = 0x00;
        }
        else if(value == 1)
        {
        value =0xFF;
        }
        else
        {
        Write_Debug_UART_Char("Backlight LED wronf Value Provided  \r\n");
        }
       
        Pin_Backlight_Write(value);
        Send_Feedback_to_USB(Error);
    }
    
    else if (command == PCB_Reset)                     
    {
        Write_Debug_UART_Char("PCB Reset Command Recived  \r\n");
        Write_Debug_UART_Char("\r\n");
        CyDelay(500);
        Send_Feedback_to_USB(0);
        CyDelay(500);
        CySoftwareReset();
    }
    else if(command == SetSpeed)  
    {
        
        Motor_Speed_X = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2];
        Motor_Speed_Y = ((int32)USB_received[9] << 24) + ((int32)USB_received[8] << 16) + ((int32)USB_received[7] << 8) + (int32)USB_received[6];
        Motor_Speed_Z = ((int32)USB_received[13] << 24) + ((int32)USB_received[12] << 16) + ((int32)USB_received[11] << 8) + (int32)USB_received[10];
        
        Write_Debug_UART_Char("SetNoOfExecution Command Recived  \r\n");
        
        update_max_velocity(Motor_Speed_X, TMC5160_nCS_MotorX);        
        update_max_velocity(Motor_Speed_Y, TMC5160_nCS_MotorY);        
        update_max_velocity(Motor_Speed_Z, TMC5160_nCS_MotorZ);
        Write_Debug_UART_Char("Value received for x,y and z is --->");
        Write_Debug_UART_Int(Motor_Speed_X);
        Write_Debug_UART_Char(",");
        Write_Debug_UART_Int(Motor_Speed_Y);
        Write_Debug_UART_Char(",");
        Write_Debug_UART_Int(Motor_Speed_Z);
        Write_Debug_UART_Char(",");
        Send_Feedback_to_USB(Error);
    }
    
    else if(command == GotoZ_Vs)
    {
    Position_Z_Requested = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2];   
    Motor_Speed_Z = ((int32)USB_received[9] << 24) + ((int32)USB_received[8] << 16) + ((int32)USB_received[7] << 8) + (int32)USB_received[6]; 
    update_max_velocity(Motor_Speed_Z,TMC5160_nCS_MotorZ);    
    Position_Z_Requested = (Position_Z_Requested / 16);
    Position_Z_Requested = Position_Z_Requested * 51.2;
    goTo_Z(Position_Z_Requested);
    Send_Feedback_to_USB(Error);
    }
    
    else if(command == GotoO_Vs)
    {        
    time_ms   = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2];   
    oil_speed = ((int32)USB_received[9] << 24) + ((int32)USB_received[8] << 16) + ((int32)USB_received[7] << 8) + (int32)USB_received[6]; 
    oil_dir   = USB_received[10];
    run_pumpvs (time_ms, oil_speed, oil_dir);
    Error = 0;
    Send_Feedback_to_USB(Error);
    }
    
    else if (command == GotoXYZ_Vs)
    {
        Position_X_Requested = ((int32)USB_received[5] << 24) + ((int32)USB_received[4] << 16) + ((int32)USB_received[3] << 8) + (int32)USB_received[2];
        Position_Y_Requested = ((int32)USB_received[9] << 24) + ((int32)USB_received[8] << 16) + ((int32)USB_received[7] << 8) + (int32)USB_received[6];
        Position_Z_Requested = ((int32)USB_received[13] << 24) + ((int32)USB_received[12] << 16) + ((int32)USB_received[11] << 8) + (int32)USB_received[10];
        
        Motor_Speed_X = ((int32)USB_received[17] << 24) + ((int32)USB_received[16] << 16) + ((int32)USB_received[15] << 8) + (int32)USB_received[14];
        Motor_Speed_Y = ((int32)USB_received[21] << 24) + ((int32)USB_received[20] << 16) + ((int32)USB_received[19] << 8) + (int32)USB_received[18];
        Motor_Speed_Z = ((int32)USB_received[25] << 24) + ((int32)USB_received[24] << 16) + ((int32)USB_received[23] << 8) + (int32)USB_received[22];
        
        CyDelayUs(10);
        
        update_max_velocity(Motor_Speed_X, TMC5160_nCS_MotorX);        
        update_max_velocity(Motor_Speed_Y, TMC5160_nCS_MotorY);        
        update_max_velocity(Motor_Speed_Z, TMC5160_nCS_MotorZ);
        
        Position_X_Requested = (Position_X_Requested / 4);
        Position_X_Requested = Position_X_Requested * 12.8;
        
        Position_Y_Requested = (Position_Y_Requested / 4);
        Position_Y_Requested = Position_Y_Requested * 12.8;
        
        Position_Z_Requested = (Position_Z_Requested / 16);
        Position_Z_Requested = Position_Z_Requested * 51.2;
        
        CyDelayUs(100);
        
        Error = goTo_XYZ(Position_X_Requested, Position_Y_Requested, Position_Z_Requested);
        CyDelay(100);
        Send_Feedback_to_USB(Error);
    }
    else if (command == SetNoOfExecution)
    {
        //set_no_of_execution();
        
        Send_Feedback_to_USB(Error);   
    }
    else if (command == Get_Status)                          
    {
        LED3_Write(0xFF);
        Write_Debug_UART_Char("Get Status Command Recived  \r\n");
        CyDelay(10);
        Send_Feedback_to_USB(0);
        LED3_Write(0x00);
    }
    else
    {
        Error = 19;//Wrong_Command_Received
        Write_Debug_UART_Char("Wrong Command Received*********** \r\n");
        UART_print_all_values();
        Send_Feedback_to_USB(19);
    }
    //Pin_USB_RX_TX_Indicator_LED_Write(0);/* turn OFF LED as a indicator to stop process the command. */
}
void Send_Feedback_to_USB(int Error)//Send Feedback to USB if USB command executed correctely 
{
     Read_All_Optical_Encoder();

    
    
        if(Error == 0)
        {            
            USB_transmit[0] = command;
            USB_transmit[1] = (command >> 8);
            USB_transmit[2] = No_Error;
            USB_transmit[3] = No_Error >> 8;
        }
        else
        {
            switch(Error)
            {
                case 1:
                {
                    USB_transmit[2] = X_Motor_Not_Working;
                    USB_transmit[3] = X_Motor_Not_Working >> 8; 
                    break;
                }
                case 2:
                {
                    USB_transmit[2] = X_Encoder_Not_Working;
                    USB_transmit[3] = X_Encoder_Not_Working >> 8; 
                    break;
                }
                case 3:
                {
                    USB_transmit[2] = X_Switch_Not_Working;
                    USB_transmit[3] = X_Switch_Not_Working >> 8; 
                    break;
                }
                case 4:
                {
                    USB_transmit[2] = X_Motor_Driver_Fault;
                    USB_transmit[3] = X_Motor_Driver_Fault >> 8; 
                    break;
                }
                case 5:
                {
                    USB_transmit[2] = Requested_X_Step_Exceeding_The_Limit;
                    USB_transmit[3] = Requested_X_Step_Exceeding_The_Limit >> 8; 
                    break;
                }
                case 6:
                {
                    USB_transmit[2] = X_Homing_Not_Done_Yet;
                    USB_transmit[3] = X_Homing_Not_Done_Yet >> 8; 
                    break;
                }
                case 7:
                {
                    USB_transmit[2] = X_Motor_Busy ;
                    USB_transmit[3] = X_Motor_Busy >> 8; 
                    break;
                }
                case 8:
                {
                    USB_transmit[2] = Y_Motor_Not_Working;
                    USB_transmit[3] = Y_Motor_Not_Working >> 8; 
                    break;
                }
                case 9:
                {
                    USB_transmit[2] = Y_Encoder_Not_Working;
                    USB_transmit[3] = Y_Encoder_Not_Working >> 8; 
                    break;
                }
                case 10:
                {
                    USB_transmit[2] = Y_Switch_Not_Working;
                    USB_transmit[3] = Y_Switch_Not_Working >> 8; 
                    break;
                }
                case 11:
                {
                    USB_transmit[2] = Y_Motor_Driver_Fault;
                    USB_transmit[3] = Y_Motor_Driver_Fault >> 8; 
                    break;
                }
                case 12:
                {
                    USB_transmit[2] = Requested_Y_Step_Exceeding_The_Limit;
                    USB_transmit[3] = Requested_Y_Step_Exceeding_The_Limit >> 8; 
                    break;
                }
                case 13:
                {
                    USB_transmit[2] = Y_Homing_Not_Done_Yet;
                    USB_transmit[3] = Y_Homing_Not_Done_Yet >> 8; 
                    break;
                }
                case 14:
                {
                    USB_transmit[2] = Y_Motor_Busy;
                    USB_transmit[3] = Y_Motor_Busy >> 8; 
                    break;
                }
                case 15:
                {
                    USB_transmit[2] = Z_Motor_Not_Working ;
                    USB_transmit[3] = Z_Motor_Not_Working >> 8; 
                    break;
                }
                case 16:
                {
                    USB_transmit[2] = Z_Encoder_Not_Working ;
                    USB_transmit[3] = Z_Encoder_Not_Working >> 8; 
                    break;
                }
                case 17:
                {
                    USB_transmit[2] = Z_Switch_Not_Working;
                    USB_transmit[3] = Z_Switch_Not_Working >> 8; 
                    break;
                }
                case 18:
                {
                    USB_transmit[2] = Z_Motor_Driver_Fault;
                    USB_transmit[3] = Z_Motor_Driver_Fault >> 8; 
                    break;
                }
                case 19:
                {
                    USB_transmit[2] = Requested_Z_Step_Exceeding_The_Limit;
                    USB_transmit[3] = Requested_Z_Step_Exceeding_The_Limit >> 8; 
                    break;
                }
                case 20:
                {
                    USB_transmit[2] = Z_Homing_Not_Done_Yet;
                    USB_transmit[3] = Z_Homing_Not_Done_Yet >> 8; 
                    break;
                }
                case 21:
                {
                    USB_transmit[2] = Z_Motor_Busy;
                    USB_transmit[3] = Z_Motor_Busy >> 8; 
                    break;
                }
                case 22:
                {
                    USB_transmit[2] = T_Motor_Not_Working;
                    USB_transmit[3] =  T_Motor_Not_Working>> 8; 
                    break;
                }
                case 23:
                {
                    USB_transmit[2] = T_Encoder_Not_Working;
                    USB_transmit[3] =  T_Encoder_Not_Working>> 8; 
                    break;
                }
                case 24:
                {
                    USB_transmit[2] = T_Switch_Not_Working;
                    USB_transmit[3] =  T_Switch_Not_Working>> 8; 
                    break;
                }
                
                case 25:
                {
                    USB_transmit[2] = T_Motor_Driver_Fault;
                    USB_transmit[3] =  T_Motor_Driver_Fault>> 8; 
                    break;
                }
                case 26:
                {
                    USB_transmit[2] = Requested_T_Step_Exceeding_The_Limit;
                    USB_transmit[3] =  Requested_T_Step_Exceeding_The_Limit>> 8; 
                    break;
                }
                case 27:
                {
                    USB_transmit[2] = T_Homing_Not_Done_Yet;
                    USB_transmit[3] =  T_Homing_Not_Done_Yet>> 8; 
                    break;
                }
                case 28:
                {
                    USB_transmit[2] = T_Motor_Busy;
                    USB_transmit[3] = T_Motor_Busy >> 8; 
                    break;
                }
                case 29:
                {
                    USB_transmit[2] = Wrong_Command_Received;
                    USB_transmit[3] = Wrong_Command_Received >> 8; 
                    break;
                }
                case 30:
                {
                    USB_transmit[2] = PCB_Paused;
                    USB_transmit[3] = PCB_Paused >> 8; 
                    break;
                }
                case 31:
                {
                    USB_transmit[2] = PCB_Busy;
                    USB_transmit[3] = PCB_Busy >> 8; 
                    break;
                }
                case 32:
                {
                    USB_transmit[2] = All_Motors_Homing_Not_Done;
                    USB_transmit[3] = All_Motors_Homing_Not_Done >> 8; 
                    break;
                }
                
                case 33:
                {
                    USB_transmit[2] = O_Motor_Not_Working;
                    USB_transmit[3] = O_Motor_Not_Working >> 8; 
                    break;
                }
            }
        }
        
        X_QuadPosition = (X_QuadPosition * 4);
        Y_QuadPosition = (Y_QuadPosition * 4);    
        T_QuadPosition = (int)(T_QuadPosition * 3.2); 
        USB_transmit[4] = (X_QuadPosition);
        USB_transmit[5] = (X_QuadPosition) >> 8;
        USB_transmit[6] = (X_QuadPosition) >> 16;
        USB_transmit[7] = (X_QuadPosition) >> 24;
        USB_transmit[8] = (Y_QuadPosition);
        USB_transmit[9] = (Y_QuadPosition) >> 8;
        USB_transmit[10] =(Y_QuadPosition) >> 16;
        USB_transmit[11] =(Y_QuadPosition) >> 24;
        USB_transmit[12] = Z_QuadPosition;
        USB_transmit[13] = Z_QuadPosition >> 8;
        USB_transmit[14] = Z_QuadPosition >> 16;
        USB_transmit[15] = Z_QuadPosition >> 24;
        USB_transmit[16] = T_QuadPosition;
        USB_transmit[17] = T_QuadPosition >> 8;
        USB_transmit[18] = T_QuadPosition >> 16;
        USB_transmit[19] = T_QuadPosition >> 24;
        USB_transmit[20] = PWM_Condenser_comare_value;
        USB_transmit[21] = PWM_Condenser_comare_value >> 8;
        USB_transmit[22] = 0;
        USB_transmit[23] = 0;
        USB_transmit[24] = 0;
        USB_transmit[25] = 0;
        USB_transmit[26] = 0;
        USB_transmit[27] = 0;
        USB_transmit[28] = Motor_Speed_X;
        USB_transmit[29] = Motor_Speed_X >> 8;
        USB_transmit[30] = Motor_Speed_Y;
        USB_transmit[31] = Motor_Speed_Y >> 8;
        USB_transmit[32] = Motor_Speed_Z;
        USB_transmit[33] = Motor_Speed_Z >> 8;
        USB_transmit[34] = 0x00;
        USB_transmit[35] = 0x00 >> 8;
        USB_transmit[36] = 0x00;
        USB_transmit[37] = 0x00;
        USB_transmit[38] = 0x00;
        USB_transmit[39] = Firmware_Version;
        USB_transmit[40] = 0;
        USB_transmit[41] = 0;
        USB_transmit[42] = 0;
        USB_transmit[43] = 0;
        USB_transmit[44] = 0;
        USB_transmit[45] = 0;
        
        
        
        
        
        Write_Debug_UART_Char("Feedback Sent to Motherboard  \r\n");
        USB_PutData(USB_transmit, 46);  //send data back to usb
    
}
void USB_Detect_Indication_Via_LED()/* LED Indicator for USB detection. */
{

}
void Initialize_USB()/* Start the USB. */
{
    USB_Start(0, USB_5V_OPERATION);   
    while (0 == USB_GetConfiguration()) /* wait untill USB not found. */
    {
        Write_Debug_UART_Char("USB not Connected***********  \r\n");
        CyDelayUs(1);
    }
    USB_CDC_Init();
    Write_Debug_UART_Char("USB Connected  \r\n");
    USB_EnableSofInt();  
}
void Is_USB_Unpluged()/* Check for changes in USB port reset if USB changes. */
{
   static bool dont_Execute_1st_Time=false;
   if(USB_IsConfigurationChanged() != 0)
   {
    Beep_Twice();
       if(USB_GetConfiguration() != 0)
       {
            if(dont_Execute_1st_Time)/* Ignore for the first time. */
            {
                Write_Debug_UART_Char("USB Unpluged PCB resetting ***********  \r\n");
                UART_print_all_values();
                CyDelay(1);
                CySoftwareReset();
            }
            dont_Execute_1st_Time = true;
       }
   }  
}
void Clear_USB_RX_Buffer()/* Initialize all USB_received 64 bits to 0. */
{
    int i =0;
    for(i=0;i<65;i++)   //Initializing all bites to 0
        USB_received[i] = 0;   
}
void Clear_Pending_USB_Data()/* Clear all pending data on usb RX buffer. */
{
    int i;
    uint8 USB_received_temp[64];
    for(i=0;i<5;i++)
        {       
            USB_GetAll(USB_received_temp);/* read and clear all Pending data. */
        }    
}
void Write_Debug_UART_Char(char Str[])
{
    //if(Pin_UART_Enable_Read()==0)
    {
        static char Str_Last_One[] = "ShonitV2.2\r\n";
        if((strncmp(Str_Last_One, Str, 10)!=0))
    	{
            UART_PCB_LOG_PutString(Str);
            CyDelayUs(1);
            strncpy(Str_Last_One, Str, 10); 
    	}
    }
}
void Write_Debug_UART_Int(int32 num)
{
   // if(Pin_UART_Enable_Read()==0)
    {
        char uart_Buffer[20];
        sprintf(uart_Buffer,"%d, ",(int)num);
        UART_PCB_LOG_PutString(uart_Buffer);
        CyDelayUs(1);
    }
}
void UART_print_all_values()
{
    Write_Debug_UART_Char("\r\n");
    Write_Debug_UART_Char("--------------------------------------------------");
    Write_Debug_UART_Char("\n");

}
//USB Functions Stop-------------------------------------------------------


//L6470 Motor Driver Functions Stop-------------------------------------------------------


uint8_t Data_To_Transfer(uint8_t data)
{   
    SPIM_WriteTxData(data);
    CyDelayUs(10);
    return 1;
}



/* --------------------------------------------------------------------------------------------
Function Name        : SPI_MOTOR_CHIP_SELECT

Prerequist Knowledge : SPI Communication Protocol, SCI Chip Select Pin, GPIO, SWITCH Statement

Function Description : This Function is used to assert or de-assert the chipselect pin of
                       selected driver IC.

Return Type & Data   : Void

Numnber of Arguments : 2

-----Argument 1-----
Name                 : Motor
Tupe                 : uint8_t
Description          : This Argument Represents the driver channel
Condition            : This Value must range from 0x00 to 0x04 since there are only 5 channels
                       available in AS76 System Configuration
--------------------

-----Argument 2-----
Name                 : Value
Tupe                 : uint8_t
Description          : This Argument Represents the GPIO Level
Condition            : This Value must either 0x00 or 0xFF (Low/High)
--------------------

---------------------------------------------------------------------------------------------*/

void SPI_MOTOR_CHIP_SELECT (uint8_t Motor, uint8_t Value)
{
    
if ((Value == 0x00) || (Value == 0xFF))  // Condition to check for valid GPIO Value
{
 switch (Motor) // Condition to select correct motor driver channel
    {
    case 0x00:
        {
          CyDelayUs(10);
          Pin_CSMotorX_Write(Value);
          CyDelayUs(10);
         // Write_Debug_UART_Char("Motor Channel 1 asserted/de-asserted for SPI Read/Write  \r\n");
          break;
        }
    case 0x01:
        {
          CyDelayUs(10);
          Pin_CSMotorY_Write(Value);
          CyDelayUs(10);
         // Write_Debug_UART_Char("Motor Channel 2 asserted/de-asserted for SPI Read/Write  \r\n");
          break;
        }
        case 0x02:
        {
          CyDelayUs(10);
          Pin_CSMotorZ_Write(Value);
         // Write_Debug_UART_Char("Motor Channel 3 asserted/de-asserted for SPI Read/Write  \r\n");
          CyDelayUs(10);
          break;
        }
        case 0x03:
        {
          CyDelayUs(10);
          Pin_CSMotorT_Write(Value);
        //  Write_Debug_UART_Char("Motor Channel 4 asserted/de-asserted for SPI Read/Write  \r\n");
          CyDelayUs(10);
          break;
        }
        case 0x04:
        {
          CyDelayUs(10);
          Pin_CSMotorO_Write(Value);
        //  Write_Debug_UART_Char("Motor Channel 5 asserted/de-asserted for SPI Read/Write  \r\n");
          CyDelayUs(10);
          break;
        }
        
        default : // If Invalid motor channel selected print error message
        {
            Write_Debug_UART_Char("No Valid Driver nCS asserted/de-asserted for SPI Read/Write  \r\n");
        }
    } 
}
else // If Invalid GPIO Value given, print error message
{
   Write_Debug_UART_Char("Invalid GPIO Level Value, Unable to assert/de-assert nCSN Pin for SPI Read/Write  \r\n"); 
}
}

//-------------------------- [] END OF SPI_MOTOR_CHIP_SELECT Function ---------------------------


/* --------------------------------------------------------------------------------------------
Function Name        : Read_32bitSPI_DATA

Prerequist Knowledge : SPI Communication Protocol, TMC5160 SPI Communication Protocol

Function Description : This Function is used to read 32bit data from the driver register
                       using 32bit SPI communication protocol specific to TMC5160.

Return Type & Data   :32 bit signed or unsigned integer which was fetched from the register

Numnber of Arguments : 2

-----Argument 1-----
Name                 : ADDR
Tupe                 : uint8_t
Description          : The Address of the TMC5160 Register from which data needs to be read
Condition            : Nil
--------------------

-----Argument 2-----
Name                 : Motor
Tupe                 : uint8_t
Description          : This Argument Represents the driver channel
Condition            : This Value must range from 0x00 to 0x04 since there are only 5 channels
                       available in AS76 System Configuration, condition to be checked in 
                       SPI_MOTOR_CHIP_SELECT Function                       
--------------------


---------------------------------------------------------------------------------------------*/


int Read_32bitSPI_DATA(uint8_t ADDR, uint8_t Motor, uint8_t* motor_status )
{
                uint32_t SPI_DATA_VALUE = 0;
               
               
                SPI_MOTOR_CHIP_SELECT (Motor, 0x00);  
                
                Data_To_Transfer(ADDR & 0x7F);                
                Data_To_Transfer(0x00);                
                Data_To_Transfer(0x00);                
                Data_To_Transfer(0x00);                
                Data_To_Transfer(0x00); 
                
                SPI_MOTOR_CHIP_SELECT (Motor, 0xFF); 
                
                CyDelay(1);
                
                SPI_MOTOR_CHIP_SELECT (Motor, 0x00);
                
                Data_To_Transfer(ADDR & 0x7F);
                *motor_status = SPIM_ReadRxData();
                Data_To_Transfer(0x00);
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData() << 24;
                Data_To_Transfer(0x00);
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData() << 16;
                Data_To_Transfer(0x00);
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData() << 8; 
                Data_To_Transfer(0x00); 
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData();
                
                SPI_MOTOR_CHIP_SELECT (Motor, 0xFF);

                CyDelay(1);
                
                SPI_MOTOR_CHIP_SELECT (Motor, 0x00);
                
                Data_To_Transfer(ADDR & 0x7F);
                *motor_status = SPIM_ReadRxData();
                Data_To_Transfer(0x00);
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData() << 24;
                Data_To_Transfer(0x00);
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData() << 16;
                Data_To_Transfer(0x00);
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData() << 8; 
                Data_To_Transfer(0x00); 
                SPI_DATA_VALUE |= (uint32_t) SPIM_ReadRxData();
                
                SPI_MOTOR_CHIP_SELECT (Motor, 0xFF);
                
                
                return SPI_DATA_VALUE;
}

//-------------------------- [] END OF Read_32bitSPI_DATA Function ---------------------------


/* --------------------------------------------------------------------------------------------
Function Name        : Write_32bitSPI_DATA

Prerequist Knowledge : SPI Communication Protocol, TMC5160 SPI Communication Protocol

Function Description : This Function is used to write 32bit data to the driver register
                       using 32bit SPI communication protocol specific to TMC5160.

Return Type & Data   :Void

Numnber of Arguments : 3

-----Argument 1-----
Name                 : ADDR
Tupe                 : uint8_t
Description          : The Address of the TMC5160 Register to which data needs to be written
Condition            : Nil
--------------------

-----Argument 2-----
Name                 : data
Tupe                 : uint8_t
Description          : The 32bit data that needs to be written to TMC5160 register
Condition            : Nil
--------------------

-----Argument 3-----
Name                 : Motor
Tupe                 : uint8_t
Description          : This Argument Represents the driver channel
Condition            : This Value must range from 0x00 to 0x04 since there are only 5 channels
                       available in AS76 System Configuration, condition to be checked in 
                       SPI_MOTOR_CHIP_SELECT Function                       
--------------------

---------------------------------------------------------------------------------------------*/

void Write_32bitSPI_DATA (uint8_t ADDR, int data, uint8_t Motor)
{
 
                SPI_MOTOR_CHIP_SELECT (Motor, 0x00);
                Data_To_Transfer(ADDR | 0x80);                
                Data_To_Transfer((data & 0xFF000000) >> 24);
                Data_To_Transfer((data & 0xFF0000) >> 16);
                Data_To_Transfer((data & 0xFF00) >> 8);
                Data_To_Transfer(data & 0xFF);     
                SPI_MOTOR_CHIP_SELECT (Motor, 0xFF); 
   
    
}

//-------------------------- [] END OF Write_32bitSPI_DATA Function ---------------------------

void Initialize_Motor(uint8_t Motor)
{
            Write_32bitSPI_DATA (0x01  , (int) 0x00000005, Motor ); // Global Status Flag Register
            Write_32bitSPI_DATA (0x00  , (int) 0x00000008, Motor ); // Global Configuration Flag Register
            Write_32bitSPI_DATA (0x03  , (int) 0x00000000, Motor ); // Uart Register
            Write_32bitSPI_DATA (0x05  , (int) 0x00000000, Motor ); // X_COMPARE Register (Position comparison register for motion controller position strobe. The Position pulse is available on output SWP_DIAG1.)
            Write_32bitSPI_DATA (0x06  , (int) 0x00000000, Motor ); // OTP_Program Register
            Write_32bitSPI_DATA (0x08  , (int) 0x0000000F, Motor ); // Factory_Config
            Write_32bitSPI_DATA (0x09  , (int) 0x00010606, Motor ); // Short Config Register
            Write_32bitSPI_DATA (0x0A  , (int) 0x00080400, Motor ); // Drive Config
            //Write_32bitSPI_DATA (0x0B  , (int) 0x00000000, Motor ); // Global Scaller (Global scaling of Motor current. This value is multiplied to the current scaling to adapt a drive to a certain  motor type. This value should be chosen before tuning  other settings because it also influences chopper hysteresis)
            // Current setting register Irun abd Ihold
            if ( Motor == TMC5160_nCS_MotorZ)
            {
            Write_32bitSPI_DATA (0x0B  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x10  , (int) 0x00070301, Motor );
            }
            else if ( Motor == TMC5160_nCS_MotorX)
            {
            Write_32bitSPI_DATA (0x0B  , 90, Motor );
            Write_32bitSPI_DATA (0x10  , (int) 0x00070101, Motor );
            }
            else if ( Motor == TMC5160_nCS_MotorY)
            {
             Write_32bitSPI_DATA (0x0B  , (int) 127, Motor );
             Write_32bitSPI_DATA (0x10  , (int) 0x00070101, Motor );
            }
            else if ( Motor == TMC5160_nCS_MotorO)
            {
             Write_32bitSPI_DATA (0x0B  , (int) 210, Motor );
             Write_32bitSPI_DATA (0x10  , (int) 0x00070100, Motor );
            }
            else
            {
             Write_32bitSPI_DATA (0x0B  , (int) 0x00000000, Motor );
             Write_32bitSPI_DATA (0x10  , (int) 0x00070501, Motor );  
            }
            Write_32bitSPI_DATA (0x11  , (int) 0x0000000A, Motor ); // TPOWERDOWN Register sets the delay time after stand still (stst) of the motor to motor current power down. Time range is about 0 to 4 seconds
            Write_32bitSPI_DATA (0x13  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x14  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x15  , (int) 0x00000000, Motor );
            
            Write_32bitSPI_DATA (0x21  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x23  , (int) 0x00000000, Motor );
            
            Write_32bitSPI_DATA (0x2C  , (int) 0x00000000, Motor );
            
            Write_32bitSPI_DATA (0x33  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x34  , (int) 0x000002AF, Motor );
            Write_32bitSPI_DATA (0x38  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x39  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x3A  , (int) 0x00010000, Motor );
            Write_32bitSPI_DATA (0x3D  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x60  , (int) 0xAAAAB554, Motor );
            Write_32bitSPI_DATA (0x61  , (int) 0x4A9554AA, Motor );
            Write_32bitSPI_DATA (0x62  , (int) 0x24492929, Motor );
            Write_32bitSPI_DATA (0x63  , (int) 0x00000008, Motor );
            Write_32bitSPI_DATA (0x64  , (int) 0xFBFFFFFF, Motor );
            Write_32bitSPI_DATA (0x65  , (int) 0xB5BB777D, Motor );
            Write_32bitSPI_DATA (0x66  , (int) 0x49295556, Motor );
            Write_32bitSPI_DATA (0x67  , (int) 0x00404222, Motor );
            Write_32bitSPI_DATA (0x68  , (int) 0xFFFF8056, Motor );
            Write_32bitSPI_DATA (0x69  , (int) 0x00F70000, Motor );
           
            Write_32bitSPI_DATA (0x6C  , (int) 0x00410153, Motor ); 
            Write_32bitSPI_DATA (0x6D  , (int) 0x00000000, Motor );

            Write_32bitSPI_DATA (0x6E  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x70  , (int) 0xC40C001E, Motor ); 
            
            Write_32bitSPI_DATA (0x21  , (int) 0x00000000, Motor );            
            Write_32bitSPI_DATA (0x24  , (int) 0x0000FFFF, Motor );
            Write_32bitSPI_DATA (0x25  , (int) 0x0000FFFF, Motor );
            Write_32bitSPI_DATA (0x26  , (int) 0x0000FFFF, Motor );
            Write_32bitSPI_DATA (0x27  , (int) 0x00000000, Motor );
            Write_32bitSPI_DATA (0x28  , (int) 0x0000FFFF, Motor );
            Write_32bitSPI_DATA (0x2A  , (int) 0x0000FFFF, Motor );
            Write_32bitSPI_DATA (0x2B  , (int) 0x00000065, Motor );
            Write_32bitSPI_DATA (0x20  , (int) 0x00000000, Motor );
}



bool IsPositionReached (uint8_t Motor)
{
         bool status;
         CyDelayUs(500);
         Read_32bitSPI_DATA(0x04, Motor, &status_x);
         CyDelayUs(100);
         Read_32bitSPI_DATA(0x04, Motor, &status_x);
         if ( (status_x & 0x20) == 0x00)
            {
                 status = false;
   
            }
         else
            {
                 status = true;
            }
            
         return status;
}

int WaitTillPositionReached (uint8_t Motor)
{
         uint8_t wait_status = 0;
         int status = 0;
         CyDelayUs(500);
         Read_32bitSPI_DATA(0x04, Motor, &wait_status);
         CyDelayUs(100);
         Read_32bitSPI_DATA(0x04, Motor, &wait_status);
         while ( (wait_status & 0x20) == 0x00)
            {
                 Read_32bitSPI_DATA(0x21, Motor,  &wait_status);                
                 CyDelayUs(100);
                                
            }
            
         return status;
}

int update_max_velocity(int velocity, uint8_t Motor)
{
    Write_32bitSPI_DATA (0x27  , (int) velocity, Motor); 
    return 0;
}

int update_max_accelaration(int accelaration, uint8_t Motor)
{
    Write_32bitSPI_DATA (0x26  , (int) accelaration, Motor); 
    return 0;
}

int run_pump (int time_ms, uint8_t direction)
{
    Write_32bitSPI_DATA (0x21  , (int) 0x00000000, TMC5160_nCS_MotorO );
    Write_32bitSPI_DATA (0x20  , (int) 0x00000000, TMC5160_nCS_MotorO );
    
    update_max_velocity(53687*2, TMC5160_nCS_MotorO);
    TMC5160_MotorO_EN_Write(0x00);
    CyDelay(15);
    if( (direction == 0x00) || (direction == 0x01))
    {
        CyDelay(1);
    }
    else
    {
      direction =0;  
    }
    
    if( (direction == 0x00) || (direction == 0x01))
    {
    if(direction == 0x00)
    {
        GotoPos(time_ms, TMC5160_nCS_MotorO);
        WaitTillPositionReached(TMC5160_nCS_MotorO);
        //Write_32bitSPI_DATA (0x20  , (int) 0x00000001, TMC5160_nCS_MotorO );
    }
    else
    {
        time_ms = 0-time_ms;
        GotoPos(time_ms, TMC5160_nCS_MotorO);
        WaitTillPositionReached(TMC5160_nCS_MotorO);
        //Write_32bitSPI_DATA (0x20  , (int) 0x00000002, TMC5160_nCS_MotorO );
    }
    }
    //CyDelay(time_ms);
    time_ms = 0;
    update_max_velocity(0x00, TMC5160_nCS_MotorO);
    Write_32bitSPI_DATA (0x21  , (int) 0x00000000, TMC5160_nCS_MotorO );
    Write_32bitSPI_DATA (0x20  , (int) 0x00000000, TMC5160_nCS_MotorO );
    CyDelay(5);
    TMC5160_MotorO_EN_Write(0xFF);
    return 0;
}
int run_pumpvs (int time_ms, int speed, uint8_t direction)
{
    Write_32bitSPI_DATA (0x20  , (int) 0x00000000, TMC5160_nCS_MotorO );
    Write_32bitSPI_DATA (0x21  , (int) 0x00000000, TMC5160_nCS_MotorO );
    update_max_velocity(speed, TMC5160_nCS_MotorO);
    TMC5160_MotorO_EN_Write(0x00);
    CyDelay(10);
    if( (direction == 0x00) || (direction == 0x01))
    {
    if(direction == 0x00)
    {
        GotoPos(time_ms, TMC5160_nCS_MotorO);
        WaitTillPositionReached(TMC5160_nCS_MotorO);
        //Write_32bitSPI_DATA (0x20  , (int) 0x00000001, TMC5160_nCS_MotorO );
    }
    else
    {
        time_ms = 0-time_ms;
        GotoPos(time_ms, TMC5160_nCS_MotorO);
        WaitTillPositionReached(TMC5160_nCS_MotorO);
        //Write_32bitSPI_DATA (0x20  , (int) 0x00000002, TMC5160_nCS_MotorO );
    }
    }
    //CyDelay(time_ms);
    update_max_velocity(0x00, TMC5160_nCS_MotorO);
    Write_32bitSPI_DATA (0x21  , (int) 0x00000000, TMC5160_nCS_MotorO );
    Write_32bitSPI_DATA (0x20  , (int) 0x00000001, TMC5160_nCS_MotorO );
    CyDelay(5);
    TMC5160_MotorO_EN_Write(0xFF);
    return 0;
}
//Motor Driver Configuration Function Stop-------------------------------------------------------

/* [] END OF FILE */

