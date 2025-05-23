#include "keyboard.h"

#include <ncursesw/ncurses.h> 

PlayerAction get_player_action() {
    int input = getch();
                        
    if (input != ERR) {
        switch (input) {
            case 'a':
            case 'A':
            case KEY_LEFT:
                return PLAYER_ACTION_MOVE_LEFT;
            
            case 'd':
            case 'D':
            case KEY_RIGHT:
                return PLAYER_ACTION_MOVE_RIGHT;
            
            case ' ':
                return PLAYER_ACTION_SHOOT;
            
            case 'q':
            case 'Q':
                return PLAYER_ACTION_QUIT;
            
            default:
                return PLAYER_ACTION_NONE;
        }
    }
    
    return PLAYER_ACTION_NONE;
}
