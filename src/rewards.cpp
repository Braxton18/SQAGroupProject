
#include "rewards.h"

vector<Reward> rewardArr;
int alloc{ 0 };

void rewardsMenu(forward_list<UserNode>& userList){
    string option;
    loadRewards("rewards.txt");
    while(true){
        cout << "Rewards Menu\nOptions:\n\t0) Back to Main menu\n\t1) Redeem reward points" 
            << "\n\t2) Manage Rewards system\n\t\tEnter Selection: ";
        cin >> option;
        if( option == "0" ){
            saveRewards("rewards.txt");
            return;
        }else if( option == "1" ){
            redeemRewards(userList);
        }else if( option == "2" ){
            manageRewards();
        }else{
            cout << "input not recognized\n";
        }
    }
}

int loadRewards(string fileName){
    ifstream fin(fileName);
    if(! fin.is_open() ){
        cout << "input file not found for rewards\n";
        return 0;
    }else{
        rewardArr.clear();      //clear remaining data
        string line;
        getline(fin, line);     //"Allocation per dollar"
        if( getline(fin, line) ){
            alloc = stoi(line);     //number of alloc
        }else{
            return 0;       //file must be empty
        }
        getline(fin, line);     //"rewards"
        while( getline(fin,line) ){     //reward name
            Reward X;
            X.name = line;
            getline(fin, line);     //reward cost
            X.cost = stoi(line);
            rewardArr.push_back(X);
        }
        return alloc;
    }
}

void saveRewards(string fileName){
    ofstream fout(fileName);
    if(! fout.is_open()){
        cout << "output file not found for rewards\n";
        return;
    }else{
        fout << "Allocation per dollar\n"
            << alloc << endl
            << "Rewards\n";
        for( int i{ 0 }; i < rewardArr.size(); ++i ){
            fout << rewardArr[i].name << endl 
                << rewardArr[i].cost << endl;
        }
    }
}

void redeemRewards(forward_list<UserNode>& userList){
    string userID;
    forward_list<UserNode>::iterator userIt{ userList.end() };
    for( int i{ 0 }; i < 3 && userIt == userList.end(); ++i ){       //only allow 10 attempts
        cout << "Please enter either your username or userID: ";
        cin >> userID;
        userIt = findUser( userID, userList );
    }
    if( userIt == userList.end() ){
        cout << "max attempts made, returning to Rewards menu...";
        sleep( 1.5 );
        return;
    }else{
        string rewardSelect;
        cout << endl;
        displayRewards();
        while(true){
            cout << "You have " << (*userIt).points << " points available\n"
                << "Enter then name of the reward you would like, or '0' to go back: ";
            cin >> rewardSelect;
            if(rewardSelect == "0"){
                saveCustomers(userList, "customers.txt");
                return;
            }else{
                for( int i{ 0 }; i < rewardArr.size(); ++i ){
                    if( rewardArr[i].name == rewardSelect ){
                        if( rewardArr[i].cost <= (*userIt).points ){
                            //give reward to user
                            (*userIt).points -= rewardArr[i].cost;
                            cout << "Congrats! You now have a " << rewardArr[i].name << endl;
                        }else{
                            cout << "Sorry, you don't have enough points\n";
                            continue;
                        }
                    }else{
                        //continue
                    }
                }
            }
        }
    }
};

void manageRewards(){
    string option;
    while(true){
        cout << "Manage Rewards\nOptions:\n\t0)Back to Rewards Menu\n\t1) Add a reward option" 
            << "\n\t2) Remove a reward option\n\t3) Change reward points allocation\n\t" 
            << "4) View available rewards\n\t\tEnter Selection: ";
        cin >> option;

        if( option == "0" ){
            return;
        }else if( option == "1" ){
            addReward();
        }else if( option == "2" ){
            removeReward();
        }else if( option == "3" ){
            changeAlloc();
        }else if( option == "4" ){
            displayRewards();
        }else{
            cout << "input not recognized\n";
        }

    }
}

void displayRewards(){
    cout << "\n\nAvailable Rewards\n"
        << "Reward\t\tCost\n";
    for(int i{ 0 }; i < rewardArr.size(); ++i ){
        cout << rewardArr[i].name << "\t\t" << rewardArr[i].cost << endl;
    }
    cout << endl;
    sleep(1.5);
}

void addReward(){
    Reward X;
    cout << "Enter the name of the reward to add: ";
    cin >> X.name;
    for(int i{0}; i < rewardArr.size(); ++i){
        if( X.name == rewardArr[i].name ){
            cout << "That is already an offered reward\n";
            sleep(1.5);
            return;
        }else{
            //continue
        }
    }
    cout << "Enter the point cost of this reward: ";
    cin >> X.cost;
    cout << "Reward added\n";
    sleep(1.5);
    rewardArr.push_back(X);
}

bool removeReward(){
    string name;
    cout << "Enter the name of the reward to remove: ";
    cin >> name;
    for( int i{0}; i < rewardArr.size(); ++i ){
        if( rewardArr[i].name == name ){
            rewardArr.erase( rewardArr.begin() + i );
            cout << "reward removed\n";
            sleep(1.5);
            return true;
        }
    }
    cout << "reward not found\n";
    sleep(1.5);
    return false;
}

void changeAlloc(){
    string x;
    cout << "Current point allocation per dollar spent is: " << alloc << endl 
        << "What would you like the new rate to be?: ";
    cin >> x;
    alloc = toInt(x);
}

