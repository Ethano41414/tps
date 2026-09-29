#include "vecteur.h"
// matrix.h est déjà dedans et stdio et stdlib sont dans matrix.h

int main() {
    int orderB;

    printf("Matrice A avec matrixToFile:\n");
    mat A=initmat(3,3);
    matrixToFile(stdout,A,3);
    printf("exemple termine\n\nImport de la matrice B depuis m1.txt\nB:\n");
    mat B=matrixFromFileByName("./m1.txt",&orderB);
    matrixToFile(stdout,B,orderB);

    printf("\nVecteur X:\n");
    VecteurType X=malloc(3*sizeof(double)); // vecteur (5, 1, 2)
    X[0]=5.0; X[1]=1.0; X[2]=2.0;
    vecteurToFile(stdout,X,3);

    printf("\nMultiplication de la matrice B avec le vecteur X\nBX:\n");
    VecteurType R=matVectmul(B,X,orderB,3);

    vecteurToFile(stdout,R,3);

    freemat(A,3); // libération mémoire de tout
    freemat(B,orderB);
    liberer_vecteur(&X);
    liberer_vecteur(&R);
    return 0;
}



