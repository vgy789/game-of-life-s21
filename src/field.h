#ifndef FIELD_H
#define FIELD_H

#include <stdbool.h>

#define N (25)
#define M (80)

int init_field(char field[][M]);
void copy_field(char dst[][M], const char src[][M]);
void print_field(char field[][M]);

#endif
