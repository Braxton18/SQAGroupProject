#include "prodManagement.h"
#include <iostream>
#include <string>
#include <forward_list>
using namespace std;


//creates a ProdNode object to be added to the product record
//NOTE: must still add the object itself to the record
//parameters: none
//return: ProdNode: object containing all of the information for the specified product
ProdNode createListing(){       //should this be dynamically allocated, how to deallocate a linked list?
    ProdNode newListing;
    cout << "\nEnter the product ID of the new product (up to 5 digits): ";
    string temp;
    cin >> temp;
    while ( temp.length() < 5 ){            //TODO: validate ID input
        temp.push_back('0');                //TODO: i don't like this
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

//removes a product listing from the records
//paramaters: product: either the product name or ID to be removed
//          productList: single linked list of products
//return: bool: true if listing successully removed, otherwise false
bool removeListing(forward_list<ProdNode> productList, string product = "" ){
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
        cout << "Product not found\n";
        return false;
    }
    return false;
}

//adds a specified number to the current stock level
//paramaters: num: the number of items being added to stock level, default is 1
//return: bool: true if stock added successfully, false otherwise
bool addStock( int num = 1 ){
    return false;
}

//removes a specified number from the current stock level
//paramaters: num: the number of items being removed from the stock level, default is 1
//return: bool: true if stock removed successfully, false otherwise
bool removeStock( int num = 1 ){
    return false;
}