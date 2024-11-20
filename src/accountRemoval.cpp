#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string enteredUsername;
string enteredNumber;
string enteredCustomerNumber;
string enteredAccountID;

bool checkUsername(string);
bool checkNumber(string);
void removeCustomer(string, string);
void removeUsernameFromFile(string);
void removeCardFromFile(string);
void removeCustomerNumberFromFile(string);
void removeAccountIDFromFile(string);
string extractCustomerNumber(string);
string extractAccountID(string);

void goToRemoval() { //Initial removal funcitno that is called when the removal choice is made on the main.cpp file
    cout << "You are now in the account removal menu." << endl;
    do {
        cout << "Please enter the username of the account you would like to remove: ";
        cin >> enteredUsername;
    } while (!checkUsername(enteredUsername)); // Checks if the username is valid and in the customer file given the entered username
    do {
        cout << "Now, please enter the credit card number of the account you would like to remove: ";
        cin >> enteredNumber;
    } while (!checkNumber(enteredNumber));// Checks if the card number is valid and in the customer file given the entered card number
    enteredCustomerNumber = extractCustomerNumber(enteredUsername);// Extract customer number and account ID from file given the entered username and card number 
    enteredAccountID = extractAccountID(enteredUsername);

    if (enteredCustomerNumber.empty() || enteredAccountID.empty()) {// Error handling
        cout << "Error: Missing customer number or account ID. Aborting removal." << endl;
        return;
    }
    else {cout << endl;}
    // Remove customer data from all necessary files
    removeUsernameFromFile(enteredUsername); //uses the entered username to find the username from the userNames.txt file and delete it 
    removeCardFromFile(enteredNumber); // uses the netered card number to find the card number on the cardNums.txt file and remove it 
    removeCustomerNumberFromFile(enteredCustomerNumber); // uses the previous funciton to find the customer number of the specific customer and remove s it from the customerNum.txt file
    removeAccountIDFromFile(enteredAccountID); // uses the previously called funciton to find the customer account id and remove it from the uniqueNums.txt file 
    removeCustomer(enteredUsername, enteredNumber); // Removes the customer entirely from the customers.txt file given the entered username and card number
    cout << "Customer removal successful." << endl;
}

bool checkUsername(string username) { // Takes the entered username and then returns true if that username exists in the customer file and false if it does not exist 
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers.txt file" << endl;// Error handling
        return false;
    }
    else{cout <<"";}
    string line;
    while (getline(file, line)) {
        if (line.find("User Name: " + username) != string::npos) {
            file.close();
            return true;
        }
        else{cout<<"";}
    }
    file.close();
    cout << "Username not found. Please try again." << endl;// Error handling
    return false;
}

bool checkNumber(string number) { //Checks to see if the entered card number matches along iwth the previouosly entered user name to ensure that the same account is refrenced in removal
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers file." << endl;// Error handling
        return false;
    }
    else{cout <<"";}
    string line;
    bool inNumBlock = false;
    while (getline(file, line)) {
        if (line.find("User Name: " + enteredUsername) != string::npos) {
            inNumBlock = true;
        }
        else{ cout<<"";}
        if (inNumBlock && line.find("Credit Card Number: " + number) != string::npos) {
            file.close();
            return true;
        }
        else{cout<<"";}
    }
    file.close();
    cout << "Credit card number does not match the username." << endl;// Error handling
    return false;
}

void removeCustomer(string customer, string card) { // Uses the card number and the username to remove the cusomter from the customer.txt fle 
    ifstream file("customers.txt");
    if (!file.is_open()) {// Error handling
        cout << "Unable to open customers file" << endl;
        return;
    }
    vector<string> lines; // Store all lines from the file
    string line;
    vector<string> buffer; // Temporary buffer for tracking lines around the match
    int removeStart = -1;  // Index of where to start removing
    int removeEnd = -1;    // Index of where to stop removing
    while (getline(file, line)) {    // Read all lines into a vector
        lines.push_back(line);
    }
    file.close();
    for (size_t i = 0; i < lines.size(); ++i) {    // Search for the username
        if (lines[i].find("User Name: " + customer) != string::npos) {
            int customerNumLine = i - 2;  // Customer number is 2 lines above
            int accountIDLine = i + 4;    // Account ID is 4 lines below
            if (customerNumLine >= 0 && accountIDLine < lines.size()) {
                enteredCustomerNumber = lines[customerNumLine];
                enteredAccountID = lines[accountIDLine];
                removeStart = (i >= 2) ? i - 2 : 0;  // Start 2 lines above the username
                removeEnd = (i + 6 < lines.size()) ? i + 6 : lines.size() - 1; // End 6 lines below
                break;
            }
        }
    }
    if (removeStart == -1 || removeEnd == -1) {    // If no match was found
        cout << "Customer not found for removal." << endl;// Error handling
        return;
    }
    ofstream outFile("customers.txt", ios::trunc);    // Write remaining lines back to the file
    if (!outFile.is_open()) {// Error handling
        cout << "Error, unable to write to customers file" << endl;
        return;
    }
    for (size_t i = 0; i < lines.size(); ++i) {
        if (i >= static_cast<size_t>(removeStart) && i <= static_cast<size_t>(removeEnd)) {  // Skip lines in the removal range
            continue;
        }
        outFile << lines[i] << endl;
    }
    outFile.close();
}

