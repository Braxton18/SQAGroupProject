#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

//includes
#include <iostream>
#include <string>
#include <forward_list>
#include "prodManagement.h"

bool loadCustomers(string);
bool loadProducts(forward_list<ProdNode>&, string);
//bool loadTransactions();
bool saveCustomerData(string);
bool saveProductData(forward_list<ProdNode>&, string);
//bool saveTransactions();

#endif