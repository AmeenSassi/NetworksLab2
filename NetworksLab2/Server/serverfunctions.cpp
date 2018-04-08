/*
** Functions.cpp This will contain All functions that will change 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <vector>
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
        ofstream outputFile;
        outputFile.open("username.txt");
        outputFile << username << endl;
        outputFile.close();
        mess = "S";
        send(new_fd, mess, 128, 0);
        //figure out what to send back.
    }
    else{
        mess = "EU";
        send(new_fd, mess, 128, 0);
    }

}

void deleteUser(int new_fd, int numbytes, char* recvbuf, Account* acc){
    char* mess;
    fstream outputFile;
    outputFile.open("userList.txt");
    string user;
    vector<string> userList;
    if(userExists(acc->getUsername())) {
        string theuser = acc->getUsername();
        string filename = theuser + ".txt";
        remove(filename);
        while (!outputFile.eof()) {
            getline(outputFile, user, '\n');
            if (!user.compare(theuser)) {
                userList.push_back(user);
            }
        }
        outputFile.close();
        remove("userList.txt");
        outputFile.open("userList.txt");
        for (vector<string>::const_iterator i = userList.begin(); i != userList.end(); ++i) {
            outputFile << *i << endl;
        }
        outputFile.close();
    }
    else {
        mess = "EU";
        send(new_fd, mess, 128, 0);
    }
}

void updateUser(int new_fd, int numbytes, char* recvbuf, Account* acc){
    char* mess;
    if(userExists(acc->getUsername())) {
        //figure out what to send back.
        numbytes = recv(new_fd, recvbuf, 128, 0);
        acc->setPassword(recvbuf);
        numbytes = recv(new_fd, recvbuf, 128, 0);
        acc->setName(recvbuf);
        numbytes = recv(new_fd, recvbuf, 128, 0);
        acc->setNumber(recvbuf);
        numbytes = recv(new_fd, recvbuf, 128, 0);
        acc->setEmail(recvbuf);
        mess = "S";
        send(new_fd, mess, 128, 0);
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

void Logout(int new_fd, int numbytes, char* recvbuf, Account* acc){
    ofstream outputFile;
    string username = acc->getUsername();
    string filename = username + ".txt";
    outputFile.open(filename);
    outputFile << acc->getUsername() << endl;
    outputFile << acc->getPassword() << endl;
    outputFile << acc->getName() << endl;
    outputFile << acc->getEmail() << endl;
    outputFile << acc->getNumber() << endl;
    int appNum = 0;
    for (vector<Appointment>::const_iterator i = acc->apps.begin(); i != acc->apps.end(); ++i) {
        cout << appNum << endl;
        cout << i->startDate + ", " + i->startTime + "." << endl;
        cout << i->endDate + ", " + i->endTime + "." << endl;
        cout << i->location + "." << endl;
        cout << i->event + "." << endl;
        appNum++;
    }


}

Account getUser(string uname){
    string outputFile = uname + ".txt";
    ifstream userList;
    Account userAccount;
    userList.open(outputFile);
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

        userAccount = Account(user,pass,name,email,phone);

        string sd;
        string st;
        string ed;
        string et;
        string loc;
        string ev;

        while(!userList.eof()){
            getline(userList, sd, '\n');
            getline(userList, sd, ',');
            getline(userList, st, '.');
            getline(userList, ed, ',');
            getline(userList, et, '.');
            getline(userList, loc, '.');
            getline(userList, ev, '.');

            userAccount.AddApp(sd, st, ed, et, loc, ev);
        }
    }
    return userAccount;
}

bool userExists(string uname){
    ifstream userList;
    string user;
    userList.open("userList.txt");
    while(!userList.eof()){
        getline(userList, user, '\n');
        if(user.compare(uname)){
            return true;
        }
    }
    return false;
}

void updateApp(Account* acc, int appNum, string st, string et, string sd, string ed, string ev, string loc, string uname) {
    Appointment app;
    app = acc->getApp(appNum);
    app.startTime = st;
    app.endTime = et;
    app.startDate = sd;
    app.endDate = ed;
    app.event = ev;
    app.location = loc;
    app.username = uname;
    acc->setApp(appNum, app);
}

void displayAll(Account* acc) {
    acc->printSchedule();
}
#endif
