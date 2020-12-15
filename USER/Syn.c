#include "Syn.h"

void RemotePinInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

  GPIO_InitStructure.GPIO_Pin = 0xff00; //PG8-PG15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOG,0xff00);
  GPIO_SetBits(GPIOG,GPIO_Pin_8 | GPIO_Pin_9);

}

void MotorPinInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  MotorPUL = 0;
}

void InputPinInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void MotorControl(motorState state)
{
  if (state == MotorStop){
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    MotorENA = 0; 
  }
  if (state == MotorUp){
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    MotorDIR = 1;
    MotorENA = 0;
  }
  if (state == MotorDown){
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    MotorDIR = 0;
    MotorENA = 0;
  }
  if (state == MotorOFF){
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
    MotorENA = 1;
  }
}

void KeyPinInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = 0x7f80; //PD7-PD14
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void BeepPinInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOG,GPIO_Pin_6);
}

void BeepON()
{
  BeepPin = 1;
}
void BeepOFF()
{
  BeepPin = 0;
}

void BiBi(u8 times)
{
  u8 i;
  for(i=0;i<times;i++)
  {
    BeepON();
    delayms(20);
    BeepOFF();
    delayms(20);
  }
}

void SWPinInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

  /*---------------------adc in control pins---------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOE,GPIO_Pin_All);
  
  /*--------------------output control pins----------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOF,GPIO_Pin_All);
  /*--------------------------------------------------------------------*/

  /*--------------------------mos driver pins---------------------------*/
  GPIO_InitStructure.GPIO_Pin = 0xfc00; //PB10-PB15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,0xfc00);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOC,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
  /*--------------------------------------------------------------------*/

  /*-------------------------discharge---------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOG,GPIO_Pin_0);
}

void ADCInit(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ͨ��ʱ��

  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
  //PC0 ��Ϊģ��ͨ����������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //PC1 ��Ϊģ��ͨ����������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  ADC_DeInit(ADC1); //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //ģ��ת�������ڵ�ͨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 //ģ��ת�������ڵ���ת��ģʽ
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ��������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC�����Ҷ���
  ADC_InitStructure.ADC_NbrOfChannel = 1;                             //˳����й���ת����ADCͨ������Ŀ
  ADC_Init(ADC1, &ADC_InitStructure);                                 //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

  ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC1

  ADC_ResetCalibration(ADC1); //ʹ�ܸ�λУ׼

  while (ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���λУ׼����

  ADC_StartCalibration(ADC1); //����ADУ׼

  while (ADC_GetCalibrationStatus(ADC1)); //�ȴ�У׼����

  //	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}

//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 GetADC(u8 ch)
{
  //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
  ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_7Cycles5); //ADC1,ADCͨ��,����ʱ��Ϊ239.5����
  ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ��ָ����ADC1�����ת����������
  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); //�ȴ�ת������

  return ADC_GetConversionValue(ADC1); //�������һ��ADC1�������ת�����
}

void StartADCRead()
{
  ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC1
}

u16 GetADCAvg(u8 ch, u8 times)
{
  u32 temp_val = 0;
  u8 t;
  for (t = 0; t < times; t++)
  {
    temp_val += GetADC(ch);
    delayus(15);
  }
  return temp_val / times;
}

void EndADCRead()
{
  ADC_Cmd(ADC1, DISABLE); 
}

void JTAG_Set(u8 mode)
{
  u32 temp;
  temp = mode;
  temp <<= 25;
  RCC->APB2ENR |= 1 << 0;
  AFIO->MAPR &= 0XF8FFFFFF;
  AFIO->MAPR |= temp;
}

void EXTILineOFF_ON(uint32_t EXTI_Line, EXTIxLine State)
{
  if(State){
    EXTI->IMR |= EXTI_Line;
  }
  else if(!State){
    EXTI->IMR &= ~(EXTI_Line);
  }
}

void ACPhaseInit()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE ); // ACPhase
    
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void VTP43TimeInit()
{
  
}

void EXTI9_5_IRQHandler(void)
{
  
   
  EXTI_ClearITPendingBit(EXTI_Line6);
}


/*--------------------------------------------------------------------------*/
//==========������������ֵ======LQ===
void Swap(u16 *a, u16 *b)    
{  
    u16 temp;  

    temp = *a;  
    *a = *b;  
    *b = temp;   
} //end of function Swap

//quick sort LOW to HIGH
void Quicksort(u16 array[], u8 maxlen, u8 begin, u8 end)  
{  
    u8 i, j;  
  
    if(begin < end) {  
        i = begin + 1;  // ��array[begin]��Ϊ��׼������˴�array[begin+1]��ʼ���׼���Ƚϣ�  
        j = end;        // array[end]����������һλ  
            
        while(i < j)  
        {  
            if(array[i] > array[begin]) {   // ����Ƚϵ�����Ԫ�ش��ڻ�׼�����򽻻�λ�á�  
                Swap(&array[i], &array[j]);  // ����������  
                j--;  
            } //end of if  
            else  {  
                i++;  // �����������һλ���������׼���Ƚϡ�  
            } //end of if else
        } //end of while 
        if(array[i] >= array[begin]){  // �������Ҫȡ�ȡ�>=������������Ԫ������ͬ��ֵʱ������ִ���  
            i--;  
        }  
  
        Swap(&array[begin], &array[i]);  // ����array[i]��array[begin]  
          
        Quicksort(array, maxlen, begin, i);  
        Quicksort(array, maxlen, j, end);  
    } //end of if(begin < end) 
}  //end of function Quicksort 

/*------------------------------------------------------------------------*/

u16 absNum(u16 a, u16 b)
{
  if((a-b)>0){
    return a-b;
  }
  else{
    return b-a;
  }

}
