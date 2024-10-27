#pragma once
#include <vector>
using namespace std;

// class Activity để lưu trữ các hoạt động của user
class Acti : public Person {
private:
    Day NgayDen;
    Time GioVao, GioRa;
    int id;
public:
    Acti() {}
    Acti(string HoTen, Day NgaySinh, string SDT, Day ngayden, Time giovao, Time giora, int ID) : Person(HoTen, NgaySinh, SDT), NgayDen(ngayden), GioVao(giovao), GioRa(giora), id(ID){}
    Day getNgayDen() {return NgayDen;}
    Time getGioVao() {return GioVao;}
    Time getGioRa() {return GioRa;}
    int getID() {return id;}
    
    void hienThiThongTin() override {
        Person::hienThiThongTin();
        cout<< "| " << setw(10) << (to_string(NgayDen.ngay) + "/" + to_string(NgayDen.thang) + "/" + to_string(NgayDen.nam))
        << "| " << setw(10) << (to_string(GioVao.gio) + ":" + to_string(GioVao.phut) + ":" + to_string(GioVao.giay))
        << "| " << setw(10) << (to_string(GioRa.gio) + ":" + to_string(GioRa.phut) + ":" + to_string(GioRa.giay))
        << "| " << id
        << " |" << endl
        << "+-----+--------------------+---------------+---------------+---------------+---------------+" << endl;
    }
    void calculate(const int GiaThuong, const int GiaVang, Day start_day, Day end_day);
};

void templateBill(Acti *x, Day current_Day, Time current_Time, double into_money, const int GiaThuong, const int GiaVang);

class QLAC
{
private:
    Person *AC[100];
    int n;

public:
    QLAC(string filename);
    ~QLAC();
    void add(string nameFile, string HoTen, Day NgaySinh, string SDT);
    void hienDS() 
	{
        for (int i = 0; i < n; i++) 
		{
            cout << left << "| "; setColor(12); cout << setw(4) << i+1; setColor(7);
            AC[i]->hienThiThongTin();
        }
    }
    void History(string Hoten);
    void History(string Hoten, Day ngay);
    void priBill(Day ngayden);
    void calculate(Day start_day, Day end_day);
    void update(string nameFile, int ch, string oldName,string newName, Day newBD, string newSDT);
};
QLAC::QLAC(string filename)
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
        string hoten, ngaysinh_str, sdt, ngayden_str, giovao_str, giora_str, id_str;
        Day ngaysinh, ngayden;
        Time giovao, giora;
        int id;
        istringstream ss(line);
        getline(ss, hoten, ',');
        getline(ss, ngaysinh_str, ',');
        getline(ss, sdt, ',');
        getline(ss, ngayden_str, ',');
        getline(ss, giovao_str, ',');
        getline(ss, giora_str, ',');
        getline(ss, id_str, ',');
        
        sscanf(ngaysinh_str.c_str(), "%d/%d/%d", &ngaysinh.ngay, &ngaysinh.thang, &ngaysinh.nam);
        sscanf(ngayden_str.c_str(), "%d/%d/%d", &ngayden.ngay, &ngayden.thang, &ngayden.nam);
        sscanf(giovao_str.c_str(), "%d:%d:%d", &giovao.gio, &giovao.phut, &giovao.giay);
        sscanf(giora_str.c_str(), "%d:%d:%d", &giora.gio, &giora.phut, &giora.giay);
        sscanf(id_str.c_str(), "%d", &id);
        hoten.erase(0, hoten.find_first_not_of(" "));
        sdt.erase(0, sdt.find_first_not_of(" "));
        if (hoten != "")
        {

        Person *p = new Acti(hoten, ngaysinh, sdt, ngayden, giovao, giora, id);
        AC[n++] = p;

        }
    }
}
QLAC::~QLAC() {
    for (int i = 0; i < n; i++) {
        delete AC[i]; // Giải phóng từng đối tượng
    }
}
void QLAC::add(string nameFile, string HoTen, Day NgaySinh, string SDT) 
{
    fstream file(nameFile, ios::app);
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }
    Day NgayDen;
    Time GioVao, GioRa;
    int id;
    int San[SL] = {0}; // Tạo ra một mảng sân để lưu id và trạng thái sân thứ i có id là i+1, giá trị s[i] = 0 (sân trống), s[i] = 1 (sân có người)

    cout << "Nhap ngay vao: ";NgayDen.nhapDay();
    cout << "Nhap gio vao: "; GioVao.nhapTime();
    cout << "Nhap gio ra: "; GioRa.nhapTime();

    for (int i = 0; i < n; i++) 
    {
        Acti *ActiPtr = dynamic_cast<Acti*>(AC[i]);  //chuyển đổi kiểu person sang acti
        if (ActiPtr != nullptr) 
        {
            if (ActiPtr->getNgayDen() == NgayDen)
            {
                if (ActiPtr->getGioVao() <= GioRa  && ActiPtr->getGioRa() >= GioRa)  //TH1
                    San[ActiPtr->getID()-1] = 1;
                if (ActiPtr->getGioVao() <= GioVao && ActiPtr->getGioRa() >= GioVao) //TH2  
                    San[ActiPtr->getID()-1] = 1;
                if (ActiPtr->getGioVao() >= GioVao && ActiPtr->getGioRa() <= GioRa) //TH3
                    San[ActiPtr->getID()-1] = 1;
                if (ActiPtr->getGioVao() <= GioVao && ActiPtr->getGioRa() >= GioRa) //TH4
                    San[ActiPtr->getID()-1] = 1;    
            }
        }
    }
    cout << "\nCac san con trong: ";
  for ( int i=0; i<SL; i++)
    {
        if (i%5==0) cout << endl << endl;
        (San[i])? setColor(12) : setColor(2); 
        cout << left <<  "| "; cout << setw(2) << i+1; cout<< " |  ";   
    }	
    setColor(7);    
    cout << "\nBan chon san: "; cin >> id;
    while (San[id-1])
    {
        cout << "San nay da co nguoi. Vui long chon lai: ";
        cin >> id;
    }
	Person *p = new Acti(HoTen, NgaySinh, SDT, NgayDen, GioVao, GioRa, id);
    AC[n++] = p;
    file <<HoTen <<","<<NgaySinh.ngay<<"/"<<NgaySinh.thang<<"/"<<NgaySinh.nam<<","<<SDT<<","<<NgayDen.ngay<<"/"<<NgayDen.thang<<"/"<<NgayDen.nam\
    <<","<<GioVao.gio<<":"<<GioVao.phut<<":"<<GioVao.giay<<","<<GioRa.gio<<":"<<GioRa.phut<<":"<<GioRa.giay<<"," << id << endl;
    cout << "Da dat san thanh cong!" << endl;
    file.close();
}
void QLAC::History(string Hoten)
{
    int k = 0;
    for (int i=0; i<n; i++)
    {
        if (AC[i]->getHoten() == Hoten)
        {
            cout << left << "| "; setColor(12); cout << setw(4) << ++k; setColor(7);
            AC[i]->hienThiThongTin();
        }
    }
}
void QLAC::History(string Hoten, Day ngay)
{
    int k = 0;
    for (int i=0; i<n; i++)
    {
        if (AC[i]->getHoten() == Hoten)
        {
            cout << left << "| "; setColor(12); cout << setw(4) << ++k; setColor(7);
            AC[i]->hienThiThongTin();
        }
    }
}

