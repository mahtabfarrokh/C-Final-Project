#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "map_editor.h"
void print_menu (int width)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7| 0<<4);
    gotoxy(0 ,0) ;
    printf("[1] Load\n") ;
    printf("[2] New single player game\n") ;
    printf("[3] New Multiplayer game\n") ;
    printf("[4] Exit\n") ;
}
void print_menu2(int width)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7| 0<<4);
    gotoxy(0 ,width*3 +2) ;
    printf("[1] Move\n") ;
    printf("[2] Split a cell\n") ;
    printf("[3] Boost energy\n") ;
    printf("[4] Save\n") ;
    printf("[5] Exit\n") ;
}
void print_menu_move (int width)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7| 0<<4);
    gotoxy(0 ,width*3 +2) ;
    printf("[1] North\n");
    printf("[2] South\n");
    printf("[3] Northeast\n");
    printf("[4] Northwest\n");
    printf("[5] Southeast\n");
    printf("[6] Southwest\n") ;
}
void print_multi (int width)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7| 0<<4);
    gotoxy(0 ,width*3 +2) ;
    printf("[1] Move\n");
    printf("[2] Boost energy\n");
    printf("[3] Exit\n");
}
