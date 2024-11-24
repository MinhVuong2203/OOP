#ifndef PERSON_H
#define PERSON_H
#include "TimeDay.h"
using namespace std;

class Person{
private:
    string Hoten;
    Day NgaySinh;
    string SDT;
public:
    Person() {}
    Person(string Hoten, Day NgaySinh, string SDT);

    string getHoten();
    Day getNgaySinh();
    string getSDT();
    void setHoTen(string newHoTen);
    void setNgaySinh(Day newNgaySinh);
    void setSDT(string newSDT);
    virtual void hienThiThongTin();
    virtual void hienThiThongTin2();
};
#endif
