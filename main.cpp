#include <iostream>
#include <string>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

const int SL = 20;

// Tạo màu
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Xử lí Time
struct Time {
    int gio, phut, giay;
};
bool checkTime(Time x)
{
    if (x.giay < 0 || x.gio < 0 || x.phut < 0 ) return false;
    if (x.giay >= 60 || x.phut >= 60 || x.gio>=24) return false;
    return true;
}
void NhapTime(Time &x)
{
    scanf("%d:%d:%d",&x.gio, &x.phut, &x.giay);
    while (checkTime(x) == false)
    {
        cout << "Thoi gian khong hop le! Vui long nhap lai: "; 
        scanf("%d:%d:%d",&x.gio, &x.phut, &x.giay);
    }
}
// Xử lí day
struct Day {
    int ngay, thang, nam;
};

bool checkDay(Day x)
{
	int maxDay=0;
	if (x.nam<1900) return false;
	if (x.thang < 1 || x.thang >12) return false;
	if (x.ngay < 1 || x.ngay > 31) return false;
	switch(x.thang)
	{
	case 1: case 3: case 5: case 7:  case 8: case 10: case 12: maxDay = 31; break;
	case 4: case 6: case 9: case 11: maxDay = 30;  break;
	case 2: if (x.nam%4 == 0) 
				maxDay = 29;
			else
				maxDay = 28;  break;
	}
	if (x.ngay > maxDay) return false;
	
	return true;
}

void NhapDay(Day &x)
{
	scanf("%d/%d/%d",&x.ngay, &x.thang, &x.nam);
    while (checkDay(x) == false)
	{
		cout << "Ngay thang nam khong hop le!\nVui long nhap lai: ";
        scanf("%d/%d/%d",&x.ngay, &x.thang, &x.nam);
	}
}

//các class liên quan
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
        cout << left 
         << "| " << setw(19) << Hoten 
         << "| " << setw(14) << (to_string(NgaySinh.ngay) + "/" + to_string(NgaySinh.thang) + "/" + to_string(NgaySinh.nam))
         << "| " << setw(14) << SDT;
    }
};

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
            << "+--------------------+---------------+---------------+---------------+---------------+" << endl;
    }
};

class QLAD{
private:
    Person *A[20];
    int n;
public:
    QLAD() { this->n = 0; } 
	
    void add(string nameFile);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) {
            A[i]->hienThiThongTin();
        }
    }
};
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
        cout << "Nhap ho ten: ";  getline(cin, HoTen);
        cout << "Nhap ngay sinh: "; NhapDay(NgaySinh);
        cout << "Nhap SDT: "; cin.ignore(); getline(cin, SDT);
        cout << "Nhap CCCD: ";  getline(cin, CCCD);
		Person *p = new Admin(HoTen, NgaySinh, SDT, CCCD);
        A[n++] = p;
        file << HoTen <<" "<< NgaySinh.ngay <<"/"<< NgaySinh.thang <<"/"<< NgaySinh.nam <<" "<< SDT <<" "<< CCCD << endl;
        
        cout << "Add Admin successful!" << endl;
        file.close();
}

class QLUS{
private:
    Person *U[100];
    int n;

public:
    QLUS(string filename);
    void add(string nameFile);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
		{
            U[i]->hienThiThongTin();
        }
    }
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
    cout << "Nhap ngay sinh: "; NhapDay(NgaySinh);
    cout << "Nhap SDT: "; cin.ignore(); getline(cin, SDT);
    cout << "Ten dang nhap: ";  getline(cin, TDN);
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

void Menu()
{
    cout << "----------------"; setColor(11); cout << "MENU"; setColor(7); cout << "---------------\n";
}

void TitleAdmin()
{
	cout << left << setw(20) << "Ho ten" 
        << setw(15) << "Ngay Sinh" 
        << setw(15) << "SDT" 
        << setw(10) << "ID" << endl;
}

void TitleUser() 
{
    cout << left 
         << "+--------------------+---------------+---------------+---------------+---------------+" << endl
         << "|       Ho ten       |   Ngay Sinh   |     SDT       | Ten dang nhap |    Mat khau   |" << endl
         << "+--------------------+---------------+---------------+---------------+---------------+" << endl;
}

int authenticateUser(string username, string password, string FilePass) {
    ifstream file(FilePass);
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << FilePass << endl;
        return 0;
    }

    string fileUsername, filePassword;

    while (file >> filePassword) {
        if (fileUsername == username) {
            file.close();
            return (filePassword == password) ? 1 : 0;
        }
        else
        fileUsername = filePassword;
    }

    file.close();
    return 0;
}

void hidePassword(std::string &password) {
    char ch;
    int i = 0;
    while (true) {
        ch = _getch(); // getch() function hides the user input
        if (ch == 13 || ch == 10) { // ASCII value of Enter key
            break;
        } else if (ch == 8 && i > 0) { // ASCII value of Backspace key
            printf("\b \b"); // Erase previous character
            password.pop_back(); // Xóa ký tự cuối cùng trong chuỗi
            i--;
        } else if (isprint(ch)) {
            printf("*");
            password.push_back(ch); // Thêm ký tự vào chuỗi
            i++;
        }
    }
}


