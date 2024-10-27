#pragma once
#include <time.h>
#include <ctime>
#include <cmath>
#include "check.hpp"
time_t presentTime;
using namespace std;

// Xử lí Time
#include <iostream>
#include <cmath>
using namespace std;

class Time {
public:
    int gio, phut, giay;

    Time() : gio(0), phut(0), giay(0) {}
    Time(int g, int p, int s) : gio(g), phut(p), giay(s) {}

    bool checkTime() const {
        if (giay < 0 || gio < 0 || phut < 0) return false;
        if (giay >= 60 || phut >= 60 || gio >= 24) return false;
        return true;
    }

    void nhapTime() {
        scanf("%d:%d:%d", &gio, &phut, &giay);
        while (!checkTime()) {
            cout << "Thoi gian khong hop le! Vui long nhap lai: ";
            scanf("%d:%d:%d", &gio, &phut, &giay);
        }
    }

    void xuatTime() const {
        if (gio < 10) cout << "0"; cout << gio << ":";
        if (phut < 10) cout << "0"; cout << phut << ":";
        if (giay < 10) cout << "0"; cout << giay;
    }

    bool operator==(const Time& b) const {
        return gio == b.gio && phut == b.phut && giay == b.giay;
    }

    bool operator!=(const Time& b) const {
        return !(*this == b);
    }

    bool operator<(const Time& b) const {
        if (gio != b.gio) return gio < b.gio;
        if (phut != b.phut) return phut < b.phut;
        return giay < b.giay;
    }

    bool operator>(const Time& b) const {
        return b < *this;
    }

    bool operator<=(const Time& b) const {
        return !(b < *this);
    }

    bool operator>=(const Time& b) const {
        return !(*this < b);
    }

    // Toán tử trừ để tính khoảng cách thời gian
    float operator-(const Time& b) const {
        float timeDifference = ((gio - b.gio) * 3600 + (phut - b.phut) * 60 + (giay - b.giay)) / 3600.0;
        return round(timeDifference * 1000) / 1000; // Làm tròn đến 3 chữ số thập phân
    }
};

//Xử lí day
class Day {
public:
    int ngay, thang, nam;

    Day() : ngay(0), thang(0), nam(0) {}
    Day(int d, int m, int y) : ngay(d), thang(m), nam(y) {}

    bool checkDay() const {
        int maxDay = 0;
        if (nam < 1900) return false;
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

    void nhapDay() {
        scanf("%d/%d/%d", &ngay, &thang, &nam);
        while (!checkDay()) {
            cout << "Ngay thang nam khong hop le!\nVui long nhap lai: ";
            scanf("%d/%d/%d", &ngay, &thang, &nam);
        }
    }

    void xuatDay() const {
        if (ngay < 10) cout << "0"; cout << ngay << "/";
        if (thang < 10) cout << "0"; cout << thang << "/";
        cout << nam;
    }

    // Định nghĩa các operator so sánh
    bool operator==(const Day& b) const {
        return ngay == b.ngay && thang == b.thang && nam == b.nam;
    }

    bool operator!=(const Day& b) const {
        return !(*this == b);
    }

    bool operator<(const Day& b) const {
        if (nam != b.nam) return nam < b.nam;
        if (thang != b.thang) return thang < b.thang;
        return ngay < b.ngay;
    }

    bool operator>(const Day& b) const {
        return b < *this;
    }

    bool operator<=(const Day& b) const {
        return !(b < *this);
    }

    bool operator>=(const Day& b) const {
        return !(*this < b);
    }

    // Toán tử trừ để tính khoảng cách giữa hai ngày
    int operator-(const Day& b) const {
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
};

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

// Lấy giờ hiện tại
Time getTime()
{
	Time time;

	time_t t = std::time(nullptr);
	tm* now = localtime(&t);
	time.gio = now->tm_hour; time.phut = now->tm_min; time.giay = now->tm_sec;

	return time;
}
