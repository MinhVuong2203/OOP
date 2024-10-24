#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;
const int GiaThuong = 50000;  //Khai báo để sử dụng cho việc in bill. từ 7h - 16h giá 50000đ/h, từ 16h - 22h giá 110000đ/h
const int GiaVang = 110000;
const int SL = 20;
 
#include "./assets/function/Title.hpp"  //liên kết với file Title
#include "./assets/function/TimeDay.hpp"
Time timeVang = {16,0,0};
#include "./assets/function/Person.hpp"
#include "./assets/function/Admin.hpp"
#include "./assets/function/User.hpp"
#include "./assets/function/Activity.hpp"
#include "./assets/function/authenticate.hpp"
#include "./assets/function/templateBill.hpp"

int main() 
{

    

    
    
    //Khai báo file
    string FAdmin = "assets//Admin.txt";
    string FUser = "assets//User.txt";
    string FRetail = "assets//Retail.txt";
    string FActivity = "assets//Activity.txt";

    QLAD AD(FAdmin);
    QLUS U(FUser);
    QLAC AC(FActivity);
    int San[SL];

    string username, password;
    
    char delay;

    Day day;  Time time;
    day = getday();
    time = getTime();
    cout << "Hom nay: " << day.ngay << "/" << day.thang << "/" << day.nam << " ";
    // In ra giờ, phút, giây
    cout << time.gio << ":" << time.phut << ":" << time.giay << "PM"<< endl;
    
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
    char choice1 = getche();	
    switch (choice1-'0') 
	{
        case 1:    
            read_loopA2:	system("cls");
            Menu();
            cout << "|                                    |" << endl;
            cout << "|"; icon_Res(); cout << "<1> Ban muon dang ki tai khoan |" << endl;
            cout << "|"; icon_login(); cout << "<2> Dang nhap                  |" << endl;
            cout << "|"; icon_return(); cout << "<3> Quay lai                   |" << endl;
            cout << "|"; icon_exit(); cout << "<4> Thoat                      |" << endl;
            cout << "|                                    |" << endl;
            cout << "+====================================+" << endl;
            cout << "Moi nhap lua chon cua ban: ";
        	char Achoice2;
			Achoice2=getche();	system("cls");	
			switch (Achoice2-'0')
			{
                case 1: AD.add(FAdmin); break;
                case 2: 
                {
                    read_loop_autA: system("cls");
                    icon_Order(); cout << "Ten dang nhap (SDT): "; cin >> username; 
                    cout << "<<<<<Ban co muon an mat khau (y/n)>>>>>>>: "; char ynA1 = getche();
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
                        delay = getch(); goto read_loop_autA;
                    }
                    
                    if (authenticateUser(username,password, FAdmin)) 
                    {
                        setColor(10);
                        cout << "\n<<< Dang nhap thanh cong >>>" << endl; 
                        setColor(7);
                        Sleep(500);  //Hàm dừng màn hình trong 0.5 giây
                        read_loopA3: system("cls"); //Xóa màn hình
                       
                        Menu();
                        cout << "|                                    |" << endl;
                        cout << "|"; icon_Res(); cout << "<1> Quan li danh sach user     |" << endl;
                        cout << "|"; icon_login(); cout << "<2> Thong ke                   |" << endl;
                        cout << "|"; icon_Res(); cout << "<3> Dat san                    |" << endl;
                        cout << "|"; icon_login(); cout << "<4> Quan li Admin              |" << endl;
                        cout << "|"; icon_login(); cout << "<5> In hoa don                 |" << endl;
                        cout << "|"; icon_return(); cout << "<6> Quay lai                   |" << endl;
                        cout << "|"; icon_exit(); cout << "<7> Thoat                      |" << endl;
                        cout << "|                                    |" << endl;
                        cout << "+====================================+" << endl;
                        cout << "Moi nhap lua chon cua ban: ";
                        char Achoice3 = getche(); 
                        switch (Achoice3 - '0')
                        {
                            case 1:
                            {   read_loopA4: system("cls"); 
                                TitleUser(); 
                                U.hienDS();  
                                Menu();
                                cout << "|                                    |" << endl;
                                cout << "|"; icon_Res(); cout << "<1> Them user                  |" << endl;
                                cout << "|"; icon_login(); cout << "<2> Xoa user                   |" << endl;
                                cout << "|"; icon_Res(); cout << "<3> Sua user                   |" << endl;
                                cout << "|"; icon_return(); cout << "<4> Quay lai                   |" << endl;
                                cout << "|"; icon_exit(); cout << "<5> Thoat                      |" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                cout << "Moi nhap lua chon cua ban: ";
                                char Achoice4_1 = getch(); cin.ignore();
                                switch (Achoice4_1 - '0')
                                {
                                case 1: cout << endl; U.add(FUser); TitleUser(); U.hienDS(); delay = getch(); 
                                    goto read_loopA4;
                                case 2: 
                                    U.hienDS();
                                    AD.delUS(FUser, U);
                                    goto read_loopA4;
                                case 3: 
                                {
                                    int i,ch;
                                    icon_Order();
                                    cout<<"Nhap so cua nguoi ban muon chinh sua:"; cin>>i;
                                    string oldName, newName, newSDT; Day newBD;
                                    
                                    U.fixUser(FUser, i, ch, oldName, newName, newBD, newSDT);
                                    AC.update(FActivity, ch, oldName, newName, newBD, newSDT);
                                    cout<<"Sau khi sua:"<<endl; U.hienThi(i);
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
                                cout << "|"; icon_Res(); cout << "<1> Sap xep theo ten           |" << endl;
                                cout << "|"; icon_login(); cout << "<2> Tim kiem                   |" << endl;
                                cout << "|"; icon_Res(); cout << "<3> Doanh thu khoang thoi gian |" << endl;
                                cout << "|"; icon_return(); cout << "<4> Quay lai                   |" << endl;
                                cout << "|"; icon_exit(); cout << "<5> Thoat                      |" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                cout << "Moi nhap lua chon cua ban: ";
                                //cout << "1. Sap xep theo ten\n2. Tim kiem\n3. Doanh thu theo khoang thoi gian\n4. Quay lai\n5. Thoat\nNhap lua chon cua ban: ";
                                char Achoice4 = getch(); 
                                switch(Achoice4 - '0')
                                {
                                    case 1:
                                    goto read_loopA5;
                                    case 2:
                                    {
                                        cout<<endl;
                                        cin.ignore();
                                        string search;
                                        icon_Order();
                                        cout<<"Nhap du lieu cua nguoi dung ma ban muon tim kiem:";
                                        getline(cin,search);
                                        AD.searchUS(search,FUser);
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
                                        double tien = AC.calculate(start_day,end_day);
                                        cout << "Doanh thu tu ngay "; start_day.xuatDay() ; cout << " den "; end_day.xuatDay(); cout << " la: "; 
                                        cout << fixed << setprecision(0) << tien << endl;
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
                            {
                                string hoten, sdt;
                                Day day;
                                icon_Order(); cout << "Nhap ten user: "; cin.ignore(); cin >> hoten;
                                icon_Order(); cout << "Nhap ngay sinh: "; day.nhapDay();
                                icon_Order(); cout << "Nhap so dien thoai: "; cin.ignore(); cin >> sdt;
                                cout << endl; AC.add(FActivity, hoten, day, sdt);
                                delay = getch();
                                goto read_loopA3;
                            }
                            case 4:
                            {
                                read_loopA4_4:    system("cls");
                                Menu();
                                cout << "|                                    |" << endl;
                                cout << "|"; icon_Res(); cout << "<1> Xoa tai khoan admin        |" << endl;
                                cout << "|"; icon_login(); cout << "<2> Sua tai khoan admin        |" << endl;
                                cout << "|"; icon_return(); cout << "<3> Quay lai                   |" << endl;
                                cout << "|"; icon_exit(); cout << "<4> Thoat                      |" << endl;
                                cout << "|                                    |" << endl;
                                cout << "+====================================+" << endl;
                                cout << "Moi nhap lua chon cua ban: ";
                                char Achoice4_4 = getch();
                                switch (Achoice4_4 - '0')
                                {
                                    case 1:
                                    {   cout<<endl;
                                        AD.hienDS();
                                        AD.delAd(FAdmin);
                                        delay = getch();
                                        goto read_loopA4_4;
                                    }
                                    case 2:
                                    {
                                        
                                        delay = getch();
                                        goto read_loopA4_4;
                                    }
                                    case 3: goto read_loopA3;
                                    case 4: return 0;
                                    default: goto read_loopA4_4;
                                }
                            }
                            case 5:
                                    AC.priBill(day); 
                                    delay = getche();
                                    goto read_loopA3;
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
                            cout << "\n<<< Dang nhap that bai >>>" << endl;
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
            read_loopU2:	system("cls");
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
			Uchoice2=getche();	system("cls");	
			switch (Uchoice2-'0')
			{
                case 1: 
                    U.add(FUser); 
                    break;
                case 2: 
                {
                    read_loop_autU: system("cls");
                    cout << "Ten dang nhap (viet lien, khong dau): "; cin >> username; 
                    cout << "<<<<<Ban co muon an mat khau (y/n)>>>>>>>: "; char ynU1 = getche();
                    if (ynU1 == 'y' ) { cout << "\nMat khau (viet lien, khong dau): ";  hidePassword(password);}
                    else if (ynU1 == 'n') { cout << "\nMat khau (viet lien, khong dau): ";  cin >> password;}
                    else {
                        cout << "\nLua chon khong hop le. Enter de quay lai!";
                        delay = getch(); goto read_loop_autU;
                    }
                    
                    if (authenticateUser(username,password, FUser))
                    {
                        cout << "\n<<< Dang nhap thanh cong>>>" << endl; 
                        // Thực hiện công việc
                        delay = getch();
                        read_loopU3: system("cls");
                        Menu();
                        cout << "1. Dat san\n2. Xem lich su dat\n3. Xoa dat san\n4. Xoa tai khoan\n5. Quay lai\n6. Thoat\nNhap lua chon cua ban: "; char Uchoice3 = getche(); cin.ignore();
                        User *x = U.getUser(username);
                        switch (Uchoice3 - '0')
                        {
                            case 1: 
                            {
                                cout << endl; AC.add(FActivity, x->getHoten(), x->getNgaySinh(), x->getSDT());
                                delay = getch();
                            }
                            goto read_loopU3;
                            case 2: system("cls");
                                AC.History(x->getHoten());
                            break;
                            case 3:
                            break;
                            
                            //xóa tài khoản user
                            case 4: {
                            system("cls");
                            cout << "Ban co that su muon xoa tai khoan(y/n)?";
                            char Uchoice4; 
                            Uchoice4 = getche();
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
                            case 5: goto read_loopU3;
                            case 6: 
                            return 0;   
                            default:
                                goto read_loopU3;
                        }
                    }
                    else 
                    {
                        cout << "\n<<< Dang nhap that bai. Enter de dang nhap lai! >>>" << endl;
                        delay = getche();
                        goto read_loop_autU;
                    }
                }
                break;
                case 3: goto read_loop1;
                case 4: break;
                default:
                    goto read_loopU2;
            }
        break; //case 2:
        case 3: break;
        default:
            goto read_loop1;
    }
    system("pause");
    return 0;
}

