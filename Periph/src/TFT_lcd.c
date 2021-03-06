#include "tft_lcd.h"
#include "Delay.h"
/*————————————————————————————————————————————
	显示图片的模
————————————————————————————————————————————*/
//16位BMP 40X40 QQ图像取模数据
//Image2LCD取模选项设置
//水平扫描
//16位
//40X40
//不包含图像头数据
//自左至右
//自顶至底
//低位在前

struct typFNT_GB162
{
       unsigned char Index[2];	
       char Msk[32];
};
#define hz16_num   50
const struct typFNT_GB162 hz16[] = {
#if USE_ONCHIP_FLASH_FONT
"电",0x02,0x00,0x02,0x00,0x02,0x00,0x7F,0xF0,0x42,0x10,0x42,0x10,0x7F,0xF0,0x42,0x10,0x42,0x10,0x7F,0xF0,0x42,0x00,0x02,0x08,0x02,0x08,0x01,0xF8,0x00,0x00,0x00,0x00,
"子",0x7F,0xF0,0x00,0x20,0x00,0x40,0x00,0x80,0x01,0x00,0x02,0x00,0xFF,0xF8,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,
"全",0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
"动",0x00,0x40,0x00,0x40,0x7C,0x40,0x00,0x40,0x01,0xFC,0x00,0x44,0xFE,0x44,0x20,0x44,0x20,0x44,0x20,0x84,0x48,0x84,0x44,0x84,0xFD,0x04,0x45,0x04,0x02,0x28,0x04,0x10,
"技",0x10,0x20,0x10,0x20,0x10,0x20,0x13,0xFE,0xFC,0x20,0x10,0x20,0x10,0x20,0x15,0xFC,0x18,0x84,0x30,0x88,0xD0,0x48,0x10,0x50,0x10,0x20,0x10,0x50,0x51,0x88,0x26,0x06,
"术",0x01,0x00,0x01,0x20,0x01,0x10,0x01,0x10,0x7F,0xFC,0x03,0x80,0x05,0x40,0x05,0x40,0x09,0x20,0x11,0x10,0x21,0x08,0x41,0x04,0x01,0x02,0x01,0x00,0x01,0x00,0x01,0x00,
"液",0x00,0x80,0x40,0x40,0x27,0xF8,0x11,0x40,0x01,0x40,0x82,0x78,0x42,0x48,0x16,0xA8,0x1A,0xD0,0x23,0x50,0x22,0x20,0x42,0x20,0x42,0x50,0x02,0x88,0x00,0x00,0x00,0x00,
"晶",0x3F,0xE0,0x20,0x20,0x3F,0xE0,0x20,0x20,0x3F,0xE0,0x00,0x00,0xFD,0xF8,0x85,0x08,0x85,0x08,0xFD,0xF8,0x85,0x08,0x85,0x08,0xFD,0xF8,0x85,0x08,0x00,0x00,0x00,0x00,
"测",0x00,0x08,0x4F,0x88,0x28,0x88,0x0A,0xA8,0x8A,0xA8,0x4A,0xA8,0x0A,0xA8,0x2A,0xA8,0x2A,0xA8,0x42,0x28,0x45,0x08,0x84,0x88,0x88,0x88,0x10,0x38,0x00,0x00,0x00,0x00,
"试",0x40,0x50,0x20,0x48,0x20,0x40,0x0F,0xF8,0x00,0x40,0xE0,0x40,0x27,0x40,0x22,0x40,0x22,0x40,0x22,0x20,0x2A,0x28,0x33,0xA8,0x2E,0x18,0x00,0x08,0x00,0x00,0x00,0x00,
"程",0x00,0x00,0x1B,0xF0,0xE2,0x10,0x22,0x10,0x23,0xF0,0xF8,0x00,0x20,0x00,0x33,0xF0,0x68,0x80,0x60,0x80,0xA3,0xF0,0x20,0x80,0x20,0x80,0x27,0xF8,0x00,0x00,0x00,0x00,
"序",0x02,0x00,0x01,0x00,0x3F,0xF8,0x20,0x00,0x2F,0xF0,0x20,0x20,0x22,0x40,0x21,0x80,0x3F,0xF8,0x20,0x88,0x20,0x90,0x40,0x80,0x40,0x80,0x83,0x80,0x00,0x00,0x00,0x00,
"颜",0x20,0x00,0x10,0xF8,0x7E,0x20,0x44,0x40,0x28,0xF8,0x7E,0x88,0x48,0xA8,0x50,0xA8,0x64,0xA8,0x48,0xA8,0x72,0xA8,0x84,0x50,0x18,0x88,0x61,0x08,0x00,0x00,0x00,0x00,
"色",0x10,0x00,0x10,0x00,0x3F,0xE0,0x40,0x40,0x80,0x80,0x7F,0xF0,0x42,0x10,0x42,0x10,0x42,0x10,0x7F,0xF0,0x40,0x00,0x40,0x08,0x40,0x08,0x3F,0xF8,0x00,0x00,0x00,0x00,
"填",0x20,0x80,0x2F,0xF8,0x20,0x80,0x27,0xF0,0xF4,0x10,0x27,0xF0,0x24,0x10,0x27,0xF0,0x24,0x10,0x27,0xF0,0x34,0x10,0xCF,0xF8,0x02,0x20,0x04,0x10,0x00,0x00,0x00,0x00,
"充",0x04,0x00,0x02,0x00,0xFF,0xF8,0x08,0x00,0x10,0x40,0x20,0x20,0x7F,0xF0,0x08,0x90,0x08,0x80,0x08,0x80,0x08,0x80,0x10,0x88,0x20,0x88,0xC0,0x78,0x00,0x00,0x00,0x00,
"文",0x04,0x00,0x02,0x00,0x02,0x00,0xFF,0xF8,0x10,0x40,0x10,0x40,0x08,0x80,0x08,0x80,0x05,0x00,0x02,0x00,0x05,0x00,0x08,0x80,0x30,0x60,0xC0,0x18,0x00,0x00,0x00,0x00,
"字",0x04,0x00,0x02,0x00,0xFF,0xF8,0x80,0x08,0x80,0x08,0x3F,0xC0,0x00,0x80,0x01,0x00,0x02,0x00,0xFF,0xF8,0x02,0x00,0x02,0x00,0x02,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,
"显",0x3F,0xE0,0x20,0x20,0x20,0x20,0x3F,0xE0,0x20,0x20,0x20,0x20,0x3F,0xE0,0x08,0x80,0x48,0x90,0x28,0x90,0x28,0xA0,0x08,0x80,0x08,0x80,0xFF,0xF8,0x00,0x00,0x00,0x00,
"示",0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF8,0x02,0x00,0x12,0x40,0x12,0x20,0x22,0x10,0x42,0x08,0x82,0x08,0x02,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,
"图",0x7F,0xF8,0x40,0x08,0x44,0x08,0x47,0xC8,0x48,0x48,0x54,0x88,0x43,0x08,0x4C,0xC8,0x73,0x38,0x40,0x88,0x4C,0x08,0x43,0x08,0x40,0x88,0x7F,0xF8,0x00,0x00,0x00,0x00,
"片",0x00,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x3F,0xF0,0x20,0x00,0x20,0x00,0x20,0x00,0x3F,0xC0,0x20,0x40,0x20,0x40,0x20,0x40,0x40,0x40,0x80,0x40,0x00,0x00,0x00,0x00,
"触",0x20,0x40,0x38,0x40,0x48,0x40,0x91,0xF0,0x7D,0x50,0x55,0x50,0x55,0x50,0x7D,0x50,0x55,0xF0,0x54,0x40,0x7C,0x40,0x54,0x50,0x57,0xF8,0x8C,0x08,0x00,0x00,0x00,0x00,
"摸",0x22,0x20,0x22,0x20,0x27,0xF8,0xFA,0x20,0x27,0xF0,0x24,0x10,0x27,0xF0,0x34,0x10,0xE7,0xF0,0x20,0x80,0x2F,0xF8,0x21,0x40,0x22,0x20,0xEC,0x18,0x00,0x00,0x00,0x00,
"输",0x40,0x80,0x41,0x40,0xF2,0x20,0x44,0x10,0x8B,0xE8,0xA0,0x00,0xF7,0x88,0x24,0xA8,0x27,0xA8,0x34,0xA8,0xE7,0xA8,0x24,0xA8,0x24,0x88,0x25,0xB8,0x00,0x00,0x00,0x00,
"入",0x08,0x00,0x04,0x00,0x04,0x00,0x02,0x00,0x02,0x00,0x05,0x00,0x05,0x00,0x08,0x80,0x08,0x80,0x10,0x40,0x10,0x40,0x20,0x20,0x40,0x10,0x80,0x08,0x00,0x00,0x00,0x00,
"程",0x00,0x00,0x1B,0xF0,0xE2,0x10,0x22,0x10,0x23,0xF0,0xF8,0x00,0x20,0x00,0x33,0xF0,0x68,0x80,0x60,0x80,0xA3,0xF0,0x20,0x80,0x20,0x80,0x27,0xF8,0x00,0x00,0x00,0x00,
"技",0x20,0x80,0x20,0x80,0x20,0x80,0xF7,0xF0,0x20,0x80,0x20,0x80,0x27,0xE0,0x32,0x20,0xE2,0x20,0x21,0x40,0x20,0x80,0x21,0x40,0x22,0x20,0xEC,0x18,0x00,0x00,0x00,0x00,
"术",0x02,0x00,0x02,0x40,0x02,0x20,0x02,0x00,0xFF,0xF8,0x07,0x00,0x0A,0x80,0x0A,0x80,0x12,0x40,0x22,0x20,0x42,0x10,0x82,0x08,0x02,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
"支",0x02,0x00,0x02,0x00,0xFF,0xF8,0x02,0x00,0x02,0x00,0x7F,0xE0,0x10,0x20,0x10,0x40,0x08,0x80,0x05,0x00,0x02,0x00,0x05,0x00,0x18,0xC0,0xE0,0x38,0x00,0x00,0x00,0x00,
"持",0x20,0x80,0x20,0x80,0x23,0xF0,0xF8,0x80,0x20,0x80,0x27,0xF8,0x28,0x20,0x30,0x20,0xE7,0xF8,0x20,0x20,0x22,0x20,0x21,0x20,0x20,0x20,0xE0,0xE0,0x00,0x00,0x00,0x00,
"专",0x02,0x00,0x02,0x00,0x7F,0xF0,0x04,0x00,0x04,0x00,0xFF,0xF8,0x08,0x00,0x10,0x00,0x3F,0xE0,0x00,0x20,0x00,0x40,0x1C,0x80,0x03,0x00,0x00,0x80,0x00,0x00,0x00,0x00,
"注",0x01,0x00,0x40,0x80,0x20,0x00,0x17,0xF0,0x00,0x80,0x80,0x80,0x40,0x80,0x00,0x80,0x17,0xF0,0x10,0x80,0x20,0x80,0x20,0x80,0x40,0x80,0x4F,0xF8,0x00,0x00,0x00,0x00,
"批",0x20,0x40,0x24,0x40,0x24,0x40,0xF4,0x48,0x24,0x50,0x27,0x60,0x24,0x40,0x34,0x40,0xE4,0x40,0x24,0x40,0x24,0x40,0x25,0x48,0x26,0x48,0xE4,0x38,0x00,0x00,0x00,0x00,
"发",0x02,0x00,0x22,0x20,0x22,0x10,0x44,0x00,0x7F,0xF8,0x04,0x00,0x08,0x00,0x0F,0xE0,0x14,0x20,0x24,0x40,0x42,0x80,0x81,0x00,0x06,0xC0,0x38,0x38,0x00,0x00,0x00,0x00,
"成",0x00,0xA0,0x00,0x90,0x00,0x80,0x7F,0xF8,0x40,0x80,0x40,0x90,0x7C,0x90,0x44,0x90,0x44,0xA0,0x44,0xA0,0x44,0x48,0x58,0xA8,0x41,0x18,0x82,0x08,0x00,0x00,0x00,0x00,
"功",0x01,0x00,0x01,0x00,0xF9,0x00,0x23,0xF0,0x21,0x10,0x21,0x10,0x21,0x10,0x21,0x10,0x21,0x10,0x39,0x10,0xC2,0x10,0x02,0x10,0x04,0x10,0x08,0x60,0x00,0x00,0x00,0x00,
"移",0x00,0x00,0x00,0x20,0x00,0x78,0x0C,0xE4,0x79,0x04,0x51,0x68,0x10,0x30,0x7E,0x60,0x19,0x98,0x1A,0x3C,0x2F,0xE4,0x48,0xE4,0x08,0x38,0x00,0x30,0x00,0x60,0x00,0x00,
"选",0x00,0x00,0x01,0x20,0x01,0x20,0x03,0xFC,0x62,0x20,0x34,0x20,0x04,0x20,0x03,0xFC,0x24,0x00,0x21,0xB0,0x21,0x20,0x22,0x20,0x32,0x3E,0x18,0x00,0x0F,0xE0,0x00,0x00,
"择",0x00,0x00,0x00,0x00,0x10,0xFC,0x13,0x04,0x11,0x0C,0x3D,0xF8,0x70,0x3E,0x10,0xD0,0x15,0x90,0x7C,0xF0,0x50,0x3E,0x18,0x10,0x1B,0xFE,0x02,0x30,0x00,0x20,0x00,0x00,
"项",0x00,0x00,0x00,0x00,0x03,0xFE,0x00,0x60,0x7C,0x40,0x12,0xFC,0x11,0x04,0x11,0x06,0x11,0x36,0x11,0x24,0x1F,0x44,0x79,0x44,0x00,0xC0,0x00,0x9C,0x01,0x86,0x00,0x00,
"目",0x00,0x00,0x00,0x00,0x0F,0xE0,0x3C,0x18,0x20,0x08,0x20,0x04,0x3E,0x04,0x60,0x04,0x60,0x04,0x7E,0x04,0x60,0x04,0x20,0x0C,0x20,0x08,0x1F,0xF0,0x01,0x80,0x00,0x00,
"短",0x00,0x00,0x08,0x00,0x11,0xFC,0x10,0x3E,0x3E,0xF8,0x2D,0x8C,0x29,0x04,0x49,0x04,0x09,0x04,0x3E,0x8C,0x50,0xFC,0x10,0x88,0x1E,0xC8,0x11,0xFC,0x10,0x0E,0x00,0x00,
"按",0x00,0x00,0x00,0x40,0x00,0x60,0x12,0xFE,0x13,0x02,0x3A,0x42,0x7F,0x44,0x10,0xC4,0x1B,0xFE,0x3C,0x98,0x71,0x90,0x11,0x30,0x11,0xA0,0x00,0x78,0x00,0x4C,0x00,0x00,
"确",0x00,0x00,0x00,0x40,0x00,0xF8,0x78,0xC4,0x1F,0x8C,0x31,0x38,0x21,0xEC,0x21,0x26,0x41,0x3A,0x7D,0xE2,0x27,0x22,0x25,0xFA,0x3D,0x26,0x01,0x24,0x01,0x04,0x00,0x00,
"定",0x00,0x00,0x01,0x00,0x01,0x70,0x5F,0xFC,0x70,0x04,0x20,0x04,0x2F,0xF8,0x01,0x00,0x11,0x00,0x11,0x38,0x21,0xC4,0x31,0x00,0x3F,0x00,0x63,0xE0,0x40,0x38,0x00,0x00,
"长",0x00,0x00,0x00,0x00,0x08,0x18,0x08,0x60,0x08,0xC0,0x0B,0x00,0x1E,0x00,0x18,0x1C,0x7F,0xF0,0x10,0x00,0x11,0x80,0x10,0xE0,0x18,0x38,0x09,0x8E,0x0F,0x00,0x00,0x00,
"按",0x00,0x00,0x00,0x40,0x00,0x60,0x12,0xFE,0x13,0x02,0x3A,0x42,0x7F,0x44,0x10,0xC4,0x1B,0xFE,0x3C,0x98,0x71,0x90,0x11,0x30,0x11,0xA0,0x00,0x78,0x00,0x4C,0x00,0x00,
"返",0x00,0x00,0x00,0x00,0x07,0xF8,0x06,0x00,0x24,0x00,0x14,0xF8,0x07,0x8C,0x04,0x04,0x24,0x08,0x26,0x18,0x25,0xF0,0x64,0x7C,0x64,0xC2,0x20,0x80,0x1F,0xC0,0x00,0x00,
"回",0x00,0x00,0x00,0x00,0x1F,0xF0,0x30,0x18,0x20,0x08,0x27,0x8C,0x2C,0x44,0x28,0x44,0x28,0x44,0x2C,0xC4,0x27,0x84,0x20,0x04,0x30,0x0C,0x1F,0xF8,0x03,0x80,0x00,0x00,
#endif
0x00,
};

