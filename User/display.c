/*display.c*/
#include "display.h"
#include "LCD_ILI9325.h"
#include "AsciiLib.h"
#include "PWMtimer.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"

typedef struct
{
	uint16_t kupcolor;
	uint16_t kdowncolor;
	uint16_t kcurcolor;
	uint16_t x1;
//	uint16_t x2;
	uint16_t y1;
//	uint16_t y2;
	uint8_t f_draw;
	char kname[4];
} st_keyview;

static st_keyview t_key[16];
static void putbuf_char(uint16_t* bufchar, uint8_t ASCI,uint16_t bkcolor, uint16_t charcolor);
static void bufLCDprint(uint8_t sizestr, uint16_t* bufstr, char* str, uint16_t bkcolor, uint16_t charcolor);
static void LCDlinestr(char* str, int16_t y,uint16_t bkcolor, uint16_t charcolor);
static uint8_t bufPrintstr[RX_BUFSZ];
static int16_t lenbufPrstr=0;
static uint8_t slowstr=0;

void Init_display(void)
{
	init_lcd_ili9325();
	lcd_fill_color(0,0,240,320,LCD_COLOR_FUCHSIA);
	uint16_t x,y;
	for(int i=0;i<16;i++) {
		x=i%4;
		y=i/4;
		t_key[i].kupcolor=LCD_COLOR_OLIVE; //цвет не нажатой кнопки
		t_key[i].kdowncolor=LCD_COLOR_AQUA; //цвет нажатой кнопки
		t_key[i].x1=20+50*x;
		t_key[i].y1=20+50*y;
		//t_key[i].x2=44+60*x;
		//t_key[i].y2=44+60*y;
		t_key[i].f_draw = 1;
		t_key[i].kcurcolor=t_key[i].kupcolor;
		sprintf(t_key[i].kname,"K%d",i+1);
	}
	lenbufPrstr=0;
	for(int i=0;i<RX_BUFSZ;i++)
		bufPrintstr[i]=0;
}

void presskey(uint16_t numkey)
{
	if(numkey<16)
	{
		t_key[numkey].kcurcolor=t_key[numkey].kdowncolor;
		t_key[numkey].f_draw = 1;
	}
}

void upkey(uint16_t numkey)
{
	if(numkey<16)
	{
		t_key[numkey].kcurcolor=t_key[numkey].kupcolor;
		t_key[numkey].f_draw = 1;
	}
}

void draw_handler(void)
{
	uint16_t bufstr[16*8*3];//3 символа 16x8
	for(int i=0;i<16;i++) {
		if(t_key[i].f_draw){
			t_key[i].f_draw=0;
			int len=strlen(t_key[i].kname);
			bufLCDprint(len,bufstr,t_key[i].kname,t_key[i].kcurcolor, LCD_COLOR_BLUE);
			lcd_fill_region(t_key[i].x1, t_key[i].y1, t_key[i].x1+8*len, t_key[i].y1+16, bufstr);
		}
	}
	if(lenbufPrstr > -1)
	{
		if(slowstr==0)
		{
			slowstr=5;
			char buf[30]="RX>";
			int i;
			for( i=0; i<lenbufPrstr; i++){
				if(i<27){
					if( (bufPrintstr[i] >= 0x20) && (bufPrintstr[i] <=0x7E))
						buf[i+3]=bufPrintstr[i];
					else
						buf[i+3]=0x20;//непечатаемый символ заменяем пробелом
				}
				if( (i+1) < RX_BUFSZ)
					bufPrintstr[i]=bufPrintstr[i+1];//двигаем строку вправо
			}
			bufPrintstr[i]=0;
			buf[i+3]=0;
			lenbufPrstr--;
			LCDlinestr(buf,290,LCD_COLOR_FUCHSIA,LCD_COLOR_AQUA);
		}
		else
			slowstr--;
		
	}
	
}

void putbuf_char(uint16_t* bufchar, uint8_t ASCI,uint16_t bkcolor, uint16_t charcolor)//16x8=128
{
	uint16_t i, j;
    uint8_t buffer[16], tmp_char;
    GetASCIICode(buffer,ASCI);  /* get font data */
    for( i=0; i<16; i++ )
    {
        tmp_char = buffer[i];
        for( j=0; j<8; j++ )
        {
            if( ((tmp_char >> (7 - j)) & 0x01) == 0x01 )
				bufchar[i*8+j]=charcolor;
			else
				bufchar[i*8+j]=bkcolor;
        }
    }
    
}

/*

void bufLCDprint(uint8_t sizestr, uint16_t* bufstr, char* str, uint16_t bkcolor, uint16_t charcolor)
{
	for(int nchr=0 ; nchr<sizestr; nchr++){
		uint16_t bufchar[16*8];
		putbuf_char(bufchar, str[nchr],bkcolor,charcolor);
		for(int irow=0;irow<16;irow++){
			for(int icol=0;icol<8;icol++){
				bufstr[(nchr*8)+irow*(sizestr*8)+icol]=bufchar[irow*8+icol];
			}
		}
	}
}



void LCDlinestr(char* str, int16_t y,uint16_t bkcolor, uint16_t charcolor)//240/8=30 символов в строке
{
	const uint16_t sizestr=30;
	uint16_t bstr[16*8*sizestr];//3840 точек
	for(int i=0;i<16*8*sizestr;i++)
		bstr[i]=bkcolor;
	for(int nchr=0 ; nchr<sizestr; nchr++){
		if( (str[nchr] >= 0x20 ) && (str[nchr] <=0x7E) ){
			uint16_t bufchar[16*8];
			putbuf_char(bufchar, str[nchr],bkcolor,charcolor);
			for(int irow=0;irow<16;irow++){
				for(int icol=0;icol<8;icol++){
					bstr[(nchr*8)+irow*(sizestr*8)+icol]=bufchar[irow*8+icol];
				}
			}
		}
		else
			break;
	}
	lcd_fill_region(0, y, 8*sizestr, y+16, bstr);
}



*/