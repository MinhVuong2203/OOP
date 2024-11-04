#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>
#include <windows.h>
#include "Title.h"
#include "VQMM.h"
using namespace std;

void displayBoard(const string prizes[], int prizeCount, int activeIndex) 
{
    system("cls");  // Xoa man hinh (tren Windows)

    for (int i = 0; i < prizeCount; ++i) {
        // Neu o hien tai dang "quay", doi mau cua o do
        if (i == activeIndex) {
            setColor(3);  
        } else {
            setColor(7);   // Mau trang cho cac o con lai
        }

        // Hien thi phan thuong tai o do, su dung setw() de can chinh
        cout << "[" << setw(13) << prizes[i] << "]\t";
        
        // Xuong dong sau moi 4 o de tao bang 3x4
        if ((i + 1) % 4 == 0) {
            cout << endl << endl;
        }
    }
    cout << endl;
    setColor(7);  // Tra lai mau trang sau khi in xong
}

void spinWheel(const string prizes[], int prizeCount) {
    int totalSpins = 20 + rand() % 20;  // So vong quay ngau nhien tu 10 den 20
    int activeIndex = 0;  // Chi so cua o dang quay

    for (int i = 0; i < totalSpins; ++i) {
        displayBoard(prizes, prizeCount, activeIndex);

        // Tang chi so len de quay sang o ke tiep
        activeIndex = (activeIndex + 1) % prizeCount;

        // Tam dung mot chut de tao hieu ung quay
        Sleep(100 + i * i - i * 5);  // Tang do tre de chay cham lai truoc khi dung
    }

    // Hien thi ket qua trung cuoi cung
    displayBoard(prizes, prizeCount, activeIndex);
    setColor(10);  // Mau xanh la cho ket qua cuoi cung
    cout << "Chuc mung! Ban da trung: " << prizes[activeIndex] << "!" << endl;
    setColor(7);
}

void VQMM()
{
    srand(static_cast<unsigned int>(time(0)));
    string prizes[] = 
    {
        "may man", "3 quan can", "1 doi dep lao", "1 thung tiger",
        "2 tiger" , "may man", "cau VinaStart", "may man",
        "may man", "1 ao Yonex", "1 loc sting", "vot Yonex LCW"
    };
    int prizeCount = sizeof(prizes) / sizeof(prizes[0]); // Kich thuoc mang
    char choice;
        setColor(11);
        cout << "----- [Vong quay may man] -----" << endl;
        setColor(7);
        cout << "Nhan 'q' de quay";
        choice = getch();
        if (choice == 'q' || choice == 'Q') 
        {
            spinWheel(prizes, prizeCount);
        } 
        else 
            cout << "Cam on vi da tham gia!" << endl;
        
}

