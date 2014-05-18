#include "main.h"

void main_loop()
{
  int which_option = -1;

  clear_screen();

  while (which_option != EXIT_OPTION)
  {
    do
    {
      which_option = menu_wait();

      if (which_option == 1)
      {
        while (!reservation_request_new(reservation_list, client_list))
        {
          printf("Ocorreu um erro a adicionar uma nova reserva.\n");
        }

        clear_screen();

        printf("Reserva adicionada com sucesso.\n\n");
      }
      else if (which_option == 2)
      {
        while (!reservation_request_cancel(reservation_list))
        {
          printf("Ocorreu um erro a cancelar uma reserva.\n");
        }

        clear_screen();

        printf("Reserva cancelada com sucesso.\n\n");
      }
      else if (which_option == 3)
      {
        clear_screen();

        while (!reservation_request_listing(reservation_list))
        {
          printf("Ocorreu um erro a listar as reservas e pré-reservas.\n");
        }
      }
      else if (which_option == 4)
      {
        while (!client_request_print(client_list))
        {
          printf("Ocorreu um erro a ler o nome do cliente\n");
        }
      }
    } while (which_option <= 0);
  }
}

int main()
{
  client_list = llist_new();
  reservation_list = llist_new();

  menu_load();
  main_loop();

  return 0;
}
