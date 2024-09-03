#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "User.h"

using namespace std;

class UserManager {
public:
    UserManager(const string& filename);
    void run();

private:
    vector<User> users;
    string filename;

    void setColor(int color);
    void printBorder();
    void saveToCSV();
    void loadFromCSV();
    void registerUser();
    bool loginUser();
};

#endif // USERMANAGER_H
