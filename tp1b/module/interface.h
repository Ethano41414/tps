#ifndef INTERFACE_H
#define INTERFACE_H

/*
name: interf_start
description: start cmd mode non cannon
entry: none
output: none
*/
void interf_start(void);
/*
name: interf_end
description: end cmd mode non cannon
entry: none
output: none
*/
void interf_end(void);
/*
name: ctrl_c
description: reaction to ctrl+c
entry: none
output: none
*/
void ctrl_c(int);
/*
name: ctrl_z
description: reaction to ctrl+z
entry: none
output: none
*/
void ctrl_z(int);
/*
name: ctrl_c
description: ?
entry: none
output: none
*/
void ctrl_cont(int);

/*
name: interfinit
description: initialise graphics
entry: none
output: none
*/
void interfinit(void);

/*
name: interfget_input
description: get the first input of stdin
entry: none
output: input
*/
char interfget_input(void);

/*
name: interfcolor
description: change text and background colors
entry: txt: text color , bg: background color
output: none
*/
void interfcolor(int txt,int bg);

/*
name: interfflip_screen
description: clear the screen without erase text
entry: none
output: none
*/
void interfflip_screen(void);

/*
name: interfwrite
description: place string text at position (row, col)
entry: row: row , col: col , text: text
output: none
*/
void interfwrite(int row,int col,const char *text);

/*
name: interfwrite_color
description: place string text with colors txt&bg at position (row, col)
entry: row: row , col: col , text: string var , txt: text color , bg: background color
output: none
*/
void interfwrite_color(int row,int col,const char *text,int txt,int bg);

/*
name: interfclear_zone
description: clear zone start at (row, col) through (nb_rows, nb_cols)
entry: row: row , col: col , nb_rows , nb_cols , text: string var , txt: text color , bg: background color
output: none
*/
void interfclear_zone(int row,int col,int nb_rows,int nb_cols);

#endif

