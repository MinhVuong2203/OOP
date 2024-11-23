#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <windows.h>
#include "check.h"
#include "Title.h"
#include "Person.h"
#include "User.h"
#include "Admin.h"
using namespace std;

QLAD::QLAD(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return;
    }
    n = 0;
    string line;
    while (getline(file, line)) {
        n++;
    }
    file.clear();
    file.seekg(0, ios::beg);

    A = new Person*[n];
    int index = 0;
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
        A[index++]  = new Admin(hoten, ngaysinh, sdt, cccd);
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
        Cap:
        if (CapCha())
        {
            Person** newA = new Person*[n + 1]; 
           for (int i = 0; i < n; ++i) { 
            newA[i] = A[i]; 
            } 
            newA[n] = new Admin(HoTen, NgaySinh, SDT, CCCD); 
            delete[] A; 
            A = newA; 
            n++;
            file << HoTen <<","<< NgaySinh.ngay <<"/"<< NgaySinh.thang <<"/"<< NgaySinh.nam <<","<< SDT <<","<< CCCD << endl; 
            setColor(6);
            cout << "\n--------[Add Admin successful]----------\n" << endl;
            setColor(7);
        }
        else{
            cout << "Sai ma Capcha!\n";
            Sleep(1000);
            goto Cap;
        } 
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
    for (int i = 0; i < n; ++i) 
    { 
        delete A[i]; } 
        delete[] A;
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

bool checkSearch(const string &s, const string &x)
{
    int n = s.length(), m = x.length(); 
    if (n < m) return false; 
    for (int i = 0; i <= n - m; i++) 
    { 
        int j = 0; 
        while (j < m && s[i + j] == x[j]) 
        { 
            j++; 
        } 
        if (j == m) return true; 
    }
    return false;
}

void PriColor(const string &s, const string &x) {
    int n = s.length(), m = x.length();

    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < m && s[i + j] == x[j]) {
            j++;
        }
        if (j == m) {
            setColor(228);  cout<< x; setColor(7);
            i += m - 1; 
        } else {
            cout << s[i];
        }
    }
}
    
void QLAD::searchUS(string nameFile)
{
    ifstream file(nameFile);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << endl;
        return;
    }
   
    string search = "", line;
    bool found;
    int i;
    char c;
    system("cls");
    while(true)
    {
        file.clear(); file.seekg(0, ios::beg); 
        icon_Order();   cout<<"Nhap du lieu cua nguoi dung ma ban muon tim kiem: ";  cout << search;
        c = getche(); 
        if (c=='\b') //Nếu nhập xóa
        {
            if (!search.empty()) { 
            search.pop_back(); 
            cout << "\b \b";
            }
        }
        else if (c==13) {
            cout << endl;
            break;  //Nếu nhập enter
        }
        else search += c;  //Nếu nhập bình thường
        system("cls");
        i=0;
        cout << endl;
        if (search.length()>0)
        {
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
            
                if (checkSearch(HoTen, search) || checkSearch(NgaySinh_str, search) || checkSearch(SDT, search) || checkSearch(username, search) || checkSearch(password, search))
                {
                    i++; found = true;
                    cout << "| "; setColor(12); cout << left << setw(4) << i;
                    setColor(7); 
                    cout << "| "; PriColor(HoTen, search); cout << right << setw(22-HoTen.length()) << "| ";
                    PriColor(NgaySinh_str, search); cout << right << setw(16-NgaySinh_str.length()) << "| ";
                    PriColor(SDT, search); cout << right << setw(16-SDT.length()) << "| ";
                    PriColor(username, search); cout << right << setw(16-username.length()) << "| ";
                    PriColor(password, search); cout << right << setw(16-password.length()) << "| ";
                    cout << "\n";
                cout << "+-----+---------------------+---------------+---------------+---------------+---------------+\n";
                }
            }
            cout << endl;
        }
        
    }
    
    bool isDate = false, isPhone = true, isName = false;
    // Kiểm tra nếu chuỗi tìm kiếm là ngày sinh
    if (search.length() == 10 && 
        ((search[2] == '/' && search[5] == '/') || (search[2] == '-' && search[5] == '-'))) {
        isDate = true;
    }
    // Kiểm tra nếu chuỗi tìm kiếm là số điện thoại

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
    // cin.ignore();
    if (i==0) 
    {
        if(isName) {cout<<"\nKhong tim thay nguoi dung co "; setColor(9); cout <<"Ho ten "; setColor(7); cout << "nay!"<<endl;}
        else if (isDate) {cout<<"\nKhong tim thay nguoi dung co "; setColor(9); cout <<"Ngay sinh "; setColor(7); cout << "nay!"<<endl;}
        else if (isPhone) {cout<<"\nKhong tim thay nguoi dung co "; setColor(9); cout <<"SDT "; setColor(7); cout << "nay!"<<endl;}
        else cout << "\nKhong tim thay nguoi dung su dung du lieu nay!" << endl;
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