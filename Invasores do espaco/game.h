#ifndef GAME_H
#define GAME_H

void init_game();
void update_game();
void render_game();
int get_game_state(); // Retorna o estado atual do jogo (0: Sair, 1: Rodando, 2: Vitória)

#endif