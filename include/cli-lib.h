#ifndef CLI_LIB_H
#define CLI_LIB_H

void cli_init();
void cli_end();
void cli_clear_screen();
void cli_draw_char(int x, int y, char c);
void cli_draw_string(int x, int y, const char* s);
void cli_draw_int(int x, int y, int value);
void cli_flush();
#endif
