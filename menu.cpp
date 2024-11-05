#include <iostream>
#include <string>
#include <limits>
#include "registration.h"
#include "prodManagement.h"
using namespace std;

// void registration ();
// void removal ();
// void createListing ();
// void removeListing ();
// void shopping ();
// void accView ();
// void redRewards();


int main (){
    int choice;
    int regis = 1;
    int remov = 2;
    int prodAdd =3;
    int prodRem = 4;
    int shop=5;
    int view= 6;
    int rewards = 7;
    while(true){

    cout << "Please indicate the number of your desired function given the following choices: \n0. Quit \n1. Account Registration \n2. Account Removal \n3. Product Addition \n4. Product Removal \n5. Shopping \n6. View Account \n7. Redeem Rewards \n\n Please ensure that your entry is one of the integer options listed." << endl;
    cin >> choice;
    if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer." << endl;
            continue;
    }
    if (choice == regis){
        goToRegistration();
    }
//     else if(choice == remov){
//         removal();
//     }
    else if(choice == prodAdd){
        productList.push_front( createListing() );
    }
    else if(choice == prodRem){
        string input;
        cout << "Enter the name or ID of the product listing to remove: ";
        cin >> input;           //input validation is taken care of in function
        removeListing( input );
    }
//      else if(choice == shop){
//         shopping();
//     }
//      else if(choice == view){ 
//         accView();
//     }
//      else if(choice == rewards)
//         redRewards();
//     }
else if (choice == 0){
    return 0;
}
    }

}
