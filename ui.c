#include "ui.h"
#include <ncurses.h>

#define PRINT_DELAY (100)

void init_ncurses(void) {
    initscr();
    timeout(PRINT_DELAY);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
}

void pause_game(int game_delay) {
    timeout(-1);
    getch();
    timeout(game_delay);
}

int game_speed_control(int game_delay, int key_pressed) {
    switch (key_pressed) {
        case '1':
            game_delay = 300;
            break;
        case '2':
            game_delay = 200;
            break;
        case '3':
            game_delay = 100;
            break;
        case '4':
            game_delay = 50;
            break;
        case ' ':
            pause_game(game_delay);
            break;
    }
    return game_delay;
}
