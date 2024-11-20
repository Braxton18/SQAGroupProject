#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

//includes
#include <iostream>
#include <string>
#include <forward_list>
#include "shopping.h"
#include "prodManagement.h"
#include "registration.h"

using namespace std;


//read customer information from text file and adds customers to a forward_list of customer nodes
//Parameters: userList: the forward_list to add nodes to
//          fileName: name of the .txt file to pull customer info from, Format: "XXX.txt"
//Return: true if customers successfully loaded, false otherwise
bool loadCustomers(forward_list<UserNode>& userList, string fileName);

//read product information from a text file and adds products to  a forward_list of product nodes
//Parameters: prodList: the forward_list to add nodes to
//           fileName: name of the .txt file to pull product information from, Format: "XXX.txt"
//Return: true if products successfully loaded, false otherwise
bool loadProducts(forward_list<ProdNode>& prodList, string fileName);

//read transaction data from text file and adds transactions to a forward_list of transaction nodes
//Parameters: transList: the forward_list to add nodes to
//          fileName: name of the .txt file to pull transaction info from, Format: "XXX.txt"
//Return: true if transactions successfully loaded, false otherwise
bool loadTransactions(forward_list<TransNode>& transList, string fileName);

//write data from a forward_list of product nodes to a .txt file for storage
//Parameters: prodList: forward_list containing product nodes to save
//          fileName: name of the .txt file to save product information to, Format: "XXX.txt"
//Return: true if products successfully saved, false otherwise
bool saveProductData(forward_list<ProdNode>& prodList, string fileName);

//write data from a forward_list of transaction nodes to a .txt file for storage
//Parameters: transList: forward_list containing product nodes to save
//          fileName: name of the .txt file to save transaction information to, Format: "XXX.txt"
//Return: true if transactions successfully saved, false otherwise
bool saveTransactions(forward_list<TransNode>& transList, string fileName);

//removes substring up to the last white space, keeping only the last word
//Parameters: line: string to remove substring from
//Return: string, last word of the line
string removeLead(string line);

//string concatPurchases(vector<string> prodIDs);


#endif