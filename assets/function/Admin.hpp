#pragma once
#include <iostream>
#include "Person.hpp"
#include "User.hpp"
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
    QLAD(string filename);

    void add(string nameFile);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
        {
            A[i]->hienThiThongTin();
        }
    }
    void fixAccountUser(string nameFile);
    void delAd(string nameFile);
    void delUS(string nameFile, QLUS &U);
   
};



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
        icon_Order();    cout << "Nhap ho ten: ";  getline(cin, HoTen);
            while (checkName(HoTen)==false){
            cout << "Ho ten khong hop le. Vui long nhap lai: ";  cin.ignore(); getline(cin, HoTen);
            }
        icon_Order(); cout << "Nhap ngay sinh (dd/mm/yyyy): "; NhapDay(NgaySinh);
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

QLAD::~QLAD() {
    for (int i = 0; i < n; i++) {
        delete A[i]; // Giải phóng từng đối tượng
    }
}

void QLAD::delAd(string nameFile){
    int deleteAdmin;

    cout<<"Nhap Admin ban muon xoa:";

    cout<<"\nNhap Admin ban muon xoa:"<<endl;

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

void QLAD::delUS(string nameFile, QLUS &U) {
    int deleteUser;
    int n = U.getN();  // Lấy số lượng user từ đối tượng U thực tế
    cout << "Nhap so thu tu cua User ban muon xoa: ";
    cin >> deleteUser;

    // Kiểm tra xem chỉ số xóa có hợp lệ không
    if (deleteUser < 1 || deleteUser > n) {
        cout << "Khong ton tai User o vi tri nay." << endl;
        return;
    }

    Person** users = U.getU();  // Lấy danh sách người dùng từ đối tượng U

    // Xóa user tại vị trí deleteUser-1
    delete users[deleteUser - 1];  // Giải phóng bộ nhớ của User

    // Dịch chuyển các phần tử sau vị trí deleteUser lên một vị trí
    for (int i = deleteUser - 1; i < n - 1; i++) {
        users[i] = users[i + 1];
    }

    n--;  // Giảm số lượng user
    U.setN(n);  // Cập nhật lại số lượng người dùng sau khi xóa

    cout << "Xoa User thanh cong." << endl;

    // Mở file để ghi lại danh sách mới
    fstream file(nameFile, ios::out);
    if (!file.is_open()) {
        cerr << "Khong the mo file: " << nameFile << endl;
        return;
    }

    // Ghi lại danh sách User vào file
    for (int i = 0; i < U.getN(); ++i) {
        User* user = dynamic_cast<User*>(users[i]);
        if (user) {
            file << user->getHoten() << ","
                 << user->getNgaySinh().ngay << "/"
                 << user->getNgaySinh().thang << "/"
                 << user->getNgaySinh().nam << ","
                 << user->getSDT() << ","
                 << user->getUsername() << ","
                 << user->getPassword() << endl;
        }
    }
    file.close();  // Đóng file sau khi ghi
}



