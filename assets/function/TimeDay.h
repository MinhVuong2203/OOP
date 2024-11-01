#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <cmath>
using namespace std;

class Time {
public:
    int gio, phut, giay;

    // Constructors
    Time();
    Time(int g, int p, int s);

    // Methods
    bool checkTime() const;
    void nhapTime();
    void xuatTime() const;

    // Operator overloads
    bool operator==(const Time& b) const;
    bool operator!=(const Time& b) const;
    bool operator<(const Time& b) const;
    bool operator>(const Time& b) const;
    bool operator<=(const Time& b) const;
    bool operator>=(const Time& b) const;
    double operator-(const Time& b) const;
};

class Day {
public:
    int ngay, thang, nam;

    // Constructors
    Day();
    Day(int d, int m, int y);

    // Methods
    bool checkDay() const;
    void nhapDay();
    void xuatDay() const;

    // Operator overloads
    bool operator==(const Day& b) const;
    bool operator!=(const Day& b) const;
    bool operator<(const Day& b) const;
    bool operator>(const Day& b) const;
    bool operator<=(const Day& b) const;
    bool operator>=(const Day& b) const;
    int operator-(const Day& b) const;
};


// Lấy ngày hien tai
Day getday();


// Lấy giờ hiện tại
Time getTime();

#endif