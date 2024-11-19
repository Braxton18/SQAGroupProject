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

void goToRemoval() {
        cout << "You are now in the account removal menu." << endl;

    do {
        cout << "Please enter the username of the account you would like to remove: ";
        cin >> enteredUsername;
    } while (!checkUsername(enteredUsername));

    do {
        cout << "Now, please enter the credit card number of the account you would like to remove: ";
        cin >> enteredNumber;
    } while (!checkNumber(enteredNumber));

    // Extract customer number and account ID from file
    enteredCustomerNumber = extractCustomerNumber(enteredUsername);
    enteredAccountID = extractAccountID(enteredUsername);

    if (enteredCustomerNumber.empty() || enteredAccountID.empty()) {
        cout << "Error: Missing customer number or account ID. Aborting removal." << endl;
        return;
    }

    // Remove customer data from all necessary files
    removeUsernameFromFile(enteredUsername);
    removeCardFromFile(enteredNumber);
    removeCustomerNumberFromFile(enteredCustomerNumber);
    removeAccountIDFromFile(enteredAccountID);
    removeCustomer(enteredUsername, enteredNumber);

    cout << "Customer removal successful." << endl;
}

bool checkUsername(string username) {
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers.txt file" << endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (line.find("User Name: " + username) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    cout << "Username not found. Please try again." << endl;
    return false;
}

bool checkNumber(string number) {
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers file." << endl;
        return false;
    }
    string line;
    bool inNumBlock = false;
    while (getline(file, line)) {
        if (line.find("User Name: " + enteredUsername) != string::npos) {
            inNumBlock = true;
        }
        if (inNumBlock && line.find("Credit Card Number: " + number) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    cout << "Credit card number does not match the username." << endl;
    return false;
}

void removeCustomer(string customer, string card) {
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers file" << endl;
        return;
    }
    vector<string> lines; // Store all lines from the file
    string line;
    vector<string> buffer; // Temporary buffer for tracking lines around the match
    int removeStart = -1;  // Index of where to start removing
    int removeEnd = -1;    // Index of where to stop removing

    // Read all lines into a vector
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Search for the username
    for (size_t i = 0; i < lines.size(); ++i) {
        // Match the username
        if (lines[i].find("User Name: " + customer) != string::npos) {
            // Assuming the customer number is 2 lines above and account ID is 2 lines below
            int customerNumLine = i - 2;  // Customer number is 2 lines above
            int accountIDLine = i + 4;    // Account ID is 4 lines below

            if (customerNumLine >= 0 && accountIDLine < lines.size()) {
                // We have valid lines for customer number and account ID
                enteredCustomerNumber = lines[customerNumLine];
                enteredAccountID = lines[accountIDLine];

                // Determine the block to remove (starting from 2 lines before the username)
                removeStart = (i >= 2) ? i - 2 : 0;  // Start 2 lines above the username
                removeEnd = (i + 6 < lines.size()) ? i + 6 : lines.size() - 1; // End 6 lines below
                break;
            }
        }
    }

    // If no match was found
    if (removeStart == -1 || removeEnd == -1) {
        cout << "Customer not found for removal." << endl;
        return;
    }

    // Write remaining lines back to the file
    ofstream outFile("customers.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error, unable to write to customers file" << endl;
        return;
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        // Skip lines in the removal range
        if (i >= static_cast<size_t>(removeStart) && i <= static_cast<size_t>(removeEnd)) {
            continue;
        }
        outFile << lines[i] << endl;
    }
    outFile.close();
}

void removeUsernameFromFile(string username) {
    ifstream file("userNames.txt");
    if (!file.is_open()) {
        cout << "Unable to open usernames.txt file." << endl;
        return;
    }
    vector<string> lines;
    string line;
    bool found = false;

    // Read all lines into the vector
    while (getline(file, line)) {
        if (line != username) {  // If the line doesn't match the username, keep it
            lines.push_back(line);
        } else {
            found = true;  // We found the username to remove
        }
    }
    file.close();

    if (!found) {
        cout << "Username not found in usernames file." << endl;
        return;
    }

    // Write the modified lines back to the file
    ofstream outFile("userNames.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error, unable to write to usernames file" << endl;
        return;
    }

    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}

