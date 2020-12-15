#include "timer.h"
#include "Syn.h"
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "sys.h"
#include "BD.h"

u32 usStepCnt = 0;

//定时器3中断服务程序
void TIM3_Init(u16 arr, u16 psc) // 中断频率 : 72M/[(arr+1)*(psc+1)]
{

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = arr;                     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //设置用来作为TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //根据指定的参数初始化TIMx的时间基数单位
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                  //使能指定的TIM3中断,允许更新中断

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           //TIM3中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM3, ENABLE); //使能TIM6
}

void TIM3_IRQHandler(void) //TIM3中断
{ 
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){ //检查TIM3更新中断发生与否{
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除TIMx更新中断标志
  }

  usStepCnt++;

  if (usStepCnt == 11){
    PCout(7) = ~PCout(7);
    usStepCnt = 0;
  }

  //    __set_FAULTMASK(1); // 关闭所有中断
  //    NVIC_SystemReset(); // 复位
}

void TIM4_Init(u16 arr, u16 psc) // 中断频率 : 72M/[(arr+1)*(psc+1)]
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = arr;
  TIM_TimeBaseStructure.TIM_Prescaler = psc;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM4, ENABLE); //使能TIM4
}


u32 TIM4_usCnt;
u16 TIM4_10usCnt;
u16 TIM4_msCnt;
u8 TIM4_sCnt;
extern u8 PD_usCntFlag;
void TIM4_IRQHandler(void) //TIM4中断
{ 
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){ //检查TIM3更新中断发生与否{
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //清除TIMx更新中断标志
  }

  if(PD_usCntFlag == 1){
    TIM4_usCnt++;
  }

  TIM4_msCnt++;
  if(TIM4_msCnt == 1000){
    TIM4_sCnt++;
    TIM4_msCnt = 0;
  }

  if(TIM4_sCnt == 5){
    TIM4_sCnt = 0;
    BiBi(7);
    DataTransfer('E',0, 0, 0, 0);
    NVIC_SystemReset(); //检测出错
  }
  //    __set_FAULTMASK(1); // 关闭所有中断
  //    NVIC_SystemReset(); // 复位
}



void EXTI_TIMxOFF_ON(TIM_TypeDef *TIMx, TIMxSwitch State)
{
  if(State){
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  }
  else{
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
  }
}

void TIMxOFF_ON(TIM_TypeDef *TIMx, TIMxSwitch State)
{
  if (State){
    TIMx->CR1 |= 0x01;
  }
  else if (!State){
    TIMx->CR1 &= ~(0x01);
  }
}

/*=====================================================

u8 TIM4CH1_CAPTURE_STA = 0;
u16 TIM4CH1_CAPTURE_VAL;

void TIM4CapInit(u16 arr, u16 psc, u8 ICPolar)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef TIM4_ICInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,GPIO_Pin_6);

  TIM_TimeBaseStructure.TIM_Period = arr;
  TIM_TimeBaseStructure.TIM_Prescaler = psc;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;
  if(ICPolar == 1)
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  else
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM4_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM4,&TIM4_ICInitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ITConfig(TIM4,TIM_IT_Update | TIM_IT_CC1,ENABLE);
  TIM_Cmd(TIM4,ENABLE);

}




void TIM4_IRQHandler(void)
{
  if((TIM4CH1_CAPTURE_STA & 0x80) == 0) //未捕获成功
  {
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
      if(TIM4CH1_CAPTURE_STA & 0x40) //已经捕获
      {
        if((TIM4CH1_CAPTURE_STA & 0x3f) == 0x3f) //高电平时间太长
        {
          TIM4CH1_CAPTURE_STA |= 0x80; //标记成功捕获一次
          TIM4CH1_CAPTURE_VAL = 0xffff;
        }
        else
        {
          TIM4CH1_CAPTURE_STA ++;
        }
      } 
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //清除TIMx更新中断标志
    }
  }

  if(TIM_GetITStatus(TIM4,TIM_IT_CC1) != RESET) //捕获1发生捕获事件
  {
    if(TIM4CH1_CAPTURE_STA & 0x40)  //捕获到一个下降沿
    {
      TIM4CH1_CAPTURE_STA |= 0x80; //标记成功捕获到一次上升沿
      TIM4CH1_CAPTURE_VAL = TIM_GetCapture1(TIM4);
      TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);
    }
    else
    {
      TIM4CH1_CAPTURE_STA = 0;
      TIM4CH1_CAPTURE_VAL = 0;
      TIM_SetCounter(TIM4,0);
      TIM4CH1_CAPTURE_STA |= 0x40;
      TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);
    }
  }
  
  TIM_ClearITPendingBit(TIM4,TIM_IT_CC1 | TIM_IT_Update);
}

==================================================*/

