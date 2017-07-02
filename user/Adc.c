#include "Adc.h"

#define SAMP_COUNT 6
u16 g_usAdcValue;
//PB1  AIN1
void Bsp_InitAdc(void)
{
  GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);
  ADC1_DeInit();
  ADC1_Init(
            /* 第1个形参表示转换模式
            ADC1_CONVERSIONMODE_SINGLE     表示连续转换
            ADC2_CONVERSIONMODE_CONTINUOUS 表示连选转换
            */
            ADC1_CONVERSIONMODE_SINGLE,
            /* 第2个形参表示转换的ADC通道 */
            ADC1_CHANNEL_1,
            /* 第3个形参表示预分频 */
            ADC1_PRESSEL_FCPU_D2,
            /* 第4个形参表示外部触发源，TIM 或者 外部GPIO */
            ADC1_EXTTRIG_TIM,
            /* 第5个形参表示是否使能外部触发模式 */
            DISABLE,
            /* 第6个形参表示ADC采集结果的数据对齐格式, 左对齐或右对齐 */
            ADC1_ALIGN_RIGHT,
            /* 第7个形参表示施密特触发通道 */
            ADC1_SCHMITTTRIG_CHANNEL9,
            /* 第8个参数表示是否使能施密特触发通道 */
            DISABLE
              );
  ADC1_StartConversion();		/* 软件启动下次ADC转换 */
}

void Bsp_AdcPro(void)
{
  static uint16_t buf[SAMP_COUNT];
  static uint8_t write;
  uint16_t sum;
  uint8_t i;
  
  buf[write] = ADC1_GetConversionValue();
  if (++write >= SAMP_COUNT)
  {
    write = 0;
  }
  sum = 0;
  for (i = 0; i < SAMP_COUNT; i++)
  {
    sum += buf[i];
  }
  g_usAdcValue = sum / SAMP_COUNT;	/* ADC采样值由若干次采样值平均 */
  ADC1_StartConversion();		/* 软件启动下次ADC转换 */
}

/*
*********************************************************************************************************
*	函 数 名: GetADC
*	功能说明: 读取ADC采样的平均值
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t GetADC(void)
{
  uint16_t ret;
  ret = g_usAdcValue;
  return ret;
}

//根据热敏电阻阻值，计算对应温度
//扩大10倍    100K  3950
u16 OM[] = 
{2999,2857,2723,2596,2475,2361,2252,2149,2052,1959,//1~10
1871,1787,1707,1631,1559,1491,1425,1363,1304,1248,//11~20
1194,1143,1094,1047,1000,960,920,881,845,810,//21~30
776,744,713,684,656,630,604,580,557,534,//31~40
513,493,473,455,437,420,403,388,373,358,//41~50
345,331,319,307,295,284,273,263,254,244,//51~60
235,227,218,210,203,195,188,182,175,169,//61~70
163,157,152,146,141,136,132,127,123,119,//71~80
115,111,107,104,100,972,940,90,87,85,//81~90
82,79,77,74,72,70,67,65,63,61//91~100
};


u16 Get_Temp()
{
  u8 Tem;
  u32 Res;
  u16 AD;
  u8 i;//,Temp;
  AD = GetADC();
  if(AD>980 || AD<50)
    return 200;
  
  Res = 1000UL*AD/(1024 - AD);//百 OM
  
  for(i=0;i<=sizeof(OM)/sizeof(OM[0]);i++)
    //for(i=0;i<14;i++)
  { 
    Tem= i;
    if( Res<OM[i])
    {
      continue;
    }
    else break;
  }
  return Tem;
}


