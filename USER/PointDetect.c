#include "PiontDetect.h"

#define xMutiple2   2
#define xMutiple3   3
#define xMutiple4   4
#define xMutiple100 100


u16 TestVTP3()
{
  u16 VTP3 = 0;
  u16 adcValue0, adcValue2;
  
  u8 i;
  u16 adcVal[5];
  u16 sum = 0;
  
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 0;
  Sw1ADCB = 0;
  Sw1ADCC = 0;
  
  delayms(3);
  for(i=0;i<5;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  for(i=0; i<5; i++)
  {
    sum = sum + adcVal[i];
  }
  VTP3 = sum/5;
  
  return (VTP3*3300 /4096)*xMutiple2;
}

u16 TestVZD601()
{
  u16 VZD601 = 0;
  u16 adcValue0, adcValue2;
  
  u8 i;
  u16 adcVal[5];
  u16 sum = 0;
  
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 1;
  Sw1ADCB = 0;
  Sw1ADCC = 0;
  
  delayms(3);
  for(i=0;i<5;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  for(i=0; i<5; i++)
  {
    sum += adcVal[i];
  }
  
  VZD601 = sum/5;
  
  return ((VZD601*3500)/4096)*xMutiple4;
}


u32 TestVCC()
{
  u16 VCC = 0;
  u16 adcValue0, adcValue2;


  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 1;
  Sw3ADCB = 1;
  Sw3ADCC = 1;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 5);
  adcValue2 = GetADCAvg(2, 5);
  VCC = (adcValue0 + adcValue2)/2;

  return ((VCC*3500)/4095)*xMutiple4;
}

u16 TestVDD()
{
  u16 VDD = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 0;
  Sw1ADCB = 1;
  Sw1ADCC = 0;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 5);
  adcValue2 = GetADCAvg(2, 5);
  
  VDD = (adcValue0 + adcValue2)/2;
  
  return (VDD*3400/4096)*xMutiple2;
}

u16 TestVTP38()
{
  u16 VTP38 = 0;
  u16 adcValue0, adcValue2;

  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 1;
  Sw1ADCB = 1;
  Sw1ADCC = 0;
  
  delayms(3);
   for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }
  
  VTP38 = sum/10;
  
  return (VTP38*3300/4096)*xMutiple2;
}


u16 TestRTH2()
{
  u16 VRTH2 = 0;
  u16 adcValue0, adcValue2;

  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 1;
  Sw3ADCB = 1;
  Sw3ADCC = 0;
  
  delayms(3);
  for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }
  
  VRTH2 = sum/10;
  return (VRTH2*3380/4096)*xMutiple2;

}

u16 TestVTP40()
{
  u16 VTP40 = 0;
  u16 adcValue0, adcValue2;

  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 0;
  Sw1ADCB = 0;
  Sw1ADCC = 1;
  
  delayms(3);
  for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }
  
  VTP40 = sum/10;
  
  return (VTP40*3360/4096)*xMutiple2;
}

u16 TestRTH1()
{
  u16 VRTH1 = 0;
  u16 adcValue0, adcValue2;

  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 0;
  Sw3ADCB = 0;
  Sw3ADCC = 1;
  
  delayms(3);
  for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }
  
  VRTH1 = sum/10;
  return (VRTH1*3360/4095)*xMutiple2;

}


u8 PD_usCntFlag = 0;
u16 TestVTP43(u8 Polar) // testing high voltage and low voltage time
{
 extern u16 TIM4_10usCnt;

 u16 LoT,HiT;

 TIM4_10usCnt = 0;
  if(Polar ==1){
    if(VTP43IN == 1){
      while(VTP43IN == 1);
      PD_usCntFlag = 1;
      while(VTP43IN == 0);
      PD_usCntFlag = 0;
      LoT = TIM4_10usCnt;
      TIM4_10usCnt = 0;
    }
    return LoT; 
  }
 else{
   while(VTP43IN == 0);
   PD_usCntFlag = 1;
   while(VTP43IN == 1);
   PD_usCntFlag = 0;
   HiT = TIM4_10usCnt;
   TIM4_10usCnt = 0;
   return HiT;
 }
}
 
  

u16 TestVC802()
{
  u16 VC802 = 0;
  u16 adcValue0, adcValue2;

  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 1;
  Sw1ADCB = 0;
  Sw1ADCC = 1;
  
  delayms(3);
  for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }
  
  VC802 = sum/10;
  
  return (VC802*3400/4096)*xMutiple2;
}


u16 TestVRYA()
{
  u16 VRYA = 0;
  u16 adcValue0, adcValue2;
  
  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  

  DVRLA = 0;
  delayms(60);

  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 0;
  
  Sw1ADCA = 1;
  Sw1ADCB = 0;
  Sw1ADCC = 0;
  
  delayms(3);
  for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }

  DVRLA = 1;
  
  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }

  VRYA = sum/10;

  return (VRYA*3360/4096)*xMutiple100;
}

u16 TestVRYB()
{
  u16 VRYB = 0;
  u16 adcValue0, adcValue2;
  
  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  
  DVRLB = 0;
  delayms(60);

  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 0;
  
  Sw1ADCA = 0;
  Sw1ADCB = 1;
  Sw1ADCC = 0;
  
  delayms(3);
  for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  
  DVRLB = 1;

  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }

  VRYB = sum/10;
  
  return (VRYB*3360/4096)*xMutiple100;

}

u16 TestVTP4()
{
  u16 VTP4 = 0;
  u16 adcValue0, adcValue2;
 
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 0;
  Sw1ADCB = 1;
  Sw1ADCC = 1;
  
  delayms(1);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VTP4 = (adcValue0 + adcValue2)/2;
  
  return (VTP4*3400/4096)*xMutiple2;
}

