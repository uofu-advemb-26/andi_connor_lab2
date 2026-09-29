// Hardware-independent logic pulled out of hello_freertos.c so it can be unit tested
#include "hello_freertos.h"

char switchCase(char c){
    // 'a' - 'A' == 32 in ASCII, so adding/subtracting 32 flips the case.
    if (c <= 'z' && c >= 'a')
        return (c - 32);
    else if (c >= 'A' && c <= 'Z')
        return (c + 32);
    else
        return c;
}

void toggle(int *count, bool *on){
    // true unless count is a multiple of 11, so every 11th call is skipped.
    if ((*count)++ % 11)
        *on = !*on;
}
