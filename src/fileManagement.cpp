//includes
#include <string>
#include <iostream>
#include <fstream>
#include "prodManagement.h"

using namespace std;

bool loadCustomers(string fileName){
    return false;
}

bool loadProducts(forward_list<ProdNode>& prodList, string fileName){
    ifstream fin(fileName);
    if( ! fin.is_open() ){
        cout << "input file not found for products\n";
        return false;
    }else{
        string line;
        ProdNode newListing;
        while( getline(fin, line) ){                //product x
            getline(fin, line);                     //ID
            newListing.prodID = line.erase(0, 1);
            getline(fin, line);                     //product name
            newListing.prodName = line.erase(0, 1);
            getline(fin, line);                     //product price
            newListing.prodPrice = stof(line);
            getline(fin, line);                     //total number of items in store
            newListing.stock = stoi(line);
            prodList.push_front( newListing );
        }
        fin.close();
    }
    return true;
}

bool saveProductData(forward_list<ProdNode>& prodList, string fileName){
    ofstream fout( fileName );
    if( ! fout.is_open() ){
        cout << "output file not found for products\n";
        return false;
    }else{
        int i{ 1 };
        while( ! prodList.empty() ){
            fout << "product " << i << endl
                << '\t' << prodList.front().prodID << endl
                << '\t' << prodList.front().prodName << endl 
                << '\t' << prodList.front().prodPrice << endl 
                << '\t' << prodList.front().stock << endl;
            prodList.pop_front();
            ++i;
        }
    }
    return true;
}