void removeCardFromFile(string cardNumber) {
    ifstream file("cardNums.txt");
    if (!file.is_open()) {
        cout << "Unable to open card_numbers.txt file." << endl;
        return;
    }
    vector<string> lines;
    string line;
    bool found = false;

    // Read all lines into the vector
    while (getline(file, line)) {
        if (line != cardNumber) {  // If the line doesn't match the card number, keep it
            lines.push_back(line);
        } else {
            found = true;  // We found the card number to remove
        }
    }
    file.close();

    if (!found) {
        cout << "Credit card number not found in card_numbers file." << endl;
        return;
    }

    // Write the modified lines back to the file
    ofstream outFile("cardNums.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error, unable to write to card_numbers file" << endl;
        return;
    }

    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}

void removeCustomerNumberFromFile(string customerNumber) {
    ifstream file("customerNum.txt");
    if (!file.is_open()) {
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

    if (!found) {
        cout << "Customer number not found in customerNum.txt file." << endl;
        return;
    }

    ofstream outFile("customerNum.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error, unable to write to customerNum.txt file." << endl;
        return;
    }

    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}

void removeAccountIDFromFile(string accountID) {
     ifstream file("uniqueNums.txt");
    if (!file.is_open()) {
        cout << "Unable to open uniqueNums.txt file." << endl;
        return;
    }
    vector<string> lines;
    string line;
    bool found = false;

    // Read all lines into the vector
    while (getline(file, line)) {
        if (line != enteredAccountID) {  // If the line doesn't match the account ID, keep it
            lines.push_back(line);
        } else {
            found = true;  // We found the account ID to remove
        }
    }
    file.close();

    if (!found) {
        cout << "Account ID not found in uniqueNums.txt file." << endl;
        return;
    }

    // Write the modified lines back to the file
    ofstream outFile("uniqueNums.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error, unable to write to uniqueNums.txt file" << endl;
        return;
    }

    for (const string& savedLine : lines) {
        outFile << savedLine << endl;
    }
    outFile.close();
}
string extractCustomerNumber(string username) {
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers.txt file." << endl;
        return "";
    }

    string line;
    vector<string> lines;

    // Read the file into a vector for easy line-based access
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Search for the username in the file
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find("User Name: " + username) != string::npos) {
            if (i >= 2) {  // Ensure there are at least 2 lines above
                string customerLine = lines[i - 2]; // 2 lines above
                size_t pos = customerLine.find("Customer ");
                if (pos != string::npos) {
                    string customerNumber = customerLine.substr(pos + 9);
                    customerNumber.erase(customerNumber.find_last_not_of(" \n\r\t") + 1); // Trim
                    cout << "Extracted customer number: " << customerNumber << endl; // Debug print
                    return customerNumber;
                }
            }
            break;
        }
    }

    cout << "Customer number extraction failed." << endl;
    return "";
}

string extractAccountID(string username) {
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Unable to open customers.txt file." << endl;
        return "";
    }
    string line;
    vector<string> lines;
    // Read the file into a vector
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    // Search for the username in the file
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find("User Name: " + username) != string::npos) {
            if (i >= 1) {  // Ensure there's at least 1 line above
                string accountLine = lines[i - 1]; // 1 line above the username
                size_t pos = accountLine.find("ID: CustID");
                if (pos != string::npos) {
                    string accountID = accountLine.substr(pos + 11);
                    accountID.erase(accountID.find_last_not_of(" \n\r\t") + 1); // Trim whitespace
                    cout << "Extracted account ID: " << accountID << endl; // Debug print
                    return accountID;
                }
            }
            break;
        }
    }
    cout << "Account ID extraction failed." << endl;
    return "";
}