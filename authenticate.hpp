#pragma once
#include <iostream>
#include "Person.hpp"
using namespace std;

int authenticateUser(string username, string password, string FilePass) {
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
        ch = _getch(); // getch() function hides the user input
        if (ch == 13 || ch == 10) { // ASCII value of Enter key
            break;
        } else if (ch == 8 && i > 0) { // ASCII value of Backspace key
            printf("\b \b"); // Erase previous character
            password.pop_back(); // Xóa ký tự cuối cùng trong chuỗi
            i--;
        } else if (isprint(ch)) {
            printf("*");
            password.push_back(ch); // Thêm ký tự vào chuỗi
            i++;
        }
    }
}
