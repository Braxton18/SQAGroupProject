#include <iostream>
#include "accountViewing.h"
#include <string>
#include <fstream>
using namespace std;

bool checkEnteredID(string);
void showAccount(string);
string enteredID;

void goToView(){ //Initial funciton that is called by the main.cpp program whenever the view account is selected
    cout <<"You are now in the account viewing page.\n"<< endl;
    do{
        cout<<"Please enter the Customer ID of the account that you would like to view: ";
        cin >> enteredID;
    }while(!checkEnteredID(enteredID));// Loops through the check until the check returns true
    showAccount(enteredID);
    return;
}

bool checkEnteredID(string ID){// Takes the entereed customer ID and ensures that it is in the customer file before moving on to displaying customer infomraiton 
    ifstream file("customers.txt");
    string line;
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return false; // 
    }
    else{ 
        cout <<"" <<endl;
    }
    while (getline(file, line)) {
        // Check if the line contains the ID
        if (line.find("ID: " + ID) != string::npos) {
            file.close();
            return true;// Returns truee if the ID is found within the customer.txt file
        }
        else{ cout<<"";}
    }
    file.close();
    cout << "Customer ID not found. Please try again.\n";
    return false; // Returns false if the account ID entered is not found in the customer file
}

void showAccount(string account){ //Displys the account information based on the account number that it is given from the user 
    ifstream file("customers.txt");
    string line;
    bool accountFound = false;
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }
    while (getline(file, line)) {
        if (line.find("ID: " + account) != string::npos) {
            accountFound = true;
            cout << "Customer Information:\n";
            cout << line << endl; // Print the ID line
            continue; // Move to the next line
        }
        else{ cout <<endl;}
        if (accountFound) {
            if (line.empty()) {   // Stop reading when hitting an empty line 
                break;
            }
            cout << line << endl;
        }
        else{cout <<"";}
    }
    if (!accountFound) {
        cout << "Customer details could not be displayed.\n";//Error handling
    }
    else{cout <<"";}
    file.close();
}
