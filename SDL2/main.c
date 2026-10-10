#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "modtp3.h"

SDL_Color cwhite={255, 255, 255, 255};
SDL_Color cred={255, 0, 0, 255};

int colors[]={0x0000ff,0x00ff00,0x00ffff,0xff0000,0xff00ff,0xffff00};

//Appuyez sur Echap pour relancer une partie

void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int use_count, int coups_max) { // IA commenté par moi
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, (use_count<=coups_max)?cwhite:cred); // creer une surface de texte avec la police voulue (TTF_Font)
    if (!surface) {
        printf("Erreur texte : %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);  // enregistre le texte dans une texture (si j'ai bien compris c'est stocké dans la VRAM)
    SDL_Rect dst = {x, y, surface->w, surface->h};  // on cré une "hitbox" de la même taille que la surface
    SDL_FreeSurface(surface); // on a plus besoin de la surface car on l'a mise dans la textire
    if (!texture) return;
    SDL_RenderCopy(renderer, texture, NULL, &dst); // affiche la texture dans le renderer et la limite au rectangle dst
    SDL_DestroyTexture(texture);  // on a plus besoin de la texture
}


void render_grid(SDL_Renderer *renderer, int **grid, int num_of_case, int case_size) {
    unsigned int color;
    SDL_Rect rect={4, 4, 50, 50};
    for (int i=0;i<num_of_case;i++)
        for (int j=0;j<num_of_case;j++) {
            color=colors[grid[i][j]];
            SDL_SetRenderDrawColor(renderer, (color&0xff0000)>>16, (color&0x00ff00)>>8, color&0x0000ff, 255);
            rect.y=4+case_size*i;
            rect.x=4+case_size*j;
            SDL_RenderFillRect(renderer, &rect);
        }
}

void gactualise_count(SDL_Renderer *renderer,TTF_Font *font, int case_size, int use_count, int coups_max) {
    char text[30];
    SDL_Rect rect={SIZE*case_size+70,55,60,25};
    sprintf(text,"%2d / %2d",use_count,coups_max);
    SDL_SetRenderDrawColor(renderer,30,30,30,255);
    SDL_RenderFillRect(renderer, &rect);
    draw_text(renderer,font,text,SIZE*case_size+70,55,use_count,coups_max);
}



int game(int num_of_case,int coups_max,int color_count) {
    int case_size=50,row,col,game_not_ended=1;
    
    num_of_colors=color_count;
    SIZE=num_of_case;
    use_count=0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window *window = SDL_CreateWindow("Flood It !",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,608,SDL_WINDOW_SHOWN);
    //SDL_SetWindowResizable(window, SDL_FALSE);
    if (window==NULL) {
        printf("Erreur fenetre : %s\n",SDL_GetError());
        SDL_Quit();
        return 0;
    }


    int **grid=init_grid(SIZE);
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (renderer==NULL) {
        printf("Erreur fenetre : %s\n",SDL_GetError());
        SDL_Quit();
        return 0;
    }
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSerif.ttf", 15);  // on importe la police d'écriture
    if (font==NULL) {
        printf("Erreur fenetre : %s\n",TTF_GetError());
        SDL_Quit();
        return 0;
    }
    
    SDL_SetRenderDrawColor(renderer,30,30,30,255); // couleur du rendu à gris
    SDL_RenderClear(renderer); // rempli l'écran (avec le gris du coup)
    render_grid(renderer,grid,SIZE,case_size);

    draw_text(renderer,font,"Nombre de coups:",SIZE*case_size+20,30,0,1);
    draw_text(renderer,font,"ESC pour rejouer",SIZE*case_size+30,580,0,1);
    gactualise_count(renderer,font,case_size,use_count,coups_max);
    SDL_RenderPresent(renderer);
    

    int run=1;
    SDL_Event event;
    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_QUIT)
                run=0;
            else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE) {
                freemat(grid,SIZE);
                grid=init_grid(SIZE);
                use_count=0;
                game_not_ended=1;
                render_grid(renderer,grid,num_of_case,case_size);
                gactualise_count(renderer,font,case_size,use_count,coups_max);
                SDL_RenderPresent(renderer);
            } else if (event.type==SDL_MOUSEBUTTONDOWN&&event.button.button==SDL_BUTTON_LEFT&&game_not_ended) {
                row=(event.button.y-4)/case_size;
                col=(event.button.x-4)/case_size;
                if (0<=row&&row<SIZE&&0<=col&&col<SIZE) {
                    fill_grid(grid[row][col],grid);
                    render_grid(renderer,grid,num_of_case,case_size);
                    gactualise_count(renderer,font,case_size,use_count,coups_max);
                    SDL_RenderPresent(renderer);
                    
                    if (is_grid_full(grid)) {
                        game_not_ended=0;
                        printf("yeahhhhhhhhhh");fflush(stdout);
                    } else if (use_count>coups_max) {
                        game_not_ended=0;
                        printf("aaaaaawwwww");fflush(stdout);
                    }
                }
            }
        }
    }
    freemat(grid,SIZE);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}






int main() {
    srand(time(0));
    return !game(12,22,6);
}


