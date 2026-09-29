#ifndef INTERFACE_H
#define INTERFACE_H

void interf_start(void);
void interf_end(void);
void ctrl_c(int);
void ctrl_z(int);
void ctrl_cont(int);

void interfinit(void);

char interfget_input(void);

void interfcolor(int txt,int bg);
void interfflip_screen(void);
void interfwrite(int row,int col,const char *text);
void interfwrite_color(int row,int col,const char *text,int txt,int bg);
void interfclear_zone(int row,int col,int nb_rows,int nb_cols);

#endif

