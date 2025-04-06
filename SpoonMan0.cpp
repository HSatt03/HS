#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int hight=23, width=49;
char map [hight][width];
int x=0,y=0,x0=0,y0=0,xn=0,yn=0,x_B,y_B;
int move_count = 0;
bool flag = false;
bool BOMB_ACTIVE = false;

//************************************
void CreateMap()
{
    int i,j;

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


    int positions3[][2] = {{3,6}, {3,14}, {3,22}, {3,30}, {3,38},
                           {7,6}, {7,14}, {7,22}, {7,30}, {7,38},
                           {11,6}, {11,14}, {11,22}, {11,30}, {11,38},
                           {15,6}, {15,14}, {15,22}, {15,30}, {15,38},
                           {19,6}, {19,14}, {19,22}, {19,30}, {19,38}};  //ديوار غير قابل تخريب
    int count3 = sizeof(positions3) / sizeof(positions3[0]);
    for(i=0;i<count3;i++)
        map[positions3[i][0]][positions3[i][1]]='X';

 }

//*********************************************
void PrintMap()
{
    int i,j;
    for(i=0;i<hight;i++)
    {
        for(j=0;j<width;j++)
            cout << map[i][j];
        cout << endl;
    }

}

//*********************************************
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//*********************************************
bool BOMB()
{
    int x1,y1;

    x1=x-4;  // كنترل خانه سمت چپ
    y1=y;
    if ((x1>1) && ((map[y1][x1]=='#') || (map[y1][x1]=='E'))) return true;

    x1=x+4;  // كنترل خانه سمت راست
    y1=y;
    if ((x1<width-3) && ((map[y1][x1]=='#') || (map[y1][x1]=='E'))) return true;

    x1=x;  // كنترل خانه سمت بالا
    y1=y-2;
    if ((x1<width-3) && ((map[y1][x1]=='#') || (map[y1][x1]=='E'))) return true;

    x1=x;  // كنترل خانه سمت پايين
    y1=y+2;
    if ((x1<width-3) && ((map[y1][x1]=='#') || (map[y1][x1]=='E'))) return true;

    return false;
}

//*********************************************
//*********************************************
int main()
{
    char ch;

    CreateMap();
    PrintMap();

    x0=2; y0=1;
    x=2; y=1;
    xn=0; yn=0;
    gotoxy(x, y);
    cout << 'P';
    while (true)
    {
        if (_kbhit())  // بررسی می‌کند که آیا کلید فشرده شده است
        {
            ch = _getch();  // دریافت ورودی کلید

            switch (ch)  // بررسی ورودی دکمه‌های جهت‌دار
            {

                case 72:  // کلید بالا
                     if (y > 1) { xn=x; yn=y-2;}
                     break;
                case 80:  // کلید پایین
                     if (y < hight-2) {xn=x; yn=y+2;} // 23 محدودیت عمودی
                     break;
                case 75:  // کلید چپ
                     if (x > 2) { yn=y; xn=x-4;}
                     break;
                case 77:  // کلید راست
                     if (x < width-3) {yn=y; xn=x+4;} // 49 محدودیت افقی
                     break;
                case 66:
                case 98:
                    if (BOMB())
                    {
                        x_B=x;
                        y_B=y;
                        gotoxy(x,y);
                        cout << "B";
                        x=x0;
                        y=y0;
                        gotoxy(x,y);
                        cout << 'P';
//                        BOMB_ACTIVE = true;
                    }
                    break;
                case 27:  // کلید ESC برای خروج
                    return 0;  // خاتمه برنامه
            }

            if (map[yn][xn]==' ')
            {
                x0=x; y0=y;
                x=xn; y=yn;
                gotoxy(x0, y0);
                cout << ' ';
                gotoxy(x, y);
                cout << 'P';
            }

        }
    }


    
}

