#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <stdlib.h>

using namespace std;

const int hight=23, width=49;
char map [hight][width];
int x,y,x0,y0,xn,yn,x_B,y_B,x_door,y_door;
int move_count=0,move_counts = 0,scope=0,bomb_count=0;
bool BOMB_ACTIVE = false;

//*********************************************
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//*********************************************
void MessageBox(int xt, int yt, const string message)
{
    int length = message.length();

    gotoxy(xt,yt);
    std::cout << "+";
    for (int i = 0; i < length + 2; ++i)
    {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    gotoxy(xt,yt+1);
    std::cout << "|";
    for (int i = 0; i < length + 2; ++i)
    {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;

    gotoxy(xt,yt+2);
    std::cout << "| " << message << " |" << std::endl;

    gotoxy(xt,yt+3);
    std::cout << "|";
    for (int i = 0; i < length + 2; ++i)
    {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;

    gotoxy(xt,yt+4);
    std::cout << "+";
    for (int i = 0; i < length + 2; ++i)
    {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}

//************************************
void CreateMap()
{
    int i,j,k;

    for(i=0;i<hight;i++)
        for(j=0;j<width;j++)
            map[i][j]=' ';

    for(j=0;j<width;j+=2)
        map[0][j]='*';
    map[0][width-1]='*';

    for(int i=1;i<hight-1;i++)
    {
        map[i][0]='*';
        if ((i%2)==1)
            for(int j=1;j<width/4;j++)
                map[i][j*4]='|';
        if ((i%2)==0)
            for(int j=2;j<width-1;j+=4)
                map[i][j]='-';
        map[i][width-1]='*';
    }

    for(j=0;j<width-1;j+=2)
        map[hight-1][j]='*';
    map[hight-1][j]='*';

    int positions1[][2] = {{5,38},{9,26},{17,14}};  //دشمن
    int count1 = sizeof(positions1) / sizeof(positions1[0]);
    for(i=0;i<count1;i++)
        map[positions1[i][0]][positions1[i][1]]='E';

    int positions2[][2] = {{1,26}, {5,2}, {5,18}, {5,22},
                          {5,26}, {9,14}, {9,34}, {13,2}, {13,10},
                          {13,38}, {13,42}, {21,10}, {19,10}, {19,26},
                          {17,10}, {17,22}, {17,30}, {17,46}}; // ديوار قابل تخريب
    int count2 = sizeof(positions2) / sizeof(positions2[0]);
    for(i=0;i<count2;i++)
        map[positions2[i][0]][positions2[i][1]]='#';

    k=rand()%(count2);
    x_door=positions2[k][1];
    y_door=positions2[k][0];

    int positions3[][2] = {{3,6}, {3,14}, {3,22}, {3,30}, {3,38},
                           {7,6}, {7,14}, {7,22}, {7,30}, {7,38},
                           {11,6}, {11,14}, {11,22}, {11,30}, {11,38},
                           {15,6}, {15,14}, {15,22}, {15,30}, {15,38},
                           {19,6}, {19,14}, {19,22}, {19,30}, {19,38}};  //ديوار غير قابل تخريب
    int count3 = sizeof(positions3) / sizeof(positions3[0]);
    for(i=0;i<count3;i++)
        map[positions3[i][0]][positions3[i][1]]='X';
    return;
 }

//*********************************************
void PrintMap()
{
    int i,j;

    gotoxy(0,0);
    for(i=0;i<hight;i++)
    {
        for(j=0;j<width;j++)
            cout << map[i][j];
        cout << endl;
    }

}

//*********************************************
void SetBomb()
{
    x_B=x;
    y_B=y;
    gotoxy(x,y);
    cout << "B";
    map[y_B][x_B] = 'B';
    x=x0;
    y=y0;
    gotoxy(x,y);
    cout << 'P';
    BOMB_ACTIVE = true;
    bomb_count+=1;

    return;
}
//*********************************************

void Destruct()
{
    int x1,y1;

    gotoxy(x_B,y_B);
    cout << ' ';
    map[y_B][x_B]=' ';

    x1=x_B-4;  // كنترل خانه سمت چپ
    y1=y_B;
    if ((x1>=2) && ((map[y1][x1]=='#') || (map[y1][x1]=='E')))
    {
        gotoxy(x1,y1);
        cout << ' ';
        map[y1][x1]=' ';
    }

    x1=x_B+4;  // كنترل خانه سمت راست
    y1=y_B;
    if ((x1<=width-3) && ((map[y1][x1]=='#') || (map[y1][x1]=='E')))
    {
        gotoxy(x1,y1);
        cout << ' ';
        map[y1][x1]=' ';
    }

    x1=x_B;  // كنترل خانه سمت بالا
    y1=y_B-2;
    if ((y1>=1) && ((map[y1][x1]=='#') || (map[y1][x1]=='E')))
    {
        gotoxy(x1,y1);
        cout << ' ';
        map[y1][x1]=' ';
    }

    x1=x_B;  // كنترل خانه سمت پايين
    y1=y_B+2;
    if ((y1<=hight-1) && ((map[y1][x1]=='#') || (map[y1][x1]=='E')))
    {
        gotoxy(x1,y1);
        cout << ' ';
        map[y1][x1]=' ';
    }

    gotoxy(x,y);

    return ;
}

//*********************************************
void ShowDashbord()
{
    gotoxy(width+3,2);
    cout << "SCOPE: " << scope << "         ";

    gotoxy(width+3,4);
    cout << "BOMBS: " << bomb_count << "         ";

    gotoxy(width+3,6);
    cout << "MOVES: " << move_counts << "         ";
    gotoxy(x, y);
}

//*********************************************
void ShowMenu()
{

}

//*********************************************
int move()
{
            if (map[yn][xn]==' ')
            {
                x0=x; y0=y;
                x=xn; y=yn;
                gotoxy(x0, y0);
                cout << ' ';
                gotoxy(x, y);
                cout << 'P';
                move_counts += 1;

                if(BOMB_ACTIVE)
                {
                    move_count += 1;
                    if(move_count == 2)
                    {
                        Destruct();
                        move_count = 0;
                        BOMB_ACTIVE = false;

                        if (((xn-x_B==4 || xn-x_B==-4) && yn==y_B) || ((yn-y_B==2 || yn-y_B==-2) && (xn==x_B)))
                        {
                            gotoxy(x,y);
                            cout << '0';

                            gotoxy(10,hight+2);
                            MessageBox(9,9,"     Game Over ...  !!!     ");
                            gotoxy(width+2,hight+2);
                            return 0;  // خاتمه برنامه
                        }
                    }
                }
            }
    return 1;
}

//*********************************************
//*********************************************
int main()
{
    char ch;

    CreateMap();
    PrintMap();

    x=2; y=1;
    x0=x; y0=y;
    xn=x; yn=y;
    gotoxy(x, y);
    cout << 'P';
    ShowDashbord();

    while (true)
    {
        if (kbhit())  // بررسی می‌کند که آیا کلید فشرده شده است
        {
            ch = getch();  // دریافت ورودی کلید

                gotoxy(5,25);
                cout << "          ";
                gotoxy(5,25);
                cout << int(ch);
                gotoxy(x,y);

            switch (ch)  // بررسی ورودی دکمه‌های جهت‌دار
            {
                case 72:  // کلید بالا
                     if (y > 1)
                     {
                         xn=x; yn=y-2;
                         if (move()==0) return 0;
                     }
                     break;
                case 80:  // کلید پایین
                     if (y < hight-2)  // 23 محدودیت عمودی
                     {
                         xn=x; yn=y+2;
                         if (move()==0) return 0;
                     }
                     break;
                case 75:  // کلید چپ
                     if (x > 2)
                     {
                         yn=y; xn=x-4;
                         if (move()==0) return 0;
                     }
                     break;
                case 77:  // کلید راست
                     if (x < width-3)  // 49 محدودیت افقی
                     {
                         yn=y; xn=x+4;
                         if (move()==0) return 0;
                     }
                     break;
                case 66:  //  كليد B يا b براي بمب
                case 98:
                    if (!BOMB_ACTIVE)
                        SetBomb();
                    break;
                case 59:  //  كليد F1 براي منو
                    ShowMenu();
                    PrintMap();
                    gotoxy(x, y);
                    cout << 'P';
                    break;
                case 27:  // کلید ESC برای خروج
//                    system("cls");
                    gotoxy(10,hight+2);
                    MessageBox(9,9,"     Game Exit ...  !!!     ");
                    gotoxy(width+2,hight+2);
                    return 0;  // خاتمه برنامه
            }

//            if ((ch==72 || ch==80 || ch==75 || ch==77) && (map[yn][xn]==' '))
//            {
//            }
            ShowDashbord();

                gotoxy(60,10);
                cout << "          ";
                gotoxy(60,10);
                cout << x0 << " old " << y0;

                gotoxy(60,12);
                cout << "          ";
                gotoxy(60,12);
                cout << x << " jari " << y;

                gotoxy(60,14);
                cout << "          ";
                gotoxy(60,14);
                cout << xn << " new " << yn;

                gotoxy(x, y);

        }
    }

}
