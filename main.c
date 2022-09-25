#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define garo 40
#define sero 40
INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;
int  zari = 6, printx = 0, printy = 4, lastnum, cnt = 0, type = 0, left = 0, right = 0;
char a[7], b[7];
void inputMouseSetting() {
    DWORD mode;

    GetConsoleMode(CIN, &mode); // 현재 콘솔 입력 모드를 가져온다.
    SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT); // 마우스 입력을 허용한다.
}

int error[32][64] =
{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0},
{0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0},
{0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,0,1,1,1,0,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0},
{0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0},
{0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0},
{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
enum colorName {
    BLACK,
    D_BLUE,
    D_GREEN,
    D_SKYBLUE,
    D_RED,
    D_VIOLET,
    D_YELLOW,
    GRAY,
    D_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

int zero[7][5] =
{ {0,1,1,1,0},
{1,0,0,0,1},
{1,0,0,0,1},
{1,0,0,0,1},
{1,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,0} };


int one[7][5] =
{ {0,0,1,0,0},
{0,1,1,0,0},
{0,0,1,0,0},
{0,0,1,0,0},
{0,0,1,0,0},
{0,0,1,0,0},
{0,1,1,1,0} };

int two[7][5] =
{ {0,1,1,1,0},
{1,0,0,0,1},
{0,0,0,0,1},
{0,0,0,1,0},
{0,0,1,0,0},
{0,1,0,0,0},
{1,1,1,1,1} };
int three[7][5] =
{ {0,1,1,1,0},
{1,0,0,0,1},
{0,0,0,0,1},
{0,0,1,1,0},
{0,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,0} };
int four[7][5] =
{ {0,0,0,1,0},
{0,0,1,1,0},
{0,1,0,1,0},
{1,0,0,1,0},
{1,1,1,1,1},
{0,0,0,1,0},
{0,0,0,1,0} };
int five[7][5] =
{ {1,1,1,1,1},
{1,0,0,0,0},
{1,1,1,1,0},
{0,0,0,0,1},
{0,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,0} };
int six[7][5] =
{ {0,1,1,1,0},
{1,0,0,0,1},
{1,0,0,0,0},
{1,1,1,1,0},
{1,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,0} };
int sev[7][5] =
{ {1,1,1,1,1},
{0,0,0,0,1},
{0,0,0,1,0},
{0,0,1,0,0},
{0,0,1,0,0},
{0,0,1,0,0},
{0,0,1,0,0} };
int eight[7][5] =

{ {0,1,1,1,0},
{1,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,0},
{1,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,0} };
int nine[7][5] =
{ {0,1,1,1,0},
{1,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,1},
{0,0,0,0,1},
{1,0,0,0,1},
{0,1,1,1,0} };
int sum[7][5] =
{ {0,0,1,0,0},
{0,0,1,0,0},
{0,0,1,0,0},
{1,1,1,1,1},
{0,0,1,0,0},
{0,0,1,0,0},
{0,0,1,0,0}, };
int bbel[7][5] =
{ {0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{1,1,1,1,1},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}, };
int gob[7][5] =
{ {1,0,0,0,1},
{1,0,0,0,1},
{0,1,0,1,0},
{0,0,1,0,0},
{0,1,0,1,0},
{1,0,0,0,1},
{1,0,0,0,1}, };
int nanu[7][5] =
{ {0,0,0,0,1},
{0,0,0,0,1},
{0,0,0,1,0},
{0,0,1,0,0},
{0,1,0,0,0},
{1,0,0,0,0},
{1,0,0,0,0}, };
int gyesangi[sero][garo] =
{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
{1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},

{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,1,1,1,1,1},
{1,1,1,1,1,3,3,3,3,31,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,4,4,4,4,32,33,4,4,4,4,1,1,1,1,1},
{1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,4,4,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,5,5,5,5,5,5,1,1,6,6,6,6,6,6,1,1,7,7,7,7,7,7,1,1,8,8,8,8,8,8,1,1,1,1,1},
{1,1,1,1,1,5,5,5,5,5,5,1,1,6,6,6,6,6,6,1,1,7,7,7,7,7,7,1,1,8,8,8,8,8,8,1,1,1,1,1},
{1,1,1,1,1,5,5,19,5,5,5,1,1,6,6,20,6,6,6,1,1,7,7,21,7,7,7,1,1,8,8,22,8,8,8,1,1,1,1,1},
{1,1,1,1,1,5,5,5,5,5,5,1,1,6,6,6,6,6,6,1,1,7,7,7,7,7,7,1,1,8,8,8,8,8,8,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,9,9,9,9,9,9,1,1,10,10,10,10,10,10,1,1,11,11,11,11,11,11,1,1,12,12,12,12,12,12,1,1,1,1,1},
{1,1,1,1,1,9,9,9,9,9,9,1,1,10,10,10,10,10,10,1,1,11,11,11,11,11,11,1,1,12,12,12,12,12,12,1,1,1,1,1},
{1,1,1,1,1,9,9,23,9,9,9,1,1,10,10,24,10,10,10,1,1,11,11,25,11,11,11,1,1,12,12,26,12,12,12,1,1,1,1,1},
{1,1,1,1,1,9,9,9,9,9,9,1,1,10,10,10,10,10,10,1,1,11,11,11,11,11,11,1,1,12,12,12,12,12,12,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,13,13,13,13,13,13,1,1,14,14,14,14,14,14,1,1,15,15,15,15,15,15,1,1,16,16,16,16,16,16,1,1,1,1,1},
{1,1,1,1,1,13,13,13,13,13,13,1,1,14,14,14,14,14,14,1,1,15,15,15,15,15,15,1,1,16,16,16,16,16,16,1,1,1,1,1},
{1,1,1,1,1,13,13,27,13,13,13,1,1,14,14,28,14,14,14,1,1,15,15,29,15,15,15,1,1,16,16,30,16,16,16,1,1,1,1,1},
{1,1,1,1,1,13,13,13,13,13,13,1,1,14,14,14,14,14,14,1,1,15,15,15,15,15,15,1,1,16,16,16,16,16,16,1,1,1,1,1},

{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,17,17,17,17,17,17,1,1,1,1,1,1,1,1,1,1,34,34,34,34,34,34,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,17,17,18,17,17,17,1,1,1,1,1,1,1,1,1,1,34,34,35,34,34,34,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,17,17,17,17,17,17,1,1,1,1,1,1,1,1,1,1,34,34,34,34,34,34,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void CursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

}
void drw(int bgColor, int textColor) {


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);

}
void click(int* xx, int* yy) {
    INPUT_RECORD record; // 콘솔 입력 버퍼의 입력 이벤트 구조체
    DWORD read; // unsigned long ( 데이터 기본 처리 단위인 WORD의 2배 )
    int posX, posY; // 마우스가 클릭된 좌표를 저장
    int winner; // 게임 무승부, 이긴 플레이어를 저장

    ReadConsoleInput(CIN, &record, 1, &read); // 콘솔 입력 이벤트 읽기

    if (record.EventType == MOUSE_EVENT) {
        if (record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED
            && !(record.Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
            && !(record.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK)) {
            int posX = record.Event.MouseEvent.dwMousePosition.X;
            int posY = record.Event.MouseEvent.dwMousePosition.Y;
        }
    }
}
void oneprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (one[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void twoprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (two[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void threeprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (three[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void fourprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (four[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void fiveprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (five[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void sixprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (six[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void sevenprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (sev[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void eightprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (eight[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void nineprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (nine[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
void zeroprint(int i) {
    int j, k;
    for (j = 0; j < 7; j++) {
        for (k = 0; k < 5; k++) {
            if (zero[j][k] == 1) {
                gotoxy(printx + i * 5 + k, printy + j);
                drw(BLUE, BLUE);
                printf(" ");
            }
        }
    }
}
int main()
{

    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT); //마우스 입력모드로 바꿈
    CursorView(0);

    for (int i = 0; i < sero; i++) {
        for (int j = 0; j < garo; j++) {
            gotoxy(j, i);
            if (gyesangi[i][j] == 1) {
                drw(GRAY, GRAY);
                printf(" ");
            }

            else if (gyesangi[i][j] != 2) {
                if (gyesangi[i][j] == 18) {
                    drw(YELLOW, BLACK);
                    printf("0");
                }
                if (gyesangi[i][j] == 19) {
                    drw(YELLOW, BLACK);
                    printf("1");
                }
                if (gyesangi[i][j] == 20) {
                    drw(YELLOW, BLACK);
                    printf("2");
                }
                if (gyesangi[i][j] == 21) {
                    drw(YELLOW, BLACK);
                    printf("3");
                }
                if (gyesangi[i][j] == 22) {
                    drw(YELLOW, BLACK);
                    printf("-");
                }
                if (gyesangi[i][j] == 23) {
                    drw(YELLOW, BLACK);
                    printf("4");
                }
                if (gyesangi[i][j] == 24) {
                    drw(YELLOW, BLACK);
                    printf("5");
                }
                if (gyesangi[i][j] == 25) {
                    drw(YELLOW, BLACK);
                    printf("6");
                }
                if (gyesangi[i][j] == 26) {
                    drw(YELLOW, BLACK);
                    printf("*");
                }
                if (gyesangi[i][j] == 27) {
                    drw(YELLOW, BLACK);
                    printf("7");
                }
                if (gyesangi[i][j] == 28) {
                    drw(YELLOW, BLACK);
                    printf("8");
                }
                if (gyesangi[i][j] == 29) {
                    drw(YELLOW, BLACK);
                    printf("9");
                }
                if (gyesangi[i][j] == 30) {
                    drw(YELLOW, BLACK);
                    printf("/");
                }
                if (gyesangi[i][j] == 31) {
                    drw(YELLOW, BLACK);
                    printf("+");
                }
                if (gyesangi[i][j] == 32) {
                    drw(YELLOW, BLACK);
                    printf("c");
                }
                if (gyesangi[i][j] == 33) {
                    drw(YELLOW, BLACK);
                    printf("e");
                }

                if (gyesangi[i][j] == 35) {
                    drw(YELLOW, BLACK);
                    printf("=");
                }
                drw(YELLOW, YELLOW);
                printf(" ");
            }

        }
    }
    int xx, yy, i, j, k;
    for (i = 0; i < 7; i++) {
        a[i] = -1;
    }
    while (1) {
        if (cnt > 6) {
            for (i = 0; i < sero; i++) {
                for (j = 0; j < garo; j++) {
                    gotoxy(j, i);
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
            for (i = 0; i < 32; i++) {
                for (j = 0; j < 64; j++) {
                    if (error[i][j] == 1) {
                        gotoxy(j, i);
                        drw(RED, RED);
                        printf(" ");
                    }
                }
            }

            exit(0);
        }
        click(&xx, &yy);
        gotoxy(50, 28);
        drw(BLACK, WHITE);
        printf("%2d %2d\n", xx, yy);
        if (gyesangi[yy + 1][xx + 1] == 3 || gyesangi[yy + 1][xx + 1] == 31) {
            type = 1;
            zari = 6;
            cnt = 0;
            for (k = 3; k < 12; k++) {
                for (j = 5; j < 35; j++) {
                    gotoxy(j, k);
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
            for (i = -1; i <= 8; i++) {
                b[i] = -1;
            }

        }
        if (gyesangi[yy + 1][xx + 1] == 8 || gyesangi[yy + 1][xx + 1] == 22) {
            type = 2;
            zari = 6;
            cnt = 0;
            for (k = 3; k < 12; k++) {
                for (j = 5; j < 35; j++) {
                    gotoxy(j, k);
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
            for (i = -1; i <= 8; i++) {
                b[i] = -1;
            }

        }
        if (gyesangi[yy + 1][xx + 1] == 12 || gyesangi[yy + 1][xx + 1] == 26) {
            type = 3;
            zari = 6;
            cnt = 0;
            for (k = 3; k < 12; k++) {
                for (j = 5; j < 35; j++) {
                    gotoxy(j, k);
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
            for (i = -1; i <= 8; i++) {
                b[i] = -1;
            }

        }
        if (gyesangi[yy + 1][xx + 1] == 16 || gyesangi[yy + 1][xx + 1] == 30) {
            type = 4;
            zari = 6;
            cnt = 0;
            for (k = 3; k < 12; k++) {
                for (j = 5; j < 35; j++) {
                    gotoxy(j, k);
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
            for (i = -1; i <= 8; i++) {
                b[i] = -1;
            }

        }
        if (gyesangi[yy + 1][xx + 1] == 4 || gyesangi[yy + 1][xx + 1] == 32 || gyesangi[yy + 1][xx + 1] == 33) {    //reset
            zari = 6;
            cnt = 0;
            type = 0;
            for (k = 3; k < 12; k++) {
                for (j = 5; j < 35; j++) {
                    gotoxy(j, k);
                    drw(BLACK, BLACK);
                    printf(" ");
                }
            }
            for (i = -1; i <= 8; i++) {
                a[i] = -1;
            }
        }
        if (type == 0) {
            for (i = 0; i <= 6; i++) {
                if (a[i] >= 0 && a[i] < 10) {
                    if (a[i] == 1) oneprint(i);
                    if (a[i] == 2) twoprint(i);
                    if (a[i] == 3) threeprint(i);
                    if (a[i] == 4) fourprint(i);
                    if (a[i] == 5) fiveprint(i);
                    if (a[i] == 6) sixprint(i);
                    if (a[i] == 7) sevenprint(i);
                    if (a[i] == 8) eightprint(i);
                    if (a[i] == 9) nineprint(i);
                    if (a[i] == 0) zeroprint(i);
                }
            }








            if (gyesangi[yy + 1][xx + 1] == 5 || gyesangi[yy + 1][xx + 1] == 19) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 1;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 6 || gyesangi[yy + 1][xx + 1] == 20) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 2;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }

            if (gyesangi[yy + 1][xx + 1] == 7 || gyesangi[yy + 1][xx + 1] == 21) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 3;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 9 || gyesangi[yy + 1][xx + 1] == 23) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 4;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);

                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 10 || gyesangi[yy + 1][xx + 1] == 24) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 5;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 11 || gyesangi[yy + 1][xx + 1] == 25) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 6;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 13 || gyesangi[yy + 1][xx + 1] == 27) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 7;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 14 || gyesangi[yy + 1][xx + 1] == 28) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 8;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 15 || gyesangi[yy + 1][xx + 1] == 29) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 9;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 17 || gyesangi[yy + 1][xx + 1] == 18) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    a[i] = a[i + 1];

                }
                a[zari] = 0;
                for (i = 0; i < 6; i++) {
                    gotoxy(60 + i, 28);
                    drw(BLACK, WHITE);
                    printf("%d", a[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (a[i] >= 0 && a[i] < 10) {
                        if (a[i] == 1) oneprint(i);
                        if (a[i] == 2) twoprint(i);
                        if (a[i] == 3) threeprint(i);
                        if (a[i] == 4) fourprint(i);
                        if (a[i] == 5) fiveprint(i);
                        if (a[i] == 6) sixprint(i);
                        if (a[i] == 7) sevenprint(i);
                        if (a[i] == 8) eightprint(i);
                        if (a[i] == 9) nineprint(i);
                        if (a[i] == 0) zeroprint(i);

                    }
                }


            }
        }
        else {
            if (gyesangi[yy + 1][xx + 1] == 34 || gyesangi[yy + 1][xx + 1] == 35) {
                int n = 1;
                if (type == 1) {

                    gotoxy(60, 31);
                    drw(BLACK, WHITE);
                    printf("%d %d", left, right);
                    type = 0;
                }
            }
            if (gyesangi[yy + 1][xx + 1] == 5 || gyesangi[yy + 1][xx + 1] == 19) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                a[zari] = 1;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }

            if (gyesangi[yy + 1][xx + 1] == 6 || gyesangi[yy + 1][xx + 1] == 20) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 2;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }

            if (gyesangi[yy + 1][xx + 1] == 7 || gyesangi[yy + 1][xx + 1] == 21) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 3;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 9 || gyesangi[yy + 1][xx + 1] == 23) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 4;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);

                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 10 || gyesangi[yy + 1][xx + 1] == 24) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 5;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 11 || gyesangi[yy + 1][xx + 1] == 25) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 6;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 13 || gyesangi[yy + 1][xx + 1] == 27) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 7;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 14 || gyesangi[yy + 1][xx + 1] == 28) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 8;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 15 || gyesangi[yy + 1][xx + 1] == 29) {
                cnt++;
                for (k = 3; k < 12; k++) {
                    for (j = 5; j < 35; j++) {
                        gotoxy(j, k);
                        drw(BLACK, BLACK);
                        printf(" ");
                    }
                }
                for (i = 0; i <= 6; i++) {

                    b[i] = b[i + 1];

                }
                b[zari] = 9;
                for (i = 0; i < 6; i++) {
                    gotoxy(61 + i, 29);
                    drw(BLACK, WHITE);
                    printf("%d", b[i]);
                }
                for (i = 0; i <= 6; i++) {
                    if (b[i] >= 0 && b[i] < 10) {
                        if (b[i] == 1) oneprint(i);
                        if (b[i] == 2) twoprint(i);
                        if (b[i] == 3) threeprint(i);
                        if (b[i] == 4) fourprint(i);
                        if (b[i] == 5) fiveprint(i);
                        if (b[i] == 6) sixprint(i);
                        if (b[i] == 7) sevenprint(i);
                        if (b[i] == 8) eightprint(i);
                        if (b[i] == 9) nineprint(i);
                        if (b[i] == 0) zeroprint(i);
                    }
                }

            }
            if (gyesangi[yy + 1][xx + 1] == 17 || gyesangi[yy + 1][xx + 1] == 18) {
            }
        }

    }
    return 0;
}
