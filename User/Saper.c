#include "Saper.h"

#include "systickms.h"

int current_X = 5;
int current_Y = 5;

int mines_count = 10;

int game_state = GAME_ON;

int field[FIELD_SIZE][FIELD_SIZE] = {
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},		
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};

/*int field[FIELD_SIZE][FIELD_SIZE] = {
    {-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1}
};*/

int mines[FIELD_SIZE][FIELD_SIZE] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
};

int open_empty[FIELD_SIZE][FIELD_SIZE] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
};

/*int mines[FIELD_SIZE][FIELD_SIZE] = {
    {0,0,0,0,0},
    {0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,0}
};*/

int count_num_in_mines(int num)
{
    int result = 0;
    int i = 0;
    for (i = 0; i < FIELD_SIZE; i++)
    {
        int j = 0;
        for (j = 0; j < FIELD_SIZE; j++)
            if (mines[i][j] == num)
                result++;       
    }
		return result;
}


void move_left(void){
    int newX = current_X - 1;
    if (newX >= 0 && newX < FIELD_SIZE){
        clear_position(field[current_Y][current_X], current_X, current_Y);
        current_X = newX;
        draw_position(current_X, current_Y);
    }
}

void move_right(void){
    int newX = current_X + 1;
    if (newX >= 0 && newX < FIELD_SIZE){
        clear_position(field[current_Y][current_X], current_X, current_Y);
        current_X = newX;
        draw_position(current_X, current_Y);
    }
}

void move_up(void){
    int newY = current_Y - 1;
    if (newY >= 0 && newY < FIELD_SIZE){
        clear_position(field[current_Y][current_X], current_X, current_Y);
        current_Y = newY;
        draw_position(current_X, current_Y);
    }
}

void move_down(void){
    int newY = current_Y + 1;
    if (newY >= 0 && newY < FIELD_SIZE){
        clear_position(field[current_Y][current_X], current_X, current_Y);
        current_Y = newY;
        draw_position(current_X, current_Y);
    }
}


#define VALID(x,y) (x >=0 && x < FIELD_SIZE && y >=0 && y < FIELD_SIZE)

void process_open_cells(int x, int y){
		int total_mines = 0;
	
		int seek_x = x - 1, seek_y = y - 1;
	
		for (seek_x = x - 1; seek_x <= x + 1; seek_x++){
				for (seek_y = y - 1; seek_y <= y + 1; seek_y++)
						if (VALID(seek_x, seek_y))
								total_mines += (mines[seek_y][seek_x] == MARK_MINE||MARK_GOOD_FLAG == mines[seek_y][seek_x] ? 1 : 0);		
		}			
		
		field[y][x] = total_mines;
        int oe = open_empty[x][y];

        printf("%d %d %d \n", x, y, oe);
		if (oe == 0){
			open_empt(x,y,x,y);
		}
		else {
			draw_image(oe, y, x);
			open_empty[x][y]=10;
		}
			
		return;
		
		if (total_mines == 0){
				seek_x = x; seek_y = y - 1;
				if (VALID(seek_x, seek_y) && field[seek_y][seek_x] == 0)
					process_open_cells(seek_x, seek_y);
				
				seek_x = x; seek_y = y + 1;
				if (VALID(seek_x, seek_y) && field[seek_y][seek_x] == 0)
					process_open_cells(seek_x, seek_y);
				
				
				seek_x = x - 1; seek_y = y;
				if (VALID(seek_x, seek_y) && field[seek_y][seek_x] == 0)
					process_open_cells(seek_x, seek_y);
				
				
				seek_x = x + 1; seek_y = y ;
				if (VALID(seek_x, seek_y) && field[seek_y][seek_x] == 0)
						process_open_cells(seek_x, seek_y);
		}
}

void open_cell(void){
    if (field[current_Y][current_X] == CELL_FLAG) return;
    
    if (mines[current_Y][current_X] == MARK_MINE){
        loose();
        return;        
    }
    
		process_open_cells(current_X, current_Y);
    draw_position(current_X, current_Y);
}


