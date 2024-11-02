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
using namespace std;


// char userName[];
int userNum[3];
string firstName;
string lastName;
string age;
string cardNum;
int userID[10] = {0};
set<int> generatedNums;
set<string> cardNumbers;
int randomNum;
string customerID;
string createID();
bool checkName(string );
bool checkNum(string, int, int);
bool checkCard(string);
int generateRandomNum(int first, long long int second);


void goToRegistration(){
    srand(time(0));

    //User name  creation 


    //Create customer ID
    customerID = createID();
    cout<< "Please follow the directions in creating your account:"<< endl;

    //First Name creation
    do {
        cout <<"Please provide your first name. Ensure that there is is not longer than 12 characters, nor that it includes numbers or special characters : ";
        cin >> firstName;
    }
    while(!checkName(firstName));

    //Last Name creation
    do {
        cout <<"Please provide your last name. Ensure that there is is not longer than 12 characters, nor that it includes numbers or special characters: ";
        cin >> lastName;
    }
    while(!checkName(lastName));

    //Age creation
    do {
        cout<<"Please enter your age. Your age must be between 18-100 and should not start with a 0: ";
        cin >> age;
    }
    while(!checkNum(age, 18, 100));

    //Credit Card Number Creation
    do{
        cout << "Please eneter your credit card number. Ensure that it is in the format XXXX-XXXX-XXXX: ";
        cin >> cardNum;
    }while(!checkCard(cardNum));

    //Points Check

    
}

string createID(){
    long long int returnedNum = generateRandomNum(1, 9999999999);

    stringstream ss;
    ss<<setw(10) << setfill('0') << returnedNum;
    string numStr = ss.str();
    string custID = "CustID";
    string fullID = custID + numStr;

    return fullID;
}

int generateRandomNum(int first, long long int second){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(first, second);
    do {
        randomNum =  dis(gen);
    }while(generatedNums.find(randomNum) != generatedNums.end());

    generatedNums.insert(randomNum);

    return randomNum;
}

bool checkName(string name){

    if(name.length() > 12){
        cout << "Sorry, your entered name is too long. Please try again."<< endl;
        return false;
    }
    else{
        cout<< endl;
    }

    for (char i : name){
        if (isdigit(i) || (!isalpha(i) && !isspace(i))){
            cout << "Sorry, your name contians a number or special character. Please try again."<< endl;
            return false;
        }
        else {
            cout << endl;
        }
    }
    return true;
}

bool checkNum(string userAge, int ageMin,  int ageMax){
    if(userAge.length() > 1 && userAge[0] == '0'){
        cout <<"Sorry, you entered an invalid entry, try again." << endl;
        return false;
    }
    else{
        for(char j: userAge){
            if (!isdigit(j)){
                cout << "Sorry, you provided an entry that was not an integer. Try again."<< endl;
                return false;
            }
            else{
                cout << endl;
            }
        }
    }
    int trueUserAge = stoi(userAge);
    if(trueUserAge< ageMin){
        cout<< "Sorry, you entered an age that is younger than the bounds. Please try again."<< endl;
        return false;
    }
    else if(trueUserAge > ageMax){
        cout <<"Sorry, you entered an age that is higher than the bounds. Please try again."<< endl;
    }
    else{
        cout << endl;
    }
    return true;
}

bool checkCard(string creditNum){
    if(creditNum.length()> 14){
        cout << "Sorry, you entered a card number that was too long, try again" << endl;
        return false;
    }
    else if(creditNum[4] != '-' || creditNum[9] != '-'){
        cout <<"Sorry, you did not input your card number in the correct format. Try again." << endl;
        return false;
    }
    else if(creditNum[0] ==0 ){
        cout <<"Sorry, you can not enter a card number that starts with 0. Please try again." << endl;
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
            cout<< "Sorry, you should only enter integers as a card number. Please try again."<< endl;
            return false;
        }
    }
    if(cardNumbers.find(creditNum) != cardNumbers.end()){
       cout <<"Sorry, that card number has been created before. Try again.";
       return false;
    }
    else{
    cardNumbers.insert(creditNum); 
    }
}

