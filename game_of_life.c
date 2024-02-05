#include <ncurses.h>
#include <stdio.h>

#define N (25)
#define M (80)

#define PRINT_DELAY (50)

#define DIED (' ')
#define LIVE ('O')
#define DIED_TAG ('d')
#define LIVE_TAG ('a')

int init_field(char field[][M]);
void start_game(char field[][M]);

void init_ncurses(void);
void print_field(char field[][M]);
void pause_game(void);

int count_neighbors(char field[][M], int y, int x);
void play_iteration(char field[][M]);

void print_field(char field[][M]);
void copy_field(char dst[][M], const char src[][M]);
int isgameover(char field[][M], char prev_field[][M]);

int main(void) {
    char field[N][M];
    int is_loaded = init_field(field);

    if (is_loaded) {
        start_game(field);
    }

    return 0;
}

void pause_game(void) {
    timeout(-1);
    getch();
    timeout(PRINT_DELAY);
}

int isgameover(char field[][M], char prev_field[][M]) {
    int is_out = 0;
    int matches = 0, live_count = 0;
    char next_field[N][M];
    copy_field(next_field, field);
    play_iteration(next_field);

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            live_count += (field[row][col] == LIVE);
            matches += (prev_field[row][col] == next_field[row][col]);
        }
    }

    is_out = (matches == N * M) || (live_count == 0);

    return is_out;
}

void play_iteration(char field[][M]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            int neighbors = count_neighbors(field, row, col);
            if (field[row][col] == LIVE && (neighbors == 2 || neighbors == 3)) {
                field[row][col] = LIVE;
            } else if (field[row][col] == DIED && neighbors == 3) {
                field[row][col] = LIVE_TAG;
            } else if ((field[row][col] == LIVE) && (neighbors < 2 || neighbors > 3)) {
                field[row][col] = DIED_TAG;
            } else {
                field[row][col] = DIED;
            }
        }
    }

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            if (field[row][col] == DIED_TAG) {
                field[row][col] = DIED;
            } else if (field[row][col] == LIVE_TAG) {
                field[row][col] = LIVE;
            }
        }
    }
}

int count_neighbors(char field[][M], int y, int x) {
    int count = 0;
    for (int row = y - 1; row <= y + 1; ++row) {
        for (int col = x - 1; col <= x + 1; ++col) {
            _Bool test1 = field[(row + N) % N][(col + M) % M] == LIVE;
            _Bool test2 = field[(row + N) % N][(col + M) % M] == DIED_TAG;

            count += (test1 || test2) && (!(y == row && x == col));
        }
    }
    return count;
}

void init_ncurses(void) {
    initscr();
    timeout(PRINT_DELAY);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
}

void print_field(char field[][M]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            printw("%c", field[row][col]);
        }
        printw("\n");
    }
}

int init_field(char field[][M]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            field[row][col] = DIED;
        }
    }

    int number, counter = 0, is_ok = 1;
    char c;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < M; col++) {
            if (is_ok != 0 && col == 79 && row < 24) {
                if ((scanf("%d%c", &number, &c) != 2 || c != '\n') || (number != 1 && number != 0)) {
                    is_ok = 0;
                    printf(
                        "The file is damaged. Error type: there is something after the last symbol in a "
                        "string");
                } else if (number == 1) {
                    field[row][col] = LIVE;
                }
            } else if (is_ok != 0 && col == 79 && row == 24) {
                if ((scanf("%d%c", &number, &c) != 1 || (number != 1 && number != 0))) {
                    is_ok = 0;
                    printf(
                        "The file is damaged. Error type: there is something after the last symbol in a "
                        "string");
                }
            } else if (is_ok != 0) {
                if ((scanf("%d", &number) != 1) || (number != 1 && number != 0)) {
                    is_ok = 0;
                    printf("The file is damaged. Error type: forbbidden symbol");
                } else if (number == 1) {
                    field[row][col] = LIVE;
                }
            }
            counter++;
        }
    }
    if (is_ok != 0 && counter != 2000) {
        is_ok = 0;
        printf("The file is damaged. Error type: the file contains more or less symbols than needs");
    }

    is_ok = (freopen("/dev/tty", "r", stdin) != NULL);

    return is_ok;
}

// int init_field(char field[][M]) {
//     for (int row = 0; row < N; ++row) {
//         for (int col = 0; col < M; ++col) {
//             field[row][col] = DIED;
//         }
//     }

//     int cell = 0;
//     int cell_couner = 0;
//     int is_ok = 1;

//     int err = 0;
//     char sep;
//     for (int row = 0; (row < N); row++) {
//         for (int col = 0; (col < M); col++) {
//             is_ok = (scanf("%d%c", &cell, &sep) == 2);
//             ++cell_couner;

//             if (is_ok && !(col < M-1 && sep == ' ')) {
//                is_ok = 0;
//                err = -1;
//             } else if (is_ok && !(col == M-1 && sep == '\n')) {
//                is_ok = 0;
//                err = -2;
//             }

//             if (is_ok) {
//                 field[row][col] = cell;
//             }
//         }
//     }

//     if (is_ok) {
//        is_ok = (getch() == EOF);
//     }
//     if (is_ok) {
//         is_ok = (freopen("/dev/tty", "r", stdin) != NULL);
//     }
//     if (!is_ok) {
//         err = -10;
//     }
//     printf("%d", err);
//     return err;
// }

void copy_field(char dst[][M], const char src[][M]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            dst[row][col] = src[row][col];
        }
    }
}

void start_game(char field[][M]) {
    char prev_field[N][M];
    int key_pressed = -1;
    int gameover = 0;

    init_ncurses();

    print_field(field);
    printw("\t\t\t\tPress any Key to Start...");
    pause_game();

    while (key_pressed != 'q' && key_pressed != 'Q' && !gameover) {
        clear();
        print_field(field);
        refresh();

        copy_field(prev_field, field);
        play_iteration(field);

        //gameover = isgameover(field, prev_field);

        key_pressed = getch();
        if (key_pressed != -1) {
            // управление скоростью
        }
    }

    if (gameover) {
        play_iteration(field);
        clear();
        print_field(field);

        printw("\t\t\t\tGAME OVER");
        pause_game();
    }

    endwin();
}