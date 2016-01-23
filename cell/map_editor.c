#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void gotoxy(int x , int y )
{
    COORD pos ;
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE) ;
    if(INVALID_HANDLE_VALUE!=hConsole)
    {
        pos.X = x ;
        pos.Y = y ;
        SetConsoleCursorPosition(hConsole , pos) ;
    }
}
void print_cell (int x,int y , int cell)
{
    if(cell==0)
    {
        gotoxy(x+1,y+1) ;
        printf("      ") ;
        gotoxy(x +1, y+2) ;
        printf("      ") ;
        gotoxy (x+1, y+3) ;
        printf("      ") ;
    }
    else
    {
        if(cell ==1)
        {
            gotoxy(x+1,y+1) ;
            printf("      ") ;
            gotoxy(x +1, y+2) ;
            printf("  **  ") ;
            gotoxy (x+1, y+3) ;
            printf("      ") ;
        }
        else
        {
        gotoxy(x+1,y+1) ;
        printf("      ") ;
        gotoxy(x +1, y+2) ;
        printf("  ??  ") ;
        gotoxy (x+1, y+3) ;
        printf("      ") ;
        }
    }

}
void map_editor (char name[])
{
    int x , y , energy , m ,n , z;
    //x=width
    //y=height
    //m = i
    //n = j
    int manba , mamooli , mamnoo , taghsim ;
    char model ;
    printf("Enter n for your map : ") ;
    scanf("%d",&x) ;
    y =x ;
    printf("Enter your file name : ") ;
    scanf("%s",name) ;
    FILE *map ;
    map = fopen(name , "w+b") ;
    fwrite(&y , sizeof(int), 1 ,map) ;
    fwrite(&x , sizeof(int), 1 ,map) ;
    gotoxy(0,0) ;
    for(m=0 ; m<25; m++)
        printf("                                             \n") ;
    gotoxy(0,0) ;
    for(m=1  ; m<= x ; m++)
    {
        gotoxy (6*m -3, 0 );
        printf("%d" , m-1) ;
    }
    for(m=y ; m>0 ; m--)
    {
        gotoxy(0 , 3*m-1 ) ;
        printf("%d" , y-m) ;
    }
    gotoxy(0,0) ;
    n = 0;

    for(n=0 ; n<x ;n++)
    {
        m= y-1 ;
        while (m>=0)
        {
            gotoxy(0 , 2 +(y)*3 ) ;
            for(z=0 ; z<7 ; z++)
                printf("                                         \n") ;
            if((x-n-1)%2!=0)
                    print_cell (6*n, 3*(y-1- m)+1 ,2) ;
            else
                    print_cell (6*n,3*(y-m-1) ,2) ;
            gotoxy(0 , 2 +(y)*3 ) ;
            printf("1.manba\n") ;
            printf("2.taghsim\n") ;
            printf("3.mamnoo\n");
            printf("4.mamooli\n") ;
            printf("what type do you want for your cell ?") ;
            scanf("%c",&model) ;
            scanf("%c",&model) ;
            if(model == '1')
            {
                printf("Enter energy :") ;
                scanf("%d",&energy) ;

            }
            else
                energy =0 ;
            fwrite(&energy , sizeof(int),1 , map) ;
            fwrite(&model , sizeof(char),1 , map) ;
            switch (model)
            {
            case '1' :
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1| 3<<4);
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
            if((x-n-1)%2!=0)
                    print_cell (6*n, 3*(y-1- m)+1 ,0) ;
            else
                    print_cell (6*n,3*(y-m-1) ,0) ;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7| 0<<4);
            m-- ;
        }
    }
    fclose(map) ;
    gotoxy(0 , 0) ;
    for(z=0 ; z< 20 ; z++)
        printf("                                                \n")  ;
    gotoxy (0,0) ;
}
