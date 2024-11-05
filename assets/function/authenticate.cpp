#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include "authenticate.h"

using namespace std;

int authenticateUser(string username, string password, string FilePass) 
{
    ifstream file(FilePass);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << FilePass << endl;
        return 0;
    }
    string line;
    stringstream ss;
    while (getline(file, line))
    {
        stringstream ss(line);
        string fileUsername, filePassword, item;
        bool isFirst = true;
        while (getline(ss, item, ',')) 
        {
            
            if(isFirst){
                filePassword = item;
                fileUsername = "";
                isFirst = false;
            }
            else{
                fileUsername = filePassword;
                filePassword = item;
            }
            if (fileUsername == username && filePassword == password) {
                file.close();
                return 1;
            }
        }
    }

    file.close();
    return 0; // Username not found
}

void hidePassword(std::string &password) {
    char ch;
    int i = 0;
    while (true) {
        ch = _getch(); 
        if (ch == 13 || ch == 10) { 
            break;
        } else if (ch == 8 && i > 0) {
            printf("\b \b"); 
            password.pop_back(); 
            i--;
        } else if (isprint(ch)) {
            printf("*");
            password.push_back(ch); 
            i++;
        }
    }
}
