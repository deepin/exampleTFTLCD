#include"myGui.h"
#include"lcd.h"
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
	LCD_ShowString((x1 < x2 ? x1 : x2) + (width - titleWidth) / 2, (y1 > y2 ? y1 : y2) - hight / 2 - 8, 90, 16, 16, title);
	/*if(hight > 2 * defaultMarginY + 16){
	 	LCD_ShowString(460, 40, 200, 16, 16, "you missed it");	
	} */

}

