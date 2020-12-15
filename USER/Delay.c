#include "Delay.h"
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"

unsigned int TimeDelay; //������ȫ�ֱ���
void DelayInit(void)
{
	if (SysTick_Config(SystemCoreClock / 1000000)) //����Ϊ1usһ���ж�
	{
		while (1)
			; //�������ʧ������ѭ��
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //ʧ�ܵδ�ʱ������Ҫʱ��ʹ��
}

void delayus(unsigned int us)
{
	TimeDelay = us;							  //us��ֵ��ȫ�ֱ���TD
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //ʹ�ܵδ�ʱ���������жϴ���
	while (TimeDelay != 0)
		; //���ж����Լ�
}

void delayms(unsigned int ms)
{
	delayus(ms * 1000); //1ms = 1000us
}

void SysTick_Handler(void) //���ж����Լ�
{
	if (TimeDelay != 0)
	{
		TimeDelay--;
	}
}

void Software_Delay(unsigned int sec)
{
	for (; sec > 0; sec--)
		;
}
