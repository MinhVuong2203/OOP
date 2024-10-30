#ifndef AUTHEN_H
#define AUTHEN_H
#include <iostream>
using namespace std;

int authenticateUser(string username, string password, string FilePass);

void hidePassword(std::string &password);
    

#endif