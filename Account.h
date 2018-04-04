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

#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Appointments {
    string username;
    string date;
    string time;
    string event;
};

class Account {

    private: 
            string password;
            string name;
            string number;
            string email;
            Appointments apps[];
            int numApps;

    
    public:
            string username;

            string getUsername();
            string getPassword();
            string getName();
            string getNumber();
            string getEmail();


//TODO - Finish this class and begin working on functions.cpp


}