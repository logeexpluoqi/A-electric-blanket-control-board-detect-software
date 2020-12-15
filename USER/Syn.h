#ifndef _Syn_h
#define _Syn_h

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "Delay.h"
#include "string.h"
#include "sys.h"
#include "timer.h"
#include "stm32f10x_adc.h"

#define MotorPUL PCout(7)
#define MotorDIR PCout(9)
#define MotorENA PCout(11)

#define Key1 PDin(7)
#define Key2 PDin(8)
#define Key3 PDin(9)
#define Key4 PDin(10)

#define LeftButton   PDin(11)
#define RightButton  PDin(12)
#define DownLimit    PDin(13)
#define UpLimit      PDin(14)

#define BeepPin PGout(6)

typedef enum {EXTI_OFF = 0, EXTI_ON = 1} EXTIxLine;
typedef enum {MotorStop = 0, MotorUp = 1, MotorDown = 2, MotorOFF = 3} motorState;


void Quicksort(u16 array[], u8 maxlen, u8 begin, u8 end);
u16  absNum(u16 a, u16 b);

void  ADCInit(void);
u16   GetADC(u8 ch);
void  StartADCRead(void);
u16   GetADCAvg(u8 ch,u8 times);
void  EndADCRead(void);

void MotorPinInit(void);
void MotorControl(motorState state);
void SWPinInit(void);
void InputPinInit(void);
void KeyPinInit(void);
void ACPhaseInit(void);
void RemotePinInit(void);

void BeepPinInit(void);
void BeepON(void);
void BeepOFF(void);

void JTAG_Set(u8 mode);
void EXTILineOFF_ON(uint32_t EXTI_Line, EXTIxLine State);

void VTP43TimeInit(void);
void EXTI9_5_IRQHandler(void);

void BiBi(u8 times);

#endif
