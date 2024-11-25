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
    system("cls");  

    for (int i = 0; i < prizeCount; ++i) {
        if (i == activeIndex) {
            setColor(228);  
        } else {
            setColor(7);  
        }
        cout << "[" << setw(13) << prizes[i] << "]\t";
        if ((i + 1) % 4 == 0) {
            cout << endl << endl;
        }
    }
    cout << endl;
    setColor(7); 
}

void spinWheel(const string prizes[], int prizeCount) {
    srand(time(0));
    int totalSpins = 20 + rand() % 20;  
    int activeIndex = 0; 
    for (int i = 0; i < totalSpins; ++i) {
        displayBoard(prizes, prizeCount, activeIndex);
        activeIndex = (activeIndex + 1) % prizeCount;
        Sleep(100 + i * i - i * 10); 
    }

    displayBoard(prizes, prizeCount, activeIndex);
    setColor(10);  
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
    int prizeCount = sizeof(prizes) / sizeof(prizes[0]); 
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
            cout << "\nCam on vi da tham gia!" << endl;
        
}

