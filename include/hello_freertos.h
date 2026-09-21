#ifndef HELLO_FREERTOS_H
#define HELLO_FREERTOS_H
int count = 0;
bool on = false;
void blink_task(__unused void *params);
void main_task(__unused void *params);
char switchCase(char c);
bool toggle();

#endif