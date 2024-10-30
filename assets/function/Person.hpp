#pragma once
#include <iomanip>

using namespace std;

class Person{
private:
    string Hoten;
    Day NgaySinh;
    string SDT;
public:
    Person() {}
    Person(string Hoten, Day NgaySinh, string SDT) {
        this->Hoten = Hoten;
        this->NgaySinh = NgaySinh;
        this->SDT = SDT;
    }

    string getHoten() { return Hoten; }
    Day getNgaySinh(){return NgaySinh;};
    string getSDT() { return SDT; }
    void setHoTen(string newHoTen) { this->Hoten = newHoTen; }
    void setNgaySinh(Day newNgaySinh) { this->NgaySinh = newNgaySinh; }
    void setSDT(string newSDT) { this->SDT = newSDT; }


    virtual void hienThiThongTin() {
        cout << "| " << setw(19) << Hoten 
            << "| " << setw(14) << (to_string(NgaySinh.ngay) + "/" + to_string(NgaySinh.thang) + "/" + to_string(NgaySinh.nam))
            << "| " << setw(14) << SDT;
    }
};
