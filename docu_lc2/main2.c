/*ce programme prend en comptre les commentaires en /* globaux mais pas ceux dans des fonctions*/
#include "module/ethanostr.h"
#include "module/mod.h"
#include <sys/stat.h>
#include <time.h>

int keepinlinecomments=0;
char path[500]="./returnedtxt.c";

enum category {
    GLOB,
    COMMENT,
    FUNCTION,
    TYPEDEFSTRUCTENUMUNION,
};

void txt3ins(char *s, char *t1, char *t2, char *t3) {
    ull z1=basicstrlen(t1),z2=basicstrlen(t2),z3=basicstrlen(t3);
    ull size=z1+z2+z3;
    for (ull i=0;i<=size;i++) {
        if (i<z1) s[i]=t1[i];
        else if (z1<=i&&i-z1<z2) s[i]=t2[i-z1];
        else s[i]=t3[i-z1-z2];
    }
}

void convertpathintoname(char *txt, char *path) {
    ull index=0;
    for (ull i=0;path[i]!='\0';i++) {
        if (path[i]=='/')
            index=i+1;
    }
    ull i=0;
    while (path[index+i]!='\0') {
        txt[i]=path[index+i];
        i++;
    }
    txt[i]='\0';
}

void get_authors(char *txt, liste_t *list) {
    cellule_t *cell=list->tete;
    ull index,i=0;
    if ((index=basicstrindex(cell->ligne,"@author"))!=INF) {
        char *p=cell->ligne;
        p+=index+7;
        while (p[i]) {
            txt[i]=p[i];
            i++;
        }
        txt[i]='\0';
    } else
        txt[0]='\0';
}


liste_t *geto(FILE *stream) {
    liste_t *list=malloc(sizeof(liste_t));
    list->tete=NULL;
    list->fin=&list->tete;
    int function_accol_count;
    char line[1000],commentsegment[800];
    enum category categ=GLOB;
    ull linsize,indexinlinecommentslash;
    int first=1;
    while (agets(line,120,stream)!=NULL) {
        if (first) {
            first=!first;
            if (basicstrin(line,"/*")) {
                if (basicstrin(line,"*/")) {append(list,"|<startblock>|");append(list,line);}
                else {
                    append(list,"|<startblock>|");
                    append(list,line);
                    while (agets(line,120,stream)&&!basicstrin(line,"*/"))
                        append(list,line);
                    append(list,line);
                }
            }
        }
        linsize=basicstrlen(line);
        commentsegment[0]='\0';
        
        indexinlinecommentslash=basicstrindex(line,"//");                                //<------/----| gère les commentaires inline (qui utilisent //)
        if ((indexinlinecommentslash!=INF)&&keepinlinecomments&&categ!=COMMENT) {        //<-----/
            basicstrsegmenti(commentsegment,line,indexinlinecommentslash,linsize);       //<----/
            line[indexinlinecommentslash]='\0';                                          //<---/
            linsize=basicstrlen(line);                                                   //<--/
        }
        if (categ==GLOB) {
            if (basicstrin(line,"#"))
                append(list,line);
            else if (basicstrin(line,"typedef")||basicstrin(line,"union")||basicstrin(line,"enum")||basicstrin(line,"struct")) {
                if (basicstrin(line,"{") || !basicstrin(line,";")) {
                    categ=TYPEDEFSTRUCTENUMUNION;
                    append(list,line);
                } else {
                    append(list,"|<globdecla>|");
                    append(list,line);
                }
            } else if ((basicstrin(line,"("))&&(basicstrin(line,")"))) {
                categ=FUNCTION;
                function_accol_count=(int)basicstrcount(line,"{")-(int)basicstrcount(line,"}");
            } else if (basicstrin(line,"/*")) {
                categ=COMMENT;
                append(list,line);
            } else if (basicstrin(line,"typedef")||basicstrin(line,"union")||basicstrin(line,"enum")||basicstrin(line,"struct")) {
                categ=TYPEDEFSTRUCTENUMUNION;
                append(list,line);
            } else if (line[0]!=' '&&line[0]!='\t'&&basicstrcount(line,";")&&categ!=FUNCTION) {
                append(list,"|<globdecla>|");
                append(list,line);
            }
        } else if (categ==TYPEDEFSTRUCTENUMUNION) {
            append(list,line);
            if (basicstrin(line,"}")&&basicstrin(line,";")) {
                categ=GLOB;
            }
        } else if (categ==COMMENT) {
            append(list,line);
            if (basicstrin(line,"*/")) {
                categ=GLOB;
            }
        } else if (categ==FUNCTION) {
            function_accol_count+=(int)basicstrcount(line,"{")-(int)basicstrcount(line,"}");
            if (function_accol_count==0) {
                categ=GLOB;
            }
        }
        if (!basicstreq(commentsegment,"")&&!(categ==FUNCTION)) {  //<-----/---|ajouter le commentaire inline après la ligne si elle à été gardée
            if (indexinlinecommentslash==0)                        //<----/
                append(list,"|<globinline>|");                     //<---/
            append(list,commentsegment);                           //<--/
        }
    }
    return list;
}




