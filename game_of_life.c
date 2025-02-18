#include <ncurses.h>
#include <stdio.h>
#include "field.h"
#include "rules.h"
#include "ui.h"

#define N (25)
#define M (80)

#define PRINT_DELAY (100)

int main(void) {
    char field[N][M];
    _Bool is_loaded = init_field(field);

    if (is_loaded) {
        start_game(field);
    } else {
        printf("The file is damaged!");
    }

    return 0;
}

void start_game(char field[][M]) {
    char prev_field[N][M];
    int key_pressed = -1;
    _Bool gameover = 0;
    int game_delay = PRINT_DELAY;

    init_ncurses();

    print_field(field);
    printw("\t\t\t\tPress any Key to Start...");
    pause_game(game_delay);

    while (key_pressed != 'q' && key_pressed != 'Q' && !gameover) {
        clear();
        print_field(field);
        refresh();

        copy_field(prev_field, field);
        play_iteration(field);

        gameover = isgameover(field, prev_field);

        key_pressed = getch();
        if (key_pressed != -1) {
            int speed = game_speed_control(game_delay, key_pressed);
            timeout(speed);
        }
    }

    if (gameover) {
        play_iteration(field);
        clear();
        print_field(field);

        printw("\t\t\t\tGAME OVER");
        pause_game(game_delay);
    }

    endwin();
}
