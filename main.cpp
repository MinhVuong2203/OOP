#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>

#include "./assets/function/Title.hpp"  //liên kết với file Title
#include "./assets/function/TimeDay.hpp"
#include "./assets/function/Person.hpp"
#include "./assets/function/Admin.hpp"
#include "./assets/function/User.hpp"
#include "./assets/function/Activity.hpp"
#include "./assets/function/authenticate.hpp"
#include  "./assets/function/templateBill.hpp"

using namespace std;

// Time time16h = {16,0,0};   //Khai báo để sử dụng cho việc in bill. từ 7h - 16h giá 50000đ/h, từ 16h - 22h giá 110000đ/h
const int GiaThuong = 50000;
const int GiaVang = 110000;


int main() 
{
    //Khai báo file
    string FAdmin = "assets//Admin.txt";
    string FUser = "assets//User.txt";
    string FRetail = "assets//Retail.txt";
    string FActivity = "assets//Activity.txt";


    QLAD AD;
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

    AC.hienDS();
    TitleUser();
    // U.hienDS();
    AC.priBill(day);
    
    setColor(10);
    	printf("+------------------------------------------------+\n");
      	printf("|     San cau long CIB xin kinh chao quy khach   |\n");
		printf("+------------------------------------------------+\n\n");
    setColor(7);
    read_loop1:
    cout << "1. Nguoi quan ly\t\t2. Nguoi dung\t\t3. Thoat\n\nMoi nhap lua chon cua ban: ";
    char choice1 = getche();	
    switch (choice1-'0') 
	{
        case 1:    
            read_loopA2:	system("cls");
            Menu();
			cout << "1. Ban muon dang ky tai khoan\n2. Dang nhap\n3. Quay lai\n4. Thoat\nMoi nhap lua chon cua ban: ";
        	char Achoice2;
			Achoice2=getche();	system("cls");	
			switch (Achoice2-'0')
			{
                case 1: AD.add(FAdmin); break;
                case 2: 
                {
                    read_loop_autA: system("cls");
                    cout << "Ten dang nhap (SDT): "; cin >> username; 
                    cout << "<<<<<Ban co muon an mat khau (y/n)>>>>>>>: "; char ynA1 = getche();
                    if (ynA1 == 'y' ) { cout << "\nMat khau (CCCD): ";  hidePassword(password);}
                    else if (ynA1 == 'n') { cout << "\nMat khau (viet lien, khong dau): ";  cin >> password;}
                    else {
                        cout << "\nLua chon khong hop le. Enter de quay lai!";
                        delay = getch(); goto read_loop_autA;
                    }
                    
                    if (authenticateUser(username,password, FAdmin)) 
                    {
                        cout << "\n<<< Dang nhap thanh cong>>>" << endl; 
                        delay = getch();
                        read_loopA3: system("cls"); //Xóa màn hình
                        Menu();
                        cout << "1. Quan li danh sach user\n2. Thong ke\n3. Dat san\n "; icon_cost(); cout << "  4. In hoa don\n";  icon_return(); cout << " 5. Quay lai\n"; icon_exit(); cout << " 6. Thoat\nNhap lua chon cua ban: "; 
                        char Achoice3 = getche();
                        switch (Achoice3 - '0')
                        {
                            case 1:
                            {   system("cls");
                                TitleUser();
                                U.hienDS();
                                Menu();
                                cout << "1. Them user\n2. Xoa user\n3. Sua user\n4.Quay lai\n5. Thoat\nNhap lua chon cua ban: "; char Achoice4 = getche(); cin.ignore();
                                switch (Achoice4 - '0')
                                {
                                case 1: cout << endl; U.add(FUser); TitleUser(); U.hienDS(); delay = getch(); 
                                goto read_loopA3;
                                case 2:
                                break;
                                case 3:
                                break;
                                case 4: goto read_loopA3;
                                case 5:
                                return 0;
                                default:
                                    break;
                                }
                            }
                            break;
                            case 2:
                            break;
                            case 3:
                            {
                                string hoten, sdt;
                                Day day;
                                cout << "\nhap ten user: "; cin.ignore(); cin >> hoten;
                                cout << "Nhap ngay sinh: "; NhapDay(day);
                                cout << "Nhap so dien thoai: "; cin.ignore(); cin >> sdt;
                                cout << endl; AC.add(FActivity, hoten, day, sdt);
                                delay = getch();
                            }
                            break;
                            case 4: goto read_loopA2;
                            case 5:
                            return 0;
                            default:
                            break;
                        }
                        // Thực hiện công việc    
                        }
                        else 
                        {
                            cout << "\n<<< Dang nhap that bai. Enter de dang nhap lai! >>>" << endl;
                            delay = getche();
                            goto read_loop_autA;
                        }
                }
                break;
                case 3: goto read_loopA2;
                case 4: break;
            }
        break;  //case 1
//////////////////////////////////////////////////
        case 2: 
            read_loopU2:	system("cls");
            Menu();
			cout << "1. Ban muon dang ky tai khoan\n2. Dang nhap\n3. Quay lai\n4. Thoat\nMoi nhap lua chon cua ban:";
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
                        cout << "1. Dat san\n2. Xem lich su dat\n3. Xoa dat san\n4. Quay lai\n5. Thoat\n6. Xoa tai khoan\nNhap lua chon cua ban: "; char Uchoice3 = getche(); cin.ignore();
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
                            case 4: goto read_loopU2;
                            case 5: 
                            return 0;
                            //xóa tài khoản user
                            case 6: {
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

                            default:
                                break;
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
            }
        break; //case 2:
        case 3: break;
    }
    system("pause");
    return 0;
}
