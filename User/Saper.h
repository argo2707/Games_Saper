#ifndef SAPER_H
#define SAPER_H

#include <stdio.h>
#include <cstdlib>

#include "LCD_ILI9325.h"
#include "main.h"
#include "Constants.h"
#include "ArrayImages.h"

#define GAME_END 0
#define GAME_ON 1


int  count_num_in_mines(int);
int  random_number(int);
void move_left(void);
void move_right(void);
void move_up(void);
void move_down(void);
void process_open_cells(int, int);
void open_cell(void);
void draw_mines(void);
void win(void);
void loose(void);
void check_win(void);
void flag_cell(void);
void draw_all(void);
void reset_arrs(void);
void spawn_mines(int);
void init_game(int);
void reload_game(void);
void process_input(uint32_t); //
void counting_empty();
void open_empt(int, int, int, int);

#endif
