#ifndef BUS_RESERVATION_H_INCLUDED
#define BUS_RESERVATION_H_INCLUDED

#include "Standard_Types.h"

//User Tickets Information
typedef struct book
{
    u8 name[50];
    u8 age;
    u16 seats_booked;
    u16 bus_number;
    u16 id; //Num of the User
}booked;

//Bus information
typedef struct Bus
{
    u8  source[50];
    u8  destination[50];
    u16 busNumber;
    u32 totalSeats;
    u32 availableSeats;
    f32 fare;
}Bus;

//User Login Information
typedef struct User
{
    u8 username[50];
    u8 password[50];
}User;

// Protypes
u32 loginUser(User users[], u32 numUsers, char username[], char password[]);
void bookTicket(Bus buses[], u32 numBuses);
void cancelTicket(Bus buses[], u32 numBuses);
void checkBusStatus(Bus buses[], u32 numBuses);

#endif // BUS_RESERVATION_H_INCLUDED