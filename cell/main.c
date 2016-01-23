#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "map_editor.h"
#include "menu.h"
//#include <multiplayer.h>
int score ;
int account =0;
int a,  b ;
char name[100] ="map.bin" ;
struct cell_move_data
{
    int cell_energy;
    int move_direction;
};
struct cell_position
{
    int x;
    int y;
};
struct cell
{

    int energy ;
    char type ;
    int mojood ;
    int energy_mojood ;
};
void make_rand_ij (int width , int height ,int number,struct cell cellule[height][width] )
{
    int m=1  ;
    int i ,  j , s ;
    double x ;
    for(s=0 ; s<number ; s++)
    {
        m= rand() ;
        x=m ;
        x=x/(RAND_MAX) ;
        x=x*height ;
        x=x*width;
        m=x ;
        j = m / height ;
        i = m- j *height ;
        if(cellule[j][i].type != '3' && cellule [j][i].mojood ==0)
        {
            cellule[j][i].mojood = 1 ;
            cellule [j][i].energy_mojood=0 ;
        }
        else
            make_rand_ij(width , height , 1 , cellule) ;
    }
}
void print_map (int height , int width , struct cell cellule[height][width] )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7|0<<4);
    gotoxy(0,0) ;
    int i , j ;
    system("cls") ;
    for(i=1  ; i<= width ; i++)
    {
        gotoxy (6*i -3, 0 );
        printf("%d" , i-1) ;
    }
    for(i=height ; i>0 ; i--)
    {
        gotoxy(0 , 3*i-1 ) ;
        printf("%d" , height-i) ;
    }
    for(i=height-1 ; i>=0; i--)
    {
        for(j=0 ; j<width; j++)
        {
            switch (cellule[i][j].type)
            {
            case '1' :
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1|3<<4);
                    break ;
            case '2' :
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1| 2<<4);
                    break ;
            case '3' :
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1| 4<<4);
                    break ;
            case '4' :
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1| 8<<4);
                    break ;


            }
            if(j%2!=0)
            {
                if(cellule[i][j].mojood==1)
                    print_cell(6*j,3*(height -i-1)+1 , 1) ;
                else
                    print_cell(6*j,3*(height -i-1) +1, 0) ;
            }
            else
            {
                if(cellule[i][j].mojood==1)
                    print_cell ( 6*j, 3*(height -i-1) ,1 ) ;
                else
                    print_cell ( 6*j, 3*(height -i -1) , 0 ) ;
            }

        }
        printf("\n") ;
    }
}

