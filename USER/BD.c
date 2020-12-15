#include "BD.h"


void RemoteControl(RemoteSW SW)
{
  extern u8 T;
  if(T == '1') {
    RMTDownON   = 0;
    delayms(1);
    RMTUpON = 1;
  } 
  else{
    RMTUpON   = 0;
    delayms(1);
    RMTDownON = 1;
  }
  delayms(5);

  switch(SW)
  {
    case RMTPWRON:{
      RMTA = 0;
      RMTB = 0;
      RMTC = 0;

      RMTCOM2 = 1;
      delayms(1);
      RMTCOM1 = 0; 
      delayms(30);
      RMTCOM1 = 1;

    } break;
    case AreaSW:{
      RMTA = 0;
      RMTB = 1;
      RMTC = 0;

      RMTCOM2 = 1;
      delayms(1);
      RMTCOM1 = 0; 
      delayms(30);
      RMTCOM1 = 1;
      delayms(20);
    } break;
    case EfficentSW:{
      RMTA = 1;
      RMTB = 1;
      RMTC = 0;

      RMTCOM1 = 1;
      delayms(1);
      RMTCOM2 = 0; 
      delayms(30);
      RMTCOM2 = 1;
      delayms(20);
    } break;
    case HalfPowerSW:{
      RMTA = 0;
      RMTB = 1;
      RMTC = 0;

      RMTCOM1 = 1;
      delayms(1);
      RMTCOM2 = 0; 
      delayms(30);
      RMTCOM2 = 1;
      delayms(20);
    } break;
    case TemperatureUpSW:{
      RMTA = 1;
      RMTB = 0;
      RMTC = 0;

      RMTCOM2 = 1;
      delayms(1);
      RMTCOM1 = 0; 
      delayms(30);
      RMTCOM1 = 1;
      delayms(20);
    } break;
    case TemperatureDownSW:{
      RMTA = 1;
      RMTB = 1;
      RMTC = 0;

      RMTCOM2 = 1;
      delayms(1);
      RMTCOM1 = 0; 
      delayms(30);
      RMTCOM1 = 1;
      delayms(20);
    } break;
    case RMTOFF:{
      RMTDownON = 0;
      RMTUpON   = 0;
    } break;
    case RMTON:{
      if(T == '1'){
        RMTUpON = 1;
      }
      else{
        RMTDownON = 1;
      }
      delayms(2);
    } break;  
  }
  delayms(5);
}

void TestERR()
{
  PWRON = 0;
  JKSW001 = 0;
  JKRLA = 0;
  JKRLB =0;
  S2V7 = 0;
  S3V5 = 0;
  S7V5 = 0;
  SP10 = 0;
  SP11 = 0;
  SP13 = 0;
  SP14 = 0;
  SP4041 = 0;
  SP63 = 0;
  SQ602 = 0;
  SQ603 = 0;
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  SINAINH = 1;
  RemoteControl(RMTOFF);

  DISCHARGE = 0;
  BeepON();
  delayms(500);
  DISCHARGE = 1;
  BeepOFF();
  NVIC_SystemReset(); 
}

void CoverPlatDown()
{
  u8 motorDownFlag = 0;

  TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);

  if(UpLimit == 1){
    //MotorControl(MotorDown);
    //delayms(10);
    MotorControl(MotorOFF);
  }
  while(LeftButton != 1 || RightButton != 1);
  
  while(1)
  {
    if(LeftButton == 1 && RightButton == 1){
      delayms(10);
      if(LeftButton == 1 && RightButton == 1){
        if(motorDownFlag == 0){
          MotorControl(MotorDown);
          motorDownFlag = 1;
        }
        if(DownLimit == 1){
          MotorControl(MotorOFF);
          MotorControl(MotorStop);
          BeepON();
          delayms(200);
          BeepOFF();
          delayms(200);
          BeepON();
          delayms(100);
          BeepOFF();
          break;
        }
      }
    }
    if(LeftButton != 1 || RightButton != 1){
      delayms(10);
      if(LeftButton != 1 || RightButton != 1){
        MotorControl(MotorOFF); 
        motorDownFlag = 0;
      }
    }
  }

  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

}

