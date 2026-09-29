#include "module/modtp3.h"
#include "module/interface.h"
#include <time.h>
#include <unistd.h>


int colors[]={1,4,3,2,5,6,7};


void actualise_grid(int **grid,int size) {
    for (int i=0;i<size;i++)
        for (int j=0;j<size;j++) {
            interfcolor(7,colors[grid[i][j]]);
            interfwrite(1+3*i,1+7*j,"       ");
            interfwrite(1+3*i+1,1+7*j,"       ");
            interfwrite(1+3*i+2,1+7*j,"       ");
        }
}


void game() {
    char tmpinput[20];
    char txt[2];txt[1]='\0';

    int p1=12,p2=6,p3=22;
    printf("Entrez la taille de la zone de jeu (carré)\npuis le nombre de couleurs (1-->7)\net le nombre de coups maximum\nentrez les 3, mettez n pour none\n");
    scanf("%d",&p1);
    scanf("%d",&p2);
    scanf("%d",&p3);
    SIZE=p1; //
    num_of_colors=p2;
    use_count=0;
    interfinit();
    interfflip_screen();
    int **grid=init_grid(SIZE),tmpintinput;
    for (int i=0;i<num_of_colors;i++) {interfcolor(7,colors[i]);txt[0]='0'+i;interfwrite(38,1+i,txt);}
    actualise_grid(grid,SIZE);
    do {
        interfcolor(7,0);
        interfwrite(30,87,"");
        fgets(tmpinput,20,stdin);
        tmpintinput=(int)(tmpinput[0]-'0');
        fill_grid(tmpintinput,grid);
        interfcolor(0,0);
        interfclear_zone(29,86,3,20);
        actualise_grid(grid,SIZE);
        interfcolor(7,0);interfwrite(15,87,"");printf("Coups %d / %d",use_count,p3);        
    } while (!is_grid_full(grid)&&use_count<p3);
    freemat(grid,SIZE);
}





int main() {
    game();
    return 0;
}