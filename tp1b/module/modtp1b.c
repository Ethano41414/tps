#include <stdio.h>
#include <stdlib.h>
/*
grid  : grid the player can see   81o initialised to 0
ggrid : game grid with all numbers  81o

each number of the grids are unsigned char to have 1octet
for ggrid it's just a memory save
for grid, the 4 first bits is the number asked, and the 5th is: 0 for good and 1 for wrong
*/
int errors_count;

void showmat(unsigned char *tmpgrid,int size) {
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) printf("%d ",(int)(tmpgrid[9*i+j]&0x0F));
        printf("\n");
    }
}

unsigned char *create_grid() { //initialise grid
    unsigned char *ggrid=calloc(81,1);
    return ggrid;
}


void fill_ggrid(unsigned char *ggrid) {
    int i,j,k;
    k=rand();
    for(j=0;j<9;++j)
        for(i=0;i<9;++i)
            ggrid[j*9+i]=(i+j*3+j/3+k)%9+1;
}

unsigned char *create_ggrid() { //initialise a ggrid (grid of the game with all numbers in it)
    unsigned char *ggrid=calloc(81,1);
    fill_ggrid(ggrid);
    return ggrid;
}

int isgridfull(unsigned char *grid) {
    for (int i=0;i<81;i++)
        if (!grid[i]||(grid[i]&0xF0))
            return 0;
    return 1;
}

int is_right_in_grid(int row, int col, unsigned char *grid, unsigned char *ggrid) {return ((grid[9*row+col] & 0x0F)==ggrid[9*row+col]);}

int place_in_grid(int row, int col, int value, unsigned char *grid, unsigned char *ggrid) { /*
    row and column of the grid impacted
    value
    grid  : grid the player can see
    ggrid : game grid with all numbers
    place 'value' at grid[row*9+col] ( equiv to grid[row][col] ) and mention if it's a error or not          */
    if ((grid[row*9+col] & 0x0F)==(ggrid[row*9+col]))  // if case is already good here, do nothing
        return 1;
    if ((grid[row*9+col] & 0x0F)==((unsigned char)value & 0x0F))  // if value is already here do nothing
        return 1;
    grid[row*9+col]=((unsigned char)value & 0x0F);
    int wrong=!is_right_in_grid(row,col,grid,ggrid);
    if (wrong) {
        grid[row*9+col]=(grid[row*9+col]|(((unsigned char)wrong)<<4)); // if value dont mach with ggrid value place 0b1 at the 5th bit
        errors_count+=1;
        return 0;
    } 
    return 1;
}