int main() 
{
    //Khai báo file
    string FAdmin = "assets//Admin.txt";
    string FUser = "assets//User.txt";
    string FRetail = "assets//Retail.txt";
    string FActivity = "assets//Activity.txt";

    QLAD AD;
    QLUS U(FUser);
    int San[SL];

    string username, password;
    time_t presentTime;
    char delay;

    // Lấy ngày hien tai
    struct tm *tm_info;
    time(&presentTime); 
    tm_info = localtime(&presentTime); 
    Day day;  Time time;
    day.ngay =  tm_info->tm_mday; day.thang = tm_info->tm_mon+1; day.nam = tm_info->tm_year+1900;
    cout << "Hom nay: " << day.ngay << "/" << day.thang << "/" << day.nam << " ";
    // In ra giờ, phút, giây
    time_t t = std::time(nullptr);
    tm* now = localtime(&t);
    time.gio = now->tm_hour; time.phut = now->tm_min; time.giay = now->tm_sec;
    cout << time.gio << ":" << time.phut << ":" << time.giay << "PM"<< endl;

    


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
            read_loopA2:	system("cls");
            Menu();
			cout << "1. Ban muon dang ky tai khoan\n2. Dang nhap\n3. Quay lai\n4. Thoat\nMoi nhap lua chon cua ban: ";
        	char Achoice2;
			Achoice2=getche();	system("cls");	
			switch (Achoice2-'0')
			{
                case 1: AD.add(FAdmin); break;
                case 2: 
                {
                    read_loop_autA: system("cls");
                    cout << "Ten dang nhap (viet lien, khong dau): "; cin >> username; 
                    cout << "<<<<<Ban co muon an mat khau (y/n)>>>>>>>: "; char ynA1 = getche();
                    if (ynA1 == 'y' ) { cout << "\nMat khau (viet lien, khong dau): ";  hidePassword(password);}
                    else if (ynA1 == 'n') { cout << "\nMat khau (viet lien, khong dau): ";  cin >> password;}
                    else {
                        cout << "\nLua chon khong hop le. Enter de quay lai!";
                        delay = getch(); goto read_loop_autA;
                    }
                    
                    if (authenticateUser(username,password, FAdmin)) 
                    {
                        cout << "\n<<< Dang nhap thanh cong>>>" << endl; 
                        delay = getch();
                        read_loopA3: system("cls");
                        Menu();
                        cout << "1. Quan li danh sach user\n2. Thong ke\n3. Dat san\n4.Quay lai\n5. Thoat\nNhap lua chon cua ban: "; char Achoice3 = getche(); 
                        switch (Achoice3 - '0')
                        {
                            case 1:
                            {   system("cls");
                                TitleUser();
                                U.hienDS();
                                Menu();
                                cout << "1. Them user\n2. Xoa user\n3. Sua user\n4.Quay lai\n5. Thoat\nNhap lua chon cua ban: "; char Achoice4 = getche(); 
                                switch (Achoice4 - '0')
                                {
                                case 1:
                                break;
                                case 2:
                                break;
                                case 3:
                                break;
                                case 4: goto read_loopA3;
                                case 5:
                                return 0;
                                default:
                                    break;
                                }
                            }
                            break;
                            case 2:
                            break;
                            case 3:
                            break;
                            case 4: goto read_loopA2;
                            break;
                            case 5:
                            return 0;
                            default:
                            break;
                        }
                        // Thực hiện công việc    
                        }
                        else 
                        {
                            cout << "\n<<< Dang nhap that bai. Enter de dang nhap lai! >>>" << endl;
                            delay = getche();
                            goto read_loop_autA;
                        }
                }
                break;
                case 3: goto read_loopA2;
                case 4: break;
            }
        break;  //case 1

        case 2: 
            read_loopU2:	system("cls");
            Menu();
			cout << "1. Ban muon dang ky tai khoan\n2. Dang nhap\n3. Quay lai\n4. Thoat\nMoi nhap lua chon cua ban:";
            char Uchoice2;
			Uchoice2=getche();	system("cls");	
			switch (Uchoice2-'0')
			{
                case 1: 
                    U.add(FUser); 
                    break;
                case 2: 
                {
                    read_loop_autU: system("cls");
                    cout << "Ten dang nhap (viet lien, khong dau): "; cin >> username; 
                    cout << "<<<<<Ban co muon an mat khau (y/n)>>>>>>>: "; char ynU1 = getche();
                    if (ynU1 == 'y' ) { cout << "\nMat khau (viet lien, khong dau): ";  hidePassword(password);}
                    else if (ynU1 == 'n') { cout << "\nMat khau (viet lien, khong dau): ";  cin >> password;}
                    else {
                        cout << "\nLua chon khong hop le. Enter de quay lai!";
                        delay = getch(); goto read_loop_autU;
                    }
                    
                    if (authenticateUser(username,password, FUser))
                    {
                        cout << "\n<<< Dang nhap thanh cong >>>" << endl;
                        
                        // Thực hiện công việc
                    }
                    else 
                    {
                        cout << "\n<<< Dang nhap that bai. Enter de dang nhap lai! >>>" << endl;
                        delay = getche();
                        goto read_loop_autU;
                    }
                }
                break;
                case 3: goto read_loopU2;
                case 4: break;
            }
        break; //case 2:
        case 3: break;
    }
    system("pause");
    return 0;
}
