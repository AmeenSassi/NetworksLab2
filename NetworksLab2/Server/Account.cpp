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

string Account::getEmail(){
    return this->email;
}

void Account::AddApp(string sd, string st, string ed, string et, string loc, string ev){
    Appointments newApp;
    newApp.username = getUsername();
    newApp.startDate = sd;
    newApp.startTime = st;
    newApp.endDate = ed;
    newApp.endTime = et;
    newApp.location = loc;
    newApp.event = ev;
    this->apps.push_back(newApp);
}

void Account::printSchedule(){
    int appNum = 0;

    for (vector<Appointments>::const_iterator i = apps.begin(); i != apps.end(); ++i){
        appNum++;
        cout << "Appointment " + appNum << endl;
        cout << "Start: " + i->startDate + ", " + i->startTime + "." << endl;
        cout << "End: " + i->endDate + ", " + i->endTime + "." << endl;
        cout << "Location: " + i->location + "." << endl;
        cout << i->event + "." << endl;
    }
 
}