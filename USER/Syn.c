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

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); //使能ADC1通道时钟

  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
  //PC0 作为模拟通道输入引脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //PC1 作为模拟通道输入引脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  ADC_DeInit(ADC1); //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC工作模式:ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //模数转换工作在单通道模式
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 //模数转换工作在单次转换模式
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 1;                             //顺序进行规则转换的ADC通道的数目
  ADC_Init(ADC1, &ADC_InitStructure);                                 //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

  ADC_Cmd(ADC1, ENABLE); //使能指定的ADC1

  ADC_ResetCalibration(ADC1); //使能复位校准

  while (ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准结束

  ADC_StartCalibration(ADC1); //开启AD校准

  while (ADC_GetCalibrationStatus(ADC1)); //等待校准结束

  //	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
}

//获得ADC值
//ch:通道值 0~3
u16 GetADC(u8 ch)
{
  //设置指定ADC的规则组通道，一个序列，采样时间
  ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_7Cycles5); //ADC1,ADC通道,采样时间为239.5周期
  ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能指定的ADC1的软件转换启动功能
  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); //等待转换结束

  return ADC_GetConversionValue(ADC1); //返回最近一次ADC1规则组的转换结果
}

void StartADCRead()
{
  ADC_Cmd(ADC1, ENABLE); //使能指定的ADC1
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
//==========交换两个数的值======LQ===
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
        i = begin + 1;  // 将array[begin]作为基准数，因此从array[begin+1]开始与基准数比较！  
        j = end;        // array[end]是数组的最后一位  
            
        while(i < j)  
        {  
            if(array[i] > array[begin]) {   // 如果比较的数组元素大于基准数，则交换位置。  
                Swap(&array[i], &array[j]);  // 交换两个数  
                j--;  
            } //end of if  
            else  {  
                i++;  // 将数组向后移一位，继续与基准数比较。  
            } //end of if else
        } //end of while 
        if(array[i] >= array[begin]){  // 这里必须要取等“>=”，否则数组元素由相同的值时，会出现错误！  
            i--;  
        }  
  
        Swap(&array[begin], &array[i]);  // 交换array[i]与array[begin]  
          
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
