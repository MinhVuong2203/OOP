#include <iostream>
#include <windows.h>
#include <iomanip>
#include "Title.h"
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
    setColor(4); 
    cout << " ]<= ";
    setColor(7);
}

void icon_choice()
{
    setColor(2); 
    cout << " (+) ";
    setColor(7);
}

void icon_confirm()
{
    setColor(4); 
    cout << " (*) ";
    setColor(7);
}

void icon_sort(){
    setColor(6);
    cout<<"[A-Z]";
    setColor(7);
}

void icon_search(){
    setColor(6);
    cout<<" ==0 ";
    setColor(7);
}

void icon_return(){
    setColor(6);
    cout << " <== ";
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

void icon_del(){
    setColor(6);
    cout << " [X] ";
    setColor(7);
}

void icon_login(){
    setColor(6);
    cout << " ->[ ";
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

void icon_cancel(){
    setColor(6);
    cout << " -x- ";
    setColor(7);
}

bool CapCha()
{
    int rd; 
    string get,getc;
        setColor(11); cout << "Dam bao rang ban khong phai la Robot\n"; setColor(7);
        srand(time(0)); // Khởi tạo seed cho hàm rand() dựa trên thời gian hiện tại 
        for (int i = 1; i <= 6; ++i) 
        { 
            char ch;
            switch (i%3)
            {
                case 0: rd = 48 + rand()%10;    break;
                case 1:  rd = 65 + rand()%26;   break;
                case 2:  rd = 97 + rand()%26;   break;
            }
            ch = static_cast<char>(rd);
            get += ch;
        } 
        cout << "Ma Capcha: ";  setColor(12);  cout << get; setColor(7);
        cout << endl;
        icon_Order();    cout << "Nhap ma Capcha: ";    getline(cin,getc);
        if (get == getc)    return 1;
    return 0;
}







