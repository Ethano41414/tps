#ifndef MODTP2_H
#define MODTP2_H

extern int errors_count; //use

void showmat(unsigned char *,int); //use

/*
name: create_grid
description: generate a dynamic empty grid
entry: none
output: grid
*/
unsigned char *create_grid(void); //use

/*
name: create_grid
description: generate a dynamic sudoku grid in grid
entry: ggrid
output: none
*/
void fill_ggrid(unsigned char *);

/*
name: create_ggrid
description: generate a dynamic sudoku grid
entry: none
output: ggrid
*/
unsigned char *create_ggrid(void); //use

/*
name: isgridfull
description: check if the grid is complete (verify if each case is not 0b0 or dont have 0b1 on the 5th bit)
entry: grid
output: 1 yes or 0 no
*/
int isgridfull(unsigned char *grid); //use

/*
name: is_right_in_grid
description: check if the number at (row, col) in grid is the same as in ggrid
entry: row , col , grid , ggrid
output: 1: in good case , 0 in bad case
*/
int is_right_in_grid(int, int, unsigned char *, unsigned char *);

/*
name: place_in_grid
description: place number in grid at (row, col) if needed
entry: row , col , value , grid , ggrid
output: 1: in good case , 0 in bad case
*/
int place_in_grid(int, int, int, unsigned char *, unsigned char *); //use   0 if not the good 1 if right number in case

#endif