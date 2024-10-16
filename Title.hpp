#pragma once
#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>
using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Menu()
{
    cout << "----------------"; setColor(11); cout << "MENU"; setColor(7); cout << "---------------\n";
}

void TitleAdmin()
{
	cout << left << setw(20) << "Ho ten" 
        << setw(15) << "Ngay Sinh" 
        << setw(15) << "SDT" 
        << setw(10) << "ID" << endl;
}

void TitleUser() 
{   setColor(6);
    cout << left 
         << "+-----+--------------------+---------------+---------------+---------------+---------------+" << endl
         << "| STT |       Ho ten       |   Ngay Sinh   |     SDT       | Ten dang nhap |    Mat khau   |" << endl
         << "+-----+--------------------+---------------+---------------+---------------+---------------+" << endl;
    setColor(7);
}
