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
#include "Account.h"
#include "serverfunctions.h"
#include <fstream>

using namespace std;

//User functions
void addUser(int new_fd, int numbytes, char* recvbuf){
    char* mess;

    numbytes = recv(new_fd,recvbuf,128,0);
    string username = recvbuf;
    numbytes = recv(new_fd,recvbuf,128,0);
    string password = recvbuf;
    numbytes = recv(new_fd,recvbuf,128,0);
    string name = recvbuf;
    numbytes = recv(new_fd,recvbuf,128,0);
    string phone = recvbuf;
    numbytes = recv(new_fd,recvbuf,128,0);
    string email = recvbuf;

    if(!userExists(username)) {
        Account newAcc = Account(username, password, name, phone, email);
        mess = "S";
        send(new_fd, mess, 128, 0);
        //figure out what to send back.
    }
    else{
        mess = "EU";
        send(new_fd, mess, 128, 0);
    }

}
void deleteUser(Account);

void updateUser(int new_fd, int numbytes, char* recvbuf, Account* acc){
    char* mess;

    numbytes = recv(new_fd,recvbuf,128,0);
    acc->setUsername(recvbuf);
    numbytes = recv(new_fd,recvbuf,128,0);
    acc->setPassword(recvbuf);
    numbytes = recv(new_fd,recvbuf,128,0);
    acc->setName(recvbuf);
    numbytes = recv(new_fd,recvbuf,128,0);
    acc->setNumber(recvbuf);
    numbytes = recv(new_fd,recvbuf,128,0);
    acc->setEmail(recvbuf);

    if(userExists(username)) {
        acc = Account(username, password, name, phone, email);
        mess = "S";
        send(new_fd, mess, 128, 0);
        //figure out what to send back.
    }
    else{
        mess = "EU";
        send(new_fd, mess, 128, 0);
    }
}

void Login(int new_fd, int numbytes, char* recvbuf){
    char* mess;

    numbytes = recv(new_fd,recvbuf,128,0);
    string username = recvbuf;
    numbytes = recv(new_fd,recvbuf,128,0);
    string password = recvbuf;

    if(userExists(username)) {
        //add code to find, open file and parse it.
        if(passVerify(password)) {
            Account acc = getUser(username);
            mess = "S";
            send(new_fd, mess, 128, 0);
            // Now what?
        }
        else{
            mess = "EP";
            send(new_fd, mess, 128, 0);
        }
    }
    else{
        mess = "EU";
        send(new_fd, mess, 128, 0);
    }
}

//Appointment functions
void addApp(Account*){

}

void removeApp(Account);
void updateApp(Account);
void displayApps(Account);

//Basic functions
Account getUser(string uname){
    string file = uname + ".txt";
    ifstream userList;
    userList.open(file);
    while(!userList.eof()){

        string user;
        string pass;
        string name;
        string email;
        string phone;

        getline(userList, user, '\n');
        getline(userList, pass, '\n');
        getline(userList, name, '\n');
        getline(userList, email, '\n');
        getline(userList, phone, '\n');

        string sd;
        string st;
        string ed;
        string et;
        string loc;
        string ev;

        getline(userList, sd, '\n');
        getline(userList, sd, ',');
        getline(userList, st, '.');
        getline(userList, ed, ',');
        getline(userList, et, '.');
        getline(userList, loc, '.');
        getline(userList, ev, '.');

    }

}

#endif
