#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <iomanip>
#include "Title.h"
#include "TimeDay.h"
#include "Person.h"
extern const int MAX_SIZE;
extern const int GiaThuong;  //Khai báo để sử dụng cho việc in bill. từ 7h - 16h giá 50000đ/h, từ 16h - 22h giá 110000đ/h
extern const int GiaVang;
extern const int SL;
extern const Time timeVang;
using namespace std;
// class Activity để lưu trữ các hoạt động của user
class Acti : public Person {
private:
    Day NgayDen;
    Time GioVao, GioRa; 
    int id;
public:
    Acti() {}
    Acti(string HoTen, Day NgaySinh, string SDT, Day ngayden, Time giovao, Time giora, int ID) : Person(HoTen, NgaySinh, SDT), NgayDen(ngayden), GioVao(giovao), GioRa(giora), id(ID){}
    Day getNgayDen() {return NgayDen;}
    Time getGioVao() {return GioVao;}
    Time getGioRa() {return GioRa;}
    int getID() {return id;}
    
    void hienThiThongTin() override {
        Person::hienThiThongTin();
        cout<< "| " << setw(10) << (to_string(NgayDen.ngay) + "/" + to_string(NgayDen.thang) + "/" + to_string(NgayDen.nam))
        << "| " << setw(10) << (to_string(GioVao.gio) + ":" + to_string(GioVao.phut) + ":" + to_string(GioVao.giay))
        << "| " << setw(10) << (to_string(GioRa.gio) + ":" + to_string(GioRa.phut) + ":" + to_string(GioRa.giay))
        << "| " << setw(3) << id
        << " |" << endl
        << "+-----+---------------------+---------------+---------------+-----------+-----------+-----------+-----+" << endl;
    }
    void calculate(const int GiaThuong, const int GiaVang, Day start_day, Day end_day);
    
};

class QLAC
{
private:
    Person *AC[100];
    int n;

public:
    QLAC(string filename);
    ~QLAC();
    void add(string nameFile, string HoTen, Day NgaySinh, string SDT);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
		{
            cout << left << "| "; setColor(12); cout << setw(4) << i+1; setColor(7);
            AC[i]->hienThiThongTin();
        }
    }
    void History(string hoten, string sdt);
    void priBill(Day ngayden, string hoten_admin);
    void calculate(Day start_day, Day end_day);
    void update(string nameFile, int ch, string oldName,string newName, Day newBD, string newSDT);
    void ActiDel(string namefile, string hoten, string sdt);
    void sortActivities(int choice);
};

#endif

