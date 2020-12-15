#include "BD.h"
#include "Delay.h"
#include "PiontDetect.h"
#include "Syn.h"
#include "oled.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "string.h"
#include "timer.h"
#include "usart.h"

void StartInit(void);
void StartPrepare(void);


int main(void)
{
  StartInit();
  MotorControl(MotorOFF);
  StartPrepare();
 
  delayms(500);
  BeepON();
  delayms(500);
  BeepOFF();
 
  if(UpLimit == 0){  
    CoverPlatUp();
  }
  
  BoardTypeConfirmation();
  CoverPlatDown();
  BoardInitSet();  
  DownLoadProcedure();
  DetectResetCircuit();
  DetectVZD601();
  DetectPowerCircuit();
  DetectInteriorTemperature();
  DetectOutTemperature();
  DetectPulseCircuit();
  DetectRelayCircuit();
  DetectContactStateCircuit();
  DetectTemperatureExamineCircuit();
  DetectRelayAndLEDCircut();
  DetectICFunction();
  Discharge();
  DetectFinish();

  
  while (1)
  {
    //OLED_P8x16Value(58, 2, TestVTB());
     BiBi(1);
  }
      
}

void StartInit()
{
  SystemInit();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  UART1Init(9600);
  ADCInit();
  DelayInit();
  OLED_Init();
  BeepPinInit();
  MotorPinInit();
  RemotePinInit();
  KeyPinInit();
  SWPinInit();
  InputPinInit();
  ACPhaseInit();
  TIM3_Init(9, 33);
  //TIM4_Init(71, 0);//中断时间1us
  TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
}

void StartPrepare()
{
  
  extern u32 TIM4_usCnt;
  extern u16 TIM4_10usCnt;
  extern u16 TIM4_msCnt;
  extern u8  TIM4_sCnt;
  

  TIM4_usCnt   = 0;
  TIM4_10usCnt = 0;
  TIM4_msCnt   = 0;
  TIM4_sCnt    = 0;
  
  
  OLED_P8x16Str(18, 0, "---BD---");
  OLED_P8x16Str(0, 2, "adcVal:");

  //UART1PutStr("OK");
  
  StartADCRead();
  
  SINAINH = 1;
  DISCHARGE = 1; //关闭放电
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  SP10 = 1;
  SP11 = 1;
  SP13 = 1;
  SP14 = 1;
  SP63 = 1;
  S7V5 = 0;
  SP4041 = 0;
  S3V5 = 0;
  S2V7 = 0;
  JKRLA = 0;
  JKRLB = 0;
  DLD = 0;
  DVRLA = 0;
  DVRLB = 0;
  DVSCR = 0;
  RMTDownON = 0;
  RMTUpON = 0;

  BiBi(2);
}


