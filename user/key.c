#include "key.h"
#include "ctrl.h"
#include "filter.h"

void Key_Init(void)
{
  GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOF, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOE, GPIO_PIN_5, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
}
/*
K1      PA1
K2      PA2
K3      PF4
K4      PE5
K5      PB5
K6      PB4
*/
u16 Get_Key(void)
{
    uint16_t ReadKey = 0;

    if(!GPIO_ReadInputPin(GPIOA, GPIO_PIN_1))
    {
        ReadKey |= PRESS_KEY1;
    }
    if(!GPIO_ReadInputPin(GPIOA, GPIO_PIN_2))
    {
        ReadKey |= PRESS_KEY2;
    }
    if(!GPIO_ReadInputPin(GPIOF, GPIO_PIN_4))
    {
        ReadKey |= PRESS_KEY3;
    }
    if(!GPIO_ReadInputPin(GPIOE, GPIO_PIN_5))
    {
        ReadKey |= PRESS_KEY4;
    }
    if(!GPIO_ReadInputPin(GPIOB, GPIO_PIN_5))
    {
        ReadKey |= PRESS_KEY5;
    }
    if(!GPIO_ReadInputPin(GPIOB, GPIO_PIN_4))
    {
        ReadKey |= PRESS_KEY6;
    }
    return ReadKey;
}

/*
#define KEY_POWER               PRESS_KEY1
#define KEY_RESET               PRESS_KEY2
#define KEY_KETTLE              PRESS_KEY3
#define KEY_TEMP                PRESS_KEY4
#define KEY_QUANTIFY            PRESS_KEY5
#define KEY_STOP                PRESS_KEY6
*/

u16 ReadKeyValue(void)
{
  static uint8_t Key_State = 0;
  static uint8_t key_time = 0;
  static uint16_t Key_LongCheck = 0;
  static uint16_t Key_Prev    = 0;     
  
  u16 Key_press;
  u16 Key_return = 0;
  
  Key_press = Get_Key();
  switch (Key_State)
  {
  case 0:
    if(Key_press != 0)
    {
      Key_Prev = Key_press;
      Key_State = 1;
    }
    break;
  case 1:
    if(Key_press == Key_Prev)
    {
      Key_return= Key_Prev | KEY_DOWN;
      if (Key_press == KEY_POWER)
      {
        Key_State = 2;
      }
      else 
      if (Key_press == KEY_RESET)
      {
        Key_State = 2;
      }
      else 
      if (Key_press == KEY_KETTLE)
      {
        Key_State = 2;
      }
      else 
      if (Key_press == KEY_TEMP)//温度水杯组合
      {
        Key_State = 3;
      }
      else 
      if (Key_press == KEY_CUP)
      {
        Key_State = 2;
      }
      else 
      if (Key_press == KEY_QUANTIFY)//温度水杯组合
      {
        Key_State = 3;
      }
      else 
      if (Key_press == KEY_TEMP|KEY_CUP)
      {
        Key_State = 2;          
      }
      return Key_return ;
    }
    else 																		//°′?üì§?e,ê????ˉ,2??ìó|°′?ü
    {
      Key_State = 0;
    }
    break;
    
  case 2://抬起  长按
//    if(Key_press != Key_Prev)    
    if((Key_press &0x3F )== 0)
    {
      Key_State = 0;
      Key_LongCheck = 0;
      Key_return = Key_Prev | KEY_UP;
      return Key_return;
    }
    if(Key_press == Key_Prev)
    {
      Key_LongCheck++;
      if(Key_LongCheck >= 150)   //长按时间三秒钟              
      {
        Key_LongCheck = 0;
        Key_State = 5;
        Key_return= Key_press |  KEY_LONG;
        return Key_return;
      }
    }
    break;
    
  case 3://组合长按
    if (Key_press == Key_Prev)
    {
      Key_LongCheck++;
      if(Key_LongCheck >= 150)
      {
        Key_LongCheck = 0;
        Key_State = 5;
        Key_return = Key_press|KEY_LONG;
        return Key_return ;
      }
    }
    else if (Key_press & (KEY_TEMP|KEY_QUANTIFY))
    {
      Key_LongCheck++;
      if (Key_LongCheck >=150)
      {
        Key_LongCheck = 0;
        Key_State = 5;
        Key_return = KEY_TEMP|KEY_QUANTIFY|KEY_LONG;
        return Key_return ;
      }
    }
    else if((Key_press &0x3F )== 0)
    {
        Key_State = 0;
        Key_LongCheck = 0;
        Key_return = Key_Prev|KEY_UP;
        return Key_return ;      
    }
    break;
    
  case 4://连按   暂不用
    if (Key_press == Key_Prev) 
    {
      Key_LongCheck++;
      if (Key_LongCheck >= 50) 
      {
        if (++key_time >= 10)
        {
          key_time = 0;                       
          Key_return = Key_press | KEY_LIAN;
          return Key_return;
        }
      }
    }
    else
    {
      Key_LongCheck = 0;
      Key_State = 5; 
    }
    break;
    
  case 5:
    if(Key_press != Key_Prev)
    {
      Key_LongCheck = 0;
      Key_State = 0;
    }
    break;    
  }
  return  NO_KEY;
}



