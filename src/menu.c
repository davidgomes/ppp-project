#include "menu.h"

void menu_load()
{
  options[0] = "Reservar lavagem ou manutenção";
  options[1] = "Cancelar lavagem ou manutenção";
  options[2] = "Listar reservas e pré-reservas";
  options[3] = "Listar informação do cliente";
}

void menu_show()
{
  int option;

  for (option = 1; option < N_OPTIONS + 1; option++)
  {
    printf("%d: %s.\n", option, options[option - 1]);
  }
}

int menu_wait()
{
  menu_show();
  
  int chosen_option;
  scanf("%d", &chosen_option);

  return chosen_option;
}
