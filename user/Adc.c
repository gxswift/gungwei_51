#include "Adc.h"

#define SAMP_COUNT 6
u16 g_usAdcValue;
//PB1  AIN1
void Bsp_InitAdc(void)
{
  GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);
  ADC1_DeInit();
  ADC1_Init(
            /* ��1���βα�ʾת��ģʽ
            ADC1_CONVERSIONMODE_SINGLE     ��ʾ����ת��
            ADC2_CONVERSIONMODE_CONTINUOUS ��ʾ��ѡת��
            */
            ADC1_CONVERSIONMODE_SINGLE,
            /* ��2���βα�ʾת����ADCͨ�� */
            ADC1_CHANNEL_1,
            /* ��3���βα�ʾԤ��Ƶ */
            ADC1_PRESSEL_FCPU_D2,
            /* ��4���βα�ʾ�ⲿ����Դ��TIM ���� �ⲿGPIO */
            ADC1_EXTTRIG_TIM,
            /* ��5���βα�ʾ�Ƿ�ʹ���ⲿ����ģʽ */
            DISABLE,
            /* ��6���βα�ʾADC�ɼ���������ݶ����ʽ, �������Ҷ��� */
            ADC1_ALIGN_RIGHT,
            /* ��7���βα�ʾʩ���ش���ͨ�� */
            ADC1_SCHMITTTRIG_CHANNEL9,
            /* ��8��������ʾ�Ƿ�ʹ��ʩ���ش���ͨ�� */
            DISABLE
              );
  ADC1_StartConversion();		/* ��������´�ADCת�� */
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
  g_usAdcValue = sum / SAMP_COUNT;	/* ADC����ֵ�����ɴβ���ֵƽ�� */
  ADC1_StartConversion();		/* ��������´�ADCת�� */
}

/*
*********************************************************************************************************
*	�� �� ��: GetADC
*	����˵��: ��ȡADC������ƽ��ֵ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
uint16_t GetADC(void)
{
  uint16_t ret;
  ret = g_usAdcValue;
  return ret;
}

//��������������ֵ�������Ӧ�¶�
//����10��    100K  3950
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
  
  Res = 1000UL*AD/(1024 - AD);//�� OM
  
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


