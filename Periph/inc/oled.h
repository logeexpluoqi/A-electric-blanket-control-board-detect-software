#ifndef _OLED_H
#define _OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	
#include "stdlib.h" 
#include "delay.h"

//-----------------OLED�˿ڶ���----------------  					   
#define OLED_CS_Clr()  	GPIO_ResetBits (GPIOD,GPIO_Pin_4)//CS
#define OLED_CS_Set()  	GPIO_SetBits	 (GPIOD,GPIO_Pin_4)

#define OLED_DC_Clr() 		GPIO_ResetBits (GPIOD,GPIO_Pin_0)//DC
#define OLED_DC_Set() 		GPIO_SetBits	 (GPIOD,GPIO_Pin_0)

#define OLED_RST_Clr() 	GPIO_ResetBits (GPIOD,GPIO_Pin_1)//RES
#define OLED_RST_Set() 	GPIO_SetBits	 (GPIOD,GPIO_Pin_1)

#define OLED_SDIN_Clr() 	GPIO_ResetBits (GPIOD,GPIO_Pin_2)//DIN/DI
#define OLED_SDIN_Set() 	GPIO_SetBits	 (GPIOD,GPIO_Pin_2)

#define OLED_SCLK_Clr() 	GPIO_ResetBits (GPIOD,GPIO_Pin_3)//CLK/DO
#define OLED_SCLK_Set() 	GPIO_SetBits	 (GPIOD,GPIO_Pin_3)
	     
		 
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

void OLED_WR_Byte(u8 dat,u8 cmd);	    	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_P6x8Char(u8 x,u8 y,u8 chr);
void OLED_P8x16Char(u8 x,u8 y,u8 chr);
void OLED_P6x8Str(u8 x,u8 y,u8 ch[]);
void OLED_P8x16Str(u8 x,u8 y,u8 ch[]);
void OLED_P6x8Value(unsigned short x, unsigned short y, int data);
void OLED_P8x16Value(unsigned short x, unsigned short y,int data);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 