liste_t *stream_get_list() {
    liste_t *list=geto(stdin);
    return list;
}

liste_t *file_get_list(char *path) {
    FILE *f=fopen(path,"r");
    if (f==NULL) return NULL;
    liste_t *list=geto(f);
    fclose(f);
    return list;
}

int write_in_file(liste_t *list, char *pth) {
    struct stat st;
    char datetxt[64]="unknown";
    if (stat(pth,&st)==0) {
        struct tm *t=localtime(&st.st_mtime);
        strftime(datetxt,sizeof datetxt,"%d/%m/%Y %H:%M:%S",t);
    }
    FILE *f=fopen(path,"w+");
    cellule_t *lin=list->tete;
    liste_t *fileinfo=init_void_list();
    liste_t *diezel=init_void_list();
    liste_t *varsl=init_void_list();
    liste_t *otherl=init_void_list();

    char temporaryconcattext[800],tmptxt[200];
    while (lin) {
        if (basicstreq(lin->ligne,"|<startblock>|")) {
            while (!basicstrin(lin->ligne,"*/")) {
                if (basicstrin(lin->ligne,"@author")) append(fileinfo,lin->ligne);
                lin=lin->suiv;
            }
        } else if (basicstreq(lin->ligne,"|<globdecla>|")) {
            lin=lin->suiv;
            append(varsl,lin->ligne);
        } else if (basicstreq(lin->ligne,"|<globinline>|")) {
            lin=lin->suiv;
            append(otherl,lin->ligne);
        } else if (basicstrin(lin->ligne,"#")) {
            if (basicstrin(lin->ligne,"#include"))
                addfirst(diezel,lin->ligne);
            else
                append(diezel,lin->ligne);
        } else {
            append(otherl,lin->ligne);
        }
        lin=lin->suiv;
    }

    append(fileinfo,"/*------------------------*/");
    convertpathintoname(tmptxt,pth);
    txt3ins(temporaryconcattext,"/*  File name: ",tmptxt,"  */");
    append(fileinfo,temporaryconcattext);
    txt3ins(temporaryconcattext,"/*  Last modification date: ",datetxt,"  */");
    append(fileinfo,temporaryconcattext);
    get_authors(tmptxt,fileinfo);
    if (tmptxt[0]!='\0') {
        cellule_t *p=fileinfo->tete->suiv;
        free(fileinfo->tete->ligne);
        free(fileinfo->tete);
        fileinfo->tete=p;
    }
    txt3ins(temporaryconcattext,"/*  Authors: ",tmptxt,"  */");
    append(fileinfo,temporaryconcattext);
    append(fileinfo,"/*------------------------*/\n");

    lin=fileinfo->tete;
    while (lin) {
        fprintf(f,"%s\n",lin->ligne);
        lin=lin->suiv;
    }
    fprintf(f,"\n");
    lin=diezel->tete;
    while (lin) {
        if (basicstrin(lin->ligne,"#include")) {
            fprintf(f,"%s\n",lin->ligne);
        } else {
            fprintf(f,"\n%s\n",lin->ligne);
        }
        lin=lin->suiv;
    }
    fprintf(f,"\n\n");
    lin=varsl->tete;
    while (lin) {
        fprintf(f,"%s\n",lin->ligne);
        lin=lin->suiv;
    }
    fprintf(f,"\n");
    lin=otherl->tete;
    while (lin) {
        fprintf(f,"%s\n",lin->ligne);
        lin=lin->suiv;
    }
    
    return 1;
}




int main(int argc, char **argv) {
    ull i;
    liste_t *list;
    if (argc>1) {
        if (basicstrin(argv[1],"help")) {
            printf("main2 in_file out_file options\n\noptions keep_inline_comment  outputname=   | use - to multiply options\n\nexemple:  main2 ./source.c ./source_h.c o-keep_inline_comment\nuse o- to specify if it is the options bloc\n\n");
        } else {
            if (argc>2&&basicstrin(argv[2],"o-")) {
                if (basicstrin(argv[2],"keep_inline_comment"))
                    keepinlinecomments=1;
                if ((i=basicstrindex(argv[2],"output_name="))!=INF) {
                    basicstrsegmenti(path,argv[2],i+12,basicstrlen(argv[2]));
                }
            }
            list=file_get_list(argv[1]);
            write_in_file(list,argv[1]);
        }
    } else
        list=stream_get_list();
    return 0;
}