void draw_mines(void) {
		int i;
		for (i = 0; i < FIELD_SIZE; i++){
				int j;
				for (j = 0; j < FIELD_SIZE; j++)
					if (mines[i][j] == MARK_MINE || mines[i][j] == MARK_GOOD_FLAG)
						draw_image(CELL_MINE, j, i);
		}
}

void win(void) {
	  fill_screen_with_color(LCD_COLOR_GREEN);
		draw_mines();
		draw_smile(CELL_GLASSES);
}

void loose(void) {
		clear_position(field[current_Y][current_X], current_X, current_Y);
		draw_mines();
		//draw_position(current_X, current_Y);
		game_state = 0;
		draw_smile(CELL_SAD);
		/*for (int i = 0; i<10;i++){
			for(int j = 0; j<10;j++)
				printf("%d ", mines[i][j]);
			printf("\n");
		}
		printf("\n");*/
}

void check_win(void){
    int good_flags_count = 0;
    int bad_flags_count = 0;
    int i = 0;
    for(i = 0; i < FIELD_SIZE; i++){
        int j = 0;
        for(j = 0; j < FIELD_SIZE; j++){
            if (mines[i][j] == MARK_GOOD_FLAG) good_flags_count++;
            if (mines[i][j] == MARK_BAD_FLAG) bad_flags_count++;
        }            
    }
    
    if (good_flags_count == mines_count && bad_flags_count == 0)
        win();
}

void flag_cell(void){
		if (field[current_Y][current_X] != CELL_COVERED && field[current_Y][current_X] != CELL_FLAG) 
				return;
	
    if (field[current_Y][current_X] == CELL_FLAG){
        field[current_Y][current_X] = CELL_COVERED;
        draw_image(CELL_COVERED, current_X, current_Y);
        if (mines[current_Y][current_X] == MARK_GOOD_FLAG) mines[current_Y][current_X] = MARK_MINE;
        else if (mines[current_Y][current_X] == MARK_BAD_FLAG) mines[current_Y][current_X] = MARK_NONE;        
    } 
		else if (field[current_Y][current_X] == CELL_COVERED){
        field[current_Y][current_X] = CELL_FLAG;
        draw_image(CELL_FLAG, current_X, current_Y);
        if (mines[current_Y][current_X] == MARK_MINE) mines[current_Y][current_X] = MARK_GOOD_FLAG;
        else if (mines[current_Y][current_X] == MARK_NONE) mines[current_Y][current_X] = MARK_BAD_FLAG;
    }
		draw_position(current_X, current_Y);
    check_win();
}

void draw_all(void){
    int x = 0;
    for (x = 0; x < FIELD_SIZE; x++){
        int y = 0;
        for (y = 0; y < FIELD_SIZE; y++){
            draw_image(field[x][y], x, y);
        }   
    }        
}

void reset_arrs(void) {
		int x = 0;
    for (x = 0; x < FIELD_SIZE; x++){
        int y = 0;
        for (y = 0; y < FIELD_SIZE; y++){
            field[x][y] = CELL_COVERED;
						mines[x][y] = MARK_NONE;
        }   
    }  
}

int random_number(int limit) {
    return  (rand()) % limit;
}

void spawn_mines(int count)
{
    mines_count = count;
    while (count_num_in_mines(MARK_MINE) != mines_count)
		{
			int r1 = random_number(FIELD_SIZE);
			int r2 =random_number(FIELD_SIZE);
			mines[r1][r2] = MARK_MINE;
		}
		
		for (int i = 0; i<10;i++){
			for(int j = 0; j<10;j++)
				printf("%d ", mines[i][j]);
			printf("\n");
		}
		printf("\n");		
}

