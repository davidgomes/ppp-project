#include <stdio.h>
#include <string.h>

#define N_OPTIONS 5
#define EXIT_OPTION N_OPTIONS

char *options[N_OPTIONS];

void menu_load();
void menu_show();
int menu_wait();