struct typFNT_GB242
{
       unsigned char Index[2];	
       char Msk[72];
};

const struct typFNT_GB242 hz24[] = 
{
#if USE_ONCHIP_FLASH_FONT
"纯",0x00,0x00,0x00,0x00,0x01,0x00,0x06,0x01,0x00,0x04,0x01,0x00,0x0C,0x01,0x08,0x08,0x7F,0xFC,0x10,0x81,0x00,0x10,0xC1,0x00,0x21,0xB1,0x10,0x4F,0x31,0x10,0x32,0x31,0x10,0x04,0x31,0x10,0x04,0x31,0x10,0x08,0x31,0x10,0x13,0x3F,0xF0,0x3C,0x01,0x10,0x30,0x01,0x00,0x00,0x01,0x04,0x01,0x81,0x04,0x06,0x01,0x04,0x78,0x01,0x06,0x20,0x01,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
"色",0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFE,0x00,0x03,0xE3,0x00,0x07,0x03,0x00,0x0C,0x03,0x00,0x1C,0x3F,0x00,0x3B,0xFF,0xC0,0x3F,0x30,0x60,0x0C,0x30,0x20,0x0C,0x30,0x20,0x0C,0x10,0x20,0x0C,0x10,0x60,0x0F,0xFF,0xC0,0x08,0x3F,0x00,0x08,0x00,0x00,0x08,0x00,0x60,0x0E,0x3F,0xE0,0x07,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"填",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0xFF,0xE0,0x0C,0x07,0xF0,0x0C,0x06,0x00,0x0C,0xFF,0x80,0x3F,0xF0,0xE0,0x1F,0xC0,0x60,0x0C,0xFE,0x30,0x0C,0xCC,0x30,0x04,0xF8,0x30,0x04,0xFF,0x20,0x04,0xC0,0x20,0x1F,0xFE,0x60,0x3E,0xC0,0x60,0x01,0xFF,0xF0,0x01,0xFF,0xF0,0x00,0x60,0x60,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"充",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x30,0x00,0x07,0xFF,0xF0,0x3F,0xFF,0xE0,0x03,0x00,0x00,0x06,0x01,0x80,0x0C,0x01,0x80,0x08,0x01,0xC0,0x18,0x07,0xE0,0x0F,0xFE,0x70,0x07,0xE0,0x00,0x02,0x06,0x00,0x06,0x04,0x00,0x04,0x04,0x00,0x04,0x04,0x00,0x0C,0x06,0x70,0x0C,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"测",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x39,0xFC,0x30,0x1F,0xCC,0x30,0x07,0x06,0xB0,0x0F,0x06,0xF0,0x19,0x07,0xB0,0x31,0x37,0xB0,0x31,0x36,0xF0,0x1F,0x27,0xF0,0x01,0x67,0xF0,0x01,0xE5,0xF0,0x01,0xE1,0xF0,0x00,0x41,0xF0,0x0C,0xF8,0xB0,0x3C,0xD8,0x30,0x00,0x8C,0x30,0x00,0x80,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"试",0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x03,0x60,0x0C,0x03,0x70,0x0C,0x03,0x30,0x00,0x3F,0xE0,0x00,0x3F,0x80,0x08,0x01,0x00,0x3C,0x01,0x80,0x04,0x7F,0x80,0x04,0x7D,0x80,0x0C,0x00,0x80,0x0C,0x10,0xC0,0x0C,0x10,0xC0,0x0C,0x18,0x40,0x0C,0x1C,0x60,0x0F,0x7E,0x60,0x06,0x70,0x30,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"文",0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0xE0,0x00,0x00,0x70,0x00,0x01,0xFF,0xE0,0x1F,0xFF,0xC0,0x18,0x01,0x00,0x00,0x03,0x00,0x00,0x06,0x00,0x00,0x0E,0x00,0x00,0x1C,0x00,0x0E,0x18,0x00,0x07,0x30,0x00,0x01,0xE0,0x00,0x00,0xF0,0x00,0x00,0xFC,0x00,0x01,0x8F,0x00,0x03,0x03,0xC0,0x02,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"字",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x3F,0x00,0x31,0xFF,0xE0,0x3F,0xC0,0x20,0x38,0x00,0x30,0x30,0xFE,0x20,0x33,0xC6,0x60,0x10,0x02,0x00,0x00,0x0C,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x0C,0x00,0x07,0xFF,0xE0,0x3F,0xFF,0xE0,0x00,0x04,0x00,0x00,0x0C,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"显",0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0x00,0x0F,0x03,0xC0,0x0C,0x00,0x40,0x1F,0xF8,0x60,0x18,0x00,0x60,0x08,0x00,0x40,0x0E,0x01,0xC0,0x07,0xFF,0x00,0x00,0x00,0x00,0x01,0x84,0x00,0x01,0x84,0x00,0x19,0x87,0x80,0x0F,0x8C,0xE0,0x07,0x8C,0x20,0x00,0xCC,0x00,0x03,0xFF,0xE0,0x1F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"示",0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x1F,0xFF,0xC0,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xC0,0x3F,0xFF,0xE0,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x06,0x13,0x00,0x0C,0x13,0xC0,0x0C,0x18,0xF0,0x18,0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"图",0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0x00,0x0F,0x03,0x80,0x1C,0xC0,0xC0,0x19,0xFC,0x60,0x11,0xC6,0x60,0x33,0x06,0x20,0x33,0xE6,0x30,0x36,0xFF,0x30,0x30,0x1F,0xF0,0x30,0x70,0x30,0x30,0xFC,0x30,0x33,0x9F,0x30,0x36,0x00,0x20,0x10,0xE0,0x60,0x18,0x7C,0x40,0x0E,0x01,0xC0,0x03,0xFF,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"片",0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x18,0x00,0x18,0x08,0x00,0x18,0x08,0x00,0x18,0x08,0x00,0x18,0x0C,0x20,0x1F,0xFF,0xF0,0x1F,0xF8,0x00,0x18,0x00,0x00,0x10,0x00,0x00,0x10,0xF8,0x00,0x1F,0xFE,0x00,0x1E,0x03,0x00,0x10,0x03,0x00,0x10,0x03,0x00,0x10,0x03,0x00,0x10,0x03,0x00,0x18,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"显",0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0x00,0x0F,0x03,0xC0,0x0C,0x00,0x40,0x1F,0xF8,0x60,0x18,0x00,0x60,0x08,0x00,0x40,0x0E,0x01,0xC0,0x07,0xFF,0x00,0x00,0x00,0x00,0x01,0x84,0x00,0x01,0x84,0x00,0x19,0x87,0x80,0x0F,0x8C,0xE0,0x07,0x8C,0x20,0x00,0xCC,0x00,0x03,0xFF,0xE0,0x1F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"示",0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x1F,0xFF,0xC0,0x00,0x7F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xC0,0x3F,0xFF,0xE0,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x06,0x13,0x00,0x0C,0x13,0xC0,0x0C,0x18,0xF0,0x18,0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"触",0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x01,0x80,0x0F,0xC1,0x80,0x1E,0x61,0x80,0x30,0x4F,0xC0,0x20,0xCF,0xE0,0x07,0x8D,0x30,0x3F,0xC9,0x30,0x33,0x79,0x30,0x33,0x79,0x30,0x3F,0xFB,0x30,0x37,0xFF,0x20,0x32,0x67,0xE0,0x3F,0xE3,0x80,0x3F,0xE3,0xC0,0x32,0x63,0x60,0x32,0x67,0xF0,0x30,0x4F,0xB0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"摸",0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xC0,0x00,0xFF,0xF0,0x0C,0x79,0xC0,0x0C,0x1F,0x80,0x0C,0x7F,0xE0,0x3F,0xE0,0x60,0x0C,0xC0,0x30,0x0C,0xFC,0x30,0x04,0xC0,0x30,0x07,0xC0,0x30,0x1E,0x60,0x60,0x3C,0x3F,0xC0,0x04,0x1C,0x00,0x04,0x7F,0xE0,0x00,0xFF,0xE0,0x00,0x30,0xC0,0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"输",0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x03,0x80,0x0C,0x0F,0xC0,0x08,0x1C,0x70,0x3F,0x70,0x00,0x1F,0x9F,0xC0,0x10,0x1F,0xC0,0x10,0x00,0x00,0x36,0x7C,0x30,0x17,0xE6,0x30,0x1F,0xE3,0xB0,0x06,0x7F,0xB0,0x02,0x77,0xF0,0x07,0xE3,0xF0,0x3F,0x7F,0xF0,0x13,0x36,0xF0,0x03,0x26,0x30,0x03,0x26,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
"入",0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x03,0x80,0x00,0x01,0xC0,0x00,0x00,0xE0,0x00,0x00,0x70,0x00,0x00,0x78,0x00,0x00,0xCC,0x00,0x00,0xC6,0x00,0x01,0x83,0x00,0x03,0x01,0x80,0x07,0x00,0xC0,0x06,0x00,0xE0,0x0C,0x00,0x70,0x18,0x00,0x30,0x18,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
#endif
0x00,
};
#define hz24_num   20

