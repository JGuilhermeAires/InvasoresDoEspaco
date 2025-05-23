#include <stdlib.h>
#include <stdio.h>   // Para sprintf
#include <string.h>  // Para strlen (NOVO)
#include "cli-lib.h"
#include "keyboard.h"
#include "game.h"

#define WIDTH 40
#define HEIGHT 20
#define MAX_BULLETS 10

// Definições para o jogador
#define PLAYER_STR "<^^>" // String do jogador: <^"^>
#define PLAYER_WIDTH 5       // Largura da string do jogador

// Definições para os inimigos (conforme sua imagem image_6236d0.png)
#define ENEMY_STR "['.']"      // String do inimigo (5 caracteres: [, ', ., ', ])
#define ENEMY_WIDTH 5        // Largura da string do inimigo
#define NUM_ENEMY_ROWS 3
#define ENEMIES_PER_ROW 5    // Alterado de 6 para 5
#define ENEMY_ROW_START_Y 2
#define ENEMY_COL_START_X 3  // Alterado de 1 para 3
#define ENEMY_X_SPACING (ENEMY_WIDTH + 2) // Espaçamento horizontal (ENEMY_WIDTH + 1 ou +2 é comum)
#define ENEMY_Y_SPACING 2

typedef struct {
    int x, y;
    int alive;
} Enemy;

typedef struct {
    int x, y;
    int active;
} Bullet;

typedef struct {
    int x, y;
} Player;

Enemy* enemies;
// enemy_count será calculado com base em NUM_ENEMY_ROWS e ENEMIES_PER_ROW
int enemy_count = NUM_ENEMY_ROWS * ENEMIES_PER_ROW; // Agora 3*5 = 15
Bullet bullets[MAX_BULLETS];
Player player;
int running = 1; // Estado do jogo: 1 = rodando, 0 = sair, 2 = vitória
int score = 0;

// NOVA FUNÇÃO para verificar se todos os inimigos foram derrotados
int all_enemies_defeated() {
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].alive) {
            return 0; // Pelo menos um inimigo está vivo
        }
    }
    return 1; // Todos os inimigos foram derrotados
}

void init_game() {
    // 'running' é definido como 1 no início (globalmente ou aqui)
    running = 1; // Garante que o jogo comece no estado ativo
    score = 0;   // Reseta o placar

    enemies = malloc(sizeof(Enemy) * enemy_count);
    int current_enemy_idx = 0;
    for (int row = 0; row < NUM_ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMIES_PER_ROW; col++) {
            if (current_enemy_idx < enemy_count) {
                enemies[current_enemy_idx].x = ENEMY_COL_START_X + col * ENEMY_X_SPACING;
                enemies[current_enemy_idx].y = ENEMY_ROW_START_Y + row * ENEMY_Y_SPACING;
                enemies[current_enemy_idx].alive = 1;
                current_enemy_idx++;
            }
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }

    player.x = (WIDTH - PLAYER_WIDTH) / 2;
    if (player.x < 1) player.x = 1;
    player.y = HEIGHT - 3;
}

void shoot_bullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].x = player.x + PLAYER_WIDTH / 2;
            bullets[i].y = player.y - 1;
            bullets[i].active = 1;
            break;
        }
    }
}

void move_bullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y--;
            if (bullets[i].y < 1) {
                bullets[i].active = 0;
            } else {
                for (int j = 0; j < enemy_count; j++) {
                    if (enemies[j].alive &&
                        bullets[i].y == enemies[j].y &&
                        bullets[i].x >= enemies[j].x &&
                        bullets[i].x < enemies[j].x + ENEMY_WIDTH) {
                        enemies[j].alive = 0;
                        bullets[i].active = 0;
                        score += 10;

                        // Verifica condição de vitória APÓS acertar um inimigo
                        if (all_enemies_defeated()) {
                            running = 2; // Mudar estado para Vitória
                        }
                        break;
                    }
                }
            }
        }
    }
}

