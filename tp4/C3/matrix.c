#include "matrix.h"


mat initmat(int n, int m) { //initialise la matrice à O_{n,m}
    mat M=malloc(n*sizeof(double*));
    for (int i=0;i<n;i++)
        M[i]=calloc(m,sizeof(double));
    return M;
}

void freemat(mat pM,int nb_row) { // libere la mémoire allouée dans la matrice nb_row pour savoir combien de lignes effacer
    for (int i=0;i<nb_row;i++) free(pM[i]);
    free(pM);
}


void matrixToFile(FILE *flux, mat M, int ordre) { //affiche l'ordre puis la matrice dans le buffer
    fprintf(flux, "%d\n", ordre);
    for (int i=0;i<ordre;i++) {
        for (int j=0;j<ordre;j++)
            fprintf(flux,"%.3f%s",M[i][j],(j==ordre-1)?"\n":" ");
        }
}

mat matrixFromFileByName(char *path,int *order) { // lit un fichier et renvoit la matrice présente dedans
	mat retour=NULL;
	FILE *f=fopen(path,"r");
	if (f) {
		int ord;
		fscanf(f,"%d",&ord);
		retour=malloc(ord*sizeof(double*));
		if (retour==NULL) {
			fclose(f);
			return NULL;
		}
		for (int i=0;i<ord;i++) {
            retour[i]=calloc(ord,sizeof(double));
            for (int j=0;j<ord;j++) {
                fscanf(f,"%lf",&retour[i][j]);
            }
		}
		*order=ord;
	} else printf("Error can't read file");
	return retour;
}




