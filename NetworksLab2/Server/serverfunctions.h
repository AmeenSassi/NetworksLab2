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
#include <iostream>
using namespace std;

#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

//Menu
void menu();

//User functions
bool signUp(int, int, char*, Account*);
bool deleteUser(int, int, char*, Account*);
bool updateUser(int, int, char*, Account*);
bool Login(int, int, char*, Account);
void Logout(int, int, char*, Account*);
Account getUser(string uname);
bool userExists(string uname);
void updateApp(Account*, int, string, string, string, string, string, string, string);
void displayApps(Account);
void displayAll(Account*);
void addApp(int, int, char*, Account*);

#endif
