/**
 * game.c
 * Created on May, 19th 2025
 * Author: Glauco Santos
*/
#include <stdlib.h>
#include <stdio.h>   
#include "cli-lib.h"
#include "keyboard.h"
#include "game.h"

#define WIDTH 40
#define HEIGHT 20
#define MAX_BULLETS 10

#define PLAYER_STR "<^^>" 
#define PLAYER_WIDTH 5       

#define ENEMY_STR "['.']"      
#define ENEMY_WIDTH 5        
#define NUM_ENEMY_ROWS 3
#define ENEMIES_PER_ROW 5    
#define ENEMY_ROW_START_Y 2
#define ENEMY_COL_START_X 3  
#define ENEMY_X_SPACING (ENEMY_WIDTH + 2) 
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
int enemy_count = NUM_ENEMY_ROWS * ENEMIES_PER_ROW; 
Bullet bullets[MAX_BULLETS];
Player player;
int running = 1; 
int score = 0;

int all_enemies_defeated() {
    for (int i = 0; i < enemy_count; i++) {
        if (enemies[i].alive) {
            return 0; 
        }
    }
    return 1; 
}

void init_game() {

    running = 1; 
    score = 0;   

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

                        if (all_enemies_defeated()) {
                            running = 2; 
                        }
                        break;
                    }
                }
            }
        }
    }
}

void update_game() {
    
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
            running = 0; 
            break;
        case PLAYER_ACTION_NONE:
            
            break;
    }

    move_bullets(); 
}

void render_game() {
    cli_clear_screen();

    if (running == 2) { 
        const char* win_message = "Parabens voce venceu";
        int msg_len = strlen(win_message);
        int msg_x = (WIDTH - msg_len) / 2;
        int msg_y = HEIGHT / 2;
        if (msg_x < 0) msg_x = 0; 

        cli_draw_string(msg_x, msg_y, win_message);
        
        char score_buffer[30];
        sprintf(score_buffer, "Pontuacao final: %d", score);
        int score_msg_len = strlen(score_buffer);
        int score_msg_x = (WIDTH - score_msg_len) / 2;
        if (score_msg_x < 0) score_msg_x = 0;
        cli_draw_string(score_msg_x, msg_y + 2, score_buffer); 

    } else { 
    
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

        for (int i = 0; i < enemy_count; i++) {
            if (enemies[i].alive) {
                if (enemies[i].x >= 1 && (enemies[i].x + ENEMY_WIDTH) <= (WIDTH - 1) &&
                    enemies[i].y >= 1 && enemies[i].y < (HEIGHT - 1)) {
                     cli_draw_string(enemies[i].x, enemies[i].y, ENEMY_STR); 
                }
            }
        }

        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                if (bullets[i].x >= 1 && bullets[i].x < (WIDTH - 1) &&
                    bullets[i].y >= 1 && bullets[i].y < (HEIGHT - 1)) {
                    cli_draw_char(bullets[i].x, bullets[i].y, '^');
                }
            }
        }

        if (player.x >= 1 && (player.x + PLAYER_WIDTH) <= (WIDTH - 1) &&
            player.y >=1 && player.y < (HEIGHT -1)){
            cli_draw_string(player.x, player.y, PLAYER_STR);
        }

        char score_buffer[30];
        sprintf(score_buffer, "Score: %d", score);
        cli_draw_string(1, HEIGHT, score_buffer);
    }
    cli_flush();
}

int get_game_state() {
    return running;
}