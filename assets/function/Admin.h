#ifndef ADMIN_H
#define ADMIN_H
#include "TimeDay.h"
#include "Person.h"
#include "Activity.h"
#include "User.h"

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
        cout << "| "<< left << setw(14)<<CCCD <<"|"<<endl;
    }
};

class QLAD{
private:
    Person *A[20];
    int n;
public:
    QLAD() { this->n = 0; } 
	~QLAD();
    QLAD(string filename);
    string getName(string username); //Lấy tên admin dựa vào tên đăng nhập để phục vụ việc in bill
    void add(string nameFile);
    void addUS(QLUS &U, string namefile);
    void hienDS() {
        for (int i = 0; i < n; i++) {
            cout<<"|  ";
            setColor(4);
            cout<< setw(3)<<i+1;
            setColor(7);
            A[i]->hienThiThongTin();
            cout<< "+-----+---------------------+---------------+---------------+---------------+" << endl;
        }
    }
    void hienDSUS(QLUS &U){
        U.hienDS();
    }
    void fixAccountUser(string nameFile);
    void delAd(string nameFile);
    void delUS(QLUS &U, string namefile, string username);
    void searchUS(string search, string nameFile);
    void priBill(QLAC &AC, Day day, string hoten_admin);
    void Calculate(QLAC &AC, Day start_day, Day end_day);
    void order(QLAC &AC,string namefile, string hoten, Day day_order, string sdt);
};

#endif