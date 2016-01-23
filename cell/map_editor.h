#ifndef MAP_EDITOR_H_INCLUDED
#define MAP_EDITOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void gotoxy(int x , int y ) ;
void print_cell (int x,int y , int cell);
void map_editor (char name[]);

#endif // MAP_EDITOR_H_INCLUDED
