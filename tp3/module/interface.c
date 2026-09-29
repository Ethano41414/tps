#include "interface.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>



static struct termios terminal_old;
static int terminal_modified=0;

void interf_start() {
    struct termios terminal_new;
    if (!terminal_modified) {
        tcgetattr(STDIN_FILENO,&terminal_old);
        terminal_modified=1;
    }
    terminal_new=terminal_old;
    terminal_new.c_lflag&=~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&terminal_new);
}

void interf_end() {
    if (terminal_modified) {
        tcsetattr(STDIN_FILENO,TCSANOW,&terminal_old);
        terminal_modified=0;
    }
    printf("\033[0m");
    fflush(stdout);
}

void ctrl_c(int sig __attribute__((unused))) {
    interf_end();
    _exit(130);
}
void ctrl_z(int sig __attribute__((unused))) {
    interf_end();
    signal(SIGTSTP,SIG_DFL);
    raise(SIGTSTP);
}
void ctrl_cont(int sig __attribute__((unused))) {signal(SIGTSTP, ctrl_z);}

void interfinit() {
    signal(SIGINT,ctrl_c);
    signal(SIGTSTP,ctrl_z);
    signal(SIGCONT,ctrl_cont);
}

char interfget_input() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}


void interfcolor(int txt,int bg) {printf("\033[%d;%dm",30+txt,40+bg);}
void interfflip_screen() {printf("\033[2J\033[H");fflush(stdout);}
void interfwrite(int row,int col,const char *text) {
    printf("\033[%d;%dH%s",row,col,text);
    fflush(stdout);
}
void interfwrite_color(int row,int col,const char *text,int txt,int bg) {
    interfcolor(txt,bg);
    printf("\033[%d;%dH%s",row,col,text);
    fflush(stdout);
    interfcolor(7,0);
}
void interfclear_zone(int row,int col,int nb_rows,int nb_cols) {
    char spaces[nb_cols+1];
    memset(spaces,' ',nb_cols);
    spaces[nb_cols]='\0';
    for (int i=row;i<row+nb_rows;i++)
        interfwrite(i,col,spaces);
}
