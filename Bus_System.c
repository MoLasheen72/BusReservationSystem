#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bus_System.h"
#include "Standard_Types.h"
#include "Bus_Reservation.h"

#define size 50
#define num_Users 3
#define num_Buses 3

static u16 choice;
static User input_users;
static User users[num_Users] = {{.username = "Amit1", .password = "1"},  //User1
                                {.username = "Amit2", .password = "2"},  //User2
                                {.username = "Amit3", .password = "3"}}; //User3

static Bus buses[num_Buses] = {{.source = "City A", .destination = "City B", .busNumber = 101, .totalSeats = 70, .availableSeats = 12, .fare = 500.0},
                               {.source = "City E", .destination = "City F", .busNumber = 201, .totalSeats = 60, .availableSeats = 10, .fare = 400.0},
                               {.source = "City X", .destination = "City Y", .busNumber = 301, .totalSeats = 50, .availableSeats = 0 , .fare = 300.0}}; 

void displayMainMenu(void)
{
      printf("\n=== Main Menu ===\n");
      printf("1. Login\n");
      printf("2. Exit\n");
}
void displayUserMenu(void)
{
      printf("\n=== User Menu ===\n");
      printf("1. Book a Ticket\n");
      printf("2. Cancel a Ticket\n");
      printf("3. Check Bus Status\n");
      printf("4. Logout\n");
}
void Bus_Reservation_System(void)
{
      while(1)
      {
            displayMainMenu();
            printf("Enter ur Choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
                  case 1 :
                        printf("Enter Username: ");
                        scanf("%s", input_users.username);

                        printf("Enter Password: ");
                        scanf("%s", input_users.password);

                        if(loginUser(users, num_Users, input_users.username, input_users.password))
                        {
                              printf("Successful Login.\nWelcome %s!\n", input_users.username);
                              while(1)
                              {
                                    displayUserMenu();
                                    printf("Enter ur Choice: ");
                                    scanf("%d", &choice);

                                    switch(choice)
                                    {
                                          case 1 :
                                                bookTicket(buses, num_Buses);
                                                break;
                                          case 2 :
                                                cancelTicket(buses, num_Buses);
                                                break;
                                          case 3 :
                                                checkBusStatus(buses, num_Buses);
                                                break;
                                          case 4 :
                                                printf("Logging Out.\n");
                                                break;
                                          default :
                                                printf("Invalid Input\n");
                                    }
                                    if(choice == 4)
                                          break;
                              }
                        }
                        else
                        {
                              printf("Incorrect Username or Password!\n");
                        }
                        break;   

                  case 2 :
                        printf("Exiting the Program\n");
                        return;

                  default :
                        printf("Invalid Input\n");
            }
      }
}