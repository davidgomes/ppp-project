#include "menu.h"

void menu_load()
{
  options[0] = "Reservar lavagem ou manutencao";
  options[1] = "hmm";
  options[2] = "Cancelar uma reserva";
  options[3] = "hmm";
  options[4] = "Listar as reservas";
}

void menu_show()
{
  int option;

  for (option = 1; option < N_OPTIONS + 1; option++)
  {
    printf("%d: %s.\n", option, options[option - 1]);
  }
}
