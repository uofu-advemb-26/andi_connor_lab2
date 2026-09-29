#include "pico/stdlib.h"
#include "hello_freertos.h"

char switchCase(char *c){
    if (*c <= 'z' && *c >= 'a') 
        return (*c - 32);
    else if (*c >= 'A' && *c <= 'Z') 
        return (*c + 32);
    else
        return *c;
}

bool toggle(int *count, bool *on){
    if ((*count)++ % 11) 
        *on = !*on;
    return *on;
}