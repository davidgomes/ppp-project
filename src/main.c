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
        clear_screen();
        
        while (!reservation_request_new(reservation_list, client_list))
        {

        }

        clear_screen();

        printf("Reserva adicionada com sucesso.\n\n");
      }
      else if (which_option == 2)
      {
        clear_screen();
          
        while (!reservation_request_cancel(reservation_list))
        {

        }

        clear_screen();

        printf("Reserva cancelada com sucesso.\n\n");
      }
      else if (which_option == 3)
      {
        clear_screen();

        while (!reservation_request_listing(reservation_list))
        {
          
        }
      }
      else if (which_option == 4)
      {
        clear_screen();

        while (!client_request_print(client_list))
        {

        }
      }
    } while (which_option <= 0);
  }
}

int main()
{
  client_list = llist_new();
  reservation_list = llist_new();

  read_client("clients.txt", client_list);
  read_reservation("reservations.txt", client_list, reservation_list);

  menu_load();
  main_loop();

  outdated_reservation_remove(reservation_list);
  write_client("clients.txt", client_list);
  write_reservations("reservations.txt", reservation_list);

  return 0;
}
