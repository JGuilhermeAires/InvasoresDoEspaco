#include "cli.h"
#include <stdio.h>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#include <windows.h>

HANDLE hOut;
DWORD dwMode;

void cli_init() {
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void cli_deinit() {
    SetConsoleMode(hOut, dwMode);
}

void cli_cls() {
    printf("\x1b[2J");
}

void cli_goto(int x, int y) {
    printf("\x1b[%d;%dH", y + 1, x + 1); // (x,y) baseado em 1
}

void cli_flush() {
    fflush(stdout);
}
