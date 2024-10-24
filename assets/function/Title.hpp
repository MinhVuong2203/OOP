#pragma once
#include <windows.h>
#include <iomanip>
using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void banner()
{
    setColor(10);
    	cout << "   _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n";
        cout << "  *                                                               *\n";
        cout << " *                          "; setColor(5); cout << "San cau long"; setColor(10); cout<<"                           *\n";
      	cout << "*                         "; setColor(4); cout << "Come In Badminton"; setColor(10); cout<<"                         *\n";
        cout << " *                     "; setColor(6); cout <<"xin kinh chao quy khach"; setColor(10); cout <<"                     *\n";
        cout << "  *                                                               *\n";
		cout << "   _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n";
    setColor(7); 
}
void Menu()
{
    cout << "================"; setColor(11); cout << "<MENU>"; setColor(7); cout << "================\n";
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
    cout << " ->[ ";
    setColor(7);
}

void icon_return(){
    setColor(6);
    cout << " <-- ";
    setColor(7);
}

void icon_cost(){
    setColor(6);
    cout << "  $  ";
    setColor(7);
}

void icon_user(){
    setColor(6);
    cout << " ^:^ ";
    setColor(7);
}

void icon_admin(){
    setColor(6);
    cout << " ^_^ ";
    setColor(7);
}

void icon_login(){
    setColor(6);
    cout << " <-> ";
    setColor(7);
}

void icon_Res(){
    setColor(6);
    cout << " <+> ";
    setColor(7);
}


void icon_Statistical(){
    setColor(6);
    cout << " %/% ";
    setColor(7);
}

void icon_Order(){
    setColor(6);
    cout << " [+] ";
    setColor(7);
}

void icon_delOrder(){
    setColor(6);
    cout << " [-] ";
    setColor(7);
}

void icon_History(){
    setColor(6);
    cout << " o-o ";
    setColor(7);
}




