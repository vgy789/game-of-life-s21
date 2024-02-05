// gcc game_of_life.c -lncurses
#include <ncurses.h>
#include <stdio.h>

// ЛОГИКА ДО КОНЦА НЕ ДОДЕЛАНА Я ПОШЁЛ СПАТЬ

#define N (25)
#define M (80)

#define PRINT_DELAY 300

#define DIED (' ')
#define LIVE ('O')
#define DIED_TAG ('d')
#define LIVE_TAG ('a')

#define MSG_ANYKEY ("\t\t\t\tPress any Key to Start...")
#define MSG_GAMEOVER ("\t\t\t\tGAME OVER")

int init_field(char field[][M]);
void play_game(char field[][M]);

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
        play_game(field);
    }

    return 0;
}

void play_game(char field[][M]) {
    char prev_field[N][M];
    int key_pressed = -1;
    int gameover = 0;

    init_ncurses();

    print_field(field);
    printw(MSG_ANYKEY);
    pause_game();

    while (key_pressed != 'q' && key_pressed != 'Q' && !gameover) {
        clear();
        print_field(field);
        refresh();

        copy_field(prev_field, field);
        play_iteration(field);

        gameover = isgameover(field, prev_field);

        key_pressed = getch();
        if (key_pressed != -1) {
            // управление скоростью
        }
    }

    if (gameover) {
        play_iteration(field);
        clear();
        print_field(field);

        printw(MSG_GAMEOVER);
        printw("\n");
        printw(MSG_ANYKEY);
        pause_game();
    }

    endwin();
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

    float number;
    int is_ok = 1;
    char sep;
    for (int row = 0; row < N && is_ok; row++) {
        for (int col = 0; col < M && is_ok; col++) {
            // is_ok = (scanf("%f%c", &number, &sep) == 2);

            // if (is_ok) {
            //     if ((col < M-1 && sep != ' ')) {
            //         is_ok = 0;
            //     } else if (col == M-1 && sep != '\n') {
            //         is_ok = 0;
            //     }
           
            //     if (is_ok && number == 1) {
            //         field[row][col] = LIVE;
            //     } else if (is_ok && number == 0) {
            //         field[row][col] = DIED;
            //     } else {
            //         is_ok = 0;
            //     }
            // }
        }
    }

    if (is_ok) {
        is_ok = (freopen("/dev/tty", "r", stdin) != NULL);
    }
    return is_ok;
}

void copy_field(char dst[][M], const char src[][M]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            dst[row][col] = src[row][col];
        }
    }
}