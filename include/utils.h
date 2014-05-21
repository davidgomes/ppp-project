#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.H>

#include "xtime.h"

#define MAX_INT_DIGITS 32
#define MAX_TIME_CHARS 128

/**
 * Clears the screen
 */
void clear_screen();
void get_str_input(char*, char*, int);
void get_int_input(char*, int*);
void time_to_str(xtime*, char*);
void ask_date(xtime*);
void time_t_to_xtime(xtime*, time_t*);

#endif
