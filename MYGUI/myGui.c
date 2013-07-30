#include"myGui.h"
#include"lcd.h"
#include"stm32f10x_type.h"
#include<string.h>
/*typedef struct{
	u16 mx1;
	u16 my1;
	u16 mx2;
	u16 my2;
	char *mtitle;
	void (*mdraw) (u16 x1, u16 y1, u16 x2, u16 y2, char *title);
}Button;
*/
void itoa(char *str, u8 num)
{
	char *head = str;
	while(num){
	 	*str++ = '0' + num % 10;
		num /= 10;
	}
	*str = '\0';
	--str;
	while(head < str){
	 	*head ^= *str;
		*str ^= *head;
		*head ^= *str;
		++head;
		--str;
	}
}
void drawButton(u16 x1, u16 y1, u16 x2, u16 y2, char *title)
{
	u16 titleLen;
	u16 titleWidth;


	u16 hight = y2 - y1;
	u16 width = x2 - x1;
	if(hight < 0){
	 	hight = -hight;
	}
	if(width < 0){
	 	width = -width;
	}

 	if(!title){
		title = defaultButtonTitle;
	}
	titleLen = strlen(title);
	titleWidth = titleLen * 8;

	LCD_DrawRectangle(x1, y1, x2, y2);
	LCD_ShowString((x1 < x2 ? x1 : x2) + (width - titleWidth) / 2, (y1 > y2 ? y1 : y2) - hight / 2 - 8, titleWidth, 16, 16, title);
	/*if(hight > 2 * defaultMarginY + 16){
	 	LCD_ShowString(460, 40, 200, 16, 16, "you missed it");	
	} */

}
void drawButtonArray(u16 xnum, u16 ynum, u16 x1, u16 y1, u16 x2, u16 y2, float gapRatio)
{
	u8 i, j, k = 1;
	char tmp[10];
	u8 xgap, ygap;
	u16 xcur, ycur, xlen, ylen;
 	u16 hight = y2 - y1;
	u16 width = x2 - x1;
	if(hight < 0){
	 	hight = -hight;
	}
	if(width < 0){
	 	width = -width;
	}	
	xgap = width * ((gapRatio == 0) ? defaultGapRatio : gapRatio);
	ygap = hight * ((gapRatio == 0) ? defaultGapRatio : gapRatio);


	xlen = (width - xgap) / xnum - xgap;
	ylen = (hight - ygap) / ynum - ygap;
	xcur = x1 + xgap;
	ycur = y1 - ylen;
		 
	for(i = 0; i < ynum; ++i){
		xcur = x1 + xgap;
		ycur += ylen + ygap;
		for(j = 0; j < xnum; ++j){
			itoa(tmp,k++);
		 	drawButton(xcur, ycur, xcur + xlen, ycur + ylen, tmp);
			xcur += xlen + xgap;
		}
	}

}

