#ifndef MODTP3_H
#define MODTP3_H

#include <stdio.h>
#include <stdlib.h>

extern int num_of_colors;
extern int SIZE;

extern int use_count;

int **init_grid(int size);

void freemat(int **grid, int size);

void showmat(int **grid,int size);

int is_grid_full(int **grid);

void recursive_fill(int i, int j, int color, int last_color, int **grid);

void fill_grid(int new_color, int **grid);

#endif