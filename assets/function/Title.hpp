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
    cout << left << "|\t" << setw(17) << "Khung gio" 
        << setw(14) << "Don gia" 
        << setw(20) << "Thoi Luong" 
        << setw(17) << "Thanh tien" << right << setw(4) << "|\n";
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

