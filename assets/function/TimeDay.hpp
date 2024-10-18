#pragma once
#include <time.h>
#include <ctime>
#include <cmath>
time_t presentTime;
using namespace std;

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

void XuatTime(Time x)
{
	if (x.gio < 10) cout << "0";  cout << x.gio << ":";
    if (x.phut < 10) cout << "0";  cout << x.phut << ":";
	if (x.giay < 10) cout << "0"; cout << x.giay;
}

int compareTime(Time a, Time b)  // a>b return 1, a<b return -1  a=b return 0
{
    if (a.gio > b.gio) return 1;
    if (a.gio < b.gio) return -1;
    if (a.phut > b.phut) return 1;
    if (a.phut < b.phut) return -1;
    if (a.giay > b.giay) return 1;
    if (a.giay < b.giay) return -1;
    return 0;
}
float distanceTime(Time a, Time b)  // Hàm tính khoảng thời gian trả về đơn vị giờ ( a > b)
{
    float timeDifference = ((a.gio - b.gio) * 3600 + (a.phut - b.phut) * 60 + (a.giay - b.giay)) / 3600.0;
    return std::round(timeDifference * 1000) / 1000; // Làm tròn đến 3 chữ số thập phân
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
void XuatDay(Day x)
{
    if (x.ngay < 10) cout << "0"; cout << x.ngay << "/";
	if (x.thang < 10) cout << "0"; cout << x.thang << "/";
	if (x.nam < 10) cout << "0"; cout << x.nam;
}
int compareDay(Day a, Day b) //hàm so sánh ngày nếu ngày a > b thì trả về 1 ngược lại trả về -1, nếu bằng nhau trả về 0
{
    if (a.nam > b.nam) return 1;
    if (a.nam < b.nam) return -1;
    if (a.thang > b.thang) return 1;
    if (a.thang < b.thang) return -1;
    if (a.ngay > b.ngay) return 1;
    if (a.ngay < b.ngay) return -1;
    return 0;
}

int distanceDay(Day a, Day b)  //Hàm tính khoảng cách giữa 2 ngày
{
	int t,luongthang=0;
	t = (a.thang < b.thang)?  a.thang+12:a.thang;
	for (int i=b.thang; i<t; i++)
	{
		int j=i;
		if (i>12) j=i-12;
			switch(j)
			{
			case 1: case 3: case 5: case 7:  case 8: case 10: case 12: luongthang++; break;
			case 4: case 6: case 9: case 11: break;
			case 2: if (a.nam%4 == 0) 
					luongthang--;
				else
					luongthang = luongthang - 2;  break;
			}		
	}
	return (a.nam - b.nam)*365 + (a.thang-b.thang)*30+luongthang +(a.ngay - b.ngay);
}


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
