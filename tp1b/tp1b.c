#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "module/interface.h"
#include "module/modtp1b.h"

#define case_color 7
#define lines_color 4
#define base_txt_color 0
#define wrong_txt_color 1
#define initial_numof_case 30
#define max_errors 4


void show_game_grid(unsigned char *grid,unsigned char *ggrid) {// show sudoku grid with first 30 numbers
    int bl,rd,row,col;
    interfwrite(4,70,"exemple 132= first row, 3rd column, test the number 2");
    interfwrite(2,6,"1      2      3       4      5      6       7      8      9");
    char ert[2]; ert[1]='\0';
    for (int i=0;i<3;i++) 
        for (int j=0;j<3;j++) {
            ert[0]='0'+3*i+j+1;
            interfwrite(5+10*i+3*j,1,ert);
        }
    
    interfcolor(0,lines_color); //zone
    interfclear_zone(3,2,31,67); 

    interfcolor(0,case_color); //cases
    interfclear_zone(4,3,9,21);
    interfclear_zone(14,3,9,21);
    interfclear_zone(24,3,9,21);
    interfclear_zone(4,25,9,21);
    interfclear_zone(14,25,9,21);
    interfclear_zone(24,25,9,21);

    interfclear_zone(4,47,9,21);
    interfclear_zone(14,47,9,21);
    interfclear_zone(24,47,9,21);
    for (int i=0;i<initial_numof_case;i++) { // first 30 numbers
        bl=1;
        do {
            rd=rand()%81;
            if (!grid[rd]) {
                grid[rd]=ggrid[rd];
                bl=0;
            }
        } while (bl);
        row=rd/9;
        col=rd%9;
        ert[0]='0'+(int)grid[rd];
        interfwrite(5+10*(row/3)+3*(row-3*(row/3)),6+22*(col/3)+7*(col-3*(col/3)),ert);
    }
}
int test_number(int row,int col,int num,unsigned char*grid,unsigned char*ggrid) {
    char ert[2]; ert[1]='\0';
    if ((grid[row*9+col] & 0x0F)==(ggrid[row*9+col])) // if num is already good, do nothing
        return 0;
    if (((grid[row*9+col] & 0x0F)==((unsigned char)num))&&(grid[row*9+col]&0xF0)) // if num is an error and also already in the grid, do nothing
        return 0;
    int not_an_error=place_in_grid(row,col,num,grid,ggrid);
    interfcolor(0,7);
    if (!not_an_error) { // if the number is wrong acutalise error count
        interfcolor(7,0);
        interfwrite(1,20,"");
        printf("%d / %d",errors_count,max_errors);
        interfcolor(1,7);
    }
    ert[0]='0'+num;
    interfwrite(5+10*(row/3)+3*(row-3*(row/3)),6+22*(col/3)+7*(col-3*(col/3)),ert); // place the number in the right case
    interfcolor(0,7);
    return not_an_error;
}

void launch_sudoku() {
    errors_count=0;
    int gridfull=0,row,col,val;
    char rep[5];
    unsigned char *grid=create_grid(); // init grids
    unsigned char *ggrid=create_ggrid();
    interfinit();
    interfflip_screen();
    
    interfwrite(1,2,"Number of errors: 0");
    show_game_grid(grid,ggrid);
    do {                           // game loop
        interfcolor(7,0);
        interfclear_zone(32,69,3,50);
        interfwrite(33,70,"");
        fgets(rep,5,stdin);
        if (strlen(rep)==(size_t)4) { //st
            row=(int)(rep[0]-'0')-1;
            col=(int)(rep[1]-'0')-1;
            val=(int)(rep[2]-'0');
            if (0<=row&&row<9&&0<=col&&col<9&&0<val&&val<=9) { //ed checking block
                if (!test_number(row,col,val,grid,ggrid)) //actualise grid if needed and if it's not an error check if the grid is full
                    gridfull=isgridfull(grid);
            }
        }
    } while ((errors_count!=max_errors)&&(!gridfull));  // quit the game if the grid is full or if the player gets too many errors
    free(grid);free(ggrid);
}






int correct_tp_test_number(int row,int col,int num,unsigned char*grid) {
    char ert[2]; ert[1]='\0';
    int not_an_error=correct_tp_place_in_grid(row,col,num,grid);
    interfcolor(0,7);
    if (!not_an_error) { // if the number is wrong acutalise number color
        interfcolor(1,7);
    }
    ert[0]='0'+num;
    interfwrite(5+10*(row/3)+3*(row-3*(row/3)),6+22*(col/3)+7*(col-3*(col/3)),ert); // place the number in the right case
    interfcolor(0,7);
    return not_an_error;
}



void correct_tp_launch_sudoku() {
    int row,col,val;
    char rep[5];
    unsigned char *grid=create_grid(); // init grids
    unsigned char *ggrid=create_ggrid();
    interfinit();
    interfflip_screen();
    
    show_game_grid(grid,ggrid);
    do {                           // game loop
        interfcolor(7,0);
        interfclear_zone(32,69,3,50);
        interfwrite(33,70,"");
        fgets(rep,5,stdin);
        if (strlen(rep)==(size_t)4) { //st
            row=(int)(rep[0]-'0')-1;
            col=(int)(rep[1]-'0')-1;
            val=(int)(rep[2]-'0'); // end
            if (0<=row&&row<9&&0<=col&&col<9&&0<val&&val<=9)
                correct_tp_test_number(row,col,val,grid); //actualise grid if needed and if it's not an error check if the grid is full
        }
    } while (!isgridfull(grid));  // quit the game if the grid is full
    free(grid);free(ggrid);
}


int main() {  // just launch the game with a new seed
    srand(time(0));
    //launch_sudoku();
    correct_tp_launch_sudoku();
    return 0;
}