#include <iostream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "Person.h"
#include "TimeDay.h"
#include "Title.h"
#include "templateBill.h"
#include "VQMM.h"
#include "Activity.h"
const int GiaThuong = 50000;  //Khai báo để sử dụng cho việc in bill. từ 7h - 16h giá 50000đ/h, từ 16h - 22h giá 110000đ/h
const int GiaVang = 110000;
const int SL = 20;
const Time timeVang = {16,0,0};
using namespace std;

string FBill = "assets//FBill.txt";
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
    if (!file.is_open()) {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }

     Day NgayDen;
    Time GioVao, GioRa;
    int id;
    int San[SL] = {0};

    // Nhập ngày vào và kiểm tra
    icon_Order();    cout << "Nhap ngay vao hoac an 'n' de lay ngay hien tai(dd/mm/yyyy): "; 
    readDay:
    string day_ptr;
    getline(cin,day_ptr);
    if (day_ptr == "n"){
    NgayDen.ngay = getday().ngay; NgayDen.thang = getday().thang; NgayDen.nam = getday().nam;
    cout << left << setw(50) << " "; setColor(6); NgayDen.xuatDay(); setColor(7); cout << endl;
    }
    else
    {
        sscanf(day_ptr.c_str(), "%d/%d/%d", &NgayDen.ngay, &NgayDen.thang, &NgayDen.nam);
        if (!NgayDen.checkDay())
        {
            cout << "Ngay khong hop le! Vui long nhap lai: ";
            goto readDay;
        }
         if (NgayDen < getday()) {
            cout << "Ngay vao khong duoc nho hon ngay hien tai. Vui long nhap lai: ";
            goto readDay;
        }
    }

    // Nhập giờ vào và kiểm tra
    icon_Order();     cout << "Nhap gio vao hoac an 'n' de lay gio hien tai: "; 
    string time_ptr;
    readTime:
    getline(cin,time_ptr);
    if (time_ptr == "n"){
        GioVao.gio = getTime().gio; GioVao.phut = getTime().phut; GioVao.giay = getTime().giay; 
        cout << left << setw(50) <<" "; setColor(6); GioVao.xuatTime(); setColor(7); cout << endl;
    }
    else{
        sscanf(time_ptr.c_str(), "%d:%d:%d", &GioVao.gio, &GioVao.phut, &GioVao.giay);
        if (!GioVao.checkTime()){
            cout << "Thoi gian khong hop le! Vui long nhap lai: ";
            goto readTime;
        }
        if (NgayDen == getday() && GioVao < getTime()){
            cout << "Gio vao khong duoc nho hon gio hien tai. Vui long nhap lai: ";
            goto readTime;
        }
    }

    // Nhập giờ ra và đảm bảo giờ vào phải trước giờ ra
    icon_Order(); cout << "Nhap gio ra: "; GioRa.nhapTime();
    while (GioVao >= GioRa) {
        cout << "Gio ra phai lon hon gio vao. Vui long nhap lai: "; GioRa.nhapTime();
    }
    // Kiểm tra trạng thái sân và đặt sân trống
    for (int i = 0; i < n; i++) {
        Acti *ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr) {
            if (ActiPtr->getNgayDen() == NgayDen) {
                if (ActiPtr->getGioVao() <= GioRa && ActiPtr->getGioRa() >= GioRa)  //TH1
                    San[ActiPtr->getID()-1] = 1;
                if (ActiPtr->getGioVao() <= GioVao && ActiPtr->getGioRa() >= GioVao) //TH2  
                    San[ActiPtr->getID()-1] = 1;
                if (ActiPtr->getGioVao() >= GioVao && ActiPtr->getGioRa() <= GioRa) //TH3
                    San[ActiPtr->getID()-1] = 1;
                if (ActiPtr->getGioVao() <= GioVao && ActiPtr->getGioRa() >= GioRa) //TH4
                    San[ActiPtr->getID()-1] = 1;    
            }
        }
    }
    // Hiển thị sân trống và yêu cầu người dùng chọn
    cout << "\nCac san con trong: ";
    for (int i = 0; i < SL; i++) {
        if (i % 5 == 0) cout << endl << endl;
        (San[i]) ? setColor(12) : setColor(2);
        cout << left << "| "; cout << setw(2) << i + 1; cout << " |  ";
    }
    setColor(7);
    // Nhập lựa chọn sân
    cout << "\n\nBan chon san: "; cin >> id;
    while (San[id - 1]) {
        setColor(4);
        cout << "San nay da co nguoi. Vui long chon lai: ";
        setColor(7);
        cin >> id;
    }
    // Thêm đối tượng và lưu vào file
    Person *p = new Acti(HoTen, NgaySinh, SDT, NgayDen, GioVao, GioRa, id);
    AC[n++] = p;
    file << HoTen << "," << NgaySinh.ngay << "/" << NgaySinh.thang << "/" << NgaySinh.nam << "," << SDT << ","
         << NgayDen.ngay << "/" << NgayDen.thang << "/" << NgayDen.nam << ","
         << GioVao.gio << ":" << GioVao.phut << ":" << GioVao.giay << ","
         << GioRa.gio << ":" << GioRa.phut << ":" << GioRa.giay << "," << id << endl;
    
    setColor(10); cout << "Da dat san thanh cong!" << endl; setColor(7);
    file.close();
}

