#ifndef HELLO_FREERTOS_H
#define HELLO_FREERTOS_H

#include <stdbool.h>

// Returns c with its case swapped if it is an ASCII letter, otherwise c unchanged.
char switchCase(char c);

// Advances the blink counter and flips *on, except when *count is a multiple of 11
void toggle(int *count, bool *on);

#endif