const unsigned char asc16[]={
#if USE_ONCHIP_FLASH_FONT
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //" "
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x10,0x10,0x00,0x00, //"!"
0x00,0x00,0x6C,0x6C,0x24,0x24,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00, //"""
0x00,0x24,0x24,0x24,0x24,0xFE,0x48,0x48,0x48,0x48,0xFC,0x90,0x90,0x90,0x90,0x00, //"#"
0x00,0x10,0x3C,0x54,0x92,0x90,0x50,0x38,0x14,0x12,0x12,0x92,0x54,0x78,0x10,0x00, //"$"
0x00,0x00,0x22,0x5C,0x94,0xA8,0x48,0x10,0x10,0x24,0x2A,0x52,0x54,0x88,0x00,0x00, //"%"
0x00,0x00,0x30,0x48,0x48,0x50,0x20,0x6E,0x54,0x94,0x8C,0x88,0x8A,0x74,0x00,0x00, //"&"
0x00,0x00,0x30,0x30,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"'"
0x00,0x04,0x08,0x10,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x10,0x08,0x04,0x00, //"("
0x00,0x80,0x40,0x20,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x20,0x40,0x80,0x00, //")"
0x00,0x00,0x00,0x00,0x10,0x54,0x38,0x10,0x38,0x54,0x10,0x00,0x00,0x00,0x00,0x00, //"*"
0x00,0x00,0x00,0x10,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00, //"+"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x20,0x00, //","
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"-"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00, //"."
0x00,0x00,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x80,0x80,0x00,0x00, //"/"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"0"
0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00, //"1"
0x00,0x00,0x38,0x44,0x82,0x82,0x04,0x08,0x10,0x20,0x40,0x82,0x84,0xFC,0x00,0x00, //"2"
0x00,0x00,0x38,0x44,0x82,0x02,0x04,0x38,0x04,0x02,0x02,0x82,0x44,0x38,0x00,0x00, //"3"
0x00,0x00,0x04,0x0C,0x14,0x14,0x24,0x24,0x44,0x44,0xFE,0x04,0x04,0x0E,0x00,0x00, //"4"
0x00,0x00,0xFC,0x80,0x80,0x80,0xB8,0xC4,0x82,0x02,0x02,0x82,0x84,0x78,0x00,0x00, //"5"
0x00,0x00,0x3C,0x42,0x82,0x80,0xB8,0xC4,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"6"
0x00,0x00,0x7E,0x42,0x82,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x10,0x00,0x00, //"7"
0x00,0x00,0x38,0x44,0x82,0x82,0x44,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"8"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x46,0x3A,0x02,0x82,0x44,0x38,0x00,0x00, //"9"
0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00, //":"
0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x20,0x00,0x00, //";"
0x00,0x00,0x00,0x00,0x06,0x18,0x60,0x80,0x60,0x18,0x06,0x00,0x00,0x00,0x00,0x00, //"<"
0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00, //"="
0x00,0x00,0x00,0x00,0xC0,0x30,0x0C,0x02,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00, //">"
0x00,0x38,0x44,0x82,0x82,0x02,0x04,0x08,0x10,0x10,0x10,0x00,0x10,0x10,0x00,0x00, //"?"
0x00,0x00,0x38,0x44,0x82,0x9A,0xAA,0xAA,0xAA,0xAA,0xAA,0x96,0x80,0x42,0x3C,0x00, //"@"
0x00,0x00,0x10,0x10,0x10,0x28,0x28,0x28,0x44,0x44,0x7C,0x44,0x44,0xEE,0x00,0x00, //"A"
0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x42,0x42,0x42,0x42,0x42,0xFC,0x00,0x00, //"B"
0x00,0x00,0x3C,0x44,0x82,0x80,0x80,0x80,0x80,0x80,0x82,0x82,0x44,0x38,0x00,0x00, //"C"
0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00, //"D"
0x00,0x00,0xFC,0x44,0x42,0x40,0x44,0x7C,0x44,0x40,0x40,0x42,0x44,0xFC,0x00,0x00, //"E"
0x00,0x00,0xFC,0x44,0x42,0x40,0x44,0x7C,0x44,0x40,0x40,0x40,0x40,0xF0,0x00,0x00, //"F"
0x00,0x00,0x34,0x4C,0x82,0x80,0x80,0x80,0x8E,0x84,0x84,0x84,0x4C,0x34,0x00,0x00, //"G"
0x00,0x00,0xEE,0x44,0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44,0x44,0xEE,0x00,0x00, //"H"
0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00, //"I"
0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0x88,0x70,0x00,0x00, //"J"
0x00,0x00,0xEE,0x44,0x48,0x48,0x50,0x60,0x50,0x48,0x48,0x44,0x44,0xEE,0x00,0x00, //"K"
0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0x44,0xFC,0x00,0x00, //"L"
0x00,0x00,0xC6,0x44,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x44,0x44,0x44,0xEE,0x00,0x00, //"M"
0x00,0x00,0xCE,0x44,0x64,0x64,0x64,0x54,0x54,0x4C,0x4C,0x4C,0x44,0xE4,0x00,0x00, //"N"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"O"
0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0x40,0x40,0x40,0xE0,0x00,0x00, //"P"
0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xBA,0x44,0x3C,0x02,0x00, //"Q"
0x00,0x00,0xF0,0x48,0x44,0x44,0x44,0x48,0x70,0x48,0x44,0x44,0x44,0xE6,0x00,0x00, //"R"
0x00,0x00,0x3C,0x44,0x82,0x80,0x40,0x30,0x0C,0x02,0x02,0x82,0x44,0x78,0x00,0x00, //"S"
0x00,0x00,0x7C,0x54,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00, //"T"
0x00,0x00,0xEE,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x38,0x00,0x00, //"U"
0x00,0x00,0xEE,0x44,0x44,0x44,0x44,0x28,0x28,0x28,0x28,0x10,0x10,0x10,0x00,0x00, //"V"
0x00,0x00,0xEE,0x44,0x54,0x54,0x54,0x54,0x54,0x54,0x28,0x28,0x28,0x28,0x00,0x00, //"W"
0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x28,0x28,0x44,0x44,0xEE,0x00,0x00, //"X"
0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00, //"Y"
0x00,0x00,0x7E,0x44,0x84,0x08,0x08,0x10,0x20,0x20,0x40,0x82,0x84,0xFC,0x00,0x00, //"Z"
0x00,0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1C,0x00, //"["
0x00,0x00,0xEE,0x44,0x54,0x54,0xFE,0x54,0x54,0x54,0x28,0x28,0x28,0x28,0x00,0x00, //"\"
0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x70,0x00, //"]"
0x00,0x30,0x48,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"^"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00, //"_"
0x00,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"`"
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x84,0x04,0x7C,0x84,0x84,0x8C,0x76,0x00,0x00, //"a"
0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x64,0x58,0x00,0x00, //"b"
0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x80,0x80,0x80,0x80,0x44,0x38,0x00,0x00, //"c"
0x00,0x00,0x0C,0x04,0x04,0x04,0x34,0x4C,0x84,0x84,0x84,0x84,0x4C,0x36,0x00,0x00, //"d"
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x84,0x84,0xFC,0x80,0x80,0x84,0x78,0x00,0x00, //"e"
0x00,0x00,0x18,0x24,0x20,0x20,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, //"f"
0x00,0x00,0x00,0x00,0x00,0x00,0x3A,0x44,0x44,0x78,0x80,0x7C,0x82,0x82,0x7C,0x00, //"g"
0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x44,0x44,0x44,0x44,0x44,0xEE,0x00,0x00, //"h"
0x00,0x00,0x10,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00, //"i"
0x00,0x00,0x10,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x90,0x60,0x00, //"j"
0x00,0x00,0xC0,0x40,0x40,0x40,0x5C,0x48,0x50,0x60,0x50,0x48,0x44,0xEE,0x00,0x00, //"k"
0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x11,0x10,0x10,0x10,0x10,0x10,0x39,0x00,0x00, //"l"
0x00,0x00,0x00,0x00,0x00,0x00,0xAC,0xD2,0x92,0x92,0x92,0x92,0x92,0xD6,0x00,0x00, //"m"
0x00,0x00,0x00,0x00,0x00,0x00,0x58,0xE4,0x44,0x44,0x44,0x44,0x44,0xEE,0x00,0x00, //"n"
0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00, //"o"
0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x64,0x42,0x42,0x42,0x64,0x58,0x40,0xE0,0x00, //"p"
0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x4C,0x84,0x84,0x84,0x4C,0x34,0x04,0x0E,0x00, //"q"
0x00,0x00,0x00,0x00,0x00,0x00,0x6C,0x30,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, //"r"
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x88,0x84,0x60,0x18,0x84,0x44,0x78,0x00,0x00, //"s"
0x00,0x00,0x00,0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x20,0x20,0x24,0x18,0x00,0x00, //"t"
0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00, //"u"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x00,0x00, //"v"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x54,0x54,0x28,0x28,0x28,0x00,0x00, //"w"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x28,0x10,0x10,0x28,0x44,0xEE,0x00,0x00, //"x"
0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0xA0,0xC0,0x00, //"y"
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x44,0x88,0x10,0x20,0x42,0x84,0xFC,0x00,0x00, //"z"
0x00,0x0C,0x10,0x10,0x10,0x10,0x10,0x60,0x10,0x10,0x10,0x10,0x10,0x10,0x0C,0x00, //"{"
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00, //"|"
0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x18,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,0x00, //"}"
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x72,0x8C,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //"~"
#endif
0x00,
};

