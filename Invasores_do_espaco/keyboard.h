/**
 * Keyboard.h
 * Created on May, 19th 2025
 * Author: Glauco Santos
*/
#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef enum {
    PLAYER_ACTION_NONE,
    PLAYER_ACTION_MOVE_LEFT,
    PLAYER_ACTION_MOVE_RIGHT,
    PLAYER_ACTION_SHOOT,
    PLAYER_ACTION_QUIT
} PlayerAction;

PlayerAction get_player_action();

#endif