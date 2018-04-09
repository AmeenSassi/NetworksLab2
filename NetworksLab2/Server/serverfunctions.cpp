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

void menu(int new_fd, int numbytes, char* recvbuf){
    char* mess;
    bool exit1 = false;
    bool login = false;
    string received;
    Account acc;
    while(!exit1){
        numbytes = recv(new_fd, recvbuf, 128, 0);
        received = recvbuf;
        if(received.compare("St1")){ // St1: Login
            mess = "St1.1";
            send(new_fd, mess, 128, 0);
            if(Login(new_fd, numbytes, recvbuf, *acc)){
                login = true;
            }
        }
        else if (received.compare("St2")) { // St2: Sign Up
            mess = "St2.1";
            send(new_fd, mess, 128, 0);
            if(signUp(new_fd, numbytes, recvbuf, *acc)){
                login = true;
            }
        }
        else if (received.compare("St3")) { // St3: Exit
            exit1 = true;
        }
        else {
            login = false;
        }
        while(login){
            mess = "F";
            send(new_fd, mess, 128, 0);
            numbytes = recv(new_fd, recvbuf, 128, 0);
            received = recvbuf;
            if(received.compare("F1")){ //Delete a User
                deleteUser(new_fd, numbytes, recvbuf, *acc);
                login = false;
            }
            else if(received.compare("F2")){ //Update a User
                updateUser(new_fd, numbytes, recvbuf, *acc);
            }
            else if(received.compare("F3")){ //Add Appointment
                addApp(new_fd, numbytes, recvbuf, *acc);
            }
            else if(received.compare("F4")) { //Remove Appointment
                mess = acc.getNumApp();
                send(new_fd, mess, 128, 0);
                numbytes = recv(new_fd, recvbuf, 128, 0);
                received = recvbuf;
                if(received < acc.getNumApp()){
                    acc.removeApp(stoi(received));
                }
            }
            else if(received.compare("F5")) { //Update Appointment
                mess = acc.getNumApp();
                send(new_fd, mess, 128, 0);
                numbytes = recv(new_fd, recvbuf, 128, 0);
                mess = recvbuf;
                int num = stoi(mess);
                if(num < acc.getNumApp()) {
                    numbytes = recv(new_fd, recvbuf, 128, 0);
                    string sd = recvbuf;
                    numbytes = recv(new_fd, recvbuf, 128, 0);
                    string ed = recvbuf;
                    numbytes = recv(new_fd, recvbuf, 128, 0);
                    string st = recvbuf;
                    numbytes = recv(new_fd, recvbuf, 128, 0);
                    string et = recvbuf;
                    numbytes = recv(new_fd, recvbuf, 128, 0);
                    string loc = recvbuf;
                    numbytes = recv(new_fd, recvbuf, 128, 0);
                    string ev = recvbuf;
                    updateApp(*acc, num, st, et, sd, ed, ev, loc, (acc.getUsername()));
                }
            }
            else if(received.compare("F6")) { //Display Appointments
                numbytes = recv(new_fd, recvbuf, 128, 0);
                received = recvbuf;
                if(received.compare("DA1")){ //Display ALL
                    displayAll(*acc);
                }
                /*else if(received.compare("DA2")){ //Display for certain date
                    mess = "DA21";
                    send(new_fd, mess, 128, 0);
                    numbytes = recv(new_fd, recvbuf, 128, 0);
                    received = recvbuf;
                    if(received.compare("D1")) {
                        mess = "D12";
                        send(new_fd, mess, 128, 0);
                        numbytes = recv(new_fd, recvbuf, 128, 0);
                        received = recvbuf;
                        acc.printSchedule(new_fd, numbytes, recvbuf, stoi(received));
                    }*/
            }
            else if(received.compare("F7")) { //Log Out
                Logout(new_fd, numbytes, recvbuf, *acc);
            }
        }
    }
}


//User functions
bool SignUp(int new_fd, int numbytes, char* recvbuf, Account* acc){
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
        acc = Account(username, password, name, phone, email);
        ofstream outputFile;
        outputFile.open("username.txt");
        outputFile << username << endl;
        outputFile.close();
        mess = "S";
        send(new_fd, mess, 128, 0);
        return true;
    }
    else{
        mess = "EU";
        send(new_fd, mess, 128, 0);
        return false;
    }

}

bool deleteUser(int new_fd, int numbytes, char* recvbuf, Account* acc){
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
        mess = "DU";
        send(new_fd, mess, 128, 0);
        return true;
    }
    else {
        mess = "EU";
        send(new_fd, mess, 128, 0);
        return false;
    }
}

bool updateUser(int new_fd, int numbytes, char* recvbuf, Account* acc){
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
        return true;
    }
    else{
        mess = "EU";
        send(new_fd, mess, 128, 0);
        return false;
    }
}

bool Login(int new_fd, int numbytes, char* recvbuf, Account* acc){
    char* mess;
    numbytes = recv(new_fd,recvbuf,128,0);
    string username = recvbuf;
    numbytes = recv(new_fd,recvbuf,128,0);
    string password = recvbuf;

    if(userExists(username)) {
        //add code to find, open file and parse it.
        if(passVerify(password)) {
            acc = getUser(username);
            mess = "S";
            send(new_fd, mess, 128, 0);
            return true;
        }
        else{
            mess = "EP";
            send(new_fd, mess, 128, 0);
            return false;
        }
    }
    else{
        mess = "EU";
        send(new_fd, mess, 128, 0);
        return false;
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
        outputFile << appNum << endl;
        outputFile << i->startDate + ", " + i->startTime + "." << endl;
        outputFile << i->endDate + ", " + i->endTime + "." << endl;
        outputFile << i->location + "." << endl;
        outputFile << i->event + "." << endl;
        appNum++;
    }
}

void addApp(int new_fd, int numbytes, char* recvbuf, Account* acc){
    mess = "AA";
    send(new_fd, mess, 128, 0);
    numbytes = recv(new_fd, recvbuf, 128, 0);
    string sd = recvbuf;
    numbytes = recv(new_fd, recvbuf, 128, 0);
    string ed = recvbuf;
    numbytes = recv(new_fd, recvbuf, 128, 0);
    string st = recvbuf;
    numbytes = recv(new_fd, recvbuf, 128, 0);
    string loc = recvbuf;
    numbytes = recv(new_fd, recvbuf, 128, 0);
    string ev = recvbuf;
    acc->AddApp(sd, st, ed, et, loc, ev);
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
    if(appNum < acc->getNumApp()) {
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
}

void displayAll(int new_fd, Account* acc) {
    acc->printSchedule(new_fd);
}

#endif
