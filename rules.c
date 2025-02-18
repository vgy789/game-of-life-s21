#include "rules.h"

#define N (25)
#define M (80)

#define DIED (' ')
#define LIVE ('O')
#define DIED_TAG ('d')
#define LIVE_TAG ('a')

int isgameover(char field[][M], char prev_field[][M]) {
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

    _Bool is_out = (matches == N * M) || (live_count == 0);

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
            _Bool test1 = (field[(row + N) % N][(col + M) % M] == LIVE);
            _Bool test2 = (field[(row + N) % N][(col + M) % M] == DIED_TAG);

            count += (test1 || test2) && (!(y == row && x == col));
        }
    }
    return count;
}
