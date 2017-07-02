#ifndef _ADC_H
#define _ADC_H


#include "stm8s.h"

void Bsp_InitAdc(void);
void Bsp_AdcPro(void);
uint16_t GetADC();
u16 Get_Temp();

#endif
