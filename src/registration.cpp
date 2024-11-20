#include <iostream>
#include "registration.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <set>
#include <random>
#include <fstream>
using namespace std;


string userName;
string firstName;
string lastName;
string age;
string cardNum;
int userPoints;
int userID[10] = {0};
set<string> existingUsers;
set<int> generatedNums;
set<string> cardNumbers;
set <int> customerCount;
int randomNum;
string customerID;


bool checkUser(string);
string createID();
bool checkName(string );
bool checkNum(string, int, int);
bool checkCard(string);
int generateRandomNum(int first, long long int second);
void loadData();
void saveData();
void saveCustomerInformation();
int findCustomerNum();



void goToRegistration(){ // Function called by the main.cpp file to create the customer
    srand(time(0));
    loadData();
    customerID = createID(); //Create customer ID
    cout<< "Please follow the directions in creating your account:"<< endl;
    do{    //User name  creation
        cout <<"Please enter your user name, starting with 'U_'. Ensure that it is at least 10 characters long and that it ends with at most 3 numbers: ";
        cin >> userName;
    }while (!checkUser(userName));// Checks that the username is valuid given the entered username
    do {    //First Name creation
        cout <<"Please provide your first name. Ensure that there is is not longer than 12 characters, nor that it includes numbers or special characters : ";
        cin >> firstName;
    }
    while(!checkName(firstName)); // Checks that the first name is valid given the entered first name 
    do {    //Last Name creation
        cout <<"Please provide your last name. Ensure that there is is not longer than 12 characters, nor that it includes numbers or special characters: ";
        cin >> lastName;
    }
    while(!checkName(lastName)); // checks that the entered last name is valid given the entered last name 
    do {    //Age creation
        cout<<"Please enter your age. Your age must be between 18-100 and should not start with a 0: ";
        cin >> age;
    }
    while(!checkNum(age, 18, 100)); // Chekcs that the entered age is valid
    do{    //Credit Card Number Creation
        cout << "Please enter your credit card number. Ensure that it is in the format XXXX-XXXX-XXXX: ";
        cin >> cardNum;
    }while(!checkCard(cardNum)); // Checks that the card number is valid given the entered card number
    userPoints =0;    //Points Check
    saveCustomerInformation(); //Writes the customer information into the customer.txt file in the exact same order each time
    saveData(); //Puts each of the entered data points into their respoective files
}

bool checkUser(string username){ // Ensures that the given username meets all of the cirteria set by the assignment requiremnts given the entered username 
    if(username[0] != 'U' ||username[1] != '_'){
        cout<< "Error, you did not add 'U_' at the start of your username, please try again."<< endl;//Error handling
        return false;
    }
    else if (username.length() < 12){
        cout << "Error, your username is not the correct length. Please try again."<< endl;//Error handling
        return false;
    }
    else{
        cout << endl;
    }
    int end = username.length()-4;
    if (isdigit(username[end])){
        cout<< "Error, more than 3 digits are used at the end of the username, please try again"<< endl;//Error handling
        return false;
    }
    for(int i = 2; i <= end; i++){
        if (isdigit(username[i]) || isspace(username[i])){
            cout << "Error, only characters and special characters are allowed in the username, please try again." << endl;//Error handling
            return false;
        }
        else {
            cout << endl;
        }
    }
    if(existingUsers.find(username) != existingUsers.end()){
       cout <<"Sorry, that username has been created before. Try again." << endl;//Error handling
       return false;
    }
    else{
        existingUsers.insert(username); 
    }
    return true;
}

string createID(){ // creates the random account number andd ensures tha the account number is unique each time
    long long int returnedNum = generateRandomNum(1, 9999999999);
    stringstream ss;
    ss<<setw(10) << setfill('0') << returnedNum;
    string numStr = ss.str();
    string custID = "CustID";
    string fullID = custID + numStr;
    return fullID;
}

int generateRandomNum(int first, long long int second){ // generates a random number given the upper and lower bounds and returns a random nummber 
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(first, second);
    do {
        randomNum =  dis(gen);
    }while(generatedNums.find(randomNum) != generatedNums.end());
    generatedNums.insert(randomNum);
    return randomNum;
}

bool checkName(string name){ // Checks that the enterd name is up to the cirteria of the assignment given the entered name 
    if(name.length() > 12){
        cout << "Sorry, your entered name is too long. Please try again."<< endl;//Error handling
        return false;
    }
    else{
        cout<< endl;
    }
    for (char i : name){
        if (isdigit(i) || (!isalpha(i) && !isspace(i))){
            cout << "Sorry, your name contians a number or special character. Please try again."<< endl;//Error handling
            return false;
        }
        else {
            cout << endl;
        }
    }
    return true;
}