void QLAC::History(string hoten, string sdt)
{
    int k = 0;
    for (int i=0; i<n; i++)
    {
        if (AC[i]->getHoten() == hoten && AC[i]->getSDT() == sdt)
        {
            cout << left << "| "; setColor(12); cout << setw(4) << ++k; setColor(7);
            AC[i]->hienThiThongTin();
        }
    }
}

void QLAC::priBill(Day ngayden, string hoten_admin) 
{
    double into_money = 0;
    int k = 0, STT;
    vector<Acti*> actiList; // Tạo danh sách tạm để lưu các đối tượng cần in
    for (int i = n - 1; i >= 0; i--) 
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr && ActiPtr->getNgayDen() == ngayden) 
        {
            cout << left << "| "; setColor(12);cout << setw(4) << ++k; setColor(7);
            ActiPtr->hienThiThongTin();
            actiList.push_back(ActiPtr); // Thêm đối tượng vào danh sách tạm
        }
    }
    cout << endl;
    icon_Order();    cout << "Nhap STT can in hoa don: ";    
    cin >> STT; cout << endl;
    if (STT <= 0 || STT > k) {
        cout << "STT khong hop le!" << endl;
        return;
    }

    k = 0;
    for (int i = n - 1; i >= 0; i--) 
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr && ActiPtr->getNgayDen() == ngayden)  
        {
            k++;
            if (k == STT) 
            {
                templateBill(ActiPtr, hoten_admin, getday(), getTime(), into_money, GiaThuong, GiaVang);
                templateBillFile(ActiPtr, hoten_admin, getday(), getTime(), into_money, GiaThuong, GiaVang, FBill);
               if (into_money >=200000)
                {
                    VQMM();
                }
                return;
            }
        }
    }
}

void QLAC::calculate(Day start_day, Day end_day)
{
    double Tong = 0;
    int k=0;
    
    for (int i=0; i<n; i++)
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr->getNgayDen() >= start_day && ActiPtr->getNgayDen() <= end_day)
        {
            cout << left << "| "; setColor(12);cout << setw(4) << ++k; setColor(7);
            ActiPtr->hienThiThongTin();
            if (ActiPtr->getGioVao() > timeVang) /*Giờ vào nằm ở giờ vip*/
            Tong += (ActiPtr->getGioRa() - ActiPtr->getGioVao())*GiaVang;
            else if (ActiPtr->getGioRa() < timeVang) //Giờ ra và ra nằm ở giờ thường
            Tong += (ActiPtr->getGioRa() - ActiPtr->getGioVao())*GiaThuong;
            else
            Tong += (ActiPtr->getGioRa() - timeVang)*GiaThuong + (timeVang - ActiPtr->getGioVao())*GiaVang;
        }
    }
    cout << "Doanh thu tu ngay "; start_day.xuatDay() ; cout << " den "; end_day.xuatDay(); cout << " la: "; 
    cout << fixed << setprecision(0) << Tong << endl;
}

void QLAC::update(string nameFile, int ch, string oldSDT,string newName, Day newBD, string newSDT){
    for (int i = 0; i < n; i++) {
        Acti *ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr->getSDT() == oldSDT) {
           if(ch==1){
            ActiPtr->setHoTen(newName);
           }
           else if(ch==2){
            ActiPtr->setNgaySinh(newBD);
           }
           else if(ch==3){
            ActiPtr->setSDT(newSDT);
           }
        }
    }
    ofstream file(nameFile);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr) {
            file << ActiPtr->getHoten() << ","
                 << ActiPtr->getNgaySinh().ngay << "/" << ActiPtr->getNgaySinh().thang << "/" << ActiPtr->getNgaySinh().nam << ","
                 << ActiPtr->getSDT() << ","
                 << ActiPtr->getNgayDen().ngay << "/" << ActiPtr->getNgayDen().thang << "/" << ActiPtr->getNgayDen().nam << ","
                 << ActiPtr->getGioVao().gio << ":" << ActiPtr->getGioVao().phut << ":" << ActiPtr->getGioVao().giay << ","
                 << ActiPtr->getGioRa().gio << ":" << ActiPtr->getGioRa().phut << ":" << ActiPtr->getGioRa().giay << ","
                 << ActiPtr->getID() << endl;
        }
    }

    file.close();
}


