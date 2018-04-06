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
#include <vector>

using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Appointments {
    string username;
    string startDate;
    string startTime;
    string endDate;
    string endTime;
    string location;
    string event;
};

class Account {

    private: 
            string password;
            string name;
            string number;
            string email;
            vector<Appointments> apps;
            int numApps;

    
    public:
            string username;

            Account(string, string, string, string, string);

            void AddApp(string, string, string, string, string, string);
            
            void setUsername(string);
            void setPassword(string);
            void setName(string);
            void setNumber(string);
            void setEmail(string);

            string getUsername();
            string getPassword();
            string getName();
            string getNumber();
            string getEmail();

            void printSchedule();
};

#endif