void QLAC::priBill(Day ngayden) 
{
    double into_money = 0;
    int k = 0, STT;
    cout << endl;
    vector<Acti*> actiList; // Tạo danh sách tạm để lưu các đối tượng cần in
    for (int i = n - 1; i >= 0; i--) 
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr && ActiPtr->getNgayDen() == ngayden) 
        {
            cout << left << "| "; setColor(12);cout << setw(4) << ++k; setColor(7);
            ActiPtr->hienThiThongTin();
            actiList.push_back(ActiPtr); // Thêm đối tượng vào danh sách tạm
        }
    }
    cout << endl;
    icon_Order();    cout << "Nhap STT can in hoa don: ";    
    cin >> STT; cout << endl;
    if (STT <= 0 || STT > k) {
        cout << "STT khong hop le!" << endl;
        return;
    }

    k = 0;
    for (int i = n - 1; i >= 0; i--) 
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr && ActiPtr->getNgayDen() == ngayden)  
        {
            k++;
            if (k == STT) 
            {
                templateBill(ActiPtr, getday(), getTime(), into_money, GiaThuong, GiaVang);
                return;
            }
        }
    }
}

void QLAC::calculate(Day start_day, Day end_day)
{
    double Tong = 0;
    for (int i=0; i<n; i++)
    {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr->getNgayDen() >= start_day && ActiPtr->getNgayDen() <= end_day)
        {
            ActiPtr->hienThiThongTin();
            if (ActiPtr->getGioVao() > timeVang) /*Giờ vào nằm ở giờ vip*/
            Tong += (ActiPtr->getGioRa() - ActiPtr->getGioVao())*GiaVang;
            else if (ActiPtr->getGioRa() < timeVang) //Giờ ra và ra nằm ở giờ thường
            Tong += (ActiPtr->getGioRa() - ActiPtr->getGioVao())*GiaThuong;
            else
            Tong += (ActiPtr->getGioRa() - timeVang)*GiaThuong + (timeVang - ActiPtr->getGioVao())*GiaVang;
        }
    }
    cout << "Doanh thu tu ngay "; start_day.xuatDay() ; cout << " den "; end_day.xuatDay(); cout << " la: "; 
    cout << fixed << setprecision(0) << Tong << endl;
}

void QLAC::update(string nameFile, int ch, string oldName,string newName, Day newBD, string newSDT){
    for (int i = 0; i < n; i++) {
        Acti *ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr->getHoten() == oldName) {
           if(ch==1){
            ActiPtr->setHoTen(newName);
           }
           else if(ch==2){
            ActiPtr->setNgaySinh(newBD);
           }
           else if(ch==3){
            ActiPtr->setSDT(newSDT);
           }
        }
    }
    ofstream file(nameFile);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << nameFile << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        Acti* ActiPtr = dynamic_cast<Acti*>(AC[i]);
        if (ActiPtr != nullptr) {
            file << ActiPtr->getHoten() << ","
                 << ActiPtr->getNgaySinh().ngay << "/" << ActiPtr->getNgaySinh().thang << "/" << ActiPtr->getNgaySinh().nam << ","
                 << ActiPtr->getSDT() << ","
                 << ActiPtr->getNgayDen().ngay << "/" << ActiPtr->getNgayDen().thang << "/" << ActiPtr->getNgayDen().nam << ","
                 << ActiPtr->getGioVao().gio << ":" << ActiPtr->getGioVao().phut << ":" << ActiPtr->getGioVao().giay << ","
                 << ActiPtr->getGioRa().gio << ":" << ActiPtr->getGioRa().phut << ":" << ActiPtr->getGioRa().giay << ","
                 << ActiPtr->getID() << endl;
        }
    }

    file.close();
}