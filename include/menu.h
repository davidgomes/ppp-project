#ifndef MENU_HEADER
#define MENU_HEADER

#include <stdio.h>
#include <string.h>

#include "utils.h"

#define N_OPTIONS 5
#define EXIT_OPTION N_OPTIONS

#define COLOR_YELLOW "\x1B[33m"
#define COLOR_WHITE "\x1B[37m"

/**
 * An array holding all the menu options as strings.
 */
char *options[N_OPTIONS];

/**
 * Loads the strings for the menu.
 */
void menu_load();

/**
 * Displays the menu.
 */
void menu_show();

/**
 * Calls menu_show and waits for the user to pick an option.
 */
int menu_wait();

#endif