void print_score (int width  , int height , struct cell cellule[height][width] )
{
    int i  , j ;
    score =0 ;
    for(i=0 ; i < height ; i ++)
    {
        for(j=0 ; j < width ; j++)
            score += cellule[i][j].energy_mojood ;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7| 0<<4);
    gotoxy(35 , width*3 +7 ) ;
    printf("Your score : %d",score) ;
}
void save_map (int width , int height , struct cell cellule[height][width])
{
     FILE *fnew ;
     fnew = fopen ("savemap.bin","w+b") ;
     if(fnew==NULL)
     {
         printf("can not save ") ;
         return -1 ;
     }
     int i , j ;
     fwrite(&width , sizeof(int) , 1 , fnew) ;
     fwrite(&height , sizeof(int) , 1 , fnew) ;
     for(i = 0 ; i <height ; i++)
     {
         for(j=width-1 ; j>=0 ; j--)
         {
            fwrite(&cellule[i][j].energy , sizeof(int) , 1 , fnew) ;
            fwrite(&cellule[i][j].type , sizeof(char) , 1 , fnew) ;
         }
     }
     fclose(fnew) ;
}
void save_cell (int width , int height , struct cell cellule[height][width])
{
     FILE * fcell ;
     fcell = fopen ("savecell.bin" , "w+b") ;
     if(fcell==NULL)
     {
         printf("can not save cell") ;
         return -1 ;
     }
     int i  , j , counter=0 ;
     for(i =0 ; i< height ; i++)
     {
        for(j=0 ; j< width ; j++)
        {
            if(cellule[i][j].mojood==1)
            {
                counter++ ;
            }
        }
     }
     fwrite(&counter , sizeof(int) , 1 , fcell) ;
     for(i =0 ; i< height ; i++)
     {
        for(j=0 ; j< width ; j++)
        {
            if(cellule[i][j].mojood==1)
            {
                fwrite(&i , sizeof(int ) , 1 , fcell) ;
                fwrite(&j , sizeof(int ) , 1 , fcell) ;
                fwrite(&cellule[i][j].energy_mojood , sizeof(int ) , 1 , fcell) ;
            }
        }
     }
     fclose(fcell) ;
}
void load (int width , int height  , struct cell cellule[height][width] )
{
        int i , j ;
        FILE *load ;
        load = fopen ("savemap.bin","rb") ;
        if(load==NULL)
        {
            printf("can not open file") ;
            return -1 ;
        }
        fread(&height , sizeof(int) , 1  , load) ;
        fread(&width , sizeof(int) , 1  , load) ;
        for(i=0; i<height ; i++)
        {
            for(j=width-1; j>=0 ; j--)
            {
                fread (&cellule[i][j].energy , sizeof(int), 1 , load) ;
                fread (&cellule[i][j].type , sizeof(char), 1 , load) ;
                cellule[i][j].mojood = 0 ;
                cellule[i][j].energy_mojood = 0  ;

            }
        }
        fclose(load) ;
        FILE *cell ;
        cell = fopen("savecell.bin" , "rb");
        if(cell==NULL)
        {
            printf("can not open file") ;
            return -1 ;
        }
        int n  , x , y ;
        fread(&n , sizeof(int) , 1 , cell) ;
        for(i=0 ; i< n ; i++)
        {
            fread(&x , sizeof(int) , 1 , cell) ;
            fread(&y , sizeof(int) , 1 , cell)  ;
            fread(&cellule[x][y].energy_mojood , sizeof(int) , 1 , cell)  ;
            cellule[x][y].mojood = 1 ;
        }
        fclose(cell) ;

}
int empty_cell (int width , int height , struct cell cellule [height][width] , int i , int j , int rand)
{
    int number=0 ;
    if(j < (height-1) && j>0 && i>0 && i<(width-1) && i %2==0  )
    {
        if(cellule[j+1][i].type!='3' && cellule[j+1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j+1 ;
            }
        }
        if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j-1 ;
            }
        }
        if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j;
            }
        }
        if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j ;
            }
        }
        if(cellule[j+1][i+1].type!='3' && cellule[j+1][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j+1 ;
            }
        }
        if(cellule[j+1][i-1].type!='3' && cellule[j+1][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j+1 ;
            }
        }
    }
    if(j < (height-1) && j>0 && i>0 && i<(width-1) && i %2!=0  )
    {
        if(cellule[j+1][i].type!='3' && cellule[j+1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j+1 ;
            }
        }
        if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j-1 ;
            }
        }
        if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j ;
            }
        }
        if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j;
            }
        }
        if(cellule[j-1][i+1].type!='3' && cellule[j-1][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j-1 ;
            }
        }
        if(cellule[j-1][i-1].type!='3' && cellule[j-1][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j-1 ;
            }
        }
    }
    if(i==0 && j==0 )
    {
        if(cellule[j+1][i].type!='3' && cellule[j+1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = 1 ;
            }
        }
        if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j ;
            }
        }
        if(cellule[j+1][i+1].type!='3' && cellule[j+1][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j+1 ;
            }
        }
    }
    if(i==(width-1) && j==(height-1))
    {
        if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j-1 ;
            }
        }
        if(cellule[j-1][i-1].type!='3' && cellule[j-1][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j-1 ;
            }
        }
        if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j;
            }
        }
    }
    if(i==(width-1) && j==0)
    {
        if(cellule[j+1][i].type!='3' && cellule[j+1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j+1 ;
            }
        }
        if(cellule[j+1][i-1].type!='3' && cellule[j+1][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j+1 ;
            }
        }
        if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j ;
            }
        }
    }
    if(i==0 && j==(height-1))
    {
        if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j-1 ;
            }
        }
        if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j;
            }
        }
        if(cellule[j-1][i+1].type!='3' && cellule[j-1][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j-1 ;
            }
        }
    }
    if(i==0 && j>0 && j <(height-1))
    {
        if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j-1 ;
            }
        }
        if(cellule[j+1][i].type!='3' && cellule[j+1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j+1 ;
            }
        }
        if(cellule[j+1][i+1].type!='3' && cellule[j+1][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j+1 ;
            }
        }
        if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i+1 ;
                b = j;
            }
        }
    }
    if(i==(width-1) &&j>0 && j <(height-1)&&width%2==0)
    {
        if(cellule[j+1][i].type!='3' && cellule[j+1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j+1 ;
            }
        }
        if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j-1 ;
            }
        }
        if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j ;
            }
        }
        if(cellule[j-1][i-1].type!='3' && cellule[j-1][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j-1 ;
            }
        }
    }
    if(i==(width-1) &&j>0 && j <(height-1)&& width%2!=0)
    {
        if(cellule[j+1][i].type!='3' && cellule[j+1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j+1 ;
            }
        }
        if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i ;
                b = j-1 ;
            }
        }
        if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i -1 ;
                b = j ;
            }
        }
        if(cellule[j+1][i-1].type!='3' && cellule[j+1][i-1].mojood ==0)
        {
            number++ ;
            if(number == rand)
            {
                a= i-1 ;
                b = j+1 ;
            }
        }
    }
    if(j==(height-1) &&  i>0 && i<(width-1))
    {
        if(i%2==0)
        {
            if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i ;
                    b = j+1 ;
                }
            }
            if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i ;
                    b = j-1 ;
                }
            }
            if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i-1 ;
                    b = j ;
                }
            }
        }
        else
        {
            if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i+1 ;
                    b = j ;
                }
            }
            if(cellule[j-1][i].type!='3' && cellule[j-1][i].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i ;
                    b = j-1 ;
                }
            }
            if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i-1 ;
                    b = j;
                }
            }
            if(cellule[j-1][i-1].type!='3' && cellule[j-1][i-1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i-1 ;
                    b = j-1 ;
                }
            }
            if(cellule[j-1][i+1].type!='3' && cellule[j-1][i+1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i+1 ;
                    b = j-1 ;
                }
            }
        }
    }
    if(j==0 &&  i>0 && i<(width-1))
    {
        if(i%2!=0)
        {
            if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i+1 ;
                    b = j ;
                }
            }
            if(cellule[1][i].type!='3' && cellule[1][i].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i ;
                    b = j+1 ;
                }
            }
            if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i-1 ;
                    b = j;
                }
            }
        }
        else
        {
            if(cellule[j][i+1].type!='3' && cellule[j][i+1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i+1;
                    b = j ;
                }
            }
            if(cellule[1][i].type!='3' && cellule[1][i].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i ;
                    b = j+1 ;
                }
            }
            if(cellule[j][i-1].type!='3' && cellule[j][i-1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i-1 ;
                    b = j;
                }
            }
            if(cellule[1][i-1].type!='3' && cellule[1][i-1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i-1 ;
                    b = j+1 ;
                }
            }
            if(cellule[1][i+1].type!='3' && cellule[1][i+1].mojood ==0)
            {
                number++ ;
                if(number == rand)
                {
                    a= i+1 ;
                    b = j+1 ;
                }
            }
        }
    }
    return number ;
}
void single_player ( int width  , int height , struct cell cellule [height][width]  )
{
    int option , i , x ,y , move , h ;
    gotoxy(0,0) ;
    for(i=0 ; i< 20  ; i++)
        printf("                                                                                      \n") ;
    gotoxy(0,0)  ;
    system("cls") ;
    print_map(height , width , cellule) ;
    print_score(width , height , cellule) ;
    print_menu2(width) ;
    printf("choose one option  :") ;
    scanf("%d",&option) ;
    while(option!=5)
    {
        if(option==1)
        {
            gotoxy(0,0) ;
            for(i=0 ; i< 25 ; i++)
                printf("                                                                                    \n") ;
            gotoxy(0,0)  ;
            print_map(height , width , cellule) ;
            print_score(width , height , cellule) ;
            printf("\nEnter your coordinate (i&j) : ") ;
            scanf("%d %d",&x, &y) ;
            gotoxy(0,0) ;
            for(i=0 ; i< 25 ; i++)
                printf("                                                                            \n") ;
            gotoxy(0,0)  ;
            print_map(height , width , cellule) ;
            print_score(width , height , cellule) ;
            print_menu_move(width) ;
            printf("\nEnter your move : ");
            scanf("%d",&move) ;
            switch(move)
            {
            case 1 :
                if(y < height-1  && cellule[y+1][x].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y+1][x].mojood =1 ;
                    cellule[y+1][x].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                break ;
            case 2 :
                if(y>0 && cellule[y-1][x].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y-1][x].mojood =1 ;
                    cellule[y-1][x].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                break ;
            case 3 :
                if(x%2==0 &&y<height-1 && x<width-1 && cellule[y+1][x+1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y+1][x+1].mojood =1 ;
                    cellule[y+1][x+1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                if(x%2!=0 &&y<height && x<width-1 && cellule[y][x+1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y][x+1].mojood =1 ;
                    cellule[y][x+1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                break ;
            case 4:
                if(x%2==0 && y<height-1 && x>0 && cellule[y+1][x-1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y+1][x-1].mojood =1 ;
                    cellule[y+1][x-1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                if(x%2!=0 && y<height && x>0 && cellule[y][x-1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y][x-1].mojood =1 ;
                    cellule[y][x-1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                break ;
            case 5 :
                if(x%2==0  && x<width-1 && cellule[y][x+1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y][x+1].mojood =1 ;
                    cellule[y][x+1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                if(x%2!=0 &&y>0 && x<width-1 && cellule[y-1][x+1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y-1][x+1].mojood =1 ;
                    cellule[y-1][x+1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                break ;
            case 6 :
                if(x%2==0 && x>0 && cellule[y][x-1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y][x-1].mojood =1 ;
                    cellule[y][x-1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                if(x%2!=0 &&y>0&& x>0 && cellule[y-1][x-1].type!='3')
                {
                    cellule[y][x].mojood= 0 ;
                    cellule[y-1][x-1].mojood =1 ;
                    cellule[y-1][x-1].energy_mojood = cellule[y][x].energy_mojood ;
                    cellule[y][x].energy_mojood = 0 ;
                }
                break ;
            }
        }
        if(option==4)
        {
            save_cell(width , height , cellule) ;
            save_map(width , height , cellule) ;
        }
        if(option==3)
        {
            printf("Enter your coordinate (i&j) : ") ;
            scanf("%d %d",&x , &y) ;
            if(cellule[y][x].type=='1')
            {
                if(cellule[y][x].energy >= 15)
                {
                    cellule[y][x].energy -=15 ;
                    if(cellule[y][x].energy_mojood <=85)
                    {
                        cellule[y][x].energy_mojood += 15;
                        score +=15 ;
                    }
                    else
                    {
                        score += 100 - cellule[y][x].energy_mojood ;
                        cellule[y][x].energy_mojood = 100 ;
                    }
                }
                else
                {
                    if(cellule[y][x].energy_mojood <=(100-cellule[y][x].energy) )
                    {
                        cellule[y][x].energy_mojood +=cellule[y][x].energy;
                        score += cellule[y][x].energy ;
                    }
                    else
                    {
                        score += 100 - cellule[y][x].energy_mojood ;
                        cellule[y][x].energy_mojood = 100 ;
                    }
                    cellule[y][x].energy =0  ;
                }
            }
        }
        if(option ==2)
        {
            printf("Enter your coordinate (i&j) : ") ;
            scanf("%d %d",&x , &y) ;
             h=empty_cell(width , height , cellule ,x,y, 16 ) ;
             a =0 ;
             b =0 ;
            if(cellule[y][x].type=='2' && cellule[y][x].energy_mojood >=80 && h)
            {
                cellule [y][x].energy_mojood = 40 ;
                int g = rand() ;
                double w = g ;
                w= w * h ;
                w= w/ (RAND_MAX) ;
                g = w ;
                h = empty_cell(width , height , cellule , x, y , g+1) ;
                cellule[b][a].mojood = 1 ;
                cellule[b][a].energy_mojood = 40 ;
            }
        }
    system("cls") ;
    print_map(height , width , cellule) ;
    print_score(width, height , cellule) ;
    print_menu2(width) ;
    printf("choose one option  :") ;
    scanf("%d",&option) ;
    }
    return 0 ;
}
void multi_player(int height , int width , struct cell cellule[height][width] )
{
    struct cell_position first , second ;
    int r  , chose , x , y , i , j , move;
    double f;
    r= rand() ;
    f=r ;
    f=f/(RAND_MAX) ;
    f=f*height ;
    f=f*width;
    r=f ;
    j = r / height ;
    i = r- j*height ;
    if(cellule[j][i].type != '3' && cellule [j][i].mojood ==0)
    {
        cellule[j][i].mojood = 1 ;
        cellule [j][i].energy_mojood=0 ;
    }
    else
    make_rand_ij(width , height , 1 , cellule) ;
    first.x=i;
    first.y = j ;
//    second = cell_new (first );
    cellule[second.y][second.x].mojood = 1 ;
    cellule [second.y][second.x].energy_mojood=0 ;
    print_map(height , width , cellule);
    print_multi(width);
    struct cell_move_data aval , dovom ;
    scanf("%d",&chose) ;
    b = j ;
    a = i ;
    while(chose!=3)
    {
         if(chose==1)
         {
            gotoxy(0,0) ;
            for(i=0 ; i< 35 ; i++)
                printf("                                                                                \n") ;
            gotoxy(0,0)  ;
            print_map(height , width , cellule) ;
            print_score(width , height , cellule) ;
            print_menu_move(width) ;
            printf("\nEnter your move : ");
            scanf("%d",&move) ;
            aval.cell_energy= cellule[b][a].energy_mojood;
            aval.move_direction = move ;
         //   dovom = cell_move (aval);
            switch(move)
            {
            case 1 :
                if(b < height-1  && cellule[b+1][a].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b+1][a].mojood =1 ;
                    cellule[b+1][a].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    b+=1 ;
                }
                break ;
            case 2 :
                if(b>0 && cellule[b-1][a].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b-1][a].mojood =1 ;
                    cellule[b-1][a].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    b= b-1 ;
                }
                break ;
            case 3 :
                if(a%2==0 &&b<height-1 && a<width-1 && cellule[b+1][a+1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b+1][a+1].mojood =1 ;
                    cellule[b+1][a+1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    b = b+1 ;
                    a = a+1 ;
                }
                if(a%2!=0 &&b<height && a<width-1 && cellule[b][a+1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b][a+1].mojood =1 ;
                    cellule[b][a+1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    a = a+1 ;
                }
                break ;
            case 4:
                if(a%2==0 && b<height-1 && a>0 && cellule[b+1][a-1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b+1][a-1].mojood =1 ;
                    cellule[b+1][a-1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    b = b+1 ;
                    a = a-1 ;
                }
                if(a%2!=0 && b<height && a>0 && cellule[b][a-1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b][a-1].mojood =1 ;
                    cellule[b][a-1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    a= a-1 ;
                }
                break ;
            case 5 :
                if(a%2==0  && a<width-1 && cellule[b][a+1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b][a+1].mojood =1 ;
                    cellule[b][a+1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    a= a+1 ;
                }
                if(a%2!=0 &&b>0 && a<width-1 && cellule[b-1][a+1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b-1][a+1].mojood =1 ;
                    cellule[b-1][a+1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    a= a+1 ;
                    b=b-1 ;
                }
                break ;
            case 6 :
                if(a%2==0 && a>0 && cellule[b][a-1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b][a-1].mojood =1 ;
                    cellule[b][a-1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    a= a-1 ;
                }
                if(x%2!=0 &&y>0&& x>0 && cellule[y-1][x-1].type!='3')
                {
                    cellule[b][a].mojood= 0 ;
                    cellule[b-1][a-1].mojood =1 ;
                    cellule[b-1][a-1].energy_mojood = cellule[b][a].energy_mojood ;
                    cellule[b][a].energy_mojood = 0 ;
                    a= a-1 ;
                    b=b-1 ;
                }
                break ;
            }
        }
        if(chose ==2 )
        {
            if(cellule[b][a].type=='1')
            {
                if(cellule[b][a].energy >= 15)
                {
                    cellule[b][a].energy -=15 ;
                    if(cellule[b][a].energy_mojood <=85)
                    {
                        cellule[b][a].energy_mojood += 15;
                        score +=15 ;
                    }
                    else
                    {
                        score += 100 - cellule[b][a].energy_mojood ;
                        cellule[b][a].energy_mojood = 100 ;
                    }
                }
                else
                {
                    if(cellule[b][a].energy_mojood <=(100-cellule[b][a].energy) )
                    {
                        cellule[b][a].energy_mojood +=cellule[b][a].energy;
                        score += cellule[b][a].energy ;
                    }
                    else
                    {
                        score += 100 - cellule[b][a].energy_mojood ;
                        cellule[b][a].energy_mojood = 100 ;
                    }
                    cellule[b][a].energy =0  ;
                }
            }
            aval.cell_energy= cellule[b][a].energy_mojood;
            aval.move_direction = 7 ;
          //  dovom = cell_move (aval);

        }
    gotoxy(0,0) ;
    for(i=0 ; i< 25 ; i++)
        printf("                                                                                            \n") ;
    gotoxy(0,0)  ;
    print_map(height , width , cellule) ;
    print_score(width, height , cellule) ;
    print_multi(width) ;
    printf("choose one option  :") ;
    scanf("%d",&chose) ;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7|0<<4);
    return 0 ;
}
int main()
{
    int height , width  , i , j  , gozine  , number , nafar , h , w =0;
    time_t t = time(NULL) ;
    srand(t) ;
    FILE *fp ;
    printf("do you want make your own map ?\n") ;
    printf("[1] yes \n") ;
    printf("[2] no \n") ;
    scanf("%d",&w) ;
    if(w == 1)
        map_editor(name) ;
    if(w != 1 )
    {
         gotoxy(0,0);
        for(i=0 ; i< 20 ; i++)
            printf("                                                                                    \n") ;
        gotoxy(0,0) ;
        print_menu(width) ;
        scanf("%d",&gozine) ;
        if(gozine==1)
        {
             printf("Enter the map addres that you want to load: ") ;
             scanf("%s",name) ;
        }
    }
    fp = fopen(name, "rb") ;
    if(fp==NULL)
    {
        printf("can not open file") ;
        return -1 ;
    }
    fread(&height , sizeof(int) , 1  , fp) ;
    fread(&width , sizeof(int) , 1  , fp) ;
    h = height ;
    struct cell cellule[height][width];
    for(i=0; i<h; i++)
    {
        for(j=width-1; j>=0 ; j--)
        {
            fread (&cellule[j][i].energy , sizeof(int), 1 , fp) ;
            fread (&cellule[j][i].type , sizeof(char), 1 , fp) ;
            cellule[j][i].mojood = 0  ;
            cellule[j][i].energy_mojood = 0  ;

        }
    }
    if(w==1)
    {
          gotoxy(0,0);
        for(i=0 ; i< 20 ; i++)
            printf("                                                                                         \n") ;
        gotoxy(0,0) ;
        print_menu(width) ;
        scanf("%d",&gozine) ;

    }
    height = h ;
    if(gozine==2)
    {
        printf("how many cellule do you want ?") ;
        scanf("%d",&number) ;

        if(number> width*h)
        {
            printf("your number is wrong!") ;
            return -1 ;
        }
        height = h ;
         gotoxy(0,0);
        for(i=0 ; i< 20 ; i++)
            printf("                                                                                                        \n") ;
        gotoxy(0,0) ;
        make_rand_ij(width , height , number , cellule) ;
        single_player (width , height , cellule) ;
    }
    if(gozine==1)
    {
           gotoxy(0,0);
        for(i=0 ; i< 20 ; i++)
            printf("                                                                                       \n") ;
        gotoxy(0,0) ;

        load(width , height , cellule)  ;
        single_player (width , height , cellule) ;

    }
    if(gozine==4)
        return 0 ;
    if(gozine==3)
    {
        multi_player(height , width , cellule) ;

    }
    gotoxy(0,0) ;
    for(i=0 ; i< 20 ; i++)
        printf("                                                   \n") ;
    gotoxy(0,0)  ;
    print_map(height , width , cellule) ;
    print_score(width, height , cellule) ;
    fclose(fp) ;
    getchar();  // wait
    return 0;
}

//MANBA : ABI  3<<4
//TAGHSIM : SABZ 2<<4
//MAMNOO : GHERMEZ 4<<4
// MAMOOOLI : TOOSI 8<<4
