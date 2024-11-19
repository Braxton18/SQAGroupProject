//includes and such

#include "shopping.h"

using namespace std;


void shopping( forward_list<UserNode> userList, forward_list<ProdNode> prodList ){
    string userID;
    //get user iterator to access
    forward_list<UserNode>::iterator userIt{ NULL };
    for( int i{ 0 }; i < 10 && userIt == NULL; ++i ){       //only allow 10 attempts
        cout << "Please enter either your username or userID: ";
        cin userID;
        userId = findUser( userID );
    }
    if( userIt == NULL ){   //Fort Knox level security
        cout << "max attempts made, returning to menu...";
        sleep( 1.5 );
        return;
    }else{
        //display products and attempt to purchase
        int n{ 0 };
        int amount{ 0 };
        int spent{ 0 };
        int purchaseFlag{ 0 };
        do{
            displayProds( prodList, 5, n );
            cout << "\nEnter 0 to go back to menu\n\t1 to see more\n\t2 to go see previous\n\tor name/ID of the item you would like to buy: ";
            string product;
            cin >> product;
            //menu options
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
                    cout << "How many would you like to purchase?: ";
                    cin >> amount;                      //TODO: input validation
                    purchaseFlag = purchase( prodList, product, amount, userIt, spent );
                    //TODO: use purchase flag to either try again, add points
                    break;
            }
        }while( purchaseFlag == 0 )

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
            return;
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

int purchase( forward_list<ProdNode> prodList, string product, int amnt, forward_list<UserNode>::iterator it, int& spent ){
    //check amnt -> if <= 0 -> return 0 (purchase successful);
    if( amnt <= 0 ){
        return 0;       //purchase successful
    }else{      //maybe do this in buy f()
        prodIt = findProduct( prodList, product );      //TODO: implement findProduct
        if( prodIt == NULL ){
            return 2;   //product not found
        }else{
            //found it
            if( amnt <= (*prodIt).stock ){
                //there is enough stock, buy it TODO
                return 0;   //purchase successful
            }else if( (*prodIt).stock == 0 ){
                cout << "No stock available\n";
                return 1;   //not enough stock
            }else{  //stock < amnt
                cout << "There are currently " << (*prodIt).stock << " of that item available, how many would you like?: ";
                cin amnt;
                return purchase( prodList, product, amnt, it, spent );  //dont love this, technically may be able to stack infinte recursions
            }
        }
    }
    
    //check available stock
    //if (stock == 0) -> cout no stock available -> return 1 (not enough stock)
    //if (stock too low) -> cout stock and ask how many they would like
    //      if(stock still too low) -> cout not enough available -> return 1 (not enough stock)
    //else subtract amt from stock
    //add transaction to record and add total amount spent
    //ask for another purchase
    //if yes -> loop
    //else -> return 0 (purchase successful) NOTE: no purchase actually necessary (amnt <= 0)

};

forward_list<ProdNode>::iterator findProduct( forward_list<ProdNode> prodList, string product ){
    forward_list<ProdNode>::iterator it = prodList.before_begin();
    while( it != prodList.end() ){
        if( product == (*it).prodID || product == (*it).prodName ){
            return it;
        }else{
            continue;
        }
    }
    return NULL;
}



//buy
    //"get money from credit card"
    //add points to user information
    //remove stock from product information