//液晶IO初始化配置
void LCD_GPIO_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	      
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB ,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_1| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
      

}
//向SPI总线传输一个8位数据
void  SPI_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
			LCD_SDA_SET; //输出数据
    else LCD_SDA_CLR;
	   
    LCD_SCL_CLR;       
    LCD_SCL_SET;
    Data<<=1; 
	}
}

//向液晶屏写一个8位指令
void Lcd_WriteIndex(u8 Index)
{
   //SPI 写命令时序开始
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}

//向液晶屏写一个8位数据
void Lcd_WriteData(u8 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}
//向液晶屏写一个16位数据
void LCD_WriteData_16Bit(unsigned short Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//写入高8位数据
	 SPI_WriteData(Data); 			//写入低8位数据
   LCD_CS_SET; 
}

void Lcd_WriteReg(unsigned char Index,u8 Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}

void Lcd_Reset(void)
{
	LCD_RST_CLR;
	delayms(100);
	LCD_RST_SET;
	delayms(50);
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void Lcd_Init(void)
{	
	LCD_GPIO_Init();
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delayms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC8); 
	
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x7f);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x9f);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on	

}


/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+1);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+1);
	
	Lcd_WriteIndex(0x2c);

}

/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd_SetXY(u16 x,u16 y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 函数功能：读TFT某一点的颜色                          
 出口参数：color  点颜色值                                 
******************************************/
unsigned int Lcd_ReadPoint(u16 x,u16 y)
{
  unsigned int Data;
  Lcd_SetXY(x,y);
  Lcd_WriteData(Data);
  return Data;
}
/*************************************************
函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void Lcd_Clear(u16 Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}

//从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//通过该函数转换
//c:GBR格式的颜色值
//返回值：RGB格式的颜色值
u16 LCD_BGR2RGB(u16 c)
{
  u16  r,g,b,rgb;   
  b=(c>>0)&0x1f;
  g=(c>>5)&0x3f;
  r=(c>>11)&0x1f;	 
  rgb=(b<<11)+(g<<5)+(r<<0);		 
  return(rgb);
}




void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc) 
{//Bresenham算法 
    unsigned short  a,b; 
    int c; 
    a=0; 
    b=R; 
    c=3-2*R; 
    while (a<b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc);     //        7 
        Gui_DrawPoint(X-a,Y+b,fc);     //        6 
        Gui_DrawPoint(X+a,Y-b,fc);     //        2 
        Gui_DrawPoint(X-a,Y-b,fc);     //        3 
        Gui_DrawPoint(X+b,Y+a,fc);     //        8 
        Gui_DrawPoint(X-b,Y+a,fc);     //        5 
        Gui_DrawPoint(X+b,Y-a,fc);     //        1 
        Gui_DrawPoint(X-b,Y-a,fc);     //        4 

        if(c<0) c=c+4*a+6; 
        else 
        { 
            c=c+4*(a-b)+10; 
            b-=1; 
        } 
       a+=1; 
    } 
    if (a==b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y-b,fc); 
        Gui_DrawPoint(X-a,Y-b,fc); 
        Gui_DrawPoint(X+b,Y+a,fc); 
        Gui_DrawPoint(X-b,Y+a,fc); 
        Gui_DrawPoint(X+b,Y-a,fc); 
        Gui_DrawPoint(X-b,Y-a,fc); 
    } 
	
} 
//画线函数，使用Bresenham 画线算法
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color)   
{
int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2, 
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping	


	Lcd_SetXY(x0,y0);
	dx = x1-x0;//计算x距离
	dy = y1-y0;//计算y距离

	if (dx>=0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;  
	} 
	
	if (dy>=0)
	{
		y_inc = 1;
	} 
	else
	{
		y_inc = -1;
		dy    = -dy; 
	} 

	dx2 = dx << 1;
	dy2 = dy << 1;

	if (dx > dy)//x距离大于y距离，那么每个x轴上只有一个点，每个y轴上有若干个点
	{//且线的点数等于x距离，以x轴递增画点
		// initialize error term
		error = dy2 - dx; 

		// draw the line
		for (index=0; index <= dx; index++)//要画的点数不会超过x距离
		{
			//画点
			Gui_DrawPoint(x0,y0,Color);
			
			// test if error has overflowed
			if (error >= 0) //是否需要增加y坐标值
			{
				error-=dx2;

				// move to next line
				y0+=y_inc;//增加y坐标值
			} // end if error overflowed

			// adjust the error term
			error+=dy2;

			// move to the next pixel
			x0+=x_inc;//x坐标值每次画点后都递增1
		} // end for
	} // end if |slope| <= 1
	else//y轴大于x轴，则每个y轴上只有一个点，x轴若干个点
	{//以y轴为递增画点
		// initialize error term
		error = dx2 - dy; 

		// draw the line
		for (index=0; index <= dy; index++)
		{
			// set the pixel
			Gui_DrawPoint(x0,y0,Color);

			// test if error overflowed
			if (error >= 0)
			{
				error-=dy2;

				// move to next line
				x0+=x_inc;
			} // end if error overflowed

			// adjust the error term
			error+=dx2;

			// move to the next pixel
			y0+=y_inc;
		} // end for
	} // end else |slope| > 1
}





/**************************************************************************************
功能描述: 在屏幕显示一凸起的按钮框
输    入: u16 x1,y1,x2,y2 按钮框左上角和右下角坐标
输    出: 无
**************************************************************************************/
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, GRAY2);  //H
	Gui_DrawLine(x1+1,y1+1,x2,y1+1, GRAY1);  //H
	Gui_DrawLine(x1,  y1,  x1,y2, GRAY2);  //V
	Gui_DrawLine(x1+1,y1+1,x1+1,y2, GRAY1);  //V
	Gui_DrawLine(x1,  y2,  x2,y2, WHITE);  //H
	Gui_DrawLine(x2,  y1,  x2,y2, WHITE);  //V
}

