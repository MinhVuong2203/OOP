#include <fstream>
    #include <algorithm>
#include "check.h"
#include "Person.h"
#include "Activity.h"
#include "User.h"
using namespace std;

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
    cin.ignore();
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
cout << "Xoa thanh cong!" << endl;

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


void QLUS::fixUser(string nameFile,int &index, int &ch, string &oldSDT,string &newName, Day &newBD, string &newSDT, string username, int w) {
    index=-1;

    if(w==1 || w==3){
    for (int i = 0; i < n; i++) {
        User *uFix = dynamic_cast<User*>(U[i]);
        if (uFix->getSDT() == oldSDT) {
            index = i;
            break;
        }
    }
    }
    else if(w==2){
    for (int i = 0; i < n; i++) {
        User *uFix = dynamic_cast<User*>(U[i]);
        if (uFix->getUsername() == username) {
            index = i;
            break;
        }
    }
    }
    if(index==-1)   {cout<<"Khong ton tai nguoi nay!"; return;} User *uFix = dynamic_cast<User*>(U[index]); oldSDT=uFix->getSDT();
    if(w!=3){
        icon_choice(); cout << "1. Sua ho ten"<<endl;
        icon_choice(); cout << "2. Sua ngay sinh"<<endl;
        icon_choice(); cout << "3. Sua SDT"<<endl;
        icon_choice(); cout << "4. Sua ten dang nhap"<<endl;
        icon_choice(); cout << "5. Sua mat khau"<<endl;
        icon_choice(); cout << "6. Thoat"<<endl;
        cin>>ch;
    }
    else ch=5;
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
            if(w!=3)         cin.ignore();
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

string getLastName(const string &fullName) {
    size_t pos = fullName.find_last_of(" ");
    return fullName.substr(pos + 1);
}

void merge(Person *U[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Person *L[n1], *R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = U[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = U[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        User *userL = dynamic_cast<User*>(L[i]);
        User *userR = dynamic_cast<User*>(R[j]);
        
        if (userL != nullptr && userR != nullptr) {
            if (getLastName(userL->getHoten()) <= getLastName(userR->getHoten())) {
                U[k] = L[i];
                i++;
            } else {
                U[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) {
        U[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        U[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Person *U[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(U, left, mid);
    mergeSort(U, mid + 1, right);
    merge(U, left, mid, right);
}

void QLUS::sort(string nameFile) {
    mergeSort(U, 0, n - 1);
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
    cout << "\nDanh sach sau khi sap xep:" << endl;
}