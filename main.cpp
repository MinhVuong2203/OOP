#include <iostream>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <fstream>

using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
struct Time {
    int gio, phut, giay;
};
void NhapTime(Time &x)
{
	cin >> x.gio >> x.phut >> x.giay;
}

struct Day {
    int ngay, thang, nam;
};

void NhapDay(Day &x) {
    cin >> x.ngay >> x.thang >> x.nam;
}

class Person{
private:
    string Hoten;
    Day NgaySinh;
    string SDT;
public:
    Person() {}
    Person(string Hoten, Day NgaySinh, string SDT) {
        this->Hoten = Hoten;
        this->NgaySinh = NgaySinh;
        this->SDT = SDT;
    }

    string getHoten() { return Hoten; }
    int getNgay() { return NgaySinh.ngay; }
    int getThang() { return NgaySinh.thang; }
    int getNam() { return NgaySinh.nam; }
    string getSDT() { return SDT; }

    virtual void hienThiThongTin() {
        cout << Hoten << " " << NgaySinh.ngay << "/" << NgaySinh.thang << "/" << NgaySinh.nam << " " <<  SDT << " ";
    }
};

class Admin : public Person {
private:
    string id;
public:
    Admin() {}
    Admin(string HoTen, Day NgaySinh, string SDT, string ID) : Person(HoTen, NgaySinh, SDT), id(ID) {}

    string getID() { return id; }

    void hienThiThongTin() override {
        Person::hienThiThongTin();
        cout << id << endl;
    }
};

class User : public Person {
private:
    Day NgayVao;
    Time GioVao;
    Time GioRa;
public:
    User() {}
    User(string HoTen, Day NgaySinh, string SDT, Day NV, Time GV, Time GR) : Person(HoTen, NgaySinh, SDT), NgayVao(NV), GioVao(GV), GioRa(GR) {}

    int getNgay() { return NgayVao.ngay; }
    int getThang() { return NgayVao.thang; }
    int getNam() { return NgayVao.nam; }

    void hienThiThongTin() override {
        Person::hienThiThongTin();
        cout << " " << NgayVao.ngay << "/" << NgayVao.thang << "/" << NgayVao.nam;
        cout << " " << GioVao.gio << ":" << GioVao.phut << ":" << GioVao.giay;
        cout << " " << GioRa.gio << ":" << GioRa.phut << ":" << GioRa.giay << endl;
        
    }
};

class QLAD{
private:
    Person *A[20];
    int n;

public:
    QLAD() { this->n = 0; }
    void add(Person *ps) 
	{
        A[n++] = ps;
        cout << "Them admin thanh cong!" << endl;
    }
    
    void hienDS() 
	{
        for (int i = 0; i < n; i++) {
            A[i]->hienThiThongTin();
        }
    }
};

class QLUS{
private:
    Person *U[20];
    int n;

public:
    QLUS() { this->n = 0; }
    void add(Person *ps) 
	{
        U[n++] = ps;
        cout << "Them nguoi choi thanh cong!" << endl;
    }
    
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
		{
            U[i]->hienThiThongTin();
        }
    }
};


void TitleAdmin()
{
	cout << left << setw(20) << "Ho ten" 
        << setw(15) << "Ngay Sinh" 
        << setw(15) << "SDT" 
        << setw(10) << "ID" << endl;
}

void TitleUser()
{
	cout << left << setw(20) << "Ho ten" 
        << setw(15) << "Ngay Sinh" 
        << setw(15) << "SDT" 
        << setw(10) << "Ngay vao"
        << setw(10) << "Gio Vao"
        << setw(10) << "Gio Ra" << endl;
}

int authenticateUser(string username, string password, string FilePass) {
    ifstream file(FilePass);
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << FilePass << endl;
        return 0;
    }

    string fileUsername, filePassword;
    while (file >> fileUsername >> filePassword) {
        if (fileUsername == username) {
            file.close();
            return (filePassword == password) ? 1 : 0; // Authentication successful or incorrect password
        }
    }

    file.close();
    return 0; // Username not found
}


