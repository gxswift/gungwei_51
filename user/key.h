#ifndef _KEY_H
#define _KEY_H
#include "stm8s.h"

#define PRESS_KEY1      0x01
#define PRESS_KEY2      0x02
#define PRESS_KEY3      0x04
#define PRESS_KEY4      0x08
#define PRESS_KEY5      0x10
#define PRESS_KEY6      0x20




#define NO_KEY          0x0000
#define KEY_DOWN        0x1000  	
#define KEY_UP          0x2000  
#define KEY_LIAN        0x4000   
#define KEY_LONG        0x8000

//---------------°´¼ü¶¨Òå----------------
#define KEY_Set              PRESS_KEY6
#define KEY_Soft               PRESS_KEY4
#define KEY_Hard              PRESS_KEY5
#define KEY_Stop                PRESS_KEY1
#define KEY_Wash                 PRESS_KEY3
#define KEY_Code            PRESS_KEY2



void Key_Init();

u16 ReadKeyValue(void);


#endif  //_KEY_H