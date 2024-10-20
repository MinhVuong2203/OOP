#pragma once

using namespace std;
 

void templateBill(Acti *x, Day current_Day, Time current_Time, double into_money, const int GiaThuong, const int GiaVang)
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
    cout << "|\tNgay in hoa don: "; XuatDay(current_Day); cout << " "; XuatTime(current_Time); cout << "PM" << right << setw(34) << "|\n";
    cout << "|\tKhach hang: " << left << setw(58) <<  x->getHoten() << "|\n";    
    cout << "|\tGio vao: "; XuatTime(x->getGioVao()); cout << "\t\t\t\t"; cout << "Gio ra: "; XuatTime(x->getGioRa()); cout << right<<setw(8) <<"|\n";
    cout << "|" << right << setw(79) << "|\n";
    TitleBill();
    float SL = distanceTime(x->getGioRa(), x->getGioVao());  
    if (compareTime(x->getGioRa(),timeVang) == -1) 
    {
        cout << left << "|\t" << setw(10) << "Thuong" << right 
            << setw(14) << GiaThuong
            << setw(14) << SL;
            into_money = GiaThuong * SL;
        cout << setw(23) << into_money << right << setw(11) << "|\n"; 
        cout << "|" << right << setw(53) << "TONG:"; setColor(2); cout << right << setw(15) << into_money; setColor(7);  cout << right << setw(11) << "|\n";
        cout << "|" << right << setw(79) << "|\n";
        cout << "+------------------------------------------------------------------------------+\n\n";
        return;
    }
    if (compareTime(x->getGioVao(),timeVang) == 1)
    {
        cout << left << "|\t" << setw(10) << "Vang"  << right 
            << setw(14) << GiaVang
            << setw(14) << SL;  
            into_money = GiaVang * SL;
        cout<< setw(23) << into_money << right << setw(11) << "|\n";
        cout << "|" << right << setw(53) << "TONG:"; setColor(2); cout << right << setw(15) << into_money; setColor(7);  cout << right << setw(11) << "|\n";
        cout << "|" << right << setw(79) << "|\n";
        cout << "+-----------------------------------------------------------------------------+\n\n";
        return;
    }
    else
    {
        float money_item = 0;
        SL = distanceTime(timeVang,x->getGioVao());  
        cout << left << "|\t" << setw(10) << "Thuong" << right 
            << setw(14) << GiaThuong
            << setw(14) << SL;
            money_item = GiaThuong * SL;
        cout << setw(23) << money_item << right << setw(11) << "|\n";
        into_money += money_item;
        SL = distanceTime(x->getGioRa(),timeVang);  
        cout << left << "|\t" << setw(10) << "Vang" << right 
            << setw(14) << GiaVang
            << setw(14) << SL;
            money_item = GiaVang * SL;
        cout << setw(23) << money_item << right << setw(11) << "|\n";
        into_money += money_item;
        cout << "|" << right << setw(53) << "TONG:"; setColor(2); cout <<right << setw(15) << into_money;  setColor(7); cout << right << setw(11) << "|\n";
        cout << "|" << right << setw(79) << "|\n"; 
        cout << "+-----------------------------------------------------------------------------+\n\n";
        return;
    }
}