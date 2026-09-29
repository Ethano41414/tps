#include "module/modtp3.h"
#include "module/interface.h"
#include <time.h>
#include <unistd.h>


int colors[]={1,4,3,2,5,6,7}; // on peut pas mettre plus de 7 couleurs dans le terminal (0=noir non compté)


void actualise_grid(int **grid,int size) { // affichage de la grille sur terminal chaque case est de dimention 3x7
    for (int i=0;i<size;i++)
        for (int j=0;j<size;j++) {
            interfcolor(7,colors[grid[i][j]]);
            interfwrite(1+3*i,1+7*j,"       ");
            interfwrite(1+3*i+1,1+7*j,"       ");
            interfwrite(1+3*i+2,1+7*j,"       ");
        }
}


void game() { // boucle de jeu principale
    char tmpinput[20];
    char txt[2];txt[1]='\0';

    int p1=12,p2=6,p3=22; //initialisation des valeurs
    printf("Entrez la taille de la zone de jeu (carré)\npuis le nombre de couleurs (1-->7)\net le nombre de coups maximum\nentrez les 3, mettez n pour none\n");
    scanf("%d",&p1);
    scanf("%d",&p2); // taille, couleurs et coups maximum
    scanf("%d",&p3);
    SIZE=p1;       // SIZE et num_of_colors ne pouvaient plus être dans un #define car elles étaient modifiées
    num_of_colors=p2;
    use_count=0;
    interfinit();          //<---/---dégage la place pour le jeu sans effacer les lignes précédentes
    interfflip_screen();   //<--/
    int **grid=init_grid(SIZE),tmpintinput; // initialisation random de la grille
    for (int i=0;i<num_of_colors;i++) { // affichage des chiffres d'indication
        interfcolor(7,colors[i]);
        txt[0]='0'+i;interfwrite(38,1+i,txt);}
    actualise_grid(grid,SIZE);
    do {
        interfcolor(7,0);                     //<-----/----|on place le curseur et on récupere le premier chiffre
        interfwrite(30,87,"");                //<----/     |que le joueur à entré dans la console
        fgets(tmpinput,20,stdin);             //<---/
        tmpintinput=(int)(tmpinput[0]-'0');   //<--/
        fill_grid(tmpintinput,grid);  // on actualise le jeu
        interfcolor(0,0);
        interfclear_zone(29,86,3,20);
        actualise_grid(grid,SIZE);
        interfcolor(7,0);interfwrite(15,87,"");printf("Coups %d / %d",use_count,p3); // actualise le nombre de coups effectués à l'écran       
    } while (!is_grid_full(grid)&&use_count<p3); //on continu le jeu tant qu'on est pas au dernier coup et que la grille n'est pas pleine
    freemat(grid,SIZE); //onoublie pas de liberer la mémoire de la grille
}


int main() {
    game();
    return 0;
}