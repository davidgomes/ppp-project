#ifndef MENU_HEADER
#define MENU_HEADER

#include <stdio.h>
#include <string.h>

#include "utils.h"

#define N_OPTIONS 5
#define EXIT_OPTION N_OPTIONS

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
