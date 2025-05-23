#include "cli-lib.h"
#include <ncursesw/ncurses.h> // Note o 'ncursesw/'// Principal include para ncurses
#include <string.h>  // Para strlen, se necessário
#include <stdio.h>   // Para sprintf, se usado para cli_draw_int

void cli_init() {
    initscr();             // Inicia o modo ncurses
    cbreak();              // Desabilita buffer de linha, torna caracteres disponíveis imediatamente
    noecho();              // Não mostra os caracteres digitados na tela
    nodelay(stdscr, TRUE); // Configura getch() para não ser bloqueante
    keypad(stdscr, TRUE);  // Permite a leitura de teclas especiais (Setas, F1, etc.)
    curs_set(0);           // Torna o cursor invisível
}

void cli_end() {
    curs_set(1);           // Torna o cursor visível novamente (opcional)
    endwin();              // Restaura as configurações normais do terminal
}

void cli_clear_screen() {
    clear();               // Função do ncurses para limpar a tela
}

void cli_draw_char(int x, int y, char c) {
    mvaddch(y, x, c);      // Move o cursor para (y,x) e desenha o caractere
}

void cli_draw_string(int x, int y, const char* s) {
    mvprintw(y, x, "%s", s); // Move o cursor para (y,x) e imprime a string
}

// Exemplo de como cli_draw_int poderia ser
void cli_draw_int(int x, int y, int value) {
    char buffer[20];
    sprintf(buffer, "%d", value);
    mvprintw(y, x, "%s", buffer);
}

void cli_flush() {
    refresh();             // Atualiza a tela física para mostrar todas as alterações feitas
}