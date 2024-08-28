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
#include <math.h>
#include "configuration.h"
#include <stdlib.h>
#include "project.h"
    
#ifndef CL6470_H_
#define CL6470_H_


unsigned long GetParam(uint8_t);
uint8_t Data_To_Transfer(uint8_t);
unsigned long ParamHandler(uint8_t , unsigned long );
void SetParam(uint8_t , unsigned long );
unsigned long Param(unsigned long, uint8_t);
int GetStatus();


void Reset_L6470();
void Process_USB_Data();

void GoTo(unsigned long);
void goTo_DIR(uint8_t, unsigned long);
void GoUntil(uint8_t, uint8_t, unsigned long);
void ReleaseSW(uint8_t, uint8_t);


void GotoPos(int Pos, uint8_t Motor);
void homeX(uint8_t Motor);
void homeY(uint8_t Motor);
void homeZ(uint8_t Motor);
void homeT(uint8_t Motor);
int update_max_velocity(int velocity, uint8_t Motor);
int update_max_accelaration(int accelaration, uint8_t Motor);
int WaitTillLimitSwitchL (uint8_t Motor);
int run_pump (int time_ms, uint8_t direction);
int run_pumpvs (int time_ms, int speed, uint8_t direction);
void flash();




//uint8_t SPI_STATUS_VALUE1 = 0xFF;

//@param int MOSI
void _Set_MOSI(int);
//@param int MISO
void _Set_MISO(int);
//@param int CS
void _Set_CS(int );
//@param int CLK
void _Set_CLK(int);
//@param int BUSY
void _Set_BUSY(int );
//@param int RESET
void _Set_RESET(int);

int Read_32bitSPI_DATA(uint8_t ADDR, uint8_t Motor, uint8_t* motor_status );
void Write_32bitSPI_DATA (uint8_t ADDR, int data, uint8_t Motor);
void SPI_MOTOR_CHIP_SELECT (uint8_t Motor, uint8_t Value);
int WaitTillPositionReached (uint8_t Motor);
bool IsPositionReached (uint8_t Motor);
int Step_correction_x(int32 steps);
int Step_correction_y(int32 steps);
int Step_correction_t(int32 steps);
int Step_correction_z(int32 steps);
void GsV2(int StartPosX,int EndPosX, int StartPosZ,int EndPosZ, int Xspeed, int Zspeed);
void GsV2_1(int StartPosX,int EndPosX, int deltaz, int Xspeed, int Zspeed,int Z_Point1,int Z_Point2);
void GsV2_2(int StartPosX,int EndPosX, int deltaz, int Xspeed, int Zspeed,int Z_Point1,int Z_Point2);
void GsV2_LR(int X1, int X2, int X3, int X4 ,int Z1, int Z2,int Z3, int Z4, int deltaz, int Xspeed, int Zspeed);


int _Get_MOSI();
int _Get_MISO();
int _Get_CS();
int _Get_CLK();
int _Get_BUSY();
int _Get_RESET();



#endif /* CL6470_H_ */
/* [] END OF FILE */

/* [] END OF FILE */