void CoverPlatUp()
{

  u8 motorUpFlag = 0;

  TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
  MotorControl(MotorOFF);
  
  BeepON();
  delayms(100);
  BeepOFF();
  delayms(50);
  BeepON();
  delayms(100);
  BeepOFF();

  while(1)
  {
    if(motorUpFlag == 0){
      delayms(10);
      if(motorUpFlag == 0){
        MotorControl(MotorUp);
        motorUpFlag = 1;
      }
    }   
    if(UpLimit == 1){
      delayms(10);
      if(UpLimit == 1){
        MotorControl(MotorOFF);
        BeepON();
        delayms(100);
        BeepOFF();
        break;
      }       
    }
  }
}

u8 DataTransfer(char D1, u16 step, u8 state, u8 dataType, u16 value)
{
  char dataStr[9];
  u8 succ = 0;
  extern u8 C,P; //分别为 C, P相关值

  dataStr[0] = D1;
  dataStr[1] = (step/10) + '0';
  dataStr[2] = (step%10) + '0';
  if(step < 1){
    dataStr[3] = state;
  }
  else{
    dataStr[3] = state + '0';
  }
  if(dataType == 0){
    dataStr[4] = dataType + '0';
  }
  else{
    dataStr[4] = dataType;
  }
  
  if(value >= 10000){
    dataStr[5] = (value/10000) + '0';
    dataStr[6] = ((value%10000)/1000) + '0';
    dataStr[7] = (value%1000)/100 + '0';
    dataStr[8] = NULL;
  }
  else{
    dataStr[5] = (value/1000) + '0';
    dataStr[6] = ((value%1000)/100) + '0';
    dataStr[7] = (value%100)/10 + '0';
    dataStr[8] = NULL;
  }
  
  UART1PutStr(dataStr);
  
  delayms(10);
  
  if(step <= 2){
    if(C == '0'){
      delayms(10);
      if(C == '0'){
        TestERR();
      }     
    }
  }
  else if(step > 2){
    if(P == '0'){
      delayms(10);
      if(P == '0'){
        TestERR();
      } 
    }
  } 
  else{
    succ = 1;
  }
  
  C = '0';
  P = '0';
  BiBi(1);
  return succ;
}

u8 ACPhaseJudge() //180°
{
  u8 Phase = 0;

  if(ACPhase == 1)
  {
    while(ACPhase == 1);
    Phase = 1;
    return Phase;
  }
  else
  {
    while(ACPhase == 0);
    delayus(500);
    while(ACPhase == 1);
    Phase = 1;
    return Phase;
  }
}

u8 BoardTypeConfirmation()
{
  u8 boardType = 0;
  extern u8 T;
  
  while(T == 0);
  boardType = T;
  
  MotorControl(MotorOFF);
  DataTransfer('C',0,boardType,0,0);
  
  return boardType;
}

u8 BoardInitSet()
{
  u8 finishFlag = 0;
  extern u8 T;

  PWRON   = 0;
  JKSW001 = 0;
  JKRLB   = 0;
  JKRLA   = 0;
  delayms(1000);

  if(T == '1'){
    RMTDownON = 0;
    RMTUpON   = 1;
  }
  else{
    RMTUpON   = 0;
    RMTDownON = 1;
  }

  PWRON   = 1;
  JKSW001 = 1;

  delayms(600);

  finishFlag = 1;
  DataTransfer('C', 1, 1, 0, 0);
 
  return finishFlag;
}

u8 DownLoadProcedure()
{
  u8 downLoadSucceceFlag = 1;
  u8 errTime = 0;
  u8 errFlag = 0;

  DLD = 1;
  delayms(1000);
  while(DLDSUCC == 0)
  {
    errTime ++;
    if(errTime == 10){   //调整允许下载时间 x0.1s
      DLD = 0;
      downLoadSucceceFlag = 0;
      errFlag = 1;
      break;
    }
    delayms(100); 
  }
  
  delayms(200);
  PWRON = 0;
  JKSW001 = 0;
  DLD = 0;
  DISCHARGE = 0;
  delayms(500);
  DISCHARGE = 1;

  if(errFlag == 1){
    DataTransfer('C', 2, 1, 0, 0);
    //TestERR();
  }
  else{
    DataTransfer('C', 2, 1, 0, 0);
  }
 
  BiBi(1);
  return downLoadSucceceFlag;
}

void DetectResetCircuit()
{
  DISCHARGE = 1;

  S2V7 = 0;
  S3V5 = 1;
  delayms(500);
  DataTransfer('D', 3, 1, 'D', TestVTP3()); //after
  S3V5 = 0;
  delayms(50);
  S3V5 = 0;
  S2V7 = 1;
  delayms(50);
  DataTransfer('D', 3, 1, '0', TestVTP3());
  S2V7 = 0;
  DISCHARGE = 0;
  delayms(500);
  DISCHARGE = 1;
  delayms(10);
}

