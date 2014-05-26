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
    printf("%s%d: %s.\n", COLOR_YELLOW, option, options[option - 1]);
  }

  printf("%s", COLOR_WHITE);
}

int menu_wait()
{
  menu_show();

  int chosen_option;
  while ((get_int_input("Insira a sua opção: ", &chosen_option)) == 1)
  {
    printf("Opção não válida\n");
  }

  if (chosen_option > 0 && chosen_option <= N_OPTIONS)
  {
    return chosen_option;
  }

  clear_screen();

  return -1;
}
