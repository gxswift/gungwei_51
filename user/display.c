#include "display.h"

/*

液晶
CS  PD4
RD  PD3
WR  PD2
DATA  PD0
*/

//
void Display_Init()
{
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST); 
  GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
  
  Ht1621_Init();
}


//LCD Lcd;
//LCD Lcd1;
void Ht1621_Init()
{	
  CS_H;
  WR_H;
  DATA_H;
  delay_ms(100); 
  SendCmd(BIAS);
  SendCmd(SYSEN); 
  SendCmd(LCDON);
  
}

void SendBit_1621(u8 dat,u8 cnt) 
{
  u8 i;
  for (i=0;i<cnt;i++)
  {

    if (dat&0x80)
      DATA_H ;
    else 
      DATA_L;
    
    WR_L;
    WR_H;
    dat <<=1;
  }
}


void SendDataBit_1621(u8 dat,u8 cnt)
{
  u8 i;
  for (i=0;i<cnt;i++)
  {
    if (dat&0x01)
      DATA_H;
    else
      DATA_L;
    
    WR_L;
    WR_H;
    dat>>=1;
  }
}	



void SendCmd(u8 cmd)
{
  CS_L;
  SendBit_1621(0x80,3);
  SendBit_1621(cmd,9);
  CS_H;
}


void Write_1621(u8 addr , u8 dat)
{
  CS_L ;
  SendBit_1621(0xa0,3);
  SendBit_1621(addr<<2,6);
  SendDataBit_1621(dat,4);
  CS_H ;
}

void WriteAll_1621(u8 addr,u8 *p,u8 cnt) 
{  
  u8 i;
  CS_L; 
  SendBit_1621(0xa0,3); 
  SendBit_1621(addr<<2,6); 
  for(i =0; i <cnt; i++,p++) 
  {  
    SendDataBit_1621(*p,8); 
  } 
  CS_H; 
} 

//-------------------------------------------------------------------------
u8 const NumberTube_TAB[17]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
0x77,0x7C,0x39,0x5E,0x79,0x71,0};


DIS_SMG Dis_Smg[7];

void SmgDisplay(DIS_SMG * Dis_Smg,u8 i)
{
  *(u8*)(Dis_Smg)=NumberTube_TAB[i];
}



  
DISPLAY DIS;

void Number_Display(u8* numberArray)
{
  u8 i;
  u8 *p;

  p = numberArray;
  for (i=0;i<7;i++)
  {
    SmgDisplay(&Dis_Smg[i],*p);
    p++;
  }
  
  DIS.Lcd.L1A	=	Dis_Smg[0].S1;
  DIS.Lcd.L1B	=	Dis_Smg[0].S2;
  DIS.Lcd.L1C	=	Dis_Smg[0].S3;
  DIS.Lcd.L1D	=	Dis_Smg[0].S4;
  DIS.Lcd.L1E	=	Dis_Smg[0].S5;
  DIS.Lcd.L1F	=	Dis_Smg[0].S6;
  DIS.Lcd.L1G	=	Dis_Smg[0].S7;
  
  DIS.Lcd.L2A	=	Dis_Smg[1].S1;
  DIS.Lcd.L2B	=	Dis_Smg[1].S2;
  DIS.Lcd.L2C	=	Dis_Smg[1].S3;
  DIS.Lcd.L2D	=	Dis_Smg[1].S4;
  DIS.Lcd.L2E	=	Dis_Smg[1].S5;
  DIS.Lcd.L2F	=	Dis_Smg[1].S6;
  DIS.Lcd.L2G	=	Dis_Smg[1].S7;
  
  DIS.Lcd.L3A	=	Dis_Smg[2].S1;
  DIS.Lcd.L3B	=	Dis_Smg[2].S2;
  DIS.Lcd.L3C	=	Dis_Smg[2].S3;
  DIS.Lcd.L3D	=	Dis_Smg[2].S4;
  DIS.Lcd.L3E	=	Dis_Smg[2].S5;
  DIS.Lcd.L3F	=	Dis_Smg[2].S6;
  DIS.Lcd.L3G	=	Dis_Smg[2].S7;
 
  DIS.Lcd.L4A	=	Dis_Smg[3].S1;
  DIS.Lcd.L4B	=	Dis_Smg[3].S2;
  DIS.Lcd.L4C	=	Dis_Smg[3].S3;
  DIS.Lcd.L4D	=	Dis_Smg[3].S4;
  DIS.Lcd.L4E	=	Dis_Smg[3].S5;
  DIS.Lcd.L4F	=	Dis_Smg[3].S6;
  DIS.Lcd.L4G	=	Dis_Smg[3].S7;
  
  DIS.Lcd.L5A	=	Dis_Smg[4].S1;
  DIS.Lcd.L5B	=	Dis_Smg[4].S2;
  DIS.Lcd.L5C	=	Dis_Smg[4].S3;
  DIS.Lcd.L5D	=	Dis_Smg[4].S4;
  DIS.Lcd.L5E	=	Dis_Smg[4].S5;
  DIS.Lcd.L5F	=	Dis_Smg[4].S6;
  DIS.Lcd.L5G	=	Dis_Smg[4].S7;
  
  DIS.Lcd.L6A	=	Dis_Smg[5].S1;
  DIS.Lcd.L6B	=	Dis_Smg[5].S2;
  DIS.Lcd.L6C	=	Dis_Smg[5].S3;
  DIS.Lcd.L6D	=	Dis_Smg[5].S4;
  DIS.Lcd.L6E	=	Dis_Smg[5].S5;
  DIS.Lcd.L6F	=	Dis_Smg[5].S6;
  DIS.Lcd.L6G	=	Dis_Smg[5].S7;
  
  DIS.Lcd.L7A	=	Dis_Smg[6].S1;
  DIS.Lcd.L7B	=	Dis_Smg[6].S2;
  DIS.Lcd.L7C	=	Dis_Smg[6].S3;
  DIS.Lcd.L7D	=	Dis_Smg[6].S4;
  DIS.Lcd.L7E	=	Dis_Smg[6].S5;
  DIS.Lcd.L7F	=	Dis_Smg[6].S6;
  DIS.Lcd.L7G	=	Dis_Smg[6].S7;
  
}



void Lcd_Display()
{
  u8 i;
  DISPLAY DisBuff;
//-------------------------------------------------
  for (i=0;i<11;i++)
  DisBuff.L[i] = DIS.L[i];
  //闪烁数据分开处理

//-------------------------------------------------
//测试部分         全部显示
/* for(i=0;i<11;i++)
     DIS.L[i] =0xFF;//0;
*/
/*
  //段位查看
     for(i=0;i<11;i++)
     DIS.L[i] =0;

     DIS.Lcd.L1D = 1; 
*/
//-------------------------------------------------
  WriteAll_1621(11,(u8*)&DisBuff.L[0] , 11);//add 11    byte  11
//---------------------------------------------------
}
