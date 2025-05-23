/**
 * Main.c
 * Created on May, 19th 2025
 * Author: Bruno Braga
*/
#define _DEFAULT_SOURCE
#include "game.h"
#include "cli-lib.h" 
#include <unistd.h>    
#include <stdio.h>

int main() {
    cli_init();     
    init_game();

    int current_state;
    while ((current_state = get_game_state()) == 1) {
        update_game();
        render_game(); 
        usleep(100 * 1000); 
    }

    
    if (current_state == 2) { 
        render_game();
        usleep(3000 * 1000); 
    } else if (current_state == 0) { 
        
    }
    
    cli_end();      
        return 0;
}
