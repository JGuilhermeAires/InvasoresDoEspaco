#include "cli-lib.h"
#include <ncursesw/ncurses.h> 
#include <string.h>  
#include <stdio.h>   

void cli_init() {
    initscr();             
    cbreak();              
    noecho();              
    nodelay(stdscr, TRUE); 
    keypad(stdscr, TRUE);  
    curs_set(0);           
}

void cli_end() {
    curs_set(1);           
    endwin();              
}

void cli_clear_screen() {
    clear();              
}

void cli_draw_char(int x, int y, char c) {
    mvaddch(y, x, c);      
}

void cli_draw_string(int x, int y, const char* s) {
    mvprintw(y, x, "%s", s); 
}


void cli_draw_int(int x, int y, int value) {
    char buffer[20];
    sprintf(buffer, "%d", value);
    mvprintw(y, x, "%s", buffer);
}

void cli_flush() {
    refresh();             // Atualiza a tela física para mostrar todas as alterações feitas
}
