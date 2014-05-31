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
        int option_1_aux = reservation_request_new(reservation_list, client_list, pre_reservation_list);
        if (option_1_aux == 1)
        {
          printf("Nao conseguimos concluir a operaçao\n");
          break;
        }
        
        else if (option_1_aux == 2)
        {
          clear_screen();
          break;
        }
        
        else
        {
          clear_screen();
          
          printf("Reserva adicionada com sucesso.\n\n");
          
        }
      }
      else if (which_option == 2)
      {
        int option_2_aux = reservation_request_cancel(reservation_list);
        clear_screen();

       if (option_2_aux == 1)
        {
          printf("Nao conseguimos concluir a operaçao\n");
          break;
        }
        
        else if (option_2_aux == 2)
        {
          clear_screen();
          break;
        }
        
        else
        {
          clear_screen();
          printf("Reserva cancelada com sucesso.\n\n");
          
        }
      }
      else if (which_option == 3)
      {
        clear_screen();
        int option_3_aux = reservation_request_listing(reservation_list);
        

        if (option_3_aux == 1)
        {
          break;
        }
        
        else if (option_3_aux == 2)
        {
          clear_screen();
          break;
        }

        else
        {
          
        }
        
      }
      else if (which_option == 4)
      {
        clear_screen();
        int option_4_aux = reservation_request_listing(pre_reservation_list);
        

        if (option_4_aux == 1)
        {
          break;
        }
        
        else if (option_4_aux == 2)
        {
          clear_screen();
          break;
        }

        else
        {
          
        }
        
      }
      else if (which_option == 5)
      {
        int option_5_aux = reservation_request_cancel(pre_reservation_list);
        clear_screen();
        
        if (option_5_aux == 1)
        {
          printf("Nao conseguimos concluir a operaçao\n");
          break;
        }
        
        else if (option_5_aux == 2)
        {
          clear_screen();
          break;
        }
        
        else
        {
          clear_screen();
          printf("Reserva cancelada com sucesso.\n\n");
          
        }
      }
      else if (which_option == 6)
      {
        clear_screen();
        int option_6_aux = client_request_print(client_list);
        
        if (option_6_aux == 1)
        {
          printf("Nao conseguimos concluir a operaçao\n");
          break;
        }
        
        else if (option_6_aux == 2)
        {
          clear_screen();
          break;
        }
      }
    } while (which_option <= 0);
  }
}

int main()
{
  client_list = llist_new();
  reservation_list = llist_new();
  pre_reservation_list = llist_new();

  read_client("clients.txt", client_list);
  read_reservation("reservations.txt", client_list, reservation_list);
  read_pre_reservation("pre_reservations.txt", client_list, pre_reservation_list);

  menu_load();
  main_loop();

  reservation_remove_outdated(reservation_list);
  reservation_remove_outdated(pre_reservation_list);
  write_client("clients.txt", client_list);
  write_reservations("reservations.txt", reservation_list);
  write_pre_reservations("pre_reservations.txt", pre_reservation_list);
  llist_destroy(client_list);
  llist_destroy(reservation_list);
  llist_destroy(pre_reservation_list);

  return 0;
}