void init_game(int count) {
		reset_arrs();
		spawn_mines(mines_count);
    draw_all();
    draw_position(current_X, current_Y);
		game_state = GAME_ON;
		counting_empty();
	  int i = 0, j = 0;
	
		for(i = 0; i < FIELD_SIZE; i++) {
			for (j = 0; j < FIELD_SIZE; j++)
				printf("%i ", mines[i][j]);
			printf("\n");
		}
		printf("\n");
}

void reload_game(void){
		draw_black();
        for(int i = 0; i < FIELD_SIZE; i++) {
			for (int j = 0; j < FIELD_SIZE; j++)
				open_empty[i][j] = 0;
		}
		init_game(mines_count);
}

void process_input(uint32_t input){ 
  if (game_state == GAME_END && input != RELAOD_GAME) 
    return; 
  
    switch (input) { 
        case MOVE_DOWN: { 
     move_down(); 
     break; 
    } 
        case MOVE_UP: { 
     move_up(); 
      break;  
    } 
        case MOVE_RIGHT: { 
     move_right(); 
      break; 
    } 
        case MOVE_LEFT: { 
     move_left(); 
     break;  
    } 
        case OPEN_CELL: {  
     open_cell(); 
      break; 
    } 
        case FLAG_CELL:  { 
     flag_cell(); 
      break;  
    } 
        case RELAOD_GAME: { 
     reload_game(); 
      break; 
    } 
    } 
}

void counting_empty(){
		for (int x=0; x<FIELD_SIZE; x++){
				for (int y=0; y<FIELD_SIZE;y++){
					int seek_x = x - 1, seek_y = y - 1;
					int total_mines = 0;
					if (mines[x][y] == 1) 
						open_empty[x][y]=-1;
					else {
						for (seek_x = x - 1; seek_x <= x + 1; seek_x++){
							for (seek_y = y - 1; seek_y <= y + 1; seek_y++)
								if (VALID(seek_x, seek_y))
									total_mines += (mines[seek_x][seek_y] == MARK_MINE||MARK_GOOD_FLAG == mines[seek_x][seek_y] ? 1 : 0);		
						}	
					
						open_empty[x][y] = total_mines;
					}
				}
		}
		
			for (int i = 0; i<10;i++){
				for(int j = 0; j<10;j++)
					printf("%d ", open_empty[i][j]);
				printf("\n");
			}
		printf("\n");
}

void open_empt(int x_prew, int y_prew, int x, int y){
    int cur_open = open_empty[x][y];
    printf("%d \n", cur_open);
    printf("%d %d \n", x, y);
	draw_image(cur_open, y, x);
	open_empty[x][y]=10;
	int seek_x = x - 1, seek_y = y-1;
	
	for (seek_x; seek_x <= x + 1; seek_x++){
	//printf("seek_x  ");
	//printf("%d %d %d %d %d %d\n", seek_x, y, x_prew, y_prew, x, y);
		
		if ((VALID(seek_x, y))&&(open_empty[seek_x][y]!=10)){
			//printf("%d \n", open_empty[seek_x][y]);
			if (open_empty[seek_x][y]==0){
				//printf("if==0");
				//printf("\n");
				open_empt(x, y, seek_x, y);
			}
		
			else 
				process_open_cells(seek_x, y);
		}
        //else printf("no x \n");
	}
    
    for (int i = 0; i<10;i++){
				for(int j = 0; j<10;j++)
					printf("%d ", open_empty[i][j]);
				printf("\n");
			}
		printf("\n");
	
	for (seek_y; seek_y <= y + 1; seek_y++){
		//printf("seek_y  ");
		//printf("%d %d %d %d %d %d\n", x, seek_y, x_prew, y_prew, x, y);

		if ((VALID(x, seek_y))&&(open_empty[x][seek_y]!=10)){
			//printf("%d \n", open_empty[seek_x][y]);
			if (open_empty[x][seek_y]==0){
				//printf("if==0");
				//printf("\n");
				open_empt(x, y, x, seek_y);
			}
		
			else 
				process_open_cells(x,seek_y);
		}
        //else printf("no y \n");
	}
}
