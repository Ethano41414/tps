#include "vecteur.h"


void vecteurToFile(FILE *flux, VecteurType vecteur, int ordre) {//affiche l'ordre puis les coefficients du vecteur dans le buffer
    fprintf(flux, "%d\n", ordre);
    for (int i=0;i<ordre;i++)
        fprintf(flux,"%.3f%s",vecteur[i],(i==ordre-1)?"\n":" ");
}


VecteurType vecteurFromFileByName(char *path,int *order) {// lit un fichier et renvoit le vecteur présent dedans
	VecteurType retour = NULL;
	double tmp;
	FILE *f=fopen(path,"r");
	if (f) {
		int ord;
		fscanf(f,"%d",&ord);
		retour=malloc(ord*sizeof(double));
		if (retour==NULL) {
			fclose(f);
			return NULL;
		}
		for (int i=0;i<ord;i++) {
			fscanf(f,"%lf",&tmp);
			retour[i]=tmp;
		}
		*order=ord;
	} else printf("Error can't read file");
	return retour;
}



double produitScalaire(VecteurType v1, VecteurType v2, int order) {
	double retour=0.0;
	for (int i=0;i<order;i++)
		retour+=v1[i]*v2[i];
    return retour;
} 

void liberer_vecteur(VecteurType *p_vecteur) { //libere la mémoire du vecteur (par adresse)
	free(*p_vecteur);
	*p_vecteur=NULL;
}


VecteurType matVectmul(mat A, VecteurType v, int orderA, int orderv) { /*
	pour un vecteur colone la multiplication matricielle est equivalent a un produit scalaire par ligne avec le vecteur*/
	if (orderA==orderv) {
		VecteurType res=malloc(orderv*sizeof(double));
		if (res==NULL) return NULL;
		for (int i=0;i<orderv;i++)
			res[i]=produitScalaire(A[i],v,orderv);
		return res;
	}
	return NULL;
}