bool checkNum(string userAge, int ageMin,  int ageMax){ // Checks that the entered age is within the bounds of the minimum and maximum age and returns true if it is, and false if it is not
    if(userAge.length() > 1 && userAge[0] == '0'){
        cout <<"Sorry, you entered an invalid entry, try again." << endl;//Error handling
        return false;
    }
    else{
        for(char j: userAge){
            if (!isdigit(j)){
                cout << "Sorry, you provided an entry that was not an integer. Try again."<< endl;//Error handling
                return false;
            }
            else{
                cout << endl;
            }
        }
    }
    int trueUserAge = stoi(userAge);
    if(trueUserAge< ageMin){
        cout<< "Sorry, you entered an age that is younger than the bounds. Please try again."<< endl;//Error handling
        return false;
    }
    else if(trueUserAge > ageMax){
        cout <<"Sorry, you entered an age that is higher than the bounds. Please try again."<< endl;//Error handling
        return false;
    }
    else{
        cout << endl;
    }
    return true;
}

bool checkCard(string creditNum){ // Checks if the card number is up to the assignment criteria and is unique, and returns true if it is and false if it is not
    if(creditNum.length()> 14){
        cout << "Sorry, you entered a card number that was too long, try again" << endl;//Error handling
        return false;
    }
    else if(creditNum[4] != '-' || creditNum[9] != '-'){
        cout <<"Sorry, you did not input your card number in the correct format. Try again." << endl;//Error handling
        return false;
    }
    else if(creditNum[0] ==0 ){
        cout <<"Sorry, you can not enter a card number that starts with 0. Please try again." << endl;//Error handling
        return false;
    }
    else {
        cout << endl;
    }
    for (int i =0; i < creditNum.length(); i++){
        if (i==4 || i == 9){
            continue;
        }
        if (creditNum[i] < '0' || creditNum[i] > '9'){
            cout<< "Sorry, you should only enter integers as a card number. Please try again."<< endl;//Error handling
            return false;
        }
    }
    if(cardNumbers.find(creditNum) != cardNumbers.end()){
       cout <<"Sorry, that card number has been created before. Try again."<< endl;//Error handling
       return false;
    }
    else{
    cardNumbers.insert(creditNum); 
    }
    return true;
}

void saveCustomerInformation(){ // Saves all of the data entered by the user into the customer.txt file and writes to the file as a new customer entry
    ofstream outFile("customers.txt", ios::app);
    int customersAmount = findCustomerNum();
    if(outFile.is_open()){
        outFile << "Customer " << customersAmount << "\n"; 
        outFile << "\tID: " << customerID << "\n"; 
        outFile << "\tUser Name: " << userName << "\n"; 
        outFile << "\tFirst Name: " << firstName << "\n"; 
        outFile << "\tLast Name: " << lastName << "\n"; 
        outFile << "\tAge " << age << "\n"; 
        outFile << "\tCredit Card Number: " << cardNum << "\n"; 
        outFile << "\tTotal Reward Points " << userPoints << "\n\n";
        outFile.close(); 
    }
    else{
        cout <<"Error, could not open file. Please try again."<< endl; //Error handling
    }
}

void loadData(){ // Loads the data of all of the files into their own respoective sets to ensure that there is no repeat data 
    ifstream userFile("userNames.txt");
    ifstream cardFile("cardNums.txt");
    ifstream uniqueNumFile("uniqueNums.txt");
    ifstream customerNumFile("customerNum.txt"); 
    if (userFile.is_open()){
        string name;
        while(getline(userFile, name)){
            existingUsers.insert(name);
        }
        userFile.close();
    }
    if (uniqueNumFile.is_open()){
        int num1;
        while(uniqueNumFile >> num1){
            generatedNums.insert(num1);
        }
        uniqueNumFile.close();
    }
    if (customerNumFile.is_open()){
        int num2;
        while(customerNumFile >> num2){
            customerCount.insert(num2);
        }
        customerNumFile.close();
    }
    if (cardFile.is_open()){
        string card;
        while(getline(cardFile, card)){
            cardNumbers.insert(card);
        }
        cardFile.close();
    }
}

void saveData(){ // Saves the newly enteerd data onto their own respective files according to what type of data point they are: accountId, username, card number, or customer number
    ofstream userFile("userNames.txt");
    ofstream cardFile("cardNums.txt");
    ofstream uniqueNumFile("uniqueNums.txt");
    ofstream customerNumFile("customerNum.txt");
    if (userFile.is_open()){
        for (const auto& user : existingUsers){
            userFile << user << endl;
        }
        userFile.close();
    }
    if (cardFile.is_open()){
        for (const auto& card : cardNumbers){
            cardFile << card << endl;
        }
        cardFile.close();
    }
    if (customerNumFile.is_open()){
        for (const auto& custCount : customerCount){
            customerNumFile << custCount << endl;
        }
        customerNumFile.close();
    }
    if (uniqueNumFile.is_open()){
        for (const auto& customerNum : generatedNums){
            uniqueNumFile << customerNum << endl;
        }
        uniqueNumFile.close();
    }
}

int findCustomerNum(){ // Finds the customer number that a newly created cuatomer is, and may give a lower custoimer number to a newly created account if that number had been previously deleted
    int customers =0;
    do {
        customers =  customers + 1;
    }while(customerCount.find(customers) != customerCount.end());
    customerCount.insert(customers);
    return customers;
}
