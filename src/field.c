#include "field.h"
#include <stdio.h>

#define N (25)
#define M (80)

#define DIED (' ')
#define LIVE ('O')

int init_field(char field[][M]) {
    float number;
    _Bool is_ok = 1;
    char sep;
    for (int row = 0; row < N && is_ok; row++) {
        for (int col = 0; col < M && is_ok; col++) {
            is_ok = (scanf("%f%c", &number, &sep) == 2);

            if (is_ok) {
                if ((col < M - 1 && sep != ' ')) {
                    is_ok = 0;
                } else if (col == M - 1 && sep != '\n') {
                    is_ok = 0;
                }

                if (is_ok && number == 1) {
                    field[row][col] = LIVE;
                } else if (is_ok && number == 0) {
                    field[row][col] = DIED;
                } else {
                    is_ok = 0;
                }
            }
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

void print_field(char field[][M]) {
    extern int printw(const char *fmt, ...);
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < M; ++col) {
            printw("%c", field[row][col]);
        }
        printw("\n");
    }
}
