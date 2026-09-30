#include<stdio.h>
#include<string.h>
void saisir(char * s)
{
  printf("Saisir une chaine\n");
  scanf("%s", s);
}

int main()
{
  char *s;

  printf("Entrer votre prenom. ");
  saisir(s);
  printf("Bonjour %s!\n", s);

  if (strcmp(s,"ddd")==0) printf("bizarre \n");

  return 0;
}