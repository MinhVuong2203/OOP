#pragma once
#include "Person.hpp"
using namespace std;

// class đối tượng user
class User : public Person {
private:
    string username;
    string password;

public:
    User() {}
    
    User(string HoTen, Day NgaySinh, string SDT, string TDN, string MK) : Person(HoTen, NgaySinh, SDT), username(TDN), password(MK) {}

    void hienThiThongTin() override {
        Person::hienThiThongTin();
        cout<< "| " << setw(14) << username
            << "| " << setw(14) << password
            << "|" << endl
            << "+-----+--------------------+---------------+---------------+---------------+---------------+" << endl;
    }
    string getUsername() {return this->username;}
    string getPassword() {return this->password;}
};
class QLUS{
private:
    Person *U[100];
    int n;

public:
    QLUS(string filename);
    ~QLUS();

    void add(string nameFile);
    void del(string nameFile, string username);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
		{
            cout << left << "| "; setColor(12); cout << setw(4) << i+1; setColor(7);
            U[i]->hienThiThongTin();
        }
    }
    User *getUser(string username)
    {
        for (int i=0; i<n; i++)
        {
            User *ActiPtr = dynamic_cast<User*>(U[i]);
            if (ActiPtr != nullptr && ActiPtr->getUsername() == username)
            return ActiPtr;   
        }
        return nullptr;
    }
    int getN(){return this->n;}
    void setN(int newN) { this->n = newN; }
    Person **getU(){return this->U;}
};

QLUS::QLUS(string filename)
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
        string hoten, ngaysinh_str, sdt, tdn, mk;
        Day ngaysinh;
        istringstream ss(line);
        getline(ss, hoten, ',');
        getline(ss, ngaysinh_str, ',');
        getline(ss, sdt, ',');
        getline(ss, tdn, ',');
        getline(ss, mk, ',');
        sscanf(ngaysinh_str.c_str(), "%d/%d/%d", &ngaysinh.ngay, &ngaysinh.thang, &ngaysinh.nam);
        hoten.erase(0, hoten.find_first_not_of(" "));
        sdt.erase(0, sdt.find_first_not_of(" "));
        tdn.erase(0, tdn.find_first_not_of(" "));
        mk.erase(0, mk.find_first_not_of(" "));
        Person *p = new User(hoten, ngaysinh, sdt, tdn, mk);
        U[n++] = p;
    }
}
void QLUS::add(string nameFile) 
{
    fstream file(nameFile, ios::app);
    string HoTen, SDT, MK, TDN;
    Day NgaySinh;
    cout << "Nhap ho ten: ";  getline(cin, HoTen);
        while (checkName(HoTen)==false){
            cout << "Ho ten khong hop le. Vui long nhap lai: ";  cin.ignore(); getline(cin, HoTen);
        }
    cout << "Nhap ngay sinh: "; NhapDay(NgaySinh);
    cout << "Nhap SDT: "; cin.ignore(); getline(cin, SDT);
        while (checkSDT(SDT)==false){
            cout << "SDT khong hop le. Vui long nhap lai: "; getline(cin, SDT);
        }
    cout << "Ten dang nhap: ";  getline(cin, TDN);
        while (checkFile(TDN, nameFile)==false){
            cout << "Ten dang nhap da co tai khoan. Vui long dung ten dang nhap khac: ";  cin.ignore(); getline(cin, TDN);
        }
    cout << "Mat khau: ";   getline(cin, MK);
	Person *p = new User(HoTen, NgaySinh, SDT, TDN, MK);
    U[n++] = p;
    file <<HoTen <<","<< NgaySinh.ngay <<"/"<< NgaySinh.thang <<"/"<< NgaySinh.nam <<","<< SDT <<","<< TDN <<","<< MK << endl;
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }
    cout << "Add User successful!" << endl;
    file.close();
}


void QLUS::del(string nameFile, string username) {
    int index = -1;

 
    for (int i = 0; i < n; i++) {
        User *ActiPtr = dynamic_cast<User*>(U[i]);
        if (ActiPtr != nullptr && ActiPtr->getUsername() == username) {
            index = i;
            break;
        }
    }
    
    for (int i = index; i < n - 1; i++) {
        U[i] = U[i + 1];
    }
    n--;

    ofstream file(nameFile, ios::out);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        User *ActiPtr = dynamic_cast<User*>(U[i]);
        if (ActiPtr != nullptr) {
            file << ActiPtr->getHoten() << "," 
                 << ActiPtr->getNgaySinh().ngay << "/" 
                 << ActiPtr->getNgaySinh().thang << "/" 
                 << ActiPtr->getNgaySinh().nam << ","
                 << ActiPtr->getSDT() << ","
                 << ActiPtr->getUsername() << ","
                 << ActiPtr->getPassword() << endl;
        }
    }

    file.close();
    cout << "Delete User successful!" << endl;
}
QLUS::~QLUS(){
    for (int i = 0; i < n; i++) {
        delete U[i];
    }
}

