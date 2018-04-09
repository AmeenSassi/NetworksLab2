/*
** Account.cpp This will contain the Account class.
*/

#include <string>
#include <vector>
#include "Account.h"
#include <iostream>

using namespace std;

Account::Account(string uname, string pass, string n, string phone, string mail){
    this->username = uname;
    this->password = pass;
    this->name = n;
    this->number = phone;
    this->email = mail;
}

Account::Account(){
    this->username = "No username found.";
    this->password = "pass not found.";
    this->name = "name not found.";
    this->number = "phone not found.";
    this->email = "email not found.";

}

void Account::setUsername(string uname){
    this->username = uname;
}

void Account::setPassword(string pass){
    this->password = pass;
}

void Account::setName(string n){
    this->name = n;
}

void Account::setNumber(string phone){
    this->number = phone;
}

void Account::setEmail(string mail){
    this->email = mail;
}
            
string Account::getUsername(){
    return this->username;
}

string Account::getPassword(){
    return this->password;
}

string Account::getName(){
    return this->name;
}

string Account::getNumber(){
    return this->number;
}

string Account::getEmail() {
    return this->email;
}

Appointment Account::getApp(int i){
    return apps.[i];
}

void Account::setApp(int i, Appointment app){
    this->apps.[i] = app;
}

void Account::removeApp(int i){
    this->apps.erase(apps.begin() + i);
}

void Account::AddApp(string sd, string st, string ed, string et, string loc, string ev){
    Appointment newApp;
    newApp.username = getUsername();
    newApp.startDate = sd;
    newApp.startTime = st;
    newApp.endDate = ed;
    newApp.endTime = et;
    newApp.location = loc;
    newApp.event = ev;
    this->apps.push_back(newApp);
}

void Account::printSchedule(int new_fd){
    int appNum = 0;
    string mess = getNumApp();
    send(new_fd, mess, 128, 0);
    for (vector<Appointment>::const_iterator i = apps.begin(); i != apps.end(); ++i) {
        mess = appNum;
        send(new_fd, mess, 128, 0);
        mess = i->startDate + ", " + i->startTime + ".";
        send(new_fd, mess, 128, 0);
        mess = i->endDate + ", " + i->endTime + ".";
        send(new_fd, mess, 128, 0);
        mess = i->location + ".";
        send(new_fd, mess, 128, 0);
        mess = i->event + ".";
        send(new_fd, mess, 128, 0);
        appNum++;
    }
}

int getNumApp(){
    return apps.size();
}