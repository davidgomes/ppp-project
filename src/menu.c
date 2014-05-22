#include "menu.h"

void menu_load()
{
  options[0] = "Reservar lavagem ou manutenção";
  options[1] = "Cancelar lavagem ou manutenção";
  options[2] = "Listar reservas e pré-reservas";
  options[3] = "Listar informação de um cliente";
  options[4] = "Sair do programa";
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
  get_int_input("Insira a sua opção: ", &chosen_option);

  if (chosen_option > 0 && chosen_option <= N_OPTIONS)
  {
    return chosen_option;
  }

  clear_screen();

  return -1;
}
