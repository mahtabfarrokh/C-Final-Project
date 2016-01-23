#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <multiplayer.h>
void gotoxy(int x , int y );
void make_rand_ij (int width , int height ,int number,struct cell cellule[height][width] );
void print_cell (int x,int y , int cell);
void print_map (int height , int width , struct cell cellule[height][width] );
void print_menu (int width);
void print_menu2(int width);
void print_score (int width  , int height , struct cell cellule[height][width] );
void print_menu_move (int width);
void print_multi (int width);
void save_map (int width , int height , struct cell cellule[height][width]);
void save_cell (int width , int height , struct cell cellule[height][width]);
void load (int width , int height  , struct cell cellule[height][width] );
int empty_cell (int width , int height , struct cell cellule [height][width] , int i , int j , int rand);
void single_player ( int width  , int height , struct cell cellule [height][width]  );
void map_editor (void);
void multi_player(int height , int width , struct cell cellule[height][width] );

#endif // HEAD_H_INCLUDED