void removeUsernameFromFile(string username) { //Uses the entered username to remove the username from the userNames.txt file
    ifstream file("userNames.txt");
    if (!file.is_open()) {// Error handling
        cout << "Unable to open usernames.txt file." << endl;
        return;
    }
    vector<string> lines;
    string line;
    bool found = false;
    while (getline(file, line)) {// Read all lines into the vector
        if (line != username) {  // If the line doesn't match the username, keep it
            lines.push_back(line);
        } else {
            found = true;  //Found the username to remove
        }
    }
    file.close();

    if (!found) {
        cout << "Username not found in usernames file." << endl;// Error handling
        return;
    }
    ofstream outFile("userNames.txt", ios::trunc);// Write the modified lines back to the file
    if (!outFile.is_open()) {
        cout << "Error, unable to write to usernames file" << endl;// Error handling
        return;
    }
    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}

void removeCardFromFile(string cardNumber) {// removes the previously entered card number form the cardNums.txt file after it is ensuresd that it exists 
    ifstream file("cardNums.txt");
    if (!file.is_open()) {// Error handling
        cout << "Unable to open card_numbers.txt file." << endl;
        return;
    }
    vector<string> lines;
    string line;
    bool found = false;
    while (getline(file, line)) {// Read all lines into the vector
        if (line != cardNumber) {  // If the line doesn't match the card number, keep it
            lines.push_back(line);
        } else {
            found = true;  // found the card number to remove
        }
    }
    file.close();
    if (!found) {// Error handling
        cout << "Credit card number not found in card_numbers file." << endl;
        return;
    }
    ofstream outFile("cardNums.txt", ios::trunc);
    if (!outFile.is_open()) {// Error handling
        cout << "Error, unable to write to card_numbers file" << endl;
        return;
    }
    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}

void removeCustomerNumberFromFile(string customerNumber) { // Removes the singular indicating customer number from the customerNum.txt file 
    ifstream file("customerNum.txt");
    if (!file.is_open()) {// Error handling
        cout << "Unable to open customerNum.txt file." << endl;
        return;
    }
    vector<string> lines;
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line != customerNumber) { // Match against the parameter
            lines.push_back(line);
        } else {
            found = true;
        }
    }
    file.close();
    if (!found) {// Error handling
        cout << "Customer number not found in customerNum.txt file." << endl;
        return;
    }
    ofstream outFile("customerNum.txt", ios::trunc);
    if (!outFile.is_open()) {// Error handling
        cout << "Error, unable to write to customerNum.txt file." << endl;
        return;
    }
    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}

void removeAccountIDFromFile(string accountID) { // Removes the account ID from the uniqueNums.txt file, therefore removing all aspects of the customer
     ifstream file("uniqueNums.txt");// Error handling
    if (!file.is_open()) {
        cout << "Unable to open uniqueNums.txt file." << endl;
        return;
    }
    vector<string> lines;
    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line != enteredAccountID) {  // If the line doesn't match the account ID, keep it
            lines.push_back(line);
        } else {
            found = true;  // found the account ID to remove
        }
    }
    file.close();
    if (!found) {
        cout << "Account ID not found in uniqueNums.txt file." << endl;// Error handling
        return;
    }
    ofstream outFile("uniqueNums.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error, unable to write to uniqueNums.txt file" << endl;// Error handling
        return;
    }
    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}

string extractCustomerNumber(string username) { // Gets the customer number by moving up the created customer.txt entry given the entered username. Returns the customer number
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers.txt file." << endl;// Error handling
        return "";
    }
    string line;
    vector<string> lines;
    while (getline(file, line)) {  // Read the file into a vector
        lines.push_back(line);
    }
    file.close();
    for (size_t i = 0; i < lines.size(); ++i) { // Search for the username in the file
        if (lines[i].find("User Name: " + username) != string::npos) {
            if (i >= 2) {  // Ensure there are at least 2 lines above
                string customerLine = lines[i - 2]; // 2 lines above
                size_t pos = customerLine.find("Customer ");
                if (pos != string::npos) {
                    string customerNumber = customerLine.substr(pos + 9);
                    customerNumber.erase(customerNumber.find_last_not_of(" \n\r\t") + 1); // Trim
                    return customerNumber;
                }
            }
            break;
        }
    }
    cout << "Customer number extraction failed." << endl;// Error handling
    return "";
}

string extractAccountID(string username) { // Extracts the customer's accountID by moving through the entry in the customer.txt file for that specific customer given the entered username. Returns the account ID
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers.txt file." << endl;// Error handling
        return "";
    }
    string line;
    vector<string> lines;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    for (size_t i = 0; i < lines.size(); ++i) {    // Search for the username in the file
        if (lines[i].find("User Name: " + username) != string::npos) {
            if (i >= 1) {  // Ensure there's at least 1 line above
                string accountLine = lines[i - 1]; // 1 line above the username
                size_t pos = accountLine.find("ID: CustID");
                if (pos != string::npos) {
                    string accountID = accountLine.substr(pos + 11);
                    accountID.erase(accountID.find_last_not_of(" \n\r\t") + 1); // Trim whitespace
                    return accountID;
                }
            }
            break;
        }
    }
    cout << "Account ID extraction failed." << endl;// Error handling
    return "";
}
