// gcc game_of_life.c -lncurses
#include <ncurses.h>
#include <stdio.h>

#define N (25)
#define M (80)

#define DIED ('Z')
#define LIVE ('#')

#define PRINT_DELAY (1000)

void initncurses(void);
void printField(int field[][M]);

void play_life(int field[][M]);
int count_neighbors(int field[][M], int y, int x);

int main(void) {
    int field[N][M];
    for (int row = 0; row < N-1; ++row) {
        for (int col = 0; col < M-1; ++col) {
            field[row][col] = 0;
        }
    }

    field[1][1] = 1;
    field[2][1] = 1;
    field[1][2] = 1;

    // считывание данных из файла через циклы и scanf.

    initncurses();
    int key_pressed = -1;

    do {
        clear();
        printField(field);
        printw("\n\n>>>%d", count_neighbors(field, 2, 2));
        refresh();

        play_life(field);


        key_pressed = getch();
        if (key_pressed != -1) {
            // управление, регулирование скорости по нажатию, пауза.
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

int count_neighbors(int field[][M], int y, int x) {
    int row = y-1;
    int col = x-1;
    int count = 0;

    for (int i = 0; i< y+1; i++) {
        for (int j = 0; x+1; j++) {
           printw("1 ");
        }
        printw("\n"); 
    }


    printw("row>>%d", row);
    return count;
}

void play_life(int field[][M]) {
    for (int row = 0; row < N-1; ++row) {
        for (int col = 0; col < M-1; ++col) {

        }
    }
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
