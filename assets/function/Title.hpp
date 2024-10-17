#pragma once
#include <windows.h>
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

void TitleBill(){
    cout << left << "\t" << setw(14) << "Khung gio" 
        << setw(10) << "Don gia" 
        << setw(10) << "SL" 
        << setw(10) << "Thanh tien" << endl;
}

void icon_exit()
{
    setColor(6); 
    cout << "->[";
    setColor(7);
}

void icon_return(){
    setColor(6);
    cout << "<--";
    setColor(7);
}

void icon_cost(){
    setColor(6);
    cout << "$";
    setColor(7);
}

