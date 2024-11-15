#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

//includes
#include <iostream>
#include <string>
#include <forward_list>
#include "prodManagement.h"

//read product information from a text file and adds products to  a forward_list of product nodes
//Parameters: prodList: the forward_list to add nodes to
//           fileName: name of the .txt file to pull product information from, Format: "XXX.txt"
//Return: true if products successfully loaded, false otherwise
bool loadProducts(forward_list<ProdNode>& prodList, string fileName);

//write data from a forward_list of product nodes to a .txt file for storage
//Parameters: prodList: forward_list containing product nodes to save
//          fileName: name of the .txt file to save product information to, Format: "XXX.txt"
//Return: true if products successfully saved, false otherwise
bool saveProductData(forward_list<ProdNode>& prodList, string fileName);

#endif