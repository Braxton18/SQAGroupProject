#ifndef PRODMANAGEMENT_H
#define PRODMANAGEMENT_H

#include <string>
#include <forward_list>
#include <iostream>
using namespace std;

struct ProdNode{
    string prodID;
    string prodName;
    float prodPrice;
    int stock;
};


ProdNode createListing();
bool removeListing(forward_list<ProdNode>&, string);
bool addStock(int);
bool removeStock(int);

/*
class Product{
    public:
        ProdNode createListing();
        bool removeListing(string);
        bool addStock(int);
        bool removeStock(int);
    private:
};
*/

#endif