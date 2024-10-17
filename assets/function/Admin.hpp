#pragma once
#include <iostream>
#include "Person.hpp"
using namespace std;

// Class đối tượng admin
class Admin : public Person {
private:
    string CCCD;
public:
    Admin() {}
    Admin(string HoTen, Day NgaySinh, string SDT,string cccd) : Person(HoTen, NgaySinh, SDT), CCCD(cccd){}

    string getCCCD() { return CCCD; }
    void hienThiThongTin() override {
        Person::hienThiThongTin();
        cout << CCCD << endl;
    }
};
class QLAD{
private:
    Person *A[20];
    int n;
public:
    QLAD() { this->n = 0; } 
	~QLAD();
    void add(string nameFile);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
        {
            A[i]->hienThiThongTin();
        }
    }
    void fixAccountUser(string nameFile);
};
void QLAD::add(string nameFile)
{
        fstream file(nameFile, ios::app);
        if (!file.is_open())
        {
            cerr << "Unable to open file: " << nameFile << endl;
            return;
        }
        string HoTen, SDT, CCCD;
        Day NgaySinh;
        cin.ignore();
        cout << "Nhap ho ten: ";  getline(cin, HoTen);
        cout << "Nhap ngay sinh: "; NhapDay(NgaySinh);
        cout << "Nhap SDT: "; cin.ignore(); getline(cin, SDT);
        cout << "Nhap CCCD: ";  getline(cin, CCCD);
		Person *p = new Admin(HoTen, NgaySinh, SDT, CCCD);
        A[n++] = p;
        file << HoTen <<","<< NgaySinh.ngay <<"/"<< NgaySinh.thang <<"/"<< NgaySinh.nam <<","<< SDT <<","<< CCCD << endl; 
        cout << "Add Admin successful!" << endl;
        file.close();
}
QLAD::~QLAD() {
    for (int i = 0; i < n; i++) {
        delete A[i]; // Giải phóng từng đối tượng
    }
}