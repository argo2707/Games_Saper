#include "ArrayImages.h"


uint16_t get_color(int color_code){
    uint16_t color = LCD_COLOR_AQUA;
    switch(color_code) {
        case 1:  { color = LCD_COLOR_LIGHT_GRAY; break; }
        case 2:  { color = LCD_COLOR_DARK_GRAY; break; }
				case 3:  { color = LCD_COLOR_BLUE; break; }
				case 4:  { color = LCD_COLOR_LIGHTGREEN; break; }
        case 5:  { color = LCD_COLOR_RED; break; }
				case 6:  { color = LCD_COLOR_PURPLE; break; }
				case 7:  { color = LCD_COLOR_BLACK; break; }
				case 8:  { color = LCD_COLOR_BROWN; break; }
				case 9:  { color = LCD_COLOR_AQUA; break; }
				case 20:  { color = LCD_COLOR_VERY_DARK_GRAY; break; }
    }
    return color;
}

uint16_t get_image_color_xy(int image_code, int x, int y){
    uint16_t color = LCD_COLOR_AQUA;
    switch (image_code){
        case CELL_COVERED : { color = get_color(COVERED[y][x]); break; }
        case CELL_UNCOVERED : { color = get_color(UNCOVERED[y][x]); break; }
        case CELL_FLAG : { color = get_color(FLAG[y][x]); break; }
		case CELL_MINE : { color = get_color(MINE[y][x]); break; }
		case CELL_GLASSES : { color = get_color(GLASSES[y][x]); break; }
		case CELL_SAD : { color = get_color(SAD[y][x]); break; }
		case CELL_ONE : { color = get_color(ONE[y][x]); break; }
		case CELL_TWO : { color = get_color(TWO[y][x]); break; }
		case CELL_THREE : { color = get_color(THREE[y][x]); break; }
		case CELL_FOUR : { color = get_color(FOUR[y][x]); break; }
		case CELL_FIVE : { color = get_color(FIVE[y][x]); break; }
		case CELL_SIX :  { color = get_color(SIX[y][x]); break; }
		case CELL_SEVEN : { color = get_color(SEVEN[y][x]); break; }
		case CELL_EIGTH : { color = get_color(EIGHT[y][x]); break; }
    }
    
    return color;
}

void draw_position(int x, int  y){
    int x_begin = x * CELL_SIZE_PIXEL, x_end = (x+1) * CELL_SIZE_PIXEL;
    int y_begin = y * CELL_SIZE_PIXEL, y_end = (y+1) * CELL_SIZE_PIXEL;
    for(; x_begin < x_end; x_begin++){
        lcd_set_pixel(x_begin, y_begin, LCD_COLOR_RED);
				lcd_set_pixel(x_begin, y_begin+1, LCD_COLOR_RED);
        lcd_set_pixel(x_begin, y_begin + CELL_SIZE_PIXEL, LCD_COLOR_RED);
				lcd_set_pixel(x_begin, y_begin + CELL_SIZE_PIXEL-1, LCD_COLOR_RED);
    }
    x_begin = x * CELL_SIZE_PIXEL;
    for(; y_begin < y_end; y_begin++){
        lcd_set_pixel(x_begin, y_begin, LCD_COLOR_RED);
				lcd_set_pixel(x_begin+1, y_begin, LCD_COLOR_RED);
        lcd_set_pixel(x_begin+CELL_SIZE_PIXEL, y_begin, LCD_COLOR_RED);
				lcd_set_pixel(x_begin+CELL_SIZE_PIXEL-1, y_begin, LCD_COLOR_RED);
    }
}

void clear_position(int image_code, int x, int y) {
    int x_begin = x * CELL_SIZE_PIXEL,  x_end = (x+1) * CELL_SIZE_PIXEL;
    int y_begin = y * CELL_SIZE_PIXEL,  y_end = (y+1) * CELL_SIZE_PIXEL;
    int img_x = 0, img_y = 0, img_x2 = 0, img_y2 = 0;
    for(; x_begin < x_end; x_begin++){
        lcd_set_pixel(x_begin, y_begin, get_image_color_xy(image_code, img_x, img_y));
				lcd_set_pixel(x_begin, y_begin+1, get_image_color_xy(image_code, img_x2, img_y2+1));
        lcd_set_pixel(x_begin, y_begin + CELL_SIZE_PIXEL, get_image_color_xy(image_code, img_x++, img_y + CELL_SIZE_PIXEL-1));
				lcd_set_pixel(x_begin, y_begin + CELL_SIZE_PIXEL-1, get_image_color_xy(image_code, img_x2++, img_y2 + CELL_SIZE_PIXEL-1));
    }
    x_begin = x * CELL_SIZE_PIXEL;
    img_x = 0; img_y = 0; img_x2 = 0; img_y2 = 0; 
    for(; y_begin < y_end; y_begin++){
        lcd_set_pixel(x_begin, y_begin, get_image_color_xy(image_code, img_x, img_y));
				lcd_set_pixel(x_begin+1, y_begin, get_image_color_xy(image_code, img_x2+1, img_y2));
        lcd_set_pixel(x_begin+CELL_SIZE_PIXEL, y_begin, get_image_color_xy(image_code, img_x+CELL_SIZE_PIXEL-1, img_y++));
        lcd_set_pixel(x_begin+CELL_SIZE_PIXEL-1, y_begin, get_image_color_xy(image_code, img_x2+CELL_SIZE_PIXEL-1, img_y2++));
    }    
}

void draw_image(int image_code, int x, int y) {
    int x_end = (x+1) * CELL_SIZE_PIXEL, y_end = (y+1) * CELL_SIZE_PIXEL;
    int x_begin = x * CELL_SIZE_PIXEL;
    int img_x = 0;
    for(; x_begin < x_end; x_begin++){
        int img_y = 0, y_begin = y * CELL_SIZE_PIXEL;
        for (; y_begin < y_end; y_begin++)  lcd_set_pixel(x_begin, y_begin, get_image_color_xy(image_code, img_x, img_y++));
        img_x++;
    }        
}

void draw_smile(int image_code) {
		int x=3;
		int y=9;
    int x_end = (x+1)*30, y_end = (y+1)*30;
    int x_begin = x*30;
    int img_x = 0;
    for(; x_begin < x_end; x_begin++){
        int img_y = 0, y_begin = y*30;
        for (; y_begin < y_end; y_begin++)  lcd_set_pixel(x_begin, y_begin, get_image_color_xy(image_code, img_x, img_y++));
        img_x++;
    }        
}

void draw_black() {
		int x=0;
		int y=0;
    int x_end = (x+1)*300, y_end = (y+1)*300;
    int x_begin = x*350;
    int img_x = 0;
    for(; x_begin < x_end; x_begin++){
        int img_y = 0, y_begin = y*350;
        for (; y_begin < y_end; y_begin++)  lcd_set_pixel(x_begin, y_begin, get_color(7));
        img_x++;
    }        
}

void fill_screen_with_color(uint16_t color){
    int x = 0;
    for(; x < DISPLAY_WIDTH; x++){   
        int y = 0;
        for (; y < DISPLAY_HEIGHT; y++)
            lcd_set_pixel(x, y, color);        
    }
}
