#include <iostream>
#include "accountViewing.h"
#include <string>
#include <fstream>
using namespace std;

bool checkEnteredID(string);
void showAccount(string);
string enteredID;

void goToView(){
    cout <<"You are now in the account viewing page.\n"<< endl;
    do{
        cout<<"Please enter the Customer ID of the account that you would like to view: ";
        cin >> enteredID;
    }while(!checkEnteredID(enteredID));
    showAccount(enteredID);
    return;
}

bool checkEnteredID(string ID){
    ifstream file("customers.txt");
    string line;
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return false;
    }
    while (getline(file, line)) {
        // Check if the line contains the ID
        if (line.find("ID: " + ID) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    cout << "Customer ID not found. Please try again.\n";
    return false;
}

void showAccount(string account){
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
        if (accountFound) {
            // Stop reading when hitting an empty line (assumes customers are separated by blank lines)
            if (line.empty()) {
                break;
            }
            cout << line << endl;
        }
    }
    if (!accountFound) {
        cout << "Customer details could not be displayed.\n";
    }
    file.close();
}