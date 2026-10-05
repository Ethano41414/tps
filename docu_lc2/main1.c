#include "module/mod.h"


/*-------------------------------------------*/
/* geto   Converti un flux en objet liste_t  */
/*                                           */
/* En entrée: *stream flux de texte          */
/*                                           */
/* En sortie: Objet liste_t                  */
/*-------------------------------------------*/
liste_t *geto(FILE *stream) {
    liste_t *list=init_void_list();
    char     line[300];
    while (agets(line,300,stream))
        append(list,line);
    return list;
}


/*---------------------------------------------------------*/
/* stream_get_list   Recupère un objet liste depuis stdin  */
/*                                                         */
/* En entrée: Rien                                         */
/*                                                         */
/* En sortie: Objet liste_t                                */
/*---------------------------------------------------------*/
liste_t *stream_get_list() {
    liste_t *list=geto(stdin);
    return list;
}

/*------------------------------------------------------------*/
/* file_get_list   Recupère un objet liste depuis un fichier  */
/*                                                            */
/* En entrée: *path Chemin vers le fichier                    */
/*                                                            */
/* En sortie: Objet liste_t                                   */
/*------------------------------------------------------------*/
liste_t *file_get_list(char *path) {
    FILE *f=fopen(path,"r");
    if (f==NULL)
        return NULL;
    liste_t *list=geto(f);
    fclose(f);
    return list;
}


int main(int argc, char **argv) { // si il existe un argument, on considère que c'est un fichier valide
    liste_t *list;
    if (argc>1) {
        list=file_get_list(argv[1]);
    } else
        list=stream_get_list();
    show_list(list);
    return 0;
}


