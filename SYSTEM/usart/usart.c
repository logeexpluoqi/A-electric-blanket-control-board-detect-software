#include "usart.h"
#include "misc.h"
#include "stm32f10x_usart.h"
//#include "Lcd_Driver.h"
uint8_t TxBuffer[256];
uint8_t TxCounter = 0;
uint8_t count = 0;

int8_t DataCnt = 0, DataBuff[2];

u8 x1 = 0, x2 = 0, x3 = 0, C = 0, P = 0, T = 0;

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**************************实现函数********************************************
*函数原型:		void UART1Init(u32 baudrate)
*功　　能:		初始化STM32-SDK开发板上的RS232接口
输入参数：
		u32 baudrate   设置RS232串口的波特率
输出参数：没有	
*******************************************************************************/
void UART1Init(u32 baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 使能 UART1 模块的时钟  使能 UART1对应的引脚端口PA的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* 配置UART1 的发送引脚
	 配置PA9 为复用输出  刷新频率50MHz
	  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* 
	  配置UART1 的接收引脚
	  配置PA10为浮地输入 
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 
	  UART1的配置:
	  1.波特率为调用程序指定的输入 baudrate;
	  2. 8位数据			  USART_WordLength_8b;
	  3.一个停止位			  USART_StopBits_1;
	  4. 无奇偶效验			  USART_Parity_No ;
	  5.不使用硬件流控制	  USART_HardwareFlowControl_None;
	  6.使能发送和接收功能	  USART_Mode_Rx | USART_Mode_Tx;
	 */
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//应用配置到UART1
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
	//启动UART1
	USART_Cmd(USART1, ENABLE);
	NVIC_Configuration();
}

/**************************实现函数********************************************
*函数原型:		void UART1PutChar(unsigned char DataToSend)
*功　　能:		RS232发送一个字节
输入参数：
		unsigned char DataToSend   要发送的字节数据
输出参数：没有	
*******************************************************************************/
void UART1PutChar(char DataToSend)
{
	//将要发送的字节写到UART1的发送缓冲区
	//USART_SendData(USART1, (unsigned char) DataToSend);
	//等待发送完成
	//while (!(USART1->SR & USART_FLAG_TXE));

	TxBuffer[count++] = DataToSend;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void UART1PutStr(char *Str) //发送函数，发送到上位机，直接用put_string即可
{
	//判断Str指向的数据是否有效.
	while (*Str)
	{
		//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
		if (*Str == '\r')
			UART1PutChar(0x0d);
		else if (*Str == '\n')
			UART1PutChar(0x0a);
		else
			UART1PutChar(*Str);
		Str++;
	}
}

void CopeSerialData(unsigned char ucData) //数据发送格式 字母+数字
{
	DataBuff[DataCnt] = ucData;
	if ( 	DataCnt     == 0 	\
		 && DataBuff[0] != 'C'	\
		 && DataBuff[0] != 'P'	\
		 && DataBuff[0] != 'T'	\
		 && DataBuff[0] != 'D'	\
		 && DataBuff[0] != 'E'	\
		 && DataBuff[0] != 'F')
		return;

	DataCnt++;

	if (DataCnt == 2)
	{
		DataCnt = 0;
		if (DataBuff[0] == 'C')
		{
			C = DataBuff[1];
		}
		else if (DataBuff[0] == 'P')
		{
			P = DataBuff[1];
		}
		else if (DataBuff[0] == 'T')
		{
			T = DataBuff[1];
		}
		else if (DataBuff[0] == 'D')
		{
			x1 = DataBuff[1];
		}
		else if (DataBuff[0] == 'E')
		{
			x2 = DataBuff[1];
		}
		else if (DataBuff[0] == 'F')
		{
			x3 = DataBuff[1];
		}
	}
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{
		USART_SendData(USART1, TxBuffer[TxCounter++]);
		if (TxCounter == count)
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE); // 全部发送完成
		}
		USART_ClearITPendingBit(USART1, USART_IT_TXE);
	}
	else if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{

		CopeSerialData((unsigned char)USART1->DR); //处理数据
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	USART_ClearITPendingBit(USART1, USART_IT_ORE);
}

//------------------End of File----------------------------
