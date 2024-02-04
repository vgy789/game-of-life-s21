// gcc game_of_life.c -lncurses
#include <ncurses.h>
#include <stdio.h>
#include <ctype.h>

// ЛОГИКА ДО КОНЦА НЕ ДОДЕЛАНА Я ПОШЁЛ СПАТЬ

#define N (25)
#define M (80)

#define PRINT_DELAY 2000

#define DIED (' ')
#define DIED_TAG ('D')
#define LIVE ('O')
#define LIVE_TAG ('L')

void initncurses(void);
void print_field(char field[][M]);
int count_neighbors(char field[][M], int y, int x);
int init_field(char field[][M]);
void play_iteration(char field[][M]);

int main(void) {
    char field[N][M];
    if (init_field(field)) {
        initncurses();
        int key_pressed = -1;

        do {
            clear();
            print_field(field);
            refresh();
            play_iteration(field);



            key_pressed = getch();
            if (key_pressed != -1) {
                // управление скоростью
            }
            
        } while (key_pressed != 'q');

        endwin();
        return 0; 
    }   else {
        return 1;
    }
}

void play_iteration(char field[][M]) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            int neighbors = count_neighbors(field, row, col);
            if (field[row][col] == DIED && neighbors == 3) {
                field[row][col] = LIVE_TAG;
            }

            if (field[row][col] == LIVE && (neighbors != 2 && neighbors != 3)) {
                field[row][col] = DIED_TAG;
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

            count += test1 || test2 && (!(y == row && x == col));
        }
    }
    return count;
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
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (is_ok != 0 && j == 79 && i < 24) {
                if ((scanf("%d%c", &number, &c) != 2 || c != '\n') || (number != 1 && number != 0)) {
                is_ok = 0;
                printf("The file is damaged. Error type: there is something after the last symbol in a string");
                }   else if (number == 1){
                        field[i][j] = LIVE;
                    }
            }   
            else if (is_ok != 0 && j == 79 && i == 24) {
                if ((scanf("%d%c", &number, &c) != 1 || (number != 1 && number != 0))) {
                    is_ok = 0;
                    printf("The file is damaged. Error type: there is something after the last symbol in a string");
                }    
            }
            else if(is_ok != 0) {
                if ((scanf("%d", &number) != 1) || (number != 1 && number != 0)) {
                    is_ok = 0;
                    printf("The file is damaged. Error type: forbbidden symbol");
                }   else if (number == 1) {
                        field[i][j] = LIVE;
                    }
            }
            counter++;
            }
        }
    if (is_ok != 0 && counter != 2000) {
        is_ok = 0;
        printf("The file is damaged. Error type: the file contains more or less symbols than needs");
    }
    freopen("/dev/tty", "r", stdin);
    return is_ok;
}
