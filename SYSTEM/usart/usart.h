#ifndef __USART_H
#define __USART_H

#include <stdio.h>
#include "stm32f10x.h"

void UART1Init(u32 baudrate);
void UART1PutChar(char DataToSend);
u8    UART1GetChar(void);
void UART1PutStr(char *Str);

void UART2Init(u32 baudrate);
void UART2PutChar(char DataToSend);
u8    UART2GetChar(void);
void UART2PutStr(char *Str);
#endif

//------------------End of File----------------------------
