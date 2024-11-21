#ifndef TITLE_H
#define TITLE_H
#include <iostream>
#include <fstream>
using namespace std;
void setColor(int color); 

void banner();

void Menu();

void TitleAdmin();

void TitleUser() ;

void TitleActi(); 

void icon_choice();

void icon_del();

void icon_confirm();

void icon_sort();

void icon_search();

void TitleBill();

void TitleBillFile(ofstream &file);

void icon_exit();

void icon_return();

void icon_cost();

void icon_user();

void icon_admin();

void icon_login();

void icon_Res();

void icon_Statistical();

void icon_Order();
void icon_delOrder();

void icon_History();

void icon_cancel();

bool CapCha();

void loading(int l, int x, int y, string text);
#endif






