#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teZZt.h"
#include "vecteur.h"

// Ne pas commenter la ligne ci-dessous
BEGIN_TEST_GROUP(vecteur)

// TEST(Exemple) {
// 	int b = 3;

// 	CHECK (3 == b);
// 	CHECK (0 == b);
// } 


TEST(AffichageA) {
   // vecteur statique a afficher
   double v1 [] = {1.0, 2.0, 3.0 };
   // creation du flux de texte => buffer
   char buffer[1024];
   FILE * file = fmemopen(buffer, 1024, "w");
   // REQUIRE ( NULL != file);

   // vecteurToFile(stdout, v1, 3);
   vecteurToFile(file, v1, 3);

   fclose(file);

   // verification de ce qui est envoye sur le flux
   // chaque composante est affichee avec trois chiffres apres la virgule
   // %.3f
   CHECK( 0==strcmp(buffer, "3\n1.000 2.000 3.000\n") );
}


TEST(AffichageB) {
   // vecteur dynamique a afficher
   double * v1 = NULL;
   // creation du flux de texte => buffer
   char buffer[1024];

   v1 = (double *) malloc(3 * sizeof(double));
   REQUIRE ( NULL != v1 ) ; // allocation impossible ?

   v1[0] = 3.0;
   v1[1] = 2.0;
   v1[2] = 1.0;

   FILE * file = fmemopen(buffer, 1024, "w");
   REQUIRE ( NULL != file); // ouverture du flux impossible ?

   // vecteurToFile(stdout, v1, 3);
   vecteurToFile(file, v1, 3);

   fclose(file);

   // verification de ce qui est envoye sur le flux
   // chaque composante est affichee avec trois chiffres apres la virgule
   // %.3f
   CHECK( 0==strcmp(buffer, "3\n3.000 2.000 1.000\n") );
   free(v1);
}


TEST(LectureA, "verification des ordres des vecteurs") {
   int ordre;
   VecteurType vec = NULL;

   vec=vecteurFromFileByName("v1.txt", &ordre);
   free(vec);
   CHECK( 3 == ordre );

   vec=vecteurFromFileByName("v2.txt", &ordre);
   free(vec);
   CHECK( 6 == ordre );

   vec=vecteurFromFileByName("v3.txt", &ordre);
   free(vec);
   CHECK( 3 == ordre );
   vec=NULL;
   // fichier non existant
   //vec = vecteurFromFileByName("v0.txt", &ordre);
   CHECK( NULL == vec);
}


TEST(LectureB, "verification de v1.txt") {
   int     ordre;
   VecteurType vec;

   vec = vecteurFromFileByName("v1.txt", &ordre);
   CHECK  ( 3    == ordre );
   REQUIRE( NULL != vec); // si vec est null, on ne veut pas continuer le test

   CHECK( EQ(vec[0], 5.0) );
   CHECK( EQ(vec[1], 6.3) );   // :-))
   CHECK( EQ(vec[2], 7.0) ); 
   free(vec);
}


TEST(LectureC, "verification de v2.txt") {
   int     ordre;
   VecteurType vec;

   vec = vecteurFromFileByName("v2.txt", &ordre);
   CHECK  ( 6    == ordre );
   REQUIRE( NULL != vec); // si vec est null, on ne veut pas continuer le test

   CHECK( EQ(vec[0], 6.1) );
   CHECK( EQ(vec[1], 5.2) );
   CHECK( EQ(vec[2], 4.3) );
   CHECK( EQ(vec[3], 3.4) );
   CHECK( EQ(vec[4], 2.5) );
   CHECK( EQ(vec[5], 1.6) );
   free(vec);
}


TEST(LectureD, "verification de v3.txt") {
   int     ordre;
   VecteurType vec;

   vec = vecteurFromFileByName("v3.txt", &ordre);
   CHECK  ( 3    == ordre );
   REQUIRE( NULL == vec); // v3 est incomplet, on VEUT que ce soit nul
   free(vec);
}


TEST(PVA) {
	VecteurType v1  = NULL;
	double v2[3] = { 1.0, 2.0, 3.0};
	int   ordre = 0;
	
	v1 = vecteurFromFileByName("v1.txt", &ordre);
	CHECK   ( 3    == ordre);
	REQUIRE ( NULL != v1);

   double ps = produitScalaire(v1, v2, ordre);
	CHECK( EQ( 38.6, ps));
   free(v1);
}


/*
   Les tests ne sont pas parfaits, ils doivent être reecrits pour ne pas avoir de fuite memoire
*/


// Ne pas commenter la ligne ci-dessous
END_TEST_GROUP(vecteur)

// programme principal du jeu tests = lancement automatique des tests decommentes
int main(void) {
	RUN_TEST_GROUP(vecteur); 
 	return 0;
}
