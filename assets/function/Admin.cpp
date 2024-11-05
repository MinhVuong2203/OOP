#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "check.h"
#include "Title.h"
#include "Person.h"
#include "User.h"
#include "Admin.h"
using namespace std;

QLAD::QLAD(string filename)
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
        string hoten, ngaysinh_str, sdt, cccd;
        Day ngaysinh;
        istringstream ss(line);
        getline(ss, hoten, ',');
        getline(ss, ngaysinh_str, ',');
        getline(ss, sdt, ',');
        getline(ss, cccd, ',');
        sscanf(ngaysinh_str.c_str(), "%d/%d/%d", &ngaysinh.ngay, &ngaysinh.thang, &ngaysinh.nam);
        hoten.erase(0, hoten.find_first_not_of(" "));
        sdt.erase(0, sdt.find_first_not_of(" "));
        cccd.erase(0, cccd.find_first_not_of(" "));
        Person *p = new Admin(hoten, ngaysinh, sdt, cccd);
        A[n++] = p;
    }
}
string QLAD::getName(string CCCD)
{
    for (int i=0; i<n; i++)
    {
        Admin* admin = dynamic_cast<Admin*>(A[i]);
        if (CCCD == admin->getCCCD())
        return admin->getHoten();
    }
    return NULL;
}
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
        // cin.ignore();
        icon_Order();    cout << "Nhap ho ten: ";   cin.ignore(); getline(cin, HoTen);
            while (checkName(HoTen)==false){
            cout << "Ho ten khong hop le. Vui long nhap lai: ";  cin.ignore(); getline(cin, HoTen);
            }
        icon_Order(); cout << "Nhap ngay sinh (dd/mm/yyyy): "; NgaySinh.nhapDay();
        icon_Order(); cout << "Nhap SDT: "; cin.ignore(); getline(cin, SDT);
            while (checkSDT(SDT)==false){
            cout << "SDT khong hop le. Vui long nhap lai: "; getline(cin, SDT);
            }
            while (checkFile(SDT, nameFile)==false){
                cout << "SDT da dang ki tai khoan. Vui long dung SDT khac: ";  cin.ignore(); getline(cin, SDT);
            }

        icon_Order(); cout << "Nhap CCCD: ";  getline(cin, CCCD);
            while (checkCCCD(CCCD) == false){
            cout << "CCCD khong hop le. Vui long nhap lai: ";  getline(cin, CCCD);
            }

		Person *p = new Admin(HoTen, NgaySinh, SDT, CCCD);
        A[n++] = p;
        file << HoTen <<","<< NgaySinh.ngay <<"/"<< NgaySinh.thang <<"/"<< NgaySinh.nam <<","<< SDT <<","<< CCCD << endl; 
        setColor(6);
        cout << "\n--------[Add Admin successful]----------\n" << endl;
        setColor(7);
        file.close();
}

void QLAD::addUS(QLUS &U, string namefile)
{
    U.add(namefile);
}

void QLAD::delUS(QLUS &U, string namefile, string username)
{
    U.del(namefile, username);
}

QLAD::~QLAD() {
    for (int i = 0; i < n; i++) {
        delete A[i]; // Giải phóng từng đối tượng
    }
}

void QLAD::delAd(string nameFile){
    int deleteAdmin;
    cout<<"\nNhap Admin ban muon xoa:";

    cin>>deleteAdmin;
    if(deleteAdmin<1 || deleteAdmin > n){
        cout<<"Khong ton tai Admin o vi tri nay";
        return;
    }
    delete A[deleteAdmin-1];
    for(int i=deleteAdmin-1;i<n-1;i++){
        A[i]=A[i+1];
    }
    n--;
    cout<<"Xoa Admin thanh cong"<<endl;
    fstream file(nameFile, ios::out);
    if (!file.is_open())
        {
            cerr << "Unable to open file: " << nameFile << endl;
            return;
        }
    for (int i = 0; i < n; ++i)
    {
        Admin* admin = dynamic_cast<Admin*>(A[i]);
        if (admin) {
            file << admin->getHoten() << "," 
                << admin->getNgaySinh().ngay << "/"
                << admin->getNgaySinh().thang << "/"
                << admin->getNgaySinh().nam << "," 
                << admin->getSDT() << "," 
                << admin->getCCCD() << endl;
        }
    }
    file.close();
}
bool check(char c) {
    return c >= '0' && c <= '9';  // Kiểm tra xem ký tự có phải là số không
    }
void QLAD::searchUS(string search, string nameFile){
    ifstream file(nameFile);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << endl;
        return;
    }
    bool isDate = false, isPhone = true, isName = false;
    // Kiểm tra nếu chuỗi tìm kiếm là ngày sinh
    if (search.length() == 10 && 
        ((search[2] == '/' && search[5] == '/') || (search[2] == '-' && search[5] == '-'))) {
        isDate = true;
    }

    // Kiểm tra nếu chuỗi tìm kiếm  là số điện thoại

    if (search.length() != 10) {
        isPhone = false;
    }
    else {
        for (char c : search) {
            if (!check(c)) {
                isPhone = false;
                break;
            }
        }
    }
    // Kiểm tra nếu chuỗi tìm kiếm là họ tên
    for (char c : search) {
        if (c == ' ') {
            isName = true;
            break;
        }
    }
    string line;
    int i=0;
    bool found = false; // Biến để kiểm tra nếu tìm thấy user
    cout<<endl;
    TitleUser();
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string item; 
        string HoTen, NgaySinh_str, SDT, username, password;
        bool isFirst = true; 
        
        getline(ss, HoTen, ',');
        getline(ss, NgaySinh_str, ',');
        getline(ss, SDT, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
       
            if (HoTen == search || NgaySinh_str == search || SDT == search || username == search || password == search) 
            {
                i++;
            cout << "| ";setColor(12);cout << setw(4) << i;
            setColor(7); 
            cout << "| " << setw(19) << HoTen
                 << "| " << setw(14) << NgaySinh_str
                 << "| " << setw(14) << SDT
                 << "| " << setw(14) << username
                 << "| " << setw(14) << password
                 << "|\n";
            cout << "+-----+--------------------+---------------+---------------+---------------+---------------+\n";

            found = true;
            }
    }
    cin.ignore();
    if (!found) {
        if(isName) cout<<"Khong tim thay nguoi dung co ho ten nay!"<<endl;
        else if (isDate) cout<<"Khong tim thay nguoi dung co ngay sinh nay"<<endl;
        else if (isPhone) cout<<"Khong tim thay nguoi dung co so dien thoai nay"<<endl;
        else cout << "Khong tim thay nguoi dung su dung du lieu nay!" << endl;
    }
    
    file.close();
}

void QLAD::priBill(QLAC &AC, Day day, string hoten_admin){
    AC.priBill(day, hoten_admin);
}

void QLAD::Calculate(QLAC &AC, Day start_day, Day end_day){
    AC.calculate(start_day, end_day);
}

void QLAD::order(QLAC &AC,string namefile, string hoten, Day day_order, string sdt)
{
    AC.add(namefile, hoten, day_order, sdt);
}