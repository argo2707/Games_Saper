#ifndef ARRAY_IMAGES_H
#define ARRAY_IMAGES_H

#include "LCD_ILI9325.h"
#include "Constants.h"
#include "main.h"
#include "Tiles.h"

#define MARK_GOOD_FLAG 3
#define MARK_BAD_FLAG 2
#define MARK_MINE 1
#define MARK_NONE 0
#define LCD_COLOR_ORANGE ((uint32_t)0xFFFFA500)
#define LCD_COLOR_LIGHTGREEN ((uint32_t)0xFF80FF80)



#define CELL_FLAG 9
#define CELL_COVERED -1
#define CELL_MINE 10
#define CELL_UNCOVERED 0
#define CELL_ONE 1
#define CELL_TWO 2
#define CELL_THREE 3
#define CELL_FOUR 4
#define CELL_FIVE 5
#define CELL_SIX 6
#define CELL_SEVEN 7
#define CELL_EIGTH 8
#define CELL_GLASSES 11
#define CELL_SAD 12

uint16_t get_color(int);
uint16_t get_image_color_xy(int, int, int);
void draw_position(int, int);
void clear_position(int, int, int);
void draw_image(int, int, int);
void fill_screen_with_color(uint16_t);
void draw_smile(int);
void draw_black();

#endif
