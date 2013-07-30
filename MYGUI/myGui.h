#ifndef _myGui_h
#define _myGui_h
#include"stm32f10x_type.h"
#define defaultButtonTitle "ButtonTitle"
#define defaultGapRatio 0.015
void drawButton(u16 x1, u16 y1, u16 x2, u16 y2, char *title);
void drawButtonArray(u16 xnum, u16 ynum, u16 x1, u16 y1, u16 x2, u16 y2, float gapRatio);
#endif