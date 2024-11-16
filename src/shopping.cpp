//includes and such

#include "shopping.h"

using namespace std;

//get customer information
    //maybe load into object?
void shopping( forward_list<UserNode> userList, forward_list<ProdNode> prodList ){
    string userID;
    forward_list<UserNode>::iterator userIt{ NULL };
    for( int i{ 0 }; i < 10 && userIt == NULL; ++i ){       //only allow 10 attempts
        cout << "Please enter either your username or userID: ";
        cin userID;
        userId = findUser( userID );
    }
    if( userIt == NULL ){
        cout << "max attempts made, returning to menu...";
        sleep( 1.5 );
        return();
    }elsee{
        int n{ 0 };
        int purchaseFlag{ 0 };
        while( true ){
            displayProds( prodList, 5, n );
            cout << "\nEnter 0 to go back to menu\n\t1 to see more\n\t2 to go see previous\n\tor name/ID of the item you would like to buy: ";
            string product;
            cin >> product;
            //attemptPurchase( prodList, product, userIt );
            switch(product){
                case "0": return();
                case "1": n += 5;
                    break;
                case "2": 
                    if( n >= 5 ){
                        n -= 5;
                    }else{
                        cout << "This is the first page\n";
                    }
                    break;
                default: 
                    purchaseFlag = purchase( prodList, product, userIt );
                    //TODO: use purchase flag to either try again, add points
                    break;
            }
        }

    }
};

forward_list<UserNode>::iterator findUser( string user, forward_list<UserNode> userList ){
    for( forward_list<UserNode>::iterator it = userList.begin(); it != userList.end(); ++it ){
        if( (*it).ID == user || (*it).username == user ){
            return it;
        }else{
            //continue
        }
    }
    cout << "user not found< enter in format U_<userId> for your username, or CustID<yourID> for your ID\n";
    return NULL;
};

void displayProds( forward_list<ProdNode> prodList, int x, int n = 0 ){
    forward_list<ProdNode>::iterator it = prodList.begin();
    for( ; n > 0; --n){
        if( it == prodList.end() ){
            cout << "no more products to show\n";
            return();
        }else{
            ++it;       //move to the node at index n, NOTE: didn't use advance() due to possibility of seg fault

        }
    };
    cout << endl;
    for( ; x > 0 && it != prodList.end(); --x ){
        cout << "\n"
            << (*it).prodName << "\t\t" << (*it).prodPrice << "\t\tAmount available: " << (*it).stock << endl;
        ++it;
    }
    cout << endl;
}

//request input to buy product or see next product page
    //on buy: break
    //on next: display next X products

//buy
    //"get money from credit card"
    //add points to user information
    //remove stock from product information
