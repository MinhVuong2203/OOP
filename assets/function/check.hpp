#pragma once

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



