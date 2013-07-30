#include"myGui.h"
#include"lcd.h"
#include"stm32f10x_type.h"
#include<string.h>

#define KeyBoardDimX 4
#define KeyBoardDimY 4
#define KeyBoardNum (KeyBoardDimX * KeyBoardDimY)
#define ListItemNum 3

rec theKeyBoard[KeyBoardNum];
rec theList[ListItemNum];


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

void drawKeyBoard(u16 x1, u16 y1, u16 x2, u16 y2)
{

 	u8 i, j, k = 0;
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
	xgap = width * defaultGapRatio;
	ygap = hight * defaultGapRatio;	 

	xlen = (width - xgap) / KeyBoardDimX - xgap;
	ylen = (hight - ygap) / KeyBoardDimY - ygap;
	xcur = x1 + xgap;
	ycur = y1 - ylen;
		 
	for(i = 0; i < KeyBoardDimY; ++i){
		xcur = x1 + xgap;
		ycur += ylen + ygap;
		for(j = 0; j < KeyBoardDimX; ++j){
			theKeyBoard[k].mx1 = xcur;
			theKeyBoard[k].my1 = ycur;
			theKeyBoard[k].mx2 = xcur + xlen;
			theKeyBoard[k].my2 = ycur + ylen;

			if(k < 3){//itoa(tmp,k++);
				itoa(tmp, 7 + k++);
			}
			else if(k > 3 && k < 7){
			 	itoa(tmp, k++);
			}
			else if(k > 7 && k < 11){
			 	itoa(tmp, k++ - 7);
			}
			else if(k == 12){
				++k;
			 	strcpy(tmp, ".");
			}
			else if(k == 13)
			{
				++k;
			 	tmp[0] = '0';
				tmp[1] = 0;
			}
			else if(k == 14){
				++k;
			 	strcpy(tmp, "cancel");
			}
			else if(k == 15)
			{
				++k;
			 	strcpy(tmp, "ok");
			}
			else{
				++k;
			 	tmp[0] = '\0';
			}

		 	drawButton(xcur, ycur, xcur + xlen, ycur + ylen, tmp);

			xcur += xlen + xgap;
		}
	}	

}
void testKeyBoard(void)
{
	u8 i=0;
	while(i < KeyBoardNum){
	 	LCD_Fill(theKeyBoard[i].mx1, theKeyBoard[i].my1, theKeyBoard[i].mx2, theKeyBoard[i].my2, YELLOW); 
		++i;
	}
}
void drawList(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u8 NumX = 1, NumY = ListItemNum;
	u8 i, j, k = 0;
	char tmp[20] = "Mode 1: blabla~";
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
	xgap = width * defaultGapRatio;
	ygap = hight * defaultGapRatio;	 

	xlen = (width - xgap) / NumX - xgap;
	ylen = (hight - ygap) / NumY - ygap;
	xcur = x1 + xgap;
	ycur = y1 - ylen;
		 
	for(i = 0; i < NumY; ++i){
		xcur = x1 + xgap;
		ycur += ylen + ygap;
		for(j = 0; j < NumX; ++j){
			theList[k].mx1 = xcur;
			theList[k].my1 = ycur;
			theList[k].mx2 = xcur + xlen;
			theList[k].my2 = ycur + ylen;

			++k;
			tmp[5] = '0' + k;

		 	drawButton(xcur, ycur, xcur + xlen, ycur + ylen, tmp);

			xcur += xlen + xgap;
		}
	}	
}

