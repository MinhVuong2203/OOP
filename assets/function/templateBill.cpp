#include <iostream>
#include <iomanip>
#include <fstream>
#include "Person.h"
#include "TimeDay.h"
#include "Activity.h"
#include "templateBill.h"
using namespace std;
 
void templateBill(Acti *x,string hoten_admin, Day current_Day, Time current_Time, double &into_money, const int GiaThuong, const int GiaVang)
{
    int color = 4;
    
    setColor(color); 
    cout << "<-------------------------------- SAN CAU LONG CIB --------------------------->\n"; setColor(7);
    cout << "|" << right << setw(79) << "|\n";
    cout << "| Dia chi: 450 - 451, duong Le Van Viet,"; cout << right << setw(40) << "|\n"; 
    cout << "|" << right << setw(40) << "phuong Tang Nhon Phu A, Quan 9" << setw(39) << "|\n";
    cout << "| Dien thoai dat san: 0818214849" << right << setw(48) << "|\n";
    cout << "| Dien thoai phan anh: 0818214849" << right << setw(47) << "|\n";    
    cout << "|" << right << setw(79) << "|\n"; 
    cout << "|"; setColor(color); cout << "\tSan "<< x->getID(); setColor(7); cout << "\t\t\t   " << "PHIEU TINH TIEN" << right << setw(30) << "|\n";
    cout << "|" << right << setw(79) << "|\n";
    cout << "|\tNgay in hoa don: "; current_Day.xuatDay(); cout << " "; current_Time.xuatTime(); cout << "PM" << right << setw(34) << "|\n";
    cout << "|\tNhan vien in hoa don: " << left << setw(48) << hoten_admin << "|\n";
    cout << "|\tKhach hang: " << left << setw(58) <<  x->getHoten() << "|\n";    
    cout << "|\tGio vao: "; x->getGioVao().xuatTime(); cout << "\t\t\t\t"; cout << "Gio ra: "; x->getGioRa().xuatTime(); cout << right<<setw(8) <<"|\n";
    cout << "|" << right << setw(79) << "|\n";
    TitleBill();
    float SLThuong, SLVang;
    {
        float money_item = 0;
        if (timeVang - x->getGioRa() >= 0)  //TH rơi hoàn toàn vào khung giờ thường 
        {
            SLThuong = x->getGioRa() - x->getGioVao();
            SLVang = 0;
        }
        else
        {  //(Vàng hoàn toàn hoặc phân nữa)
            if (x->getGioVao() - timeVang >= 0)  //TH rơi vào khung giờ vàng hoàn toàn
            {
                SLThuong = 0;
                SLVang = x->getGioRa() - x->getGioVao();
            }
            else
            {  //TH rơi vào cả 2 khung giờ
                SLThuong = timeVang - x->getGioVao();
                SLVang = x->getGioRa() - timeVang;
            }
        }

        cout << left << "|\t" << setw(10) << "Thuong" << right 
            << setw(14) << GiaThuong
            << setw(14) << SLThuong;
            money_item = GiaThuong * SLThuong;
        cout << setw(23) << money_item << right << setw(11) << "|\n";
        into_money += money_item;

        cout << left << "|\t" << setw(10) << "Vang" << right 
            << setw(14) << GiaVang
            << setw(14) << SLVang;
            money_item = GiaVang * SLVang;
        cout << setw(23) << money_item << right << setw(11) << "|\n";
        into_money += money_item;
        cout << "|" << right << setw(53) << "TONG:"; setColor(2); cout <<right << setw(15) << into_money;  setColor(7); cout << right << setw(11) << "|\n";
        cout << "|" << right << setw(79) << "|\n"; 
        cout << "+-----------------------------------------------------------------------------+\n\n";
        return;
    }
}

void templateBillFile(Acti *x,string hoten_admin, Day current_Day, Time current_Time, double &into_money, const int GiaThuong, const int GiaVang, string namefile)
{
    ofstream file(namefile);
    if (!file.is_open()) { 
        cout << "Khong mo duoc file." << endl; 
        return; 
    }
    int color = 4;
    setColor(color); 
    file << "<-------------------------------- SAN CAU LONG CIB --------------------------->\n"; setColor(7);
    file << "|" << right << setw(79) << "|\n";
    file << "| Dia chi: 450 - 451, duong Le Van Viet,"; file << right << setw(40) << "|\n"; 
    file << "|" << right << setw(40) << "phuong Tang Nhon Phu A, Quan 9" << setw(39) << "|\n";
    file << "| Dien thoai dat san: 0818214849" << right << setw(48) << "|\n";
    file << "| Dien thoai phan anh: 0818214849" << right << setw(47) << "|\n";    
    file << "|" << right << setw(79) << "|\n"; 
    file << "|"; setColor(color); file << "\t\tSan "<< x->getID(); setColor(7); file << "\t\t\t   " << "PHIEU TINH TIEN" << right << setw(38) << "|\n";
    file << "|" << right << setw(79) << "|\n";
    file << "|\t\tNgay in hoa don: "; current_Day.xuatDayFile(file); file << " "; current_Time.xuatTimeFile(file); file << "PM" << right << setw(34) << "|\n";
    file << "|\t\tNhan vien in hoa don: " << left << setw(48) << hoten_admin << "|\n";
    file << "|\t\tKhach hang: " << left << setw(58) <<  x->getHoten() << "|\n";    
    file << "|\t\tGio vao: "; x->getGioVao().xuatTimeFile(file); file << "\t\t\t\t\t\t"; file << "Gio ra: "; x->getGioRa().xuatTimeFile(file); file << right<<setw(16) <<"|\n";
    file << "|" << right << setw(79) << "|\n";
    TitleBillFile(file);
    float SLThuong, SLVang;
    {
        float money_item = 0;
        if (timeVang - x->getGioRa() >= 0)  //TH rơi hoàn toàn vào khung giờ thường 
        {
            SLThuong = x->getGioRa() - x->getGioVao();
            SLVang = 0;
        }
        else
        {  //(Vàng hoàn toàn hoặc phân nữa)
            if (x->getGioVao() - timeVang >= 0)  //TH rơi vào khung giờ vàng hoàn toàn
            {
                SLThuong = 0;
                SLVang = x->getGioRa() - x->getGioVao();
            }
            else
            {  //TH rơi vào cả 2 khung giờ
                SLThuong = timeVang - x->getGioVao();
                SLVang = x->getGioRa() - timeVang;
            }
        }

        file << left << "|\t\t" << setw(10) << "Thuong" << right 
            << setw(14) << GiaThuong
            << setw(14) << SLThuong;
            money_item = GiaThuong * SLThuong;
        file << setw(23) << money_item << right << setw(11) << "|\n";
        into_money += money_item;

        file << left << "|\t\t" << setw(10) << "Vang" << right 
            << setw(14) << GiaVang
            << setw(14) << SLVang;
            money_item = GiaVang * SLVang;
        file << setw(23) << money_item << right << setw(11) << "|\n";
        into_money += money_item;
        file << "|" << right << setw(53) << "TONG:"; setColor(2); file <<right << setw(15) << into_money;  setColor(7); file << right << setw(11) << "|\n";
        file << "|" << right << setw(79) << "|\n"; 
        file << "+-----------------------------------------------------------------------------+\n\n";
        file.close();
        return;
    }
    
}