/**************************************************************************************
功能描述: 在屏幕显示一凹下的按钮框
输    入: u16 x1,y1,x2,y2 按钮框左上角和右下角坐标
输    出: 无
**************************************************************************************/
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, WHITE); //H
	Gui_DrawLine(x1,  y1,  x1,y2, WHITE); //V
	
	Gui_DrawLine(x1+1,y2-1,x2,y2-1, GRAY1);  //H
	Gui_DrawLine(x1,  y2,  x2,y2, GRAY2);  //H
	Gui_DrawLine(x2-1,y1+1,x2-1,y2, GRAY1);  //V
  Gui_DrawLine(x2  ,y1  ,x2,y2, GRAY2); //V
}


void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) < 128) 
		{
			k=*s;
			if (k==13) 
			{
				x=x0;
				y+=16;
			}
			else 
			{
				if (k>32) k-=32; else k=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[k*16+i]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
						else 
						{
							if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
						}
					}
				x+=8;
			}
			s++;
		}
			
		else 
		{
		

			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    if(hz16[k].Msk[i*2]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
									else 
									{
										if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
									}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		} 
		
	}
}

void Gui_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k;

	while(*s) 
	{
		if( *s < 0x80 ) 
		{
			k=*s;
			if (k>32) k-=32; else k=0;

		    for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	
					Gui_DrawPoint(x+j,y+i,fc);
					else 
					{
						if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
					}
				}
			s++;x+=8;
		}
		else 
		{

			for (k=0;k<hz24_num;k++) 
			{
			  if ((hz24[k].Index[0]==*(s))&&(hz24[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<24;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3]&(0x80>>j))
								Gui_DrawPoint(x+j,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+2]&(0x80>>j))	
								Gui_DrawPoint(x+j+16,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+16,y+i,bc);
								}
							}
				    }
			  }
			}
			s+=2;x+=24;
		}
	}
}

//取模方式 水平扫描 从左到右 低位在前
void showimage(const unsigned char *p) //显示120*120 QQ图片
{
  	int i,j,k; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //清屏  
	
	for(k=0;k<1;k++)
	{
	   	for(j=0;j<1;j++)
		{	
			Lcd_SetRegion(40*j,40*k,40*j+119,40*k+119);		//坐标设置
		    for(i=0;i<120*120;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}
