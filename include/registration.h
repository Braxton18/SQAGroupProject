#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>

using namespace std;

void goToRegistration();

struct UserNode{
    string ID;
    string userName;
    string fName;
    string lName;
    int age;
    string cardNum;
    int points;
};

#endif