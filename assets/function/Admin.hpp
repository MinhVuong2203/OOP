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
    void delUS(string nameFile);

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
void QLAD::delAd(string nameFile){
    int deleteAdmin;
    cout<<"Nhap Admin ban muon xoa:";
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
void QLAD::delUS(string nameFile){
    QLUS qlus(nameFile);
    
    int deleteUser;
    int n=qlus.getN();
    cout<<"Nhap User ban muon xoa:";
    cin>>deleteUser;
    if(deleteUser<1 || deleteUser> n){
        cout<<"Khong ton tai User o vi tri nay";
        return;
    }
    Person** U = qlus.getU();
    delete U[deleteUser-1];
    for(int i=deleteUser-1;i<n-1;i++){
        U[i]=U[i+1];
    }
    n--;
    qlus.setN(qlus.getN()-1);
    cout<<"Xoa User thanh cong"<<endl;
    fstream file(nameFile, ios::out);
    if (!file.is_open())
        {
            cerr << "Unable to open file: " << nameFile << endl;
            return;
        }
    for (int i = 0; i < qlus.getN(); ++i) {
        User* user = dynamic_cast<User*>(U[i]);
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
    file.close();    
}