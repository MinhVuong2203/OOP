// #include <iostream>
#include <iomanip>
#include "TimeDay.h"
#include "Person.h"
using namespace std;
Person::Person(string Hoten, Day NgaySinh, string SDT)
{
    this->Hoten = Hoten; 
    this->NgaySinh = NgaySinh;
    this->SDT = SDT;
}

string Person:: getHoten() { return Hoten; }
Day Person::getNgaySinh(){return NgaySinh;};
string Person::getSDT() { return SDT; }
void Person::setHoTen(string newHoTen) { this->Hoten = newHoTen; }
void Person::setNgaySinh(Day newNgaySinh) { this->NgaySinh = newNgaySinh; }
void Person::setSDT(string newSDT) { this->SDT = newSDT; }

void Person::hienThiThongTin() 
{
    cout << "| " << left << setw(20) << Hoten 
         << "| " << left << setw(14) << (to_string(NgaySinh.ngay) + "/" + to_string(NgaySinh.thang) + "/" + to_string(NgaySinh.nam))
         << "| " << left << setw(14) << SDT;
}
void Person::hienThiThongTin2() 
{
    cout << "| " << left << setw(20) << Hoten 
         << "| " << left << setw(14) << (to_string(NgaySinh.ngay) + "/" + to_string(NgaySinh.thang) + "/" + to_string(NgaySinh.nam))
         << "| " << left << setw(14) << SDT;
}