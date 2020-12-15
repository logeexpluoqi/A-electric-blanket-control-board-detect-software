#ifndef _BD_H
#define _BD_H

#include "Syn.h"
#include "PiontDetect.h"

typedef enum {RMTPWRON = 0, AreaSW = 1, EfficentSW = 2, HalfPowerSW = 3, \
               TemperatureUpSW = 4, TemperatureDownSW = 5, RMTOFF = 6, RMTON = 7} RemoteSW;

extern u8 TIM4_sCnt;              
               
void TestERR(void);
void RemoteControl(RemoteSW SW);
void CoverPlatDown(void);
void CoverPlatUp(void);
u8 DataTransfer(char D1, u16 D2_3, u8 D4, u8 type, u16 value);
u8 ACPhaseJudge(void);
u8 BoardTypeConfirmation(void);
u8 BoardInitSet(void);
u8 DownLoadProcedure(void);
void DetectResetCircuit(void);
void DetectVZD601(void);
void DetectPowerCircuit(void);
void DetectInteriorTemperature(void);
void DetectOutTemperature(void);
void DetectPulseCircuit(void);
void DetectRelayCircuit(void);
void DetectContactStateCircuit(void);
void DetectTemperatureExamineCircuit(void);
void DetectRelayAndLEDCircut(void);
void DetectICFunction(void);
void Discharge(void);
void DetectFinish(void);



#endif
