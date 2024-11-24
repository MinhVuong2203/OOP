#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include "check.h"
using namespace std;
//Hàm check số điện thoại
bool checkName(string x)
{
    int n = x.length();
    if (n<=1) return false;
    for (int i=0; i<n; i++)
    if (x[i] == ' ') return true;
    return false;
}

bool checkSDT(string x)
{
    if (x.length() != 10) return false;  
     if (x[0] != '0') return false;
    return true;
}

bool checkFile(string x, string namefile)
{
    ifstream file(namefile);
    file.seekg(0, ios::beg);
    string s;
    while (getline(file, s,','))
    {
        if (s==x)
        {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

bool checkCCCD(string x)
{
     if (x.length() != 12 || x[0] !='0' ) return false;  
    return true;
}

string capitalizeAndTrim(string s) {
    stringstream ss(s);
    string word, result;

    while (ss >> word) { 
        if (!word.empty()) {
            word[0] = toupper(word[0]);  
            for (size_t i = 1; i < word.length(); ++i) {
                word[i] = tolower(word[i]);  
            }
            result += word + " ";
        }
    }

    if (!result.empty()) {
        result.pop_back(); 
    }

    return result;
}

bool checkMK(string x){
    if(x.length()< 6) return false;
    bool checkhoa=false, checkthuong=false, checkso=false;
    for(int i=0;i<x.length();i++){
        if (islower(x[i])) checkthuong = true;
        if (isupper(x[i])) checkhoa = true;
        if (isdigit(x[i])) checkso = true;
        if (checkthuong && checkhoa && checkso) break;
    }
    return checkthuong && checkhoa && checkso;
}
