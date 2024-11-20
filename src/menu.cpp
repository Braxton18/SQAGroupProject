#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>
#include "registration.h"
#include "prodManagement.h"
#include "fileManagement.h"
#include "shopping.h"
#include "accountRemoval.h"
#include "accountViewing.h"

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
    const double sleepTime{ 1.5 };
    forward_list<ProdNode> productList;
    forward_list<UserNode> userList;
    forward_list<TransNode> transList;

    loadProducts(productList, "products.txt");      //technically returns T/F if wanted to ensure file was found
    loadTransactions(transList, "transactions.txt");

    while(true){
        cout << "\nPlease indicate the number of your desired function given the following choices: \n0. Quit \n1. Account Registration \n2. Account Removal \n3. Product Addition \n4. Product Removal \n5. Shopping \n6. View Account \n7. Redeem Rewards \n\n Please ensure that your entry is one of the integer options listed." << endl;
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
        else if(choice == remov){
            goToRemoval();
        }
        else if(choice == prodAdd){
            productList.push_front( createListing() );
            cout << "Listing added\n";
            sleep(sleepTime);
        }
        else if(choice == prodRem){
            string input;
            cout << "Enter the name or ID of the product listing to remove: ";
            cin >> input;           //input validation is taken care of in function
            if( removeListing( productList, input )){
                cout << "Product successfully removed\n";
                sleep(sleepTime);
            }else{
                cout << "Product not found\n";
                sleep(sleepTime);
            };
        }
          else if(choice == shop){
            loadCustomers( userList, "customers.txt" );
            transList.push_front( shopping( userList, productList, transList ) );
         }
         else if(choice == view){ 
            goToView();
        }
    //      else if(choice == rewards)
    //         redRewards();
    //     }
        else if (choice == 0){
            saveProductData(productList, "products.txt");
            saveTransactions(transList, "transactions.txt");
            return 0;
        }
    }
}
