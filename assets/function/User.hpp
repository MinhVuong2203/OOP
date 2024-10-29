#pragma once
#include "Person.hpp"
#include "Activity.hpp"
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
    void setUsername(string newUsername) { this->username = newUsername; }
    void setPassword(string newPassword) { this->password = newPassword; }

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
    void fixUser(string nameFile,int index, int &ch, string &oldName,string &newName, Day &newBD, string &newSDT);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
		{
            cout << left << "| "; setColor(12); cout << setw(4) << i+1; setColor(7);
            U[i]->hienThiThongTin();
        }
    }
    void hienThi(int i) 
	{
            cout << left << "| "; setColor(12); cout << setw(4) << i; setColor(7);
            U[i-1]->hienThiThongTin(); 
    }
    User *getUser(string username)    //Hàm lấy thông tin một user
    {
        for (int i=0; i<n; i++)
        {
            User *ActiPtr = dynamic_cast<User*>(U[i]);
            if (ActiPtr != nullptr && ActiPtr->getUsername() == username)
            return ActiPtr;   
        }
        return nullptr;
    }
    string arrayGetUsername(int x)  // Hàm lấy tên đăng nhập dựa vào chỉ số trong mảng quản lí user
    {
            User *ActiPtr = dynamic_cast<User*>(U[x-1]);
            return ActiPtr->getUsername();  
        return nullptr;
    }

    int getN(){return this->n;}
    void setN(int newN) { this->n = newN; }
    Person **getU(){return this->U;}
    void order(string namefile, QLAC &AC, string hoten, Day ngaysinh, string sdt);
    void History(QLAC &AC, string hoten, string sdt);
    void ActiDel(string FActivity, QLAC &AC, string hoten, string sdt);
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
    cout << "Nhap ngay sinh: "; NgaySinh.nhapDay();
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
    int index;
    for (int i = 0; i < n; i++) {
        User *uDelu = dynamic_cast<User*>(U[i]);
        if (uDelu->getUsername() == username) {
            index = i;
            break;
        }
    }
    for (int i = index; i < n; i++) {
        U[i] = U[i + 1];
    }
    n--;
cout << "Delete User successful!" << endl;

    ofstream file(nameFile, ios::out);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        User *uDelu = dynamic_cast<User*>(U[i]);
        if (uDelu != nullptr) {
            file << uDelu->getHoten() << "," 
                 << uDelu->getNgaySinh().ngay << "/" 
                 << uDelu->getNgaySinh().thang << "/" 
                 << uDelu->getNgaySinh().nam << ","
                 << uDelu->getSDT() << ","
                 << uDelu->getUsername() <<","
                 << uDelu->getPassword() << endl;
        }
    }

    file.close();
}
QLUS::~QLUS(){
    for (int i = 0; i < n; i++) {
        delete U[i];
    }
}


void QLUS::fixUser(string nameFile,int index, int &ch, string &oldName,string &newName, Day &newBD, string &newSDT) {
    if (index < 1 || index > n) {
        cout << "So thu tu khong hop le!" << endl;
        return;
    }
    User *uFix = dynamic_cast<User*>(U[index - 1]);
    if (uFix == nullptr) {
        cout << "User not found!" << endl;
        return;
    }
    oldName=uFix->getHoten();
        cout << "1. Sua ho ten\n2. Sua ngay sinh\n3. Sua SDT\n4. Sua TDN\n5. Sua mat khau\n6. Thoat\nNhap lua chon cua ban: "; cin>>ch;
    switch (ch) {
        case 1: {
            cout << "Nhap ho ten moi: ";
            cin.ignore();
            getline(cin, newName);
            while (!checkName(newName)) {
                cout << "Ho ten khong hop le. Vui long nhap lai: ";
                getline(cin, newName);
            }
            uFix->setHoTen(newName);
            break;
        }
        case 2: {
            cout << "Nhap ngay sinh moi: ";
            newBD.nhapDay();
            uFix->setNgaySinh(newBD);
            break;
        }
        case 3: {
            cout << "Nhap SDT moi: ";
            cin.ignore();
            getline(cin, newSDT);
            while (!checkSDT(newSDT)) {
                cout << "SDT khong hop le. Vui long nhap lai: ";
                getline(cin, newSDT);
            }
            uFix->setSDT(newSDT);
            break;
        }
        case 4: {
            string newUsername;
            cout << "Nhap ten dang nhap moi: ";
            cin.ignore();
            getline(cin, newUsername);
            while (!checkFile(newUsername, nameFile)) {
                cout << "Ten dang nhap da co tai khoan. Vui long nhap ten dang nhap khac: ";
                getline(cin, newUsername);
            }
            uFix->setUsername(newUsername);
            break;
        }
        case 5: {
            string newPassword;
            cout << "Nhap mat khau moi: ";
            cin.ignore();
            getline(cin, newPassword);
            uFix->setPassword(newPassword);
            break;
        }
        case 6:
        ch=0; break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            return;
    }
    ofstream file(nameFile, ios::out);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        User *user = dynamic_cast<User*>(U[i]);
        if (user != nullptr) {
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

void QLUS::order(string namefile, QLAC &AC, string hoten, Day ngaysinh, string sdt)
{
    AC.add(namefile, hoten, ngaysinh, sdt);
}


void QLUS::History(QLAC &AC, string hoten, string sdt)
{
    AC.History(hoten, sdt);
}

void QLUS::ActiDel(string namefile, QLAC &AC, string hoten, string sdt)
{
    AC.ActiDel(namefile, hoten, sdt);
}

