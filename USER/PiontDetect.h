#ifndef PointDetect_H
#define PointDetect_H

#include "Syn.h"

#define Sw1ADCINH   PEout(0)
#define Sw1ADCC     PEout(3)
#define Sw1ADCB     PEout(2)
#define Sw1ADCA     PEout(1)

#define Sw2ADCINH   PEout(4)
#define Sw2ADCC     PEout(7)
#define Sw2ADCB     PEout(6)
#define Sw2ADCA     PEout(5)

#define Sw3ADCINH   PEout(8)
#define Sw3ADCC     PEout(11)
#define Sw3ADCB     PEout(10)
#define Sw3ADCA     PEout(9)

#define Sw4ADCINH   PEout(12)
#define Sw4ADCC     PEout(15)
#define Sw4ADCB     PEout(14)
#define Sw4ADCA     PEout(13)

#define SP10        PFout(1)
#define SP11        PFout(2)
#define SP13        PFout(3)
#define SP14        PFout(4)
#define SP4041      PFout(5)
#define SP63        PFout(6)
#define S2V7        PFout(7)
#define S3V5        PFout(8)
#define S7V5        PFout(9)
#define SQ602       PFout(10)
#define SQ603       PFout(11)

#define SINAINH     PFout(12)
#define SINAA       PFout(13)
#define SINAB       PFout(14)
#define SINAC       PFout(15)

#define JKRLA       PBout(12)
#define JKSW001     PBout(11)
#define PWRON       PBout(10)

#define JKRLB       PBout(13)
#define P60         PBout(14)
#define DVRLA       PBout(15)

#define DVRLB       PCout(0)
#define DVSCR       PCout(1)
#define DLD         PCout(2)
#define DISCHARGE   PGout(0)

#define RMTA        PGout(11)
#define RMTB        PGout(13)
#define RMTC        PGout(15)
#define RMTUpON     PGout(12)
#define RMTDownON   PGout(14)
#define RMTCOM1     PGout(9)
#define RMTCOM2     PGout(8)

#define DLDSUCC     PBin(5)
#define VTP43IN     PBin(6)
#define SgnP60      PDin(4)
#define ACPhase     PDin(5)




u16 TestVTP3(void);
u16 TestVZD601(void);
u32 TestVCC(void);
u16 TestVDD(void);
u16 TestVTP38(void);
u16 TestVTP40(void);
u16 TestVTP43(u8 Polar); 
u16 TestVC802(void);
u16 TestVTP4(void);
u16 TestVTP29(void);
u16 TestVTA(void);
u16 TestVTB(void);
u16 TestLED304R(void);
u16 TestLED304G(void);
u16 TestLED301(void);
u16 TestLED302(void);
u16 TestVQ301(void);
u16 TestVTP41(void);
u16 TestVP70(void);
u16 TestVP71(void);
u16 TestVP72(void);
u16 TestVP73(void);
u16 TestVQ406(void);
u16 TestRTH1(void);
u16 TestRTH2(void);
u16 TestVSCR701(void);
u16 TestVRYA(void);
u16 TestVRYB(void);




#endif
