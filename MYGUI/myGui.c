#include"gt811.h"
#include"myGui.h"
#include"lcd.h"
#include"touch.h"
#include"stm32f10x_type.h"
#include<string.h>

#define KeyBoardDimX 4
#define KeyBoardDimY 4
#define KeyBoardNum (KeyBoardDimX * KeyBoardDimY)
#define ListItemNum 3

rec theKeyBoard[KeyBoardNum];
rec theList[ListItemNum];

u16 str2int(char *str)
{
	u16 res = 0;
	while(*str){
		res *= 10;
		res += *str - '0';
		++str;	 	
	}
	return res;
}
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


	short hight = y2 - y1;
	short width = x2 - x1;
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
 	short hight = y2 - y1;
	short width = x2 - x1;
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
 	short hight = y2 - y1;
	short width = x2 - x1;
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
			else if( k == 3){
			 	++k;
				strcpy(tmp, "<-");

			}
			else if( k == 7){
			 	++k;
				strcpy(tmp, "clr");

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
 	short hight = y2 - y1;
	short width = x2 - x1;
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

u8 pointInRec(u16 x, u16 y, rec *theRec)
{
 	return (x > theRec ->mx1) && (x < theRec ->mx2) && (y > theRec ->my1) && (y < theRec ->my2);
}
#include"delay.h"
#define KeyBoardBuf 20
u8 readKeyBoard(u16 *typedNum)
{
	u16 t = 0;
	u8 i = 0;
	u16 xcur, ycur;
	char tmp[KeyBoardBuf], *pbuf = tmp, *beg = tmp;
	while(1){
		//delay_ms(200);
		ctp_dev.scan();
		if(!ctp_dev.tpsta&0X1F){
			delay_ms(20);
			++t;
			if(t == 1000){
			 	LCD_BackLightSet(1);
				t = 0;
			}
			continue;
		}
		xcur = ctp_dev.x[0];
		ycur = ctp_dev.y[0];
		i = 0;
		while(!pointInRec(xcur, ycur, &theKeyBoard[i])){
		 	++i;
			if(i == KeyBoardNum){
		 		break;
			}
		}
		switch(i){
		 	case 0:
				*pbuf++ = '0' + 7;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 1:
				*pbuf++ = '0' + 8;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 2:
				*pbuf++ = '0' + 9;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 3:
				--pbuf;
				break;
			case 4:
				*pbuf++ = '0' + 4;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 5:
				*pbuf++ = '0' + 5;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 6:
				*pbuf++ = '0' + 6;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 7:
				pbuf = tmp;
				break;
			case 8:
				*pbuf++ = '0' + 1;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 9:
				*pbuf++ = '0' + 2;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 10:
				*pbuf++ = '0' + 3;
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = atoi(tmp);
					return 1;
				}
				break;
			case 11:
				break;
			case 12:
				*pbuf++ = '.';
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = str2int(tmp);
					return 1;
				}
				break;
			case 13:
				*pbuf++ = '0';
				if(pbuf - tmp == KeyBoardBuf - 1){
					*pbuf = 0;
				 	*typedNum = str2int(tmp);
					return 1;
				}
				break;
			case 14:
				return 0;
			case 15:
				*pbuf = 0;
				*typedNum = str2int(tmp);
				return 1;

		}

		ctp_dev.scan();
		while(ctp_dev.tpsta&0X1F){
			ctp_dev.scan();	
		}
	}		 	
	
}
