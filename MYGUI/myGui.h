#ifndef _myGui_h
#define _myGui_h
#include"stm32f10x_type.h"
#define defaultButtonTitle "ButtonTitle"
#define defaultGapRatio 0.015

typedef struct
{
	u16 mx1;
	u16 my1;
	u16 mx2;
	u16 my2;
}rec;

void drawButton(u16 x1, u16 y1, u16 x2, u16 y2, char *title);
void drawButtonArray(u16 xnum, u16 ynum, u16 x1, u16 y1, u16 x2, u16 y2, float gapRatio);
void drawKeyBoard(u16 x1, u16 y1, u16 x2, u16 y2);
void drawList(u16 x1, u16 y1, u16 x2, u16 y2);
void testKeyBoard(void);
u8 readKeyBoard(u16 *);
#endif