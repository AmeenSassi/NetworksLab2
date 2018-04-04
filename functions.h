/*
** Functions.cpp This will contain All functions that will change 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//User functions
void addUser();
void deleteUser(Account);
void updateUser(Account);
void Login(Account);

//Appointment functions
void addApp(Account);
void removeApp(Account);
void updateApp(Account);
void displayApps(Account);

//Basic functions
Account getUser(string);

#endif
