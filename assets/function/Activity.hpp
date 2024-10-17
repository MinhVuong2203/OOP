#pragma once
#include <vector>
// #include "Person.hpp"
// #include "TimeDay.hpp"
// #include "templateBill.hpp"
using namespace std;
const int SL = 20;

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
        << "| " << id
        << " |" << endl
        << "+-----+--------------------+---------------+---------------+---------------+---------------+" << endl;
    }
};
void templateBill(Acti *x, Day current_Day, Time current_Time, double into_money, const int GiaThuong, const int GiaVang);
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
    void History(string Hoten);
    void priBill(Day ngayden);
   
};
QLAC::QLAC(string filename)
{
    this->n = 0;
    ifstream file(filename);
    if (!file.is_open()) {
    cerr << "Unable to open file" << endl;
        return;
    }
    
    string line;
    while (getline(file, line))
    {
        string hoten, ngaysinh_str, sdt, ngayden_str, giovao_str, giora_str, id_str;
        Day ngaysinh, ngayden;
        Time giovao, giora;
        int id;
        istringstream ss(line);
        getline(ss, hoten, ',');
        getline(ss, ngaysinh_str, ',');
        getline(ss, sdt, ',');
        getline(ss, ngayden_str, ',');
        getline(ss, giovao_str, ',');
        getline(ss, giora_str, ',');
        getline(ss, id_str, ',');
        
        sscanf(ngaysinh_str.c_str(), "%d/%d/%d", &ngaysinh.ngay, &ngaysinh.thang, &ngaysinh.nam);
        sscanf(ngayden_str.c_str(), "%d/%d/%d", &ngayden.ngay, &ngayden.thang, &ngayden.nam);
        sscanf(giovao_str.c_str(), "%d:%d:%d", &giovao.gio, &giovao.phut, &giovao.giay);
        sscanf(giora_str.c_str(), "%d:%d:%d", &giora.gio, &giora.phut, &giora.giay);
        sscanf(id_str.c_str(), "%d", &id);
        hoten.erase(0, hoten.find_first_not_of(" "));
        sdt.erase(0, sdt.find_first_not_of(" "));
        if (hoten != "")
        {

        Person *p = new Acti(hoten, ngaysinh, sdt, ngayden, giovao, giora, id);
        AC[n++] = p;

        }
    }
}
QLAC::~QLAC() {
    for (int i = 0; i < n; i++) {
        delete AC[i]; // Giải phóng từng đối tượng
    }
}
void QLAC::add(string nameFile, string HoTen, Day NgaySinh, string SDT) 
{
    fstream file(nameFile, ios::app);
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }
    Day NgayDen;
    Time GioVao, GioRa;
    int id;
    int San[SL] = {0}; // Tạo ra một mảng sân để lưu id và trạng thái sân thứ i có id là i+1, giá trị s[i] = 0 (sân trống), s[i] = 1 (sân có người)

    cout << "Nhap ngay vao: "; NhapDay(NgayDen);
    cout << "Nhap gio vao: "; NhapTime(GioVao);
    cout << "Nhap gio ra: "; NhapTime(GioRa);

    for (int i = 0; i < n; i++) 
    {
        Acti *ActiPtr = dynamic_cast<Acti*>(AC[i]);  //chuyển đổi kiểu person sang acti
        if (ActiPtr != nullptr) 
        {
            if (compareDay(ActiPtr->getNgayDen(), NgayDen) == 0)
            {
                if (compareTime(ActiPtr->getGioVao(), GioRa) <=0 && compareTime(ActiPtr->getGioRa(), GioRa) >=0) //TH1
                    San[ActiPtr->getID()-1] = 1;
                if (compareTime(ActiPtr->getGioVao(), GioVao) <=0 && compareTime(ActiPtr->getGioRa(), GioVao) >=0)  //TH2  
                    San[ActiPtr->getID()-1] = 1;
                if (compareTime(ActiPtr->getGioVao(), GioVao) >=0 && compareTime(ActiPtr->getGioRa(), GioRa) <=0) //TH3
                    San[ActiPtr->getID()-1] = 1;
                if (compareTime(ActiPtr->getGioVao(), GioVao) <=0 && compareTime(ActiPtr->getGioRa(), GioRa) >=0) //TH4
                    San[ActiPtr->getID()-1] = 1;    
            }
        }
    }
    cout << "\nCac san con trong: ";
  for ( int i=0; i<SL; i++)
    {
        if (i%5==0) cout << endl << endl;
        (San[i])? setColor(12) : setColor(2); 
        cout << left <<  "| "; cout << setw(2) << i+1; cout<< " |  ";   
    }	
    setColor(7);    
    cout << "\nBan chon san: "; cin >> id;
    while (San[id-1])
    {
        cout << "San nay da co nguoi. Vui long chon lai: ";
        cin >> id;
    }
	Person *p = new Acti(HoTen, NgaySinh, SDT, NgayDen, GioVao, GioRa, id);
    AC[n++] = p;
    file <<HoTen <<","<<NgaySinh.ngay<<"/"<<NgaySinh.thang<<"/"<<NgaySinh.nam<<","<<SDT<<","<<NgayDen.ngay<<"/"<<NgayDen.thang<<"/"<<NgayDen.nam\
    <<","<<GioVao.gio<<":"<<GioVao.phut<<":"<<GioVao.giay<<","<<GioRa.gio<<":"<<GioRa.phut<<":"<<GioRa.giay<<"," << id << endl;
    cout << "Da dat san thanh cong!" << endl;
    file.close();
}
void QLAC::History(string Hoten)
{
    int k = 0;
    for (int i=0; i<n; i++)
    {
        if (AC[i]->getHoten() == Hoten)
        {
            cout << left << "| "; setColor(12); cout << setw(4) << ++k; setColor(7);
            AC[i]->hienThiThongTin();
        }
    }
}

void QLAC::priBill(Day ngayden) 
{
    double into_money = 0;
    int k = 0, STT;
    vector<Acti*> actiList; // Tạo danh sách tạm để lưu các đối tượng cần in
    for (int i = n - 1; i >= 0; i--) 
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr && compareDay(ActiPtr->getNgayDen(), ngayden) == 0) 
        {
            cout << left << "| "; setColor(12);cout << setw(4) << ++k; setColor(7);
            ActiPtr->hienThiThongTin();
            actiList.push_back(ActiPtr); // Thêm đối tượng vào danh sách tạm
        }
    }

    cout << "Nhap STT can in hoa don: ";    cin >> STT;

    if (STT <= 0 || STT > k) {
        cout << "STT khong hop le!" << endl;
        return;
    }

    k = 0;
    for (int i = n - 1; i >= 0; i--) 
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr && compareDay(ActiPtr->getNgayDen(), ngayden) == 0) 
        {
            k++;
            if (k == STT) 
            {
                templateBill(ActiPtr, getday(), getTime(), into_money, 50000, 110000);
                return;
            }
        }
    }
}
