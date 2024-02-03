// gcc game_of_life.c -lncurses

#include <ncurses.h>
#include <stdio.h>

#define N (25)
#define M (80)

#define DIED ' '
#define LIVE '#'

#define PRINT_DELAY 1000

void initncurses(void);
void printField(int field[][M]);

int main(void) {
    int field[N][M];
    for (int row = 0; row < N-1; ++row) {
        for (int col = 0; col < M-1; ++col) {
            field[row][col] = 0;
        }
    }

    field[4][4] = 1;
    field[5][4] = 1;
    field[4][5] = 1;
    
    initncurses();
    int key_pressed = -1;

    do {
        clear();
        printField(field);
        refresh();

        key_pressed = getch();
        if (key_pressed != -1) {

        }
    } while (key_pressed != 'q');

    endwin();
    return 0;
}

void initncurses(void) {
    initscr();
    // start_color();
    cbreak();
    timeout(PRINT_DELAY);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    // init_pair(1, COLOR_RED, COLOR_RED);
    // init_pair(2, COLOR_CYAN, COLOR_CYAN);
    // init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    // init_pair(4, COLOR_GREEN, COLOR_GREEN);
    // init_pair(5, -1, -1);
}

void printField(int field[][M]) {
    for (int row = 0; row < N-1; ++row) {
        for (int col = 0; col < M-1; ++col) {
            if (field[row][col] == 0) {
                printw("%c", DIED);
            } else {
                printw("%c", LIVE);
            }
        }
        printw("\n");
    }
}