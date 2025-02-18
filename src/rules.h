#ifndef RULES_H
#define RULES_H

#include <stdbool.h>
#include "field.h"

#define N (25)
#define M (80)

void play_iteration(char field[][M]);
int count_neighbors(char field[][M], int y, int x);
int isgameover(char field[][M], char prev_field[][M]);

#endif
