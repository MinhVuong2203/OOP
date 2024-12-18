#include <time.h>
#include <ctime>
#include <fstream>
#include <cmath>
#include <sstream>
#include "check.h"
#include "TimeDay.h"
time_t presentTime;

// Lấy ngày hien tai
Day getday()
{
	Day day;
	struct tm *tm_info;
	time(&presentTime); 
	tm_info = localtime(&presentTime); 
	day.ngay =  tm_info->tm_mday; day.thang = tm_info->tm_mon+1; day.nam = tm_info->tm_year+1900;
	return day;
}

int getYear(){
    time_t t = std::time(nullptr);
    tm* local_time = std::localtime(&t);
    int current_year = 1900 + local_time->tm_year;
    return current_year;
}

// Lấy giờ hiện tại
Time getTime()
{
	Time time;

	time_t t = std::time(nullptr);
	tm* now = localtime(&t);
	time.gio = now->tm_hour; time.phut = now->tm_min; time.giay = now->tm_sec;

	return time;
}

Time::Time() : gio(0), phut(0), giay(0) {}
Time::Time(int g, int p, int s) : gio(g), phut(p), giay(s) {}

bool Time::checkTime() const {
    if (giay < 0 || gio < 0 || phut < 0) return false;
    if (giay >= 60 || phut >= 60 || gio >= 24) return false;
    return true;
}
void Time::nhapTime() {
    string input;
    while (true) {
        getline(cin, input);
        stringstream ss(input);
        char sep1, sep2;
        if (ss >> gio >> sep1 >> phut >> sep2 >> giay && sep1 == ':' && sep2 == ':' && checkTime()) {
            break; // Thoát vòng lặp nếu nhập đúng định dạng và thời gian hợp lệ
        } else {
            cout << "Thoi gian khong hop le! Vui long nhap lai." << endl;
        }
    }
}

void Time::xuatTime() const {
    if (gio < 10) cout << "0"; cout << gio << ":";
    if (phut < 10) cout << "0"; cout << phut << ":";
    if (giay < 10) cout << "0"; cout << giay;
}
void Time::xuatTimeFile(ofstream &file) const {
    if (file.is_open()){
        if (gio < 10) file << "0"; file << gio << ":";
        if (phut < 10) file << "0"; file << phut << ":";
        if (giay < 10) file << "0"; file << giay;
    }
}
bool Time::operator==(const Time& b) const {
    return gio == b.gio && phut == b.phut && giay == b.giay;
}
bool Time::operator!=(const Time& b) const {
    return !(*this == b);
}
bool Time::operator<(const Time& b) const {
    if (gio != b.gio) return gio < b.gio;
    if (phut != b.phut) return phut < b.phut;
    return giay < b.giay;
}
bool Time::operator>(const Time& b) const {
    return b < *this;
}
bool Time::operator<=(const Time& b) const {
    return !(b < *this);
}
bool Time::operator>=(const Time& b) const {
    return !(*this < b);
}
double Time::operator-(const Time& b) const {
    double timeDifference = ((gio - b.gio) * 3600 + (phut - b.phut) * 60 + (giay - b.giay)) / 3600.0;
    return round(timeDifference * 1000) / 1000; // Làm tròn đến 3 chữ số thập phân
}

//Xử lí day
Day::Day() : ngay(0), thang(0), nam(0) {}
Day::Day(int d, int m, int y) : ngay(d), thang(m), nam(y) {}
bool Day::checkDay() const {
    int maxDay = 0;
    if (nam < 1901) return false;
    if (thang < 1 || thang > 12) return false;
    if (ngay < 1 || ngay > 31) return false;
    switch (thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxDay = 31; break;
        case 4: case 6: case 9: case 11:
            maxDay = 30; break;
        case 2:
            if (nam % 4 == 0)
                maxDay = 29;
            else
                maxDay = 28; break;
    }
    return ngay <= maxDay;
}
#include <ctime>

bool Day::checkDayPlay() const {
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    int currentYear = currentTime->tm_year + 1900; 
    int currentMonth = currentTime->tm_mon + 1;  
    int currentDay = currentTime->tm_mday;       
    int maxYear = currentYear + 1;
    int maxMonth = currentMonth;
    int maxDay = currentDay;
    if (nam > maxYear || (nam == maxYear && (thang > maxMonth || (thang == maxMonth && ngay > maxDay)))) 
        return false;
    if (thang < 1 || thang > 12) return false;
    if (ngay < 1 || ngay > 31) return false;
    int maxDaysInMonth = 0;
    switch (thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxDaysInMonth = 31; break;
        case 4: case 6: case 9: case 11:
            maxDaysInMonth = 30; break;
        case 2:
            if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0))
                maxDaysInMonth = 29;
            else
                maxDaysInMonth = 28; 
            break;
    }

    return ngay <= maxDaysInMonth;
}

void Day::nhapDay() {
    string input;
    while (true) {
        getline(cin, input);
        stringstream ss(input);
        char sep1, sep2;
        if (ss >> ngay >> sep1 >> thang >> sep2 >> nam && sep1 == '/' && sep2 == '/' && checkDay() && (getYear() - nam) > 6) {
          break; 
        } else {
            cout << "Ngay thang nam khong hop le!\nVui long nhap lai: "; 
        }
    }
}


void Day::nhapDayCur() {
    string input;
    while (true) {
        getline(cin, input);
        stringstream ss(input);
        char sep1, sep2;
        if (ss >> ngay >> sep1 >> thang >> sep2 >> nam && sep1 == '/' && sep2 == '/' && checkDay()) {
          break; 
        } else {
            cout << "Ngay thang nam khong hop le!\nVui long nhap lai: "; 
        }
    }
}

void Day::xuatDay() const {
    if (ngay < 10) cout << "0"; cout << ngay << "/";
    if (thang < 10) cout<< "0"; cout << thang << "/";
    cout << nam;
}

void Day::xuatDayFile(ofstream &file) const {
    if (file.is_open()){
        if (ngay < 10) file << "0"; file << ngay << "/";
        if (thang < 10) file << "0"; file << thang << "/";
        file << nam;
    }
}
bool Day::operator==(const Day& b) const {
    return ngay == b.ngay && thang == b.thang && nam == b.nam;
}
bool Day::operator!=(const Day& b) const {
    return !(*this == b);
}
bool Day::operator<(const Day& b) const {
    if (nam != b.nam) return nam < b.nam;
    if (thang != b.thang) return thang < b.thang;
    return ngay < b.ngay;
}
bool Day::operator>(const Day& b) const {
    return b < *this;
}
bool Day::operator<=(const Day& b) const {
    return !(b < *this);
}
bool Day::operator>=(const Day& b) const {
    return !(*this < b);
}
int Day::operator-(const Day& b) const {
    int luongthang = 0, t = (thang < b.thang) ? thang + 12 : thang;
    for (int i = b.thang; i < t; i++) {
        int j = (i > 12) ? i - 12 : i;
        switch (j) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                luongthang++; break;
            case 4: case 6: case 9: case 11:
                break;
            case 2:
                if (nam % 4 == 0)
                    luongthang--;
                else
                    luongthang -= 2;
                break;
        }
    }
    return (nam - b.nam) * 365 + (thang - b.thang) * 30 + luongthang + (ngay - b.ngay);
}