void update_game() {
    // Não processa input se o jogo não estiver no estado ativo (running == 1)
    // Esta verificação será feita no loop principal em main.c antes de chamar update_game
    
    PlayerAction action = get_player_action();

    switch (action) {
        case PLAYER_ACTION_MOVE_LEFT:
            if (player.x > 1) {
                player.x--;
            }
            break;
        case PLAYER_ACTION_MOVE_RIGHT:
            if (player.x < WIDTH - 1 - PLAYER_WIDTH) {
                 player.x++;
            }
            break;
        case PLAYER_ACTION_SHOOT:
            shoot_bullet();
            break;
        case PLAYER_ACTION_QUIT:
            running = 0; // Mudar estado para Sair
            break;
        case PLAYER_ACTION_NONE:
            // Nenhuma ação
            break;
    }

    move_bullets(); // Movimenta as balas (que pode levar ao estado de vitória)
}

void render_game() {
    cli_clear_screen();

    if (running == 2) { // Estado de Vitória
        const char* win_message = "Parabens voce venceu";
        int msg_len = strlen(win_message);
        int msg_x = (WIDTH - msg_len) / 2;
        int msg_y = HEIGHT / 2;
        if (msg_x < 0) msg_x = 0; // Garante que não saia da tela à esquerda

        cli_draw_string(msg_x, msg_y, win_message);
        
        // Opcional: mostrar pontuação final também na tela de vitória
        char score_buffer[30];
        sprintf(score_buffer, "Pontuacao final: %d", score);
        int score_msg_len = strlen(score_buffer);
        int score_msg_x = (WIDTH - score_msg_len) / 2;
        if (score_msg_x < 0) score_msg_x = 0;
        cli_draw_string(score_msg_x, msg_y + 2, score_buffer); // 2 linhas abaixo da msg de vitoria

    } else { // Estado ativo (running == 1) ou preparo para sair (running == 0)
        // Desenha as bordas
        for (int x = 0; x < WIDTH; x++) {
            cli_draw_char(x, 0, '-');
            cli_draw_char(x, HEIGHT - 1, '-');
        }
        for (int y = 1; y < HEIGHT - 1; y++) {
            cli_draw_char(0, y, '|');
            cli_draw_char(WIDTH - 1, y, '|');
        }
        cli_draw_char(0, 0, '+');
        cli_draw_char(WIDTH - 1, 0, '+');
        cli_draw_char(0, HEIGHT - 1, '+');
        cli_draw_char(WIDTH - 1, HEIGHT - 1, '+');

        // Desenha os inimigos
        for (int i = 0; i < enemy_count; i++) {
            if (enemies[i].alive) {
                if (enemies[i].x >= 1 && (enemies[i].x + ENEMY_WIDTH) <= (WIDTH - 1) &&
                    enemies[i].y >= 1 && enemies[i].y < (HEIGHT - 1)) {
                     cli_draw_string(enemies[i].x, enemies[i].y, ENEMY_STR); // Usa o ENEMY_STR "['.']"
                }
            }
        }

        // Desenha as balas
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                if (bullets[i].x >= 1 && bullets[i].x < (WIDTH - 1) &&
                    bullets[i].y >= 1 && bullets[i].y < (HEIGHT - 1)) {
                    cli_draw_char(bullets[i].x, bullets[i].y, '^');
                }
            }
        }

        // Desenha o jogador
        if (player.x >= 1 && (player.x + PLAYER_WIDTH) <= (WIDTH - 1) &&
            player.y >=1 && player.y < (HEIGHT -1)){
            cli_draw_string(player.x, player.y, PLAYER_STR);
        }

        // Desenha o placar
        char score_buffer[30];
        sprintf(score_buffer, "Score: %d", score);
        cli_draw_string(1, HEIGHT, score_buffer);
    }
    cli_flush();
}

// Implementação da função declarada em game.h
int get_game_state() {
    return running;
}