int main() {
    QLAD AD;
    QLUS U;
    string HoTen, id, SDT;
    Day NgaySinh, NgayVao;
    Time GioVao, GioRa;
    string username, password;
    time_t presentTime;
    struct tm *tm_info;
    time(&presentTime); // Lay thoi gian hien tai
    tm_info = localtime(&presentTime); // chuyen doi thanh cau truc "tm"
    Day day;
    day.ngay =  tm_info->tm_mday; day.thang = tm_info->tm_mon+1; day.nam = tm_info->tm_year+1900;
    printf("Hom nay: %02d/%02d/%04d\n\n", day.ngay, day.thang, day.nam );

    string FileAdminPass = "FileAdminPass.txt";


    setColor(10);
    	printf("+------------------------------------------------+\n");
      	printf("|     San cau long CIB xin kinh chao quy khach   |\n");
		printf("+------------------------------------------------+\n\n");
    setColor(7);
    cout << "1. Nguoi quan ly\t\t2. Nguoi dung\t\t3. Thoat\n\nMoi nhap lua chon cua ban: ";
    char choice1 = getche();	
    switch (choice1-'0') 
	{
        case 1:
            read_loop2:	system("cls");
            cout << "---------MENU---------\n";
			cout << "1. Ban muon dang ky tai khoan\n2. Dang nhap\n3. Quay lai\n4. Thoat\nMoi nhap lua chon cua ban:";
        	char choice2;
			choice2=getche();	system("cls");	
			switch (choice2-'0')
			{
                case 1: 
                case 2: read_loop_aut: system("cls");
                    cout << "Ten dang nhap (viet lien, khong dau): "; cin >> username; 
                    cout << "Mat khau (viet lien, khong dau): "; cin >> password;
                    if (authenticateUser(username,password, FileAdminPass)) 
                    {
                        cout << "Dang nhap thanh cong"; 
                        // Thực hiện công việc
                    }
                    else 
                    {
                        cout << "\n<<< Dang nhap that bai. Enter de dang nhap lai! >>>";
                        char delay = getche();
                        goto read_loop_aut;
                    }
                break;
                case 3: goto read_loop2;
                case 4: break;
            }

        case 2:

        case 3: break;
    }





    // cout << "---------MENU---------\n";
    // cout << "1. Them nguoi quan li\n";
    // cout << "2. Xuat danh sach admin\n";
    // cout << "3. Them nguoi choi\n";
    // cout << "4. Xuat danh sach nguoi dung\n";
    // int chose;
    // while (true) 
    // {
    //     cout << "Moi nhap lua chon: "; cin >> chose;
    //     switch (chose) 
	// 	{
    //         case 1: {
    //             cout << "Nhap ho ten: "; cin.ignore(); getline(cin, HoTen);
    //             cout << "Nhap ngay sinh: "; NhapDay(NgaySinh);
    //             cout << "Nhap SDT: "; cin.ignore(); getline(cin, SDT);
    //             cout << "Nhap id: ";  getline(cin, id);

    //             Person *p = new Admin(HoTen, NgaySinh, SDT, id);
    //             AD.add(p);
    //             break;
    //         }
    //         case 2:
    //             TitleAdmin();
    //             AD.hienDS();
    //             break;
    //         case 3: 
    //         {
	// 			cout << "Nhap ho ten: "; cin.ignore(); getline(cin, HoTen);
    //             cout << "Nhap ngay sinh: "; NhapDay(NgaySinh);
    //             cout << "Nhap SDT: "; cin.ignore(); getline(cin, SDT);
    //             cout << "Nhap ngay vao: "; NhapDay(NgayVao);      
	// 			cout << "Nhap gio vao: "; NhapTime(GioVao);
	// 			cout << "Nhap gio ra: "; NhapTime(GioRa);  
				
	// 			Person *p = new User(HoTen, NgaySinh, SDT, NgayVao, GioVao, GioRa);
	// 			U.add(p);
	// 			break;
	// 		}
	// 		case 4:
	// 			TitleUser();
    //             U.hienDS();
    //             break;
	// 	}
    // }

    system("pause");
    return 0;
}
