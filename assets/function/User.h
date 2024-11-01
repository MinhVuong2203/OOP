#ifndef USER_H
#define USER_H
#include "Activity.h"

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

#endif