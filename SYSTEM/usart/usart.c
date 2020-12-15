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

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void UART1Init(u32 baudrate)
*��������:		��ʼ��STM32-SDK�������ϵ�RS232�ӿ�
���������
		u32 baudrate   ����RS232���ڵĲ�����
���������û��	
*******************************************************************************/
void UART1Init(u32 baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� UART1 ģ���ʱ��  ʹ�� UART1��Ӧ�����Ŷ˿�PA��ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* ����UART1 �ķ�������
	 ����PA9 Ϊ�������  ˢ��Ƶ��50MHz
	  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* 
	  ����UART1 �Ľ�������
	  ����PA10Ϊ�������� 
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 
	  UART1������:
	  1.������Ϊ���ó���ָ�������� baudrate;
	  2. 8λ����			  USART_WordLength_8b;
	  3.һ��ֹͣλ			  USART_StopBits_1;
	  4. ����żЧ��			  USART_Parity_No ;
	  5.��ʹ��Ӳ��������	  USART_HardwareFlowControl_None;
	  6.ʹ�ܷ��ͺͽ��չ���	  USART_Mode_Rx | USART_Mode_Tx;
	 */
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//Ӧ�����õ�UART1
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
	//����UART1
	USART_Cmd(USART1, ENABLE);
	NVIC_Configuration();
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void UART1PutChar(unsigned char DataToSend)
*��������:		RS232����һ���ֽ�
���������
		unsigned char DataToSend   Ҫ���͵��ֽ�����
���������û��	
*******************************************************************************/
void UART1PutChar(char DataToSend)
{
	//��Ҫ���͵��ֽ�д��UART1�ķ��ͻ�����
	//USART_SendData(USART1, (unsigned char) DataToSend);
	//�ȴ��������
	//while (!(USART1->SR & USART_FLAG_TXE));

	TxBuffer[count++] = DataToSend;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void UART1PutStr(char *Str) //���ͺ��������͵���λ����ֱ����put_string����
{
	//�ж�Strָ��������Ƿ���Ч.
	while (*Str)
	{
		//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
		if (*Str == '\r')
			UART1PutChar(0x0d);
		else if (*Str == '\n')
			UART1PutChar(0x0a);
		else
			UART1PutChar(*Str);
		Str++;
	}
}

void CopeSerialData(unsigned char ucData) //���ݷ��͸�ʽ ��ĸ+����
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
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE); // ȫ���������
		}
		USART_ClearITPendingBit(USART1, USART_IT_TXE);
	}
	else if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{

		CopeSerialData((unsigned char)USART1->DR); //��������
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	USART_ClearITPendingBit(USART1, USART_IT_ORE);
}

//------------------End of File----------------------------
