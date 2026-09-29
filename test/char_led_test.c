#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "hello_freertos.h"

int count;
bool on;

void setUp(void) {
    count = 0;
    on = false;
}

void tearDown(void) {
    count = 0;
    on = false;
}

void test_switchchar_lowercase()
{
    // loop through ASCII values for lowercase letters a-z
    for (int i = 'a'; i <= 'z'; i++) {
        char c = (char)i;
        char expected = (char)(c - 32);
        char actual = switchCase(c);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(expected, actual, "Lowercase letter case switch failed.");
    }
}

void test_switchchar_uppercase()
{
    // loop through ASCII values for uppercase letters A-Z
    for (int i = 'A'; i <= 'Z'; i++) {
        char c = (char)i;
        char expected = (char)(c + 32);
        char actual = switchCase(c);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(expected, actual, "Uppercase letter case switch failed.");
    }
}

void test_switchchar_non_letter()
{
    char non_letters[] = {'0', '9', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '=', '+', '[', ']', '{', '}', ';', ':', '\'', '"', ',', '.', '/', '<', '>', '?', '\\', '|'};
    for (int i = 0; i < sizeof(non_letters); i++) {
        char c = non_letters[i];
        char actual = switchCase(c);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(c, actual, "Non-letter character case switch failed.");
    }
}       

void test_toggle_led(void)
{
    count++; // Increment count past 0 to ensure toggle will flip the LED state
    if (on == true) {
        toggle(&count, &on);
        TEST_ASSERT_TRUE_MESSAGE(on == false, "LED toggle failed.");
    }
    else {
        toggle(&count, &on);
        TEST_ASSERT_TRUE_MESSAGE(on == true, "LED toggle failed.");
    }
}

void test_toggle_led_multiple(void)
{
    bool prev;
    for (int i = 0; i < 12; i++) {
        prev = on;
        toggle(&count, &on);

        // test toggle works normally each time except when count is 0 or 11
        if (i > 0 && i < 11) {
            TEST_ASSERT_TRUE_MESSAGE(on != prev, "When count wasn't 0 or 11, LED did not toggle.");
        } else {
            TEST_ASSERT_TRUE_MESSAGE(on == prev, "LED toggled when count was 0 or 11.");
        }
    }
}

int main (void)
{
    stdio_init_all();
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_switchchar_lowercase);
        RUN_TEST(test_switchchar_uppercase);
        RUN_TEST(test_switchchar_non_letter);
        RUN_TEST(test_toggle_led);
        RUN_TEST(test_toggle_led_multiple);
        sleep_ms(5000);
        UNITY_END();
    }
}
