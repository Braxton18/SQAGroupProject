#ifndef SHOPPING_H
#define SHOPPING_H

#include <string>
#include "registration.h"
#include "prodManagement.h"

//shopping implementation, allows users to sign in and browse and purchase
//Parameters: users: forward list of users
//          prods: forward list of products
//Return: none
void shopping( forward_list<UserNode> userList, forward_list<ProdNode> prodList );

//finds the node of user information in a forward list of users which has a matching name or userID as "user"
//Parameters: user: string to match to UserNode, either the users name or ID
//          userList: forward list of user information
//Return: iterator to the UserNode that matches "user", NULL if user not found
forward_list<UserNode>::iterator findUser( string user, forward_list<UserNode> userList );

//displays a specified number of products
//Parameters: prodList: forward list of products
//          x: number of products to be displayed, DEFAULT 5
//          n: product index to begin at, DEFAULT 0
//Return: none
void displayProds( forward_list<ProdNode> prodList, int x, int n );

//finds and attempts to purchase a specified product
//Parameters: prodList: forward list of products
//          product: either product ID or name to buy
//          amnt: number of the specified product the user would like to buy
//          it: iterator pointing to the user trying to buy the product
//          spent: amount spent by the user in this transaction
//Return: 0 if successful
//          1 if not enough stock
//          2 if product not found
int purchase( forward_list<ProdNode> prodList, string product, int amnt, forward_list<UserNode>::iterator it, int& spent );

//finds the product in a forward_list specified by "product"
//Parameters: prodList: forward list of products
//          product: product ID or name of the product to buy
//Return: iterator to the ProdNode containing the desired product, NULL if product not found
forward_list<ProdNode>::iterator findProduct( forward_list<ProdNode> prodList, string product );




#endif