//includes
#include <string>
#include <iostream>
#include <fstream>
#include "fileManagement.h"
#include "prodManagement.h"
#include "registration.h"

using namespace std;

bool loadCustomers(forward_list<UserNode>& userList, string fileName){
    userList.clear();       //clear any current data
    ifstream fin(fileName);
    if ( !fin.is_open() ){
        cout << "input file not found for products\n";
        return false;
    }else{
        string line;
        UserNode user;
        while( getline( fin, line )){           //customer X
            getline( fin, line );               //ID
            user.ID = removeLead(line);
            getline( fin, line );               //user name
            user.userName = removeLead(line);
            getline( fin, line );               //first name
            user.fName = removeLead(line);
            getline( fin, line );               //last name
            user.lName = removeLead(line);
            getline( fin, line );               //age
            user.age = stoi(removeLead(line));
            getline( fin, line );               //card
            user.cardNum = removeLead(line);
            getline( fin, line );               //points
            user.points = stoi(removeLead(line));

            userList.push_front( user );
        }
        fin.close();
    }
    return true;
}

bool loadProducts(forward_list<ProdNode>& prodList, string fileName){
    prodList.clear();       //clear any current data
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

bool loadTransactions(forward_list<TransNode>& transList, string fileName){
    transList.clear();      //clear any current data
    ifstream fin( fileName );
    if( ! fin.is_open() ){
        cout << "input file not found for transactions\n";
        return false;
    }else{
        string line;
        TransNode transaction;
        while( getline( fin, line ) ){      //transaction X
            getline( fin, line );           //ID
            transaction.transID = line.erase(0,1);
            getline( fin, line );           //userID
            transaction.userID = line.erase(0,1);
            getline( fin, line );           //products bought
            transaction.prodIDs = line.erase(0,1);       //NOTE: this inserts all words into first element, this isn't a problem since we never actually need to access them
            getline( fin, line );           //total cost
            transaction.total = stoi(line.erase(0,1));
            getline( fin, line );           //total rewards
            transaction.rewards = stoi(line.erase(0,1));

            transList.push_front(transaction);
        }
        fin.close();
    }
    return true;
};

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
        fout.close();
    }
    return true;
}

bool saveTransactions(forward_list<TransNode>& transList, string fileName){
    ofstream fout( fileName );
    if( ! fout.is_open() ){
        cout << "output file not found for transactions\n";
        return false;
    }else{
        int i{ 1 };
        while( ! transList.empty() ){               //write everything to text file
            fout << "Transaction " << i << endl         //note, we don't edit transactions so rewriting prev transactions is pointless, but easy
                << '\t' << transList.front().transID << endl 
                << '\t' << transList.front().userID << endl
                << '\t' << transList.front().prodIDs << endl  
                << '\t' << transList.front().total << endl 
                << '\t' << transList.front().rewards << endl;
            transList.pop_front();
            ++i;
        }
        fout.close();
    }
    return true;
};

string removeLead(string line){
    return line.substr( line.find_last_of(':') + 2);
};

// string concatPurchases(vector<string> prodIDs){
//     string purchases = "";
//     for( int i{ 0 }; i < prodIDs.size(); ++i ){       //put all purchases in a string
//         purchases += prodIDs[i] + ' ';
//     }
//     return purchases;
//}

