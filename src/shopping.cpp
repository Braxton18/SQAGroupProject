//includes and such

#include "shopping.h"

using namespace std;


TransNode shopping( forward_list<UserNode>& userList, forward_list<ProdNode>& prodList, forward_list<TransNode>& transList ){
    string userID;
    TransNode transaction = {.total = 0, .rewards = 0};
    //get user iterator to access
    forward_list<UserNode>::iterator userIt{ userList.before_begin() };
    for( int i{ 0 }; i < 10 && userIt == userList.before_begin(); ++i ){       //only allow 10 attempts
        cout << "Please enter either your username or userID: ";
        cin >> userID;
        userIt = findUser( userID, userList );
    }
    if( userIt == userList.end() ){   //Fort Knox level security
        cout << "max attempts made, returning to menu...";
        sleep( 1.5 );
        return transaction;
    }else{
        //display products and attempt to purchase
        int n{ 0 };
        int amount{ 0 };
        int purchaseFlag{ 0 };
        string temp;
        do{
            displayProds( prodList, 5, n );
            cout << "\nEnter 0 to go back to menu\n\t1 to see more\n\t2 to go see previous\n\tor name/ID of the item you would like to buy: ";
            string product;
            cin >> product;
            //menu options
            if( product == "0" ){
                return transaction;
            }else if( product == "1" ){
                n += 5;
            }else if( product == "2" ){
                if( n >= 5 ){
                    n -= 5;
                }else{
                    cout << "This is the first page\n";
                }
            }else{
                do{
                    cout << "How many would you like to purchase?: ";
                    cin >> temp;                      //TODO: input validation
                    amount = toInt(temp);
                    purchaseFlag = purchase( prodList, product, amount, userIt, transaction );
                }while( purchaseFlag == 1 );    //while not enough stock    TODO: add in limit to loop
            }
        }while( purchaseFlag == 0 || purchaseFlag == 2 );
    }
    return transaction;
};

forward_list<UserNode>::iterator findUser( string user, forward_list<UserNode>& userList ){
    for( forward_list<UserNode>::iterator it = userList.begin(); it != userList.end(); ++it ){
        if( (*it).ID == user || (*it).userName == user ){
            return it;
        }else{
            //continue
        }
    }
    cout << "user not found< enter in format U_<userId> for your username, or CustID<yourID> for your ID\n";
    return userList.end();
};

void displayProds( forward_list<ProdNode>& prodList, int x, int n = 0 ){
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

int purchase( forward_list<ProdNode>& prodList, string product, int amnt, forward_list<UserNode>::iterator it, TransNode& T ){
    //check amnt -> if <= 0 -> return 0 (purchase successful);
    if( amnt <= 0 ){
        return 0;       //purchase successful
    }else{
        forward_list<ProdNode>::iterator prodIt = findProduct( prodList, product );
        if( prodIt == prodList.end() ){
            return 2;   //product not found
        }else{
            //found it
            if( amnt <= (*prodIt).stock ){
                (*prodIt).stock = (*prodIt).stock - amnt;
                T.total += ( amnt * (*prodIt).prodPrice );
                T.prodIDs += (' ' + (*prodIt).prodID );
                T.userID = (*it).userName;
                //TODO T.ID
                return 0;   //purchase successful
            }else{      //stock < amnt
                cout << "Not enough stock available\n";
                sleep(1.2);
                return 1;   //not enough stock
            }
        }
    }
    
};

forward_list<ProdNode>::iterator findProduct( forward_list<ProdNode>& prodList, string product ){
    forward_list<ProdNode>::iterator it = prodList.begin();
    while( it != prodList.end() ){
        if( product == (*it).prodID || product == (*it).prodName ){
            return it;
        }else{
            ++it;
        }
    }
    cout << "product not found\n";
    sleep(1.2);
    return prodList.end();
}

int toInt( string s ){
    string temp = "";
    for( string::iterator i{ s.begin() }; i != s.end(); ++i ){
        if( isdigit(*i) ){
            temp.push_back( *i );
        }else{
            //continue;
        }
    }
    if( temp.length() > 0 ){
        return stoi(temp);
    }else{
        return 0;
    }
}



//buy
    //"get money from credit card"
    //add points to user information
    //remove stock from product information
