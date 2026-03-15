#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bus_Reservation.h"
#include "Standard_Types.h"

#define max_Passengers 180

static u16 i, j, k;                                        //General Use
static u16 count, correct_user, correct_pass;              //For loginUser 
static u8  input_ticket_name[50];
static u16 input_bus_number, input_seats_number, correct_name; //For bookTicket & cancelTicket
static u16 status_bus, input_id;
static u16 current_users = 6, new_id; 

booked passenger[max_Passengers] = {{.name = "Fam",   .age = 20, .seats_booked = 58, .bus_number = 101, .id = 1},

                                    {.name = "Farid", .age = 16, .seats_booked = 15, .bus_number = 201, .id = 1},
                                    {.name = "Ahmed", .age = 32, .seats_booked = 35, .bus_number = 201, .id = 2},

                                    {.name = "Emad",  .age = 34, .seats_booked = 10, .bus_number = 301, .id = 1},
                                    {.name = "Faris", .age = 19, .seats_booked = 15, .bus_number = 301, .id = 2},
                                    {.name = "Ryad",  .age = 26, .seats_booked = 25, .bus_number = 301, .id = 3}};
u16 strLen(u8 str[])//Instead of strlen Built in Function
{
      for(count = 0; str[count] != '\0'; count++);
      return count;
}
u32 loginUser(User users[], u32 num_Users, char username[], char password[])
{     
      for(i = 0; i < num_Users; i++)
      {
            correct_user = 0;
            correct_pass = 0;
            //THE && TO CHECK IF THE THE USER FOR THE SAME PASS 
            if((strLen(username) == strLen(users[i].username)) && (strLen(password) == strLen(users[i].password)))
            {
                  //USER CHECK
                  for(j = 0; j < strLen(username); j++)
                  {
                        if(username[j] != users[i].username[j])
                              break;
                        if(j == (strLen(username) - 1))
                              correct_user = 1;   //Correct User
                  }
                  //PASS CHECK
                  for(j = 0; j < strLen(password); j++)
                  {
                        if(password[j] != users[i].password[j])
                              break;
                        if (j == (strLen(password) - 1))
                              correct_pass = 1;   //Correct Pass
                  }
                  if(correct_user && correct_pass)
                        return 1;   //Break if User & Pass r Found
            }
      }
      return 0;
}
void bookTicket(Bus buses[], u32 num_Buses)
{
      printf("Enter Bus Number: ");
      scanf("%d", &input_bus_number);

      printf("Enter Number of Seats: ");
      scanf("%d", &input_seats_number);

      if(input_seats_number < 0)
      {
            printf("You Can't book Zero Tickets\n");
            return;
      }
            
      for (i = 0; i < num_Buses; i++)
      {
            if(input_bus_number == buses[i].busNumber)
            {
                  if(buses[i].availableSeats >= input_seats_number)
                  {
                        if(buses[i].availableSeats == buses[i].totalSeats)//If this True Then there are no Passengers
                              new_id = 1;
                        else
                        {
                              //To Get the ID of the Passenger for Later Modifying
                              for(j = 0; j < current_users; j++)
                              {
                                    if((input_bus_number == passenger[j].bus_number) && passenger[j].id != 0)
                                          new_id = passenger[j].id + 1; //Give the New User an ID
                              }
                        }
                              
                              printf("Enter Your Name: ");
                              scanf("%s", passenger[current_users].name);//Asigning The new User's Name
                              
                              printf("Enter your Age: ");
                              scanf("%d", &passenger[current_users].age);//Asigning The new User's Age

                              passenger[current_users].bus_number = input_bus_number;//Assign The Bus Number to The New User
                              passenger[current_users].seats_booked = input_seats_number;//Assign The Seats Number to The New User
                              passenger[current_users].id = new_id;//Assign The ID to The New User
                              
                              buses[i].availableSeats -= input_seats_number;//Updating Available Seats
                              current_users++;//Updating Users by One

                              printf("Booking Successful!\n%d Seats Booked on Bus Number %d\nYour Ticket's Name is: %s\nYour Ticket's ID is: %d\n", input_seats_number, input_bus_number, passenger[current_users].name, new_id);
                              return;
                  }
                  else
                  {
                        printf("Available Seats r not Enough.\nOnly %d Seats r Available\n", buses[i].availableSeats);
                        return;
                  }
            }
      }
      printf("Invalid Bus Number\n");
}
void cancelTicket(Bus buses[], u32 num_Buses)
{
      printf("Enter Ticket's Name: ");
      scanf("%s", input_ticket_name);
      
      printf("Enter Ticket's ID: ");
      scanf("%d", &input_id);
      if(input_id == 0)
      {
            printf("Wrong ID\n");
            return;
      }
      
      printf("Enter Bus Number: ");
      scanf("%d", &input_bus_number);

      printf("Enter Number of Seats to Cancel: ");
      scanf("%d", &input_seats_number);
      if(input_seats_number == 0)
      {
            printf("Wrong Seats Number\n");
            return;
      }

      correct_name = 0;

      //Check Input Data
      for(k = 0; k < current_users; k++)
      {
            if((strLen(passenger[k].name) == strLen(input_ticket_name)) && (passenger[k].id == input_id) && (passenger[k].bus_number == input_bus_number))//If Name & ID & Bus Number Match at the Same time
            {
                  for(j = 0; j < strLen(input_ticket_name); j++)
                  {
                        if(input_ticket_name[j] != passenger[k].name[j])
                              break;
                        if(j == (strLen(input_ticket_name) - 1))
                        {
                              correct_name = 1;   //Correct Name
                              break;
                        }
                  }

                  if(correct_name)
                  {
                        if(input_seats_number <= passenger[k].seats_booked)
                        {             
                              if(input_seats_number == passenger[k].seats_booked)
                              {
                                    //current_users--; //Delete User Because He Canceled All The Booked Tickets 
                                    passenger[k].id = 0;//It means This User Is out of the System rn
                              }
                                    
                              printf("Cancelling Successful!\n%d Seats Were Canceled on Bus Number %d\n", input_seats_number, input_bus_number);
                              
                              //Find the Bus To Modify its Data
                              for(i = 0; i < num_Buses; i++)
                              {
                                    if(buses[i].busNumber == input_bus_number)
                                    break; 
                              }

                              buses[i].availableSeats   += input_seats_number;//Update Avialable Seats in That Bus
                              passenger[k].seats_booked -= input_seats_number;//Update User Booked Seats
                              return;
                        }
                        else
                        {

                              printf("Error: You Cant Cancel More than You have reserved!\n");
                              return;
                        }
                  }
            }
      }

      printf("Invalid Name or ID or Bus!\n");
}
void checkBusStatus(Bus buses[], u32 num_Buses)
{
      printf("Enter Bus Number: ");
      scanf("%d", &status_bus);

      for(i = 0; i < num_Buses; i++)
      {
            if(buses[i].busNumber == status_bus)
                  break;
            if(i == (num_Buses - 1))
            {
                  printf("Invalid Bus Number\n");
                  return;
            }
      }

      printf("\nStatus for Bus Number %d are:\n", status_bus);
      printf("Source: %s\n", buses[i].source);
      printf("Destination: %s\n", buses[i].destination);
      printf("Total Seats: %d\n", buses[i].totalSeats);
      printf("Available Seats: %d\n", buses[i].availableSeats);
      printf("Fare: %.2f\n", buses[i].fare);
}