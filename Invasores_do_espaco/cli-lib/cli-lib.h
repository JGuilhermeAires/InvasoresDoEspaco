#ifndef CLI_LIB_H
#define CLI_LIB_H

void cli_init();      // Para inicializar o ncurses
void cli_end();       // Para finalizar o ncurses
void cli_clear_screen();
void cli_draw_char(int x, int y, char c);
void cli_draw_string(int x, int y, const char* s);
void cli_draw_int(int x, int y, int value); // Você pode implementar isso com sprintf e cli_draw_string
void cli_flush();     // Para atualizar a tela do ncurses

#endif