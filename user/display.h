#ifndef _display_H_
#define _display_H_

#include "stm8s.h"
#include "wtn4105.h"

/*

“∫æß
CS  PD4
RD  PD3
WR  PD2
DATA  PD0
*/


#define DATA_L          GPIO_WriteLow (GPIOD, GPIO_PIN_0)
#define DATA_H          GPIO_WriteHigh(GPIOD, GPIO_PIN_0)

#define CS_L            GPIO_WriteLow (GPIOD, GPIO_PIN_4)
#define CS_H            GPIO_WriteHigh(GPIOD, GPIO_PIN_4)   

#define WR_L            GPIO_WriteLow (GPIOD, GPIO_PIN_2)
#define WR_H            GPIO_WriteHigh(GPIOD, GPIO_PIN_2)


#define BIAS		0x2A//0x24  0x26∆´—π…Ë÷√1/2  1/3;
#define SYSEN		0x01
#define LCDOFF	        0x02
#define LCDON		0x03

typedef struct
{
  u8 S1:1;
  u8 S2:1;
  u8 S3:1;
  u8 S4:1;
  u8 S5:1;
  u8 S6:1;
  u8 S7:1;
} DIS_SMG;

typedef struct
{
 //25
  u8 L7B:1;
  u8 L7G:1;
  u8 L7C:1;
  u8 LL:1;
  //24
  u8 L7A:1;
  u8 L7F:1;
  u8 L7E:1;
  u8 L7D:1;
  //23
  u8 L6B:1;
  u8 L6G:1;
  u8 L6C:1;
  u8 LY9:1;
  //22
  u8 L6A:1;
  u8 L6F:1;
  u8 L6E:1;
  u8 L6D:1;
  //21
  u8 L5B:1;
  u8 L5G:1;
  u8 L5C:2;
  //20
  u8 L5A:1;
  u8 L5F:1;
  u8 L5E:1;
  u8 L5D:1;
  //19
  u8 L4B:1;
  u8 L4G:1;
  u8 L4C:1;
  u8 LL2:1;
  //18
  u8 L4A:1;
  u8 L4F:1;
  u8 L4E:1;
  u8 L4D:1;
  //17
  u8 LT9:1;
  u8 LT10:1;
  u8 LT11:1;
  u8 LZ9:1;
  //16
  u8 LY8:1;
  u8 LY7:1;
  u8 LY6:1;
  u8 LY5:1;
 //15
  u8 LZ8:1;
  u8 LZ7:1;
  u8 LZ6:1;
  u8 LZ5:1;
  //14
  u8 LY4:1;
  u8 LY3:1;
  u8 LY2:1;
  u8 LY1:1;
 //13 
  u8 LZ4:1;
  u8 LZ3:1;
  u8 LZ2:1;
  u8 LZ1:1;
  //12
  u8 LT8:1;
  u8 LT7:1;
  u8 LT6:1;
  u8 LT5:1;
  //11
  u8 LT4:1;
  u8 LT3:1;
  u8 LT2:1;
  u8 LT1:1;
  //10
  u8 L3B:1;
  u8 L3G:1;
  u8 L3C:1;
  u8 TDS:1;
//9 
  u8 L3A:1;
  u8 L3F:1;
  u8 L3E:1;
  u8 L3D:1;
  //8
  u8 L2B:1;
  u8 L2G:1;
  u8 L2C:1;
  u8 LCC:1;
 //7 
  u8 L2A:1;
  u8 L2F:1;
  u8 L2E:1;
  u8 L2D:1;
  //6
  u8 L1B:1;
  u8 L1G:1;
  u8 L1C:1;
  u8 LL1:1;
  //5
  u8 L1A:1;
  u8 L1F:1;
  u8 L1E:1;
  u8 L1D:5;
 
}LCD;

typedef union 
{
  LCD Lcd;
  u8 L[11];
}DISPLAY;


void Display_Init();
void Ht1621_Init();
void SendCmd(u8 cmd);

void Number_Display(u8* numberArray);
void Lcd_Display();
#endif