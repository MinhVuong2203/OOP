#pragma once

using namespace std;
Time timeVang = {16,0,0};   //Khai báo để sử dụng cho việc in bill. từ 7h - 16h giá 50000đ/h, từ 16h - 22h giá 110000đ/h
// void calculate()

void templateBill(Acti *x, Day current_Day, Time current_Time, double into_money, const int GiaThuong, const int GiaVang)
{
    int color = 4;
    
    setColor(color); 
    cout << "<-------------------------------- SAN CAU LONG CIB --------------------------->\n"; setColor(7);
    cout << "| Dia chi: 450 - 451, duong Le Van Viet,\n|\tphuong Tang Nhon Phu A, Quan 9\n";
    cout << "| Dien thoai dat san: 0818214849\n";
    cout << "| Dien thoai phan anh: 0818214849\n|\n|"; setColor(color);
    cout << "\tSan " << x->getID(); setColor(7); cout << "\t\t\t   " << "PHIEU TINH TIEN\n|\n";
    cout << "|\tNgay in hoa don: "; XuatDay(current_Day); cout << " "; XuatTime(current_Time); cout << "PM" << endl;
    cout << "|\tKhach hang: " << x->getHoten();
    cout << "\n|\tGio vao: "; XuatTime(x->getGioVao()); cout << "\t\t\t\t"; cout << "Gio ra: "; XuatTime(x->getGioRa());
    cout << endl << endl;
    TitleBill();
    float SL = distanceTime(x->getGioRa(), x->getGioVao());  
    if (compareTime(x->getGioRa(),timeVang) == -1) 
    {
        cout << left << "\t" << setw(14) << "Thuong" 
            << setw(10) << GiaThuong
            << setw(10) << SL;
            into_money = GiaThuong * SL;
        cout << setw(10) << into_money << endl;
        return;
    }
    if (compareTime(x->getGioVao(),timeVang) == 1)
    {
        cout << left << "\t" << setw(14) << "Vang" 
            << setw(10) << GiaVang
            << setw(10) << SL;  
            into_money = GiaThuong * SL;
        cout<< setw(10) << into_money << endl;
        return;
    }
    else
    {
        float money_item = 0;
        SL = distanceTime(timeVang,x->getGioVao());  
        cout << left << "\t" << setw(14) << "Thuong" 
            << setw(10) << GiaThuong
            << setw(10) << SL;
            money_item = GiaThuong * SL;
        cout << setw(10) << money_item << endl;
        into_money += money_item;
        SL = distanceTime(x->getGioRa(),timeVang);  
        cout << left << "\t" << setw(14) << "Vang" 
            << setw(10) << GiaVang
            << setw(10) << SL;
            money_item = GiaVang * SL;
        cout << setw(10) << money_item << endl;
        into_money += money_item;
        cout << left << setw(26) << "Thanh tien: "; setColor(2); cout << setw(9) << into_money << endl;
        return;
    }

    cout << "\n------------------------------------------------------------------------------\n\n";
}