u16 TestVTP29()
{
  u16 VTP29 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 0;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw1ADCA = 1;
  Sw1ADCB = 1;
  Sw1ADCC = 1;
  
  delayms(1);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VTP29 = (adcValue0 + adcValue2)/2;
  
  return (VTP29*3400/4096)*xMutiple2;
}

u16 TestVTA()
{
  u16 VTA = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 0;
  Sw2ADCB = 0;
  Sw2ADCC = 0;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VTA = (adcValue0 + adcValue2)/2;
  return (VTA*3400/4096)*xMutiple2;
}

u16 TestVTB()
{
  u16 VTB = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 1;
  Sw2ADCB = 0;
  Sw2ADCC = 0;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VTB = (adcValue0 + adcValue2)/2;
  return (VTB*3400/4096)*xMutiple2;

}

u16 TestLED304R()
{
  u16 VLED304R = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 0;
  Sw2ADCB = 0;
  Sw2ADCC = 1;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VLED304R = (adcValue0 + adcValue2)/2;

  return (VLED304R*3400/4096)*xMutiple2;
}

u16 TestLED304G()
{
  u16 VLED304G = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 1;
  Sw2ADCB = 0;
  Sw2ADCC = 1;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VLED304G = (adcValue0 + adcValue2)/2;
  return (VLED304G*3400/4096)*xMutiple2;

}

u16 TestLED301()
{
  u16 VLED301 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 0;
  Sw2ADCB = 1;
  Sw2ADCC = 0;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VLED301 = (adcValue0 + adcValue2)/2;
  return (VLED301*3400/4096)*xMutiple2;
}

u16 TestLED302()
{
  u16 VLED302 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 1;
  Sw2ADCB = 1;
  Sw2ADCC = 0;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 15);
  adcValue2 = GetADCAvg(2, 15);
  
  VLED302 = (adcValue0 + adcValue2)/2;
  return (VLED302*3400/4096)*xMutiple2;

}

u16 TestVQ301()
{
  u16 VQ301 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 1;
  Sw3ADCB = 0;
  Sw3ADCC = 1;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 5);
  adcValue2 = GetADCAvg(2, 5);
  
  VQ301 = (adcValue0 + adcValue2)/2;
  return (VQ301*3400/4096)*xMutiple4;

}


u16 TestVTP41()
{
  u16 VTP41 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 0;
  Sw2ADCB = 1;
  Sw2ADCC = 1;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 5);
  adcValue2 = GetADCAvg(2, 5);
  
  VTP41 = (adcValue0 + adcValue2)/2;
  return (VTP41*3400/4096)*xMutiple2;

}


u16 TestVP70()
{
  u16 VP70 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 0;
  Sw3ADCINH = 1;
  Sw4ADCINH = 1;
  
  Sw2ADCA = 1;
  Sw2ADCB = 1;
  Sw2ADCC = 1;
  
  delayms(1);
  adcValue0 = GetADCAvg(0, 25);
  adcValue2 = GetADCAvg(2, 25);
  
  VP70 = (adcValue0 + adcValue2)/2;
  return (VP70*3400/4096)*xMutiple2;
}

u16 TestVP71()
{
  u16 VP71 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 0;
  Sw3ADCB = 0;
  Sw3ADCC = 0;
  
  delayms(1);
  adcValue0 = GetADCAvg(0, 25);
  adcValue2 = GetADCAvg(2, 25);
  
  VP71 = (adcValue0 + adcValue2)/2;
  return (VP71*3400/4096)*xMutiple2;

}

u16 TestVP72()
{
  u16 VP72 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 1;
  Sw3ADCB = 0;
  Sw3ADCC = 0;
  
  delayms(1);
  adcValue0 = GetADCAvg(0, 25);
  adcValue2 = GetADCAvg(2, 25);
  
  VP72 = (adcValue0 + adcValue2)/2;
  return (VP72*3400/4096)*xMutiple2;

}

u16 TestVP73()
{
  u16 VP73 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 0;
  Sw3ADCB = 1;
  Sw3ADCC = 0;
  
  delayms(1);
  adcValue0 = GetADCAvg(0, 25);
  adcValue2 = GetADCAvg(2, 25);
  
  VP73 = (adcValue0 + adcValue2)/2;
  return (VP73*3400/4096)*xMutiple2;

}

u16 TestVQ406()
{
  u16 VQ406 = 0;
  u16 adcValue0, adcValue2;
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 0;
  Sw4ADCINH = 1;
  
  Sw3ADCA = 0;
  Sw3ADCB = 1;
  Sw3ADCC = 1;
  
  delayms(3);
  adcValue0 = GetADCAvg(0, 5);
  adcValue2 = GetADCAvg(2, 5);
  
  VQ406 = (adcValue0 + adcValue2)/2;
  return (VQ406*3400/4096)*xMutiple4;

}


u16 TestVSCR701()
{
  u16 VSCR701 = 0;
  u16 adcValue0, adcValue2;
  u8 i;
  u16 adcVal[10];
  u16 sum = 0;
  
  DVSCR = 0;
  delayms(60);
  
  Sw1ADCINH = 1;
  Sw2ADCINH = 1;
  Sw3ADCINH = 1;
  Sw4ADCINH = 0;
  
  Sw4ADCA = 0;
  Sw4ADCB = 0;
  Sw4ADCC = 0;

  delayms(3);
  for(i=0;i<10;i++)
  {
    adcValue0 = GetADCAvg(0, 5);
    adcValue2 = GetADCAvg(2, 5);
    adcVal[i] = (adcValue0 + adcValue2)/2;
  }
  for(i=0; i<10; i++)
  {
    sum += adcVal[i];
  }
  
  VSCR701 = sum/10;
  return (VSCR701*3400/4096)*xMutiple100;

}







