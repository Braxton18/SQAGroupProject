//Braxton Reece and Grant Wilke

#ifndef PRODMANAGEMENT_H
#define PRODMANAGEMENT_H

#include <string>
#include <forward_list>
#include <iostream>
using namespace std;

//nodes to store each instance of product
//prodID: id number of the product, format: Prod#####
//prodName: name of the product
//prodPrice: price the product sells for
//stock: amount of the item currently available to sell
struct ProdNode{
    string prodID;
    string prodName;
    float prodPrice;
    int stock;
};

//creates a ProdNode object to be added to the product record
//NOTE: must still add the object itself to the record
//parameters: none
//return: ProdNode: object containing all of the information for the specified product
ProdNode createListing();

//removes a product listing from the records
//paramaters: product: either the product name or ID to be removed
//          productList: single linked list of products
//return: bool: true if listing successully removed, otherwise false
bool removeListing(forward_list<ProdNode>& productList, string product);

#endif