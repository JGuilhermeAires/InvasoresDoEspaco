#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "cli.h"

#define LARGURA 80
#define ALTURA 25
#define MAX_INIMIGOS 5

typedef struct {
    int x, y;
    int ativo;
} Inimigo;

typedef struct {
    int x, y;
    int ativo;
} Tiro;

int jogadorX = 35;
int jogadorY = ALTURA - 2;
int jogadorAnteriorX = 35;

Tiro tiro = {0, 0, 0};
Inimigo inimigos[MAX_INIMIGOS];

void inicializar_inimigos() {
    for (int i = 0; i < MAX_INIMIGOS; i++) {
        inimigos[i].x = i * 15 + 5;
        inimigos[i].y = 3;
        inimigos[i].ativo = 1;
    }
}

void apagar_jogador() {
    cli_goto(jogadorAnteriorX, jogadorY);
    printf("     ");
}

void desenhar_jogador() {
    cli_goto(jogadorX, jogadorY);
    printf("</^\\>");
}

void mover_jogador() {
    if (_kbhit()) {
        char tecla = _getch();
        jogadorAnteriorX = jogadorX;

        if (tecla == 75 && jogadorX > 0) jogadorX -= 2; // seta esquerda
        if (tecla == 77 && jogadorX < LARGURA - 5) jogadorX += 2; // seta direita
        if (tecla == ' ' && !tiro.ativo) {
            tiro.x = jogadorX + 2;
            tiro.y = jogadorY - 1;
            tiro.ativo = 1;
        }
    }
}

void atualizar_tiro() {
    if (tiro.ativo) {
        cli_goto(tiro.x, tiro.y);
        printf(" "); // apagar anterior
        tiro.y--;

        if (tiro.y < 0) {
            tiro.ativo = 0;
        } else {
            cli_goto(tiro.x, tiro.y);
            printf("^");
        }

        // verificar colisão
        for (int i = 0; i < MAX_INIMIGOS; i++) {
            if (inimigos[i].ativo &&
                tiro.x >= inimigos[i].x &&
                tiro.x <= inimigos[i].x + 6 &&
                tiro.y == inimigos[i].y) {
                inimigos[i].ativo = 0;
                tiro.ativo = 0;
                cli_goto(inimigos[i].x, inimigos[i].y);
                printf("       ");
            }
        }
    }
}

void desenhar_inimigos() {
    for (int i = 0; i < MAX_INIMIGOS; i++) {
        if (inimigos[i].ativo) {
            cli_goto(inimigos[i].x, inimigos[i].y);
            printf("/(\"..\")\\");
        }
    }
}


int main() {
    cli_init();
    cli_cls();
    inicializar_inimigos();

    while (1) {
        apagar_jogador();
        mover_jogador();
        desenhar_jogador();
        atualizar_tiro();
        desenhar_inimigos();
        cli_flush();
        Sleep(50);
    }

    cli_deinit();
    return 0;
}