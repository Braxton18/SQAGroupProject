#ifndef PRODMANAGEMENT_H
#define PRODMANGEMENT_H

#include <string>
#include <forward_list>
using namespace std;

struct ProdNode{
    string prodID;
    string prodName;
    float prodPrice;
    int stock;
};

forward_list<ProdNode> productList;

ProdNode createListing();
bool removeListing(string);
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