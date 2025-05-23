#include "keyboard.h"
// #include <conio.h>   // REMOVA ESTA LINHA (específica do Windows)
#include <ncursesw/ncurses.h> // Note o 'ncursesw/'  // ADICIONE ESTA LINHA (para getch(), ERR, KEY_LEFT, KEY_RIGHT, etc.)

PlayerAction get_player_action() {
    int input = getch(); // getch() do ncurses.
                         // Se nodelay(stdscr, TRUE) foi chamado em cli_init(),
                         // getch() não será bloqueante.

    // Opcional: Se você perceber que múltiplas teclas pressionadas rapidamente
    // estão sendo processadas de uma vez, você pode querer limpar o buffer de entrada.
    // flushinp(); // Descomente se necessário, mas use com cautela.

    if (input != ERR) { // ERR é retornado por getch() se nenhuma tecla foi pressionada (no modo não bloqueante)
        switch (input) {
            case 'a':
            case 'A':
            case KEY_LEFT: // KEY_LEFT é uma constante do ncurses para a tecla da seta esquerda
                return PLAYER_ACTION_MOVE_LEFT;
            
            case 'd':
            case 'D':
            case KEY_RIGHT: // KEY_RIGHT é uma constante do ncurses para a tecla da seta direita
                return PLAYER_ACTION_MOVE_RIGHT;
            
            case ' ': // Espaço para atirar
                return PLAYER_ACTION_SHOOT;
            
            case 'q':
            case 'Q':
                return PLAYER_ACTION_QUIT;
            
            // Você pode adicionar outras teclas aqui, se desejar (ex: KEY_UP, KEY_DOWN)
            // case KEY_UP:
            //     // alguma ação
            //     break;

            default:
                return PLAYER_ACTION_NONE; // Ou alguma outra ação padrão se uma tecla não mapeada for pressionada
        }
    }
    
    return PLAYER_ACTION_NONE; // Nenhuma tecla relevante pressionada
}
