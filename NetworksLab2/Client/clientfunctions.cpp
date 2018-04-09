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
#include "clientfunctions.h"

using namespace std;

void menu(int sockfd, int numbytes, char* sendbuf) {
    char *mess;
    bool exit1 = false;
    bool login = false;
    string received;
    while (!exit1) {
        cout << "Hello, welcome to the your Calender. Please select an option." << endl;
        cout << "1. Login" << endl;
        cout << "2. Sign up" << endl;
        cout << "3. Exit" << endl;
        getline(cin, received);
        if (received.compare("1")) {
            mess = "St1";
            send(sockfd, mess, 128, 0);
            numbytes = recv(sockfd, sendbuf, 128, 0);
            received = sendbuf;
            if (received.compare("St1.1")) { // St1: Login
                cout << "Enter Username" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Password" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                numbytes = recv(sockfd, sendbuf, 128, 0);
                received = sendbuf;
                if(recived.compare("S")){
                    login = true;
                }
                else
                {
                    cout << "Invalid Entry" << endl;
                }
            }
        }
        else if (received.compare("2")) {
            mess = "St2";
            send(sockfd, mess, 128, 0);
            numbytes = recv(sockfd, sendbuf, 128, 0);
            received = sendbuf;
            if (received.compare("St2.1")) { // St2: Sign Up
                cout << "Enter Username" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Password" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Name" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Phone Number" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Email Address" << endl;
                getline(cin, mess);
                numbytes = recv(sockfd, sendbuf, 128, 0);
                received = sendbuf;
                if(recived.compare("S")){
                    login = true;
                }
                else
                {
                    cout << "Invalid Entry" << endl;
                }
            }
        }
        else if (received.compare("3")) {
            mess = "St3";
            send(sockfd, mess, 128, 0);
            exit1 = true;
        }
        else {
            cout << "Invalid Entry" << endl;
        }
        while(login){
            numbytes = recv(new_fd, sendbuf, 128, 0);
            received = recvbuf;
            if(received.compare("F")){ //Display options
                cout << "Select an option" << endl;
                cout << "1. Delete Account" << endl;
                cout << "2. Update Info" << endl;
                cout << "3. Add Appointment" << endl;
                cout << "4. Remove Appointment" << endl;
                cout << "5. Update Appointment" << endl;
                cout << "6. Display Schedule" << endl;
                cout << "7. Log Out" << endl;
            }
            getline(std::cin, received);
            if (received.compare("1")) {
                mess = "F1";
                send(sockfd, mess, 128, 0);
                numbytes = recv(new_fd, sendbuf, 128, 0);
                received = sendbuf;
                if (received.compare("DU")) { // St1: Login
                    cout << "User Deleted. Logging out..." << endl;
                    login = false;
                }
                else {
                    cout << "Error Occurred." << endl;
                }
            }
            else if (received.compare("2")) {
                mess = "F2";
                send(sockfd, mess, 128, 0);
                cout << "Enter Password" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Name" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Phone Number" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Email Address" << endl;
                getline(cin, mess);
                numbytes = recv(sockfd, sendbuf, 128, 0);
                received = sendbuf;
                if(recived.compare("S")){
                    login = true;
                }
                else
                {
                    cout << "Invalid Entry" << endl;
                }
            }
            else if (received.compare("3")) {
                mess = "F3";
                send(sockfd, mess, 128, 0);
                cout << "Enter Start Date" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter End Date" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Start Time" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter End Time" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Location" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Event" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
            }
            else if (received.compare("4")) {
                mess = "F4";
                send(sockfd, mess, 128, 0);
                numbytes = recv(sockfd, sendbuf, 128, 0);
                received = sendbuf;
                cout << "You have " + sendbuf + " appointments." << endl;
                cout << "Please Enter which appointment you'd like to remove (a number value)." << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Removed." << endl;
            }
            else if (received.compare("5")) {
                mess = "F5";
                send(sockfd, mess, 128, 0);
                numbytes = recv(sockfd, sendbuf, 128, 0);
                received = sendbuf;
                cout << "You have " + sendbuf + " appointments." << endl;
                cout << "Please Enter which appointment you'd like to update (a number value)." << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Start Date" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter End Date" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Start Time" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter End Time" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Location" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Enter Event" << endl;
                getline(cin, mess);
                send(sockfd, mess, 128, 0);
                cout << "Updated" << endl;
            }
            else if (received.compare("6")) {
                mess = "F6";
                send(sockfd, mess, 128, 0);
                cout << "Please select which option you'd like." << endl;
                cout << "1. Display All" << endl;
                getline(cin, received);
                if (received.compare("1")) {
                    mess = "DA1";
                    send(sockfd, mess, 128, 0);
                    numbytes = recv(sockfd, sendbuf, 128, 0);
                    int appNum = sendbuf;
                    for (int i = appNum; i < 0; i--) {
                        numbytes = recv(sockfd, sendbuf, 128, 0);
                        received = sendbuf;
                        cout << received << endl;
                        numbytes = recv(sockfd, sendbuf, 128, 0);
                        received = sendbuf;
                        cout << received << endl;
                        numbytes = recv(sockfd, sendbuf, 128, 0);
                        received = sendbuf;
                        cout << received << endl;
                        numbytes = recv(sockfd, sendbuf, 128, 0);
                        received = sendbuf;
                        cout << received << endl;
                        numbytes = recv(sockfd, sendbuf, 128, 0);
                        received = sendbuf;
                        cout << received << endl;
                    }
                }
            }
            else if(received.compare("7")) {
                mess = "F7";
                send(sockfd, mess, 128, 0);
                cout << "Thank you. Logging out...." << endl;
                login = false;
            }
        }
    }
}