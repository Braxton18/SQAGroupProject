#include <iostream>
#include <string>
#include <forward_list>
#include "prodmanagement.h"
using namespace std;


ProdNode createListing(){
    ProdNode newListing;
    cout << "\nEnter the product ID of the new product (up to 5 digits): ";
    string temp;
    cin >> temp;
    while ( temp.length() < 5 ){            //TODO: validate ID input
        temp.insert(temp.begin(), '0');
    }
    newListing.prodID = "Prod" + temp;      //TODO: check input ID against already existing IDs

    cout << "Enter the product name: ";
    cin >> newListing.prodName;

    cout << "Enter the price to list the product at: ";     //TODO: check input is string
    cin >> newListing.prodPrice;

    cout << "How many of the product are ready to sell?: ";
    cin >> newListing.stock;
    while( newListing.stock < 0 ){      //TODO: check that input is int     maybe cin a string and check?
        cout << "Current stock can not be a negative number, please try again: ";
        cin >> newListing.stock;
    }

    return newListing;
}


bool removeListing(forward_list<ProdNode>& productList, string product = "" ){
    if( product == "" ){
        cout << "No product specified\n";
        return false;
    }else{
        forward_list<ProdNode>::iterator prev = productList.before_begin();
        for (forward_list<ProdNode>::iterator it = productList.begin(); it != productList.end(); ++it){
            if( (*it).prodName == product || (*it).prodID == product ){
                productList.erase_after( prev );
                return true;
            } else {
                ++prev;
                //continue;
            }
        }
        return false;
    }
    return false;
}