void DetectVZD601()
{
  S7V5 = 1;
  JKRLA = 1;
  delayms(100);
  DataTransfer('D', 4, 1, 'D', TestVZD601()); //after
  S7V5 = 0;
  JKRLA = 0;
  delayms(1000);
}

void DetectPowerCircuit()
{
  u16 VCC,VCCR,VDD,VDDR;
  u16 adcVal[15];
  u8 i;
  extern u8 T;

  delayms(1000);
  PWRON = 1;
  JKSW001 = 1;
  delayms(1000);

  if(T == '1'){
    ACPhaseJudge();
    delayms(13);
    DataTransfer('D', 5, 1, 'H', TestVRYA()); //after
  }

  for(i=0; i<15; i++)
  {
    adcVal[i] = TestVCC();
    delayms(1);
  }

  Quicksort(adcVal,15,0,14);
  VCC   = (adcVal[0]+adcVal[14])/2;
  VCCR  = absNum(adcVal[14],adcVal[0]);

  DataTransfer('D', 5, 1, 'H', VCC/100); //after
  DataTransfer('D', 5, 1, '0', VCCR); //after

  for(i=0; i<15; i++)
  {
    adcVal[i] = TestVDD();
    delayms(1);
  }

  Quicksort(adcVal,15,0,14);
  VDD   = (adcVal[0]+adcVal[14])/2;
  VDDR  = absNum(adcVal[14],adcVal[0]);

  DataTransfer('D', 5, 1, 'D', VDD); //after
  DataTransfer('D', 5, 1, '0', VDDR); //after

}

void DetectInteriorTemperature()
{
  u16 adcVal;

  adcVal = absNum(TestVTP38(),TestRTH2());
  DataTransfer('D', 6, 1, '0', adcVal); //after
}

void DetectOutTemperature()
{
  u16 adcVal;

  adcVal = absNum(TestVTP40(),TestRTH1());
  DataTransfer('D', 7, 1, '0', adcVal); //after

}

//========================================================
void DetectPulseCircuit()
{
  DataTransfer('D', 8, 1, 'T',  TestVTP43(0)); //after
  DataTransfer('D', 8, 1, 'T',  TestVTP43(1)); //after
  DataTransfer('D', 8, 1, 'D',  TestVC802()); //after
}
//========================================================
void DetectRelayCircuit()
{
  extern u8 T;
  delayms(400);

  ACPhaseJudge();
  delayms(13);//确定相位
  DataTransfer('D', 9, 1, '0', TestVRYA()); //after

  if(T != '1')
  {
    ACPhaseJudge();
    delayms(13);//确定相位
    DataTransfer('D', 9, 1, '0', TestVRYB()); //after 
  }
}
//=======================================================
void DetectContactStateCircuit()
{
  extern u8 T;
 
  ACPhaseJudge();
  delayms(12);
  DataTransfer('D', 10, 1, '0', TestVTP4()); //after 

  ACPhaseJudge();
  delayms(3);
  DataTransfer('D', 10, 1, 'D', TestVTP4()); //after 

  if(T != '1'){
    ACPhaseJudge();
    delayms(12);
    DataTransfer('D', 10, 1, '0', TestVTP29()); //after 

    ACPhaseJudge();
    delayms(3);
    DataTransfer('D', 10, 1, 'D', TestVTP29()); //after 
  }
}
//======================================================
void DetectTemperatureExamineCircuit()
{
  u16 VTA,VTAR,VTB,VTBR,VDD;
  u16 adcVal[15];
  u8 i;
  extern u8 T;
  extern u8 TIM4_sCnt;

  delayms(2900);

  TIM4_sCnt = 0;

  for(i=0; i<15; i++)
  {
    adcVal[i] = TestVDD();
    delayms(1);
  }
  Quicksort(adcVal,15,7,14);
  VDD = (adcVal[0]+adcVal[14])/2;

  for(i=0; i<15; i++)
  {
    adcVal[i] = TestVTA();
    delayms(1);
  }
  Quicksort(adcVal,15,7,14);
  VTA = VDD - (adcVal[0]+adcVal[14])/2;
  VTAR = absNum(adcVal[14], adcVal[0]);

  DataTransfer('D', 11, 1, 'D', VTA); //after
  DataTransfer('D', 11, 1, '0', VTAR); //after

  if(T != '1'){
    delayms(1000);
    for(i=0; i<15; i++)
    {
      adcVal[i] = TestVTB();
      delayms(1);
    }
    Quicksort(adcVal,15,7,14);
    VTB = VDD - (adcVal[0]+adcVal[14])/2;
    VTBR = absNum(adcVal[14], adcVal[0]);

    DataTransfer('D', 11, 1, 'D', VTB); //after
    DataTransfer('D', 11, 1, '0', VTBR); //after
  }
  TIM4_sCnt = 0;
}

