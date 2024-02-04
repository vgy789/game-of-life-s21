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

void init_ncurses(void);
void print_start();  // печатать интро игры
int init_field(char field[][M]);
void play_iteration(char field[][M]);
int count_neighbors(char field[][M], int y, int x);

void print_intro(void);

void print_field(char field[][M]);
void copy_field(char dst[][M], const char src[][M]);
int isgameover(char field[][M], char prev_field[][M]);

int main(void) {
    int key_pressed = -1;
    char field[N][M];
    char prev_field[N][M];
    int gameover = 0;

    int is_loaded = init_field(field);
    if (!is_loaded) key_pressed = 'q';

    init_ncurses();
    print_intro();
    getch();

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
        printw("\t\t\t\tGAME OVER");
        getch();
    }

    endwin();
    return 0;
}

void print_intro(void) {
    printw("  G)gggg                                O)oooo   f)FFF    L)       ##  f)FFF         \n");
    printw(" G)                                    O)    oo f)        L)          f)             \n");
    printw("G)  ggg  a)AAAA   m)MM MMM  e)EEEEE    O)    oo f)FFF     L)       i) f)FFF  e)EEEEE \n");
    printw("G)    gg  a)AAA  m)  MM  MM e)EEEE     O)    oo f)        L)       i) f)     e)EEEE  \n");
    printw(" G)   gg a)   A  m)  MM  MM e)         O)    oo f)        L)       i) f)     e)      \n");
    printw("  G)ggg   a)AAAA m)      MM  e)EEEE     O)oooo  f)        L)llllll i) f)      e)EEEE \n\n");

    printw("\t\t\t\tPress Any Key... ");
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

    int number;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((scanf("%d", &number) != 1) || (number != 1 && number != 0)) {
                printf("The file is damaged");
                return 0;
            } else if (number == 1) {
                field[i][j] = LIVE;
            }
        }
    }
    if (freopen("/dev/tty", "r", stdin))
        ;
    return 1;
}

void copy_field(char dst[][M], const char src[][M]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            dst[row][col] = src[row][col];
        }
    }
}