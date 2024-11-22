#include <iostream>
#include <conio.h>
#include <windows.h>
#include "./assets/function/Title.h" 
#include "./assets/function/TimeDay.h"
#include "./assets/function/Person.h"
#include "./assets/function/Admin.h"
#include "./assets/function/User.h"
#include "./assets/function/Activity.h"
#include "./assets/function/authenticate.h"
#include "./assets/function/templateBill.h"
#include "./assets/function/VQMM.h"
using namespace std;

int main() 
{
    loading(50,48,11,"...LOADING...");
    //Khai báo file
    string FAdmin = "assets//Admin.txt";
    string FUser = "assets//User.txt";
    string FActivity = "assets//Activity.txt";
    
    QLAD AD(FAdmin);
    QLUS U(FUser);
    QLAC AC(FActivity);
    int San[SL], check = 5;
    string username, password;
    Day day;  Time time_cr;
    day = getday();
    time_cr = getTime();
    char delay;
    cout << "Hom nay: " << day.ngay << "/" << day.thang << "/" << day.nam << " ";
    // In ra giờ, phút, giây
    cout << time_cr.gio << ":" << time_cr.phut << ":" << time_cr.giay << "PM"<< endl;
    banner();
    read_loop1: 
    cout << "+===============================+" << endl;
    cout << "|                               |" << endl;
    cout << "|"; icon_admin(); cout << "<1> Nguoi quan ly         |" << endl;
    cout << "|"; icon_user(); cout << "<2> Nguoi dung            |" << endl;
    cout << "|"; icon_exit(); cout << "<3> Thoat                 |" << endl;
    cout << "|                               |" << endl;
    cout << "+===============================+" << endl;
    cout << "Moi nhap lua chon cua ban: ";
    char choice1 = getchar();	
    switch (choice1-'0') 
	{
        case 1:    
            read_loopA2:	
            Menu();
            cout << "|                                    |" << endl;
            cout << "|"; icon_Res(); cout << "<1> Ban muon dang ki tai khoan |" << endl;
            cout << "|"; icon_login(); cout << "<2> Dang nhap                  |" << endl;
            cout << "|"; icon_return(); cout << "<3> Quay lai                   |" << endl;
            cout << "|"; icon_exit(); cout << "<4> Thoat                      |" << endl;
            cout << "|                                    |" << endl;
            cout << "+====================================+" << endl;
            cout << "Moi nhap lua chon cua ban: ";
        	char Achoice2; check = 5;
			Achoice2=getchar();	system("cls");	
			switch (Achoice2-'0')
			{
                case 1: AD.add(FAdmin);     break;
                case 2: 
                {
                    read_loop_autA: system("cls");
                    if (check == 0 ) return 0;
                    icon_Order(); cout << "Ten dang nhap (SDT): "; cin >> username; cin.ignore();
                    cout << "<<<<<Ban co muon an mat khau (y/n)>>>>>>>: "; char ynA1 = getchar();
                    if (ynA1 == 'y' ) 
                    {   cout << endl;
                        icon_Order(); cout << "Mat khau (CCCD): ";  
                        hidePassword(password);
                    }
                    else if (ynA1 == 'n') 
                    {   cout << endl;
                        icon_Order(); cout << "Mat khau (CCCD): ";  
                        cin >> password;
                    }
                    else 
                    {
                        cout << "\nLua chon khong hop le. Enter de quay lai!";
                        delay = getche(); goto read_loop_autA;
                    }
                    loading(40,50,11, "[Dang dang nhap]");      
                    if (authenticateUser(username,password, FAdmin)) 
                    {
                        setColor(10);
                        cout << "\n:)) Dang nhap thanh cong :))" << endl; 
                        setColor(7);
                        Sleep(1000);  //Hàm dừng màn hình trong 0.5 giây
                        read_loopA3: system("cls"); //Xóa màn hình
                       
                        Menu();
                        cout << "|                                    |" << endl;
                        cout << "|"; icon_Res();    cout << "<1> Quan li danh sach user     |" << endl;
                        cout << "|"; icon_Res();    cout << "<2> Thong ke                   |" << endl;
                        cout << "|"; icon_Res();    cout << "<3> Dat san                    |" << endl;
                        cout << "|"; icon_Res();    cout << "<4> Quan li Admin              |" << endl;
                        cout << "|"; icon_Res();    cout << "<5> In hoa don                 |" << endl;
                        cout << "|"; icon_return(); cout << "<6> Quay lai                   |" << endl;
                        cout << "|"; icon_exit();   cout << "<7> Dang xuat                  |" << endl;
                        cout << "|                                    |" << endl;
                        cout << "+====================================+" << endl;
                        cout << "Moi nhap lua chon cua ban: ";
                        char Achoice3 = getchar(); 
                        switch (Achoice3 - '0')
                        {   
                            case 1:
                            {   read_loopA4: system("cls");  
                                U.sort(FUser);
                                U.hienDS();
                                Menu();
                                cout << "|                                    |" << endl;
                                cout << "|"; icon_Res(); cout << "<1> Them user                  |" << endl;
                                cout << "|"; icon_del(); cout << "<2> Xoa user                   |" << endl;
                                cout << "|"; icon_Res(); cout << "<3> Sua user                   |" << endl;
                                cout << "|"; icon_return(); cout << "<4> Quay lai                   |" << endl;
                                cout << "|"; icon_exit();   cout << "<5> Dang xuat                  |" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                cout << "Moi nhap lua chon cua ban: ";
                                char Achoice4_1 = getchar(); 
                                switch (Achoice4_1 - '0')
                                {
                                case 1:  AD.addUS(U, FUser); TitleUser(); AD.hienDSUS(U); delay = getche(); 
                                    goto read_loopA4;
                                case 2: 
                                {
                                    cin.ignore();
                                    int STTdel;
                                    system("cls");
                                    icon_Order(); cout << "Xac nhan muon xoa user (y/n): "; char Achoice4_2 = getchar();
                                    if (Achoice4_2 == 'y' || Achoice4_2 == 'Y')
                                    { 
                                        TitleUser();
                                        AD.hienDSUS(U);
                                        cout << "Nhap STT nguoi dung can xoa: "; cin >> STTdel;
                                        while (STTdel<=0 || STTdel > U.getN())
                                        {
                                            cout << "STT khong hop le. Vui long nhap lai: "; cin >> STTdel;
                                        }
                                        AD.delUS(U, FUser, U.arrayGetUsername(STTdel));
                                        delay = getche();
                                        goto read_loopA4;
                                    }
                                    else  goto read_loopA4;
                                }
                                case 3: 
                                {
                                    int ch, i;
                                    cout<<endl;icon_Order();
                                    string oldSDT, newName, newSDT, username; Day newBD;
                                    cout<<"Nhap SDT cua nguoi ban muon chinh sua: "; cin.ignore(); getline(cin, oldSDT);
                                    U.fixUser(FUser, i, ch, oldSDT, newName, newBD, newSDT, username, 1);
                                    AC.update(FActivity, ch, oldSDT, newName, newBD, newSDT);
                                    if(i!=-1){cout<<"Sau khi sua:"<<endl;   TitleUser(); U.hienThi(i);}
                                    delay=getch();
                                    goto read_loopA4;
                                }
                                case 4: goto read_loopA3;
                                case 5:
                                return 0;
                                default:
                                    goto read_loopA4;
                                }
                            }
                            case 2:
                            {
                                read_loopA5:
                                system("cls");
                                Menu();
                                cout << "|                                    |" << endl;
                                cout << "|"; icon_sort(); cout << "<1> Sap xep theo ten           |" << endl;
                                cout << "|"; icon_search(); cout << "<2> Tim kiem                   |" << endl;
                                cout << "|"; icon_cost(); cout << "<3> Doanh thu khoang thoi gian |" << endl;
                                cout << "|"; icon_return(); cout << "<4> Quay lai                   |" << endl;
                                cout << "|"; icon_exit();   cout << "<5> Dang xuat                  |" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                cout << "Moi nhap lua chon cua ban: ";
                                char Achoice4 = getchar(); 
                                switch(Achoice4 - '0')
                                {
                                    case 1:
                                    {
                                        U.sort(FUser);
                                        TitleUser();
                                        AD.hienDSUS(U);
                                        delay=getch();
                                        goto read_loopA5;
                                    }
                                    
                                    case 2:
                                    {
                                        cout<<endl;
                                        cin.ignore();
                                        AD.searchUS(FUser);
                                        delay=getch();
                                        goto read_loopA5;
                                    }
                                   
                                    case 3:
                                    {
                                        Day start_day, end_day;
                                        cout << endl;
                                        icon_Order(); cout << "Nhap thoi gian bat dau: "; start_day.nhapDay();
                                        cout << endl;
                                        icon_Order(); cout << "Nhap thoi gian ket thuc: "; end_day.nhapDay();
                                        TitleActi();
                                        AD.Calculate(AC, start_day,end_day);
                                        delay = getch();
                                    goto read_loopA5;
                                    }
                                    case 4:
                                    goto read_loopA3;
                                    case 5:
                                    return 0;
                                    default: goto read_loopA5;
                                }
                            goto read_loopA3;
                            }
                            case 3:
                            {   read_loopA4_3: system("cls");
                                string hoten, sdt;
                                Day day;
                                cout << endl;Menu();
                                cout << "|                                    |" << endl;
                                cout << "|"; icon_Res(); cout << setw(31) << left << "<1> Khach le" << "|" << endl;
                                cout << "|"; icon_login(); cout << setw(31) << left << "<2> Khach da co tai khoan" << "|" << endl;
                                cout << "|"; icon_return(); cout << setw(31) << left << "<3> Quay lai" << "|" << endl;
                                cout << "|"; icon_exit(); cout << setw(31) << left << "<4> Dang xuat" << "|" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                char Achoice4_3 = getch();
                                switch (Achoice4_3-'0')
                                {
                                case 1:
                                {
                                    icon_Order(); cout << "Nhap ten khach le: "; cin.ignore(); getline(cin, hoten);
                                    hoten = hoten + " (Khach le)";
                                    break;
                                }
                                case 2: 
                                {
                                    icon_Order(); cout << "Nhap ten user: "; cin.ignore(); getline(cin, hoten);
                                    break;
                                }
                                case 3: goto read_loopA3;
                                case 4: return 0;
                                default: goto read_loopA4_3;
                                }
                                icon_Order(); cout << "Nhap ngay sinh: "; day.nhapDay();
                                icon_Order(); cout << "Nhap so dien thoai: "; cin.ignore(); getline(cin, sdt);
                                cout << endl; 
                                AD.order(AC, FActivity, hoten, day, sdt);
                                delay = getch();
                                goto read_loopA3;
                            }
                            case 4:
                            {
                                read_loopA4_4:    system("cls");
                                Menu();
                                cout << "|                                    |" << endl;
                                cout << "|"; icon_del(); cout << "<1> Xoa tai khoan admin        |" << endl;
                                cout << "|"; icon_return(); cout << "<2> Quay lai                   |" << endl;
                                cout << "|"; icon_exit(); cout << "<3> Dang xuat                      |" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                cout << "Moi nhap lua chon cua ban: ";
                                char Achoice4_4 = getch();
                                switch (Achoice4_4 - '0')
                                {
                                    case 1:
                                    {   cout<<endl;
                                        TitleAdmin();
                                        AD.hienDS();
                                        AD.delAd(FAdmin);
                                        delay = getch();
                                        goto read_loopA4_4;
                                    }
                                    case 2: goto read_loopA3;
                                    case 3: return 0;
                                    default: goto read_loopA4_4;
                                }
                            }
                            case 5:
                            {
                                TitleActi();
                                AD.priBill(AC,day, AD.getName(password)); 
                                delay = getche();
                                goto read_loopA3;
                            }
                            case 6: goto read_loopA2;
                            case 7:
                            return 0;
                            default: goto read_loopA3;
                        }
                        // Thực hiện công việc    
                        }
                        else 
                        {
                            setColor(4);
                            cout << "\n:(( Dang nhap that bai :((" << endl;
                            cout << "Ban con " << --check << " lan dang nhap!\n";
                            cout << "Nhan 0 de thoat hoac Enter de nhap lai"; delay = getch();
                            if ((delay - '0')==0) return 0;
                            setColor(7);
                            Sleep(500);
                            goto read_loop_autA;
                        }
                }
                break;
                case 3: goto read_loop1;
                case 4: return 0;
                default: goto read_loopA2;
            }
        break;  //case 1
//////////////////////////////////////////////////
        case 2: 
            read_loopU2:	system("cls"); check = 5;
			Menu();
            cout << "|                                    |" << endl;
            cout << "|"; icon_Res(); cout << "<1> Ban muon dang ki tai khoan |" << endl;
            cout << "|"; icon_login(); cout << "<2> Dang nhap                  |" << endl;
            cout << "|"; icon_return(); cout << "<3> Quay lai                   |" << endl;
            cout << "|"; icon_exit(); cout << "<4> Thoat                      |" << endl;
            cout << "|                                    |" << endl;
            cout << "+====================================+" << endl;
            cout << "Moi nhap lua chon cua ban: ";
            char Uchoice2;
			Uchoice2=getchar();	system("cls");	
			switch (Uchoice2-'0')
			{
                case 1: 
                    U.add(FUser); 
                    break;
                case 2: 
                {
                    read_loop_autU: system("cls");
                    //   cin.ignore();
                      if (check == 0) return 0; //Check số lần đăng nhập
                    cout << "Ten dang nhap (viet lien, khong dau): "; cin >> username;  cin.ignore();
                    cout << "<<<<<Ban co muon an mat khau (y/n)>>>>>>>: "; char ynU1 = getchar();
                    if (ynU1 == 'y' ) { cout << "\nMat khau (viet lien, khong dau): ";  hidePassword(password);}
                    else if (ynU1 == 'n') { cout << "\nMat khau (viet lien, khong dau): ";  cin >> password;}
                    else {
                        cout << "\nLua chon khong hop le. Enter de quay lai!";
                        delay = getch(); goto read_loop_autU;
                    }
                    loading(40,50,11, "[Dang dang nhap]");
                    if (authenticateUser(username,password, FUser))
                    {
                        setColor(10);
                        cout << "\n:)) Dang nhap thanh cong :))" << endl; 
                        setColor(7);
                        Sleep(500);  //Hàm dừng màn hình trong 0.5 giây
                        // Thực hiện công việc
                        read_loopU3: system("cls");
                        Menu();
                        cout << "|                                    |" << endl;
                        cout << "|"; icon_Res(); cout << setw(31) << left << "<1> Dat san" << "|" << endl;
                        cout << "|"; icon_History(); cout << setw(31) << left << "<2> Xem lich su dat" << "|" << endl;
                        cout << "|"; icon_del(); cout << setw(31) << left << "<3> Xoa dat san" << "|" << endl;
                        cout << "|"; icon_del(); cout << setw(31) << left << "<4> Xoa tai khoan" << "|" << endl;
                        cout << "|"; icon_Order(); cout << setw(31) << left << "<5> Sua thong tin" << "|" << endl;
                        cout << "|"; icon_return(); cout << setw(31) << left << "<6> Quay lai" << "|" << endl;
                        cout << "|"; icon_exit(); cout << setw(31) << left << "<7> Dang xuat" << "|" << endl;
                        cout << "|                                    |" << endl;
                        cout << "+====================================+" << endl;

                        icon_Order();    cout << "Nhap lua chon cua ban: "; 
                        char Uchoice3 = getch(); cin.ignore();
                        User *x = U.getUser(username);
                        
                        switch (Uchoice3 - '0')
                        {
                            case 1: 
                            {
                                cout << endl;
                                U.order(FActivity, AC, x->getHoten(), x->getNgaySinh(), x->getSDT());
                                delay = getch();
                            }
                            goto read_loopU3;
                            case 2: system("cls");
                                read_loophis: system("cls");
                                U.History(AC, x->getHoten(), x->getSDT());
                                int choice;
                                cout << "|                                    |" << endl;
                                cout << "|"; icon_choice(); cout  << setw(31) << left<< "<1> Gan day nhat" << "|" << endl;
                                cout << "|"; icon_choice(); cout  << setw(31) << left<< "<2> Xa nhat" << "|" << endl;
                                cout << "|"; icon_choice(); cout  << setw(31) << left<< "<3> Theo thoi luong choi " << "|" << endl;
                                cout << "|"; icon_return(); cout  << setw(31) << left<< "<4> Quay lai" << "|" << endl;
                                cout << "|"; icon_exit(); cout  << setw(31) << left<< "<5> Dang xuat" << "|" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                icon_Order();    cout << "Nhap lua chon cua ban: "; 
                                cin>>choice;
                                switch(choice){
                                    case 1:
                                    case 2:
                                    case 3:
                                        AC.sortActivities(choice);
                                        goto read_loophis;
                                    case 4:
                                        goto read_loopU3;
                                    case 5:
                                        return 0;
                                }
                            case 3:
                                system("cls");
                                U.ActiDel(FActivity, AC, x->getHoten(), x->getSDT());
                                Sleep(500);
                                goto read_loopU3;
                            break;
                            
                            //xóa tài khoản user
                            case 4: 
                            {
                                system("cls");
                                icon_confirm(); cout << "Ban co that su muon xoa tai khoan(y/n)?";
                                char Uchoice4; 
                                Uchoice4 = getchar();    
                                system("cls");
                                if (Uchoice4 == 'y') {
                                U.del(FUser, username); 
                                goto read_loop1;
                                } else if (Uchoice4 == 'n') {
                                cout << "\nVui long nhan Enter de quay lai!";
                                delay = getch(); 
                                goto read_loopU3;
                                } else {
                                cout << "\nLua chon khong hop le. Enter de quay lai!";
                                delay = getch(); 
                            goto read_loopU3;
                            }
                            }
                            case 5:
                            {
                                    int ch, i;
                                    cout<<endl;
                                    string oldSDT, newName, newSDT; Day newBD;
                                    U.fixUser(FUser, i, ch, oldSDT, newName, newBD, newSDT, username, 2);
                                    AC.update(FActivity, ch, oldSDT, newName, newBD, newSDT);
                                    if(i!=-1){cout<<"Sau khi sua:"<<endl; U.hienThi(i);}
                                    delay=getch();
                                    goto read_loopU3;
                                }
                            case 6: goto read_loopU2;
                            case 7: 
                            return 0;   
                            default:
                                goto read_loopU3;
                        }
                    }
                    else 
                    {
                        setColor(4);
                            cout << "\n:(( Dang nhap that bai :((" << endl;
                        setColor(7);
                            cout << "Ban con " << --check << " lan dang nhap!\n";
                            cout << "1. Dang nhap lai\t\t2. Quen mat khau\t\t3. Thoat"; delay = getch();
                            switch(delay - '0')
                            {
                                case 1:  goto read_loop_autU;
                                case 2: 
                                {   
                                    system("cls");
                                    int ch, i;
                                    string get, getc;
                                    string SDT, newName, newSDT; Day newBD; cin.ignore();
                                    icon_Order(); cout<<"Hay nhap so dien thoai cua ban: ";  getline(cin,SDT);
                                    if (CapCha()){
                                        U.fixUser(FUser, i, ch, SDT, newName, newBD, newSDT, username, 3);
                                        if (i!=-1)  cout << "Doi mau khau thanh cong";
                                    }
                                    else
                                    cout << "Sai ma Capcha!";
                                    
                                    delay = getch();
                                    goto read_loop_autU;
                                }
                                case 3:  return 0;
                                default: return 0;
                            }
                    }
                }
                break;
                case 3: goto read_loop1;
                case 4: break;
                default:
                    goto read_loopU2;
            }
        break;
        case 3: break;
        default: system("cls");
            goto read_loop1;
    }
    system("pause");
    return 0;
}