void DetectRelayAndLEDCircut()
{
  u16 VTP41,VTP41R;
  u16 adcVal[15];
  u16 VQ301H,VQ301L;
  u16 VQ301[20];
  u8 i;
  extern u8 T;


  delayms(20);
  RemoteControl(RMTON);
  RemoteControl(RMTPWRON); //全面 304使用 ON
  DataTransfer('D', 12, 1, 'D', TestLED304R());

  //全面，省工 301 ON, 302 OFF
  RemoteControl(EfficentSW);
  //===============================================
  DataTransfer('D', 12, 1, 'D', TestLED301());
  if(T == '1'){
    DataTransfer('D', 12, 1, 'D', TestLED302());
  }

  if(T != '1'){
    DataTransfer('D', 12, 1, 'D', TestLED301());
  }

  //===============================================
  delayms(300);
  ACPhaseJudge();
  delayms(13);
  DataTransfer('D', 12, 1, 'D', TestVRYA()); //A面 ON
  
  delayms(50);
//蜂鸣器输出
  for(i=0; i<20; i++)
  {
    VQ301[i] = TestVQ301();
    delayus(200);
  }

  Quicksort(VQ301,20,9,19);
  VQ301H = VQ301[19];
  VQ301L = VQ301[0];

  RemoteControl(EfficentSW); //定时功能 LED302 ON
  DataTransfer('D', 12, 1, 'H', VQ301H/100);
  DataTransfer('D', 12, 1, 'D', VQ301L);

  //===========================================

  delayms(200);
  ACPhaseJudge();
  delayms(13);
  DataTransfer('D', 12, 1, 'H', TestVRYA()); //VRTA OFF

  delayms(100);
  ACPhaseJudge();
  delayms(13);
  DataTransfer('D', 12, 1, 'H', TestVRYB()); //VRTB ON

  //VTP41
  for(i=0; i<15; i++)
  {
    adcVal[i] = TestVTP41();
    delayms(1);
  }

  Quicksort(adcVal,15,0,14);
  VTP41   = (adcVal[0]+adcVal[14])/2;
  VTP41R  = absNum(adcVal[14],adcVal[0]);
  DataTransfer('D', 12, 1, 'D', VTP41); 
  DataTransfer('D', 12, 1, '0', VTP41R); 



  TIM4_sCnt = 0;
}

void DetectICFunction()
{
  PWRON = 0;
  JKSW001 = 0;
  RemoteControl(RMTOFF);
  Discharge();
  delayms(1000);
  PWRON = 1;
  JKSW001 = 1;

  SP4041 = 1;

//ANI0
  SP63 = 0; //此时为高电平
  delayms(1);

  SINAINH  = 0;
  SINAC    = 0; 
  SINAB    = 0;
  SINAA    = 0;

  SP10 = 1;  //都为上拉输入
  SP11 = 1;
  SP13 = 1;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70());
  DataTransfer('D', 13, 1, 'D',TestVP71());
  DataTransfer('D', 13, 1, 'D',TestVP72());
  DataTransfer('D', 13, 1, '0',TestVP73());

