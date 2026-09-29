#ifndef MODTP2_H
#define MODTP2_H

extern int errors_count; //use

void showmat(unsigned char *,int); //use

unsigned char *create_grid(void); //use

void fill_ggrid(unsigned char *);

unsigned char *create_ggrid(void); //use

int isgridfull(unsigned char *grid); //use

int is_right_in_grid(int, int, unsigned char *, unsigned char *);

int place_in_grid(int, int, int, unsigned char *, unsigned char *); //use   0 if not the good 1 if right number in case

#endif