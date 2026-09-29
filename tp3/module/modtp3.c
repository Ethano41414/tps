#include "modtp3.h"

int num_of_colors;
int SIZE;
int use_count=0;

int **init_grid(int size) {
    int **mat=malloc(size*sizeof(int*));
    for (int i=0;i<size;i++) {
        mat[i]=malloc(size*sizeof(int));
        for (int j=0;j<size;j++)
            mat[i][j]=rand()%num_of_colors;
    }
    return mat;
}

void freemat(int **grid, int size) {
    for (int i=0;i<size;i++)
        free(grid[i]);
    free(grid);
}

void showmat(int **grid,int size) {
    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++)
            printf("%d ",grid[i][j]);
        printf("\n");
    }
}

int is_grid_full(int **grid) {
    int color=grid[0][0];
    for (int i=0;i<SIZE;i++)
        for (int j=0;j<SIZE;j++)
            if (grid[i][j]!=color) return 0;
    return 1;
}

void recursive_fill(int i, int j, int color, int last_color, int **grid) {
    if (i < 0 || i >= SIZE || j < 0 || j >= SIZE)
        return;
    if (grid[i][j] != last_color)
        return;
    grid[i][j]=color;
    recursive_fill(i,j+1, color, last_color, grid);
    recursive_fill(i+1,j, color, last_color, grid);
    recursive_fill(i,j-1, color, last_color, grid);
    recursive_fill(i-1,j, color, last_color, grid);
}

void fill_grid(int new_color, int **grid) {
    int orig_color=grid[0][0];
    recursive_fill(0,0,new_color,orig_color,grid);
    use_count++;
}





