//Braxton Reece and Grant Wilke

#ifndef REWARDS_H
#define REWARDS_H


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <forward_list>
#include "shopping.h"
#include "registration.h"
#include "fileManagement.h"

using namespace std;

struct Reward{
    string name;
    int cost;
};

//displays the user menu for the rewards functionality
//Parameters: userList: forward list of user nodes
//return: none
void rewardsMenu(forward_list<UserNode>& userList);

//loads reward info into an array of reward objects
//Parameters: fileName: name of the .txt file to pull reward info from, Format: "XXX.txt"
//return: the number of points allocated per dollar spent
int loadRewards(string fileName);

//saves reward info into a file
//Parameters: fileName: name of the .txt file to store reward info in, Format: "XXX.txt"
//return: none
void saveRewards(string fileName);

//allows users to redeem their reward points for awards
//Parameters: userList: forward list of user nodes
//return: none
void redeemRewards(forward_list<UserNode>& userList);

//displays reward management menu
//Parameters: none
//return: none
void manageRewards();

//displays the available rewards to choose from along with their costs
//Parameters: none
//return: none
void displayRewards();

//allows user to add a reward option and its cost
//Parameters: none
//return: none
void addReward();

//allows user to specifiy a reward to remove
//Parameters: none
//return: true if successfully removed, false othwerwise
bool removeReward();

//allows user to change the number of reward points given for purchases
//Parameters: none
//return: none
void changeAlloc();





#endif