void QLAC::ActiDel(string namefile, string hoten, string sdt)
{
    int k = 0, STT;
    vector<int> a;
    for (int i=0; i<n; i++)
    {
        Acti *ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if ((ActiPtr->getHoten() == hoten) && (ActiPtr->getSDT() == sdt))
        {
            if (  (ActiPtr->getNgayDen() > getday()) || ((ActiPtr->getNgayDen() == getday()) && ActiPtr->getGioVao() > getTime())  )
            {
                cout << left << "| "; setColor(12); cout << setw(4) << ++k; setColor(7);
                AC[i]->hienThiThongTin();
                a.push_back(i);
            }
        }
    }
    if (a.empty()) {
        cout << "Quy khach chua dat san nao! Enter de quay lai" << endl;
        char delay = getch();
        return;
    }
    icon_Order();    cout << "Nhap STT can xoa: "; cin >> STT;
    while (STT <= 0 || STT > a.size()){
        setColor(4); cout << "STT ban nhap khong hop le. Vui long nhap lai: "; setColor(7); cin >> STT;
    }
    int index = a.at(STT-1);

    for (int i = index; i < n; i++) {
        AC[i] = AC[i + 1];
    }
    n--; 
    setColor(10);
    cout << "Delete activity successful!" << endl; 
    setColor(7);

    ofstream file(namefile, ios::out);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << namefile << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr) {
            file << ActiPtr->getHoten() << ","
                << ActiPtr->getNgaySinh().ngay << "/" << ActiPtr->getNgaySinh().thang << "/" << ActiPtr->getNgaySinh().nam << ","
                << ActiPtr->getSDT() << ","
                << ActiPtr->getNgayDen().ngay << "/" << ActiPtr->getNgayDen().thang << "/" << ActiPtr->getNgayDen().nam << ","
                << ActiPtr->getGioVao().gio << ":" << ActiPtr->getGioVao().phut << ":" << ActiPtr->getGioVao().giay << ","
                << ActiPtr->getGioRa().gio << ":" << ActiPtr->getGioRa().phut << ":" << ActiPtr->getGioRa().giay << ","
                << ActiPtr->getID() << endl;
        }
    }

    file.close();
    
}

void QLAC::sortActivities(int choice) {
    if (n == 0) {
        cout << "Bạn " << endl;
        return;
    }

    switch (choice) {
        case 1:
            std::sort(AC, AC + n, [](Person *a, Person *b) {
                Acti *actA = dynamic_cast<Acti*>(a);
                Acti *actB = dynamic_cast<Acti*>(b);
                return actA->getNgayDen() > actB->getNgayDen() ||
                       (actA->getNgayDen() == actB->getNgayDen() && actA->getGioVao() > actB->getGioVao());
            });
            break;

        case 2:
            std::sort(AC, AC + n, [](Person *a, Person *b) {
                Acti *actA = dynamic_cast<Acti*>(a);
                Acti *actB = dynamic_cast<Acti*>(b);
                return actA->getNgayDen() < actB->getNgayDen() ||
                       (actA->getNgayDen() == actB->getNgayDen() && actA->getGioVao() < actB->getGioVao());
            });
            break;

        case 3:
            std::sort(AC, AC + n, [](Person *a, Person *b) {
                Acti *actA = dynamic_cast<Acti*>(a);
                Acti *actB = dynamic_cast<Acti*>(b);
                int durationA = (actA->getGioRa().gio * 3600 + actA->getGioRa().phut * 60 + actA->getGioRa().giay) - 
                                (actA->getGioVao().gio * 3600 + actA->getGioVao().phut * 60 + actA->getGioVao().giay);
                int durationB = (actB->getGioRa().gio * 3600 + actB->getGioRa().phut * 60 + actB->getGioRa().giay) - 
                                (actB->getGioVao().gio * 3600 + actB->getGioVao().phut * 60 + actB->getGioVao().giay);
                return durationA > durationB;
            });
            break;

        default:
            return;
    }
}