//ANI1
  SP63 = 0; //此时为高电平
  delayms(1);

  SINAINH  = 0;
  SINAC    = 0; 
  SINAB    = 0;
  SINAA    = 1;

  SP10 = 1;  //都为上拉输入
  SP11 = 1;
  SP13 = 1;
  SP14 = 0;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//ANI2
  SP63 = 0; //此时为高电平
  delayms(2);

  SINAINH  = 0;
  SINAC    = 0; 
  SINAB    = 1;
  SINAA    = 0;

  SP10 = 1;  //都为上拉输入
  SP11 = 1;
  SP13 = 0;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//ANI3
  SP63 = 0; //此时为高电平
  delayms(2);

  SINAINH  = 0;
  SINAC    = 0; 
  SINAB    = 1;
  SINAA    = 1;

  SP10 = 1;  //都为上拉输入
  SP11 = 1;
  SP13 = 0;
  SP14 = 0;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//ANI4
  SP63 = 0; //此时为高电平
  delayms(2);

  SINAINH  = 0;
  SINAC    = 1; 
  SINAB    = 0;
  SINAA    = 0;

  SP10 = 1;  //都为上拉输入
  SP11 = 0;
  SP13 = 1;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//ANI5
  SP63 = 0; //此时为高电平
  delayms(2);

  SINAINH  = 0;
  SINAC    = 1; 
  SINAB    = 0;
  SINAA    = 1;

  SP10 = 1;  //都为上拉输入
  SP11 = 0;
  SP13 = 1;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//ANI6
  SP63 = 0; //此时为高电平
  delayms(2);

  SINAINH  = 0;
  SINAC    = 1; 
  SINAB    = 1;
  SINAA    = 0;

  SP10 = 1;  //都为上拉输入
  SP11 = 0;
  SP13 = 0;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//ANI7
  SP63 = 0; //此时为高电平
  delayms(2);

  SINAINH  = 0;
  SINAC    = 1; 
  SINAB    = 1;
  SINAA    = 1;

  SP10 = 1;  //都为上拉输入
  SP11 = 0;
  SP13 = 1;
  SP14 = 0;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

  SINAINH  = 1;

//MCU判别
  SP63 = 0; //此时为高电平
  delayms(2);

  SP10 = 1;  //都为上拉输入
  SP11 = 0;
  SP13 = 0;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, '0',TestVP71()); 
  DataTransfer('D', 13, 1, '0',TestVP72()); 
  DataTransfer('D', 13, 1, 'D',TestVP73()); 

//继电器B Lo
  SP63 = 0; //此时为高电平
  delayms(2);

  SP10 = 0;  //都为上拉输入
  SP11 = 1;
  SP13 = 1;
  SP14 = 0;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, 'D',TestVP70()); 
  DataTransfer('D', 13, 1, '0',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//继电器B Hi
  SP63 = 0; //此时为高电平
  delayms(2);

  SP10 = 0;  //都为上拉输入
  SP11 = 1;
  SP13 = 0;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, 'D',TestVP70()); 
  DataTransfer('D', 13, 1, '0',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//机型判别
  SP63 = 0; //此时为高电平
  delayms(2);

  SP10 = 0;  //都为上拉输入
  SP11 = 1;
  SP13 = 1;
  SP14 = 0;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, 'D',TestVP73()); 

//继电器A Lo
  SP63 = 0; //此时为高电平
  delayms(2);

  SP10 = 0;  //都为上拉输入
  SP11 = 0;
  SP13 = 1;
  SP14 = 0;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, '0',TestVP70()); 
  DataTransfer('D', 13, 1, 'D',TestVP71()); 
  DataTransfer('D', 13, 1, '0',TestVP72()); 
  DataTransfer('D', 13, 1, 'D',TestVP73()); 

//继电器A Hi
  SP63 = 0; //此时为高电平
  delayms(2);

  SP10 = 0;  //都为上拉输入
  SP11 = 0;
  SP13 = 0;
  SP14 = 1;

  SP63 = 1;
  delayms(2);
  SP63 = 0;
  DataTransfer('D', 13, 1, 'D',TestVP70()); 
  DataTransfer('D', 13, 1, '0',TestVP71()); 
  DataTransfer('D', 13, 1, 'D',TestVP72()); 
  DataTransfer('D', 13, 1, '0',TestVP73()); 

//继电器驱动电源
  DataTransfer('D', 13, 1, 'D',TestVQ406());

//VSCR OFF
  SP10 = 0;  //都为上拉输入
  SP11 = 0;
  SP13 = 0;
  SP14 = 1;

  DataTransfer('D', 13, 1, 'H',TestVSCR701()); //after

//VCSR ON
  SP10 = 0;  //都为上拉输入
  SP11 = 0;
  SP13 = 1;
  SP14 = 1;

  SP63 = 1;
  DataTransfer('D', 13, 1, 'D',TestVSCR701()); //after

  TIM4_sCnt = 0;
}

void Discharge()
{
  PWRON   = 0;
  JKSW001 = 0;
  JKRLA   = 0;
  JKRLB   = 0;
  delayms(1);
  DISCHARGE = 0;
  delayms(2000);
  DISCHARGE = 1;
  TIM4_sCnt = 0;
}

void DetectFinish()
{
  delayms(100);
  RMTDownON = 0;
  RMTUpON = 0;
  DataTransfer('C', 0, 0, 0, 0);
  NVIC_SystemReset(); 
}



