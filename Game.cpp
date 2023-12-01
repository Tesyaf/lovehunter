#include <iostream>
#include <fstream>
#include <conio.h>
#include <direct.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 29
#define WIN_WIDTH 70

#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define DARKYELLOW 6
#define WHITE 7
#define GREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define PINK 13
#define YELLOW 14
#define LIGHTWHITE 15

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int LoveY[2];
int LoveX[2];
bool LoveFlag[2];
char player[4][5] = {
'\\',' ',' ',' ','/',
' ','\\','0','/',' ',
' ','|',' ','|',' ',
' ','A','A','A',' '};

// posisi awal player secara horizontal di tengah layar
int playerPosX = WIN_WIDTH / 2;

// posisi awal player secara vertical di bawah layar
int playerPosY = 25;

// score awal
int score = 0;

void textcolor(int color)
{
	SetConsoleTextAttribute(Console, color);
}

void gotoxy(int x, int y)
{
	/*
		pindahkan kursor ke koordinat x horizontal atau kolom
		dan koordinat y vertikal atau baris
	*/
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(Console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(Console, &lpCursor);
}


//Menggambar border permainan
void drawBorder()
{
	textcolor(GREY);
	// bikin border kiri dan kanan
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			gotoxy(0 + j, i);
			cout << "\xcc";
			gotoxy(WIN_WIDTH - j, i);
			cout << "\xcc";
		}
	}
	// lebar area permainan xx
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		gotoxy(SCREEN_WIDTH,i);
		cout << "\xcc";
	}
	textcolor(WHITE);
}


//Memunculkan Love secara random
void genLove(int index)
{
	/*
		bikin posisi Love di koordinat horizontal x
		minimal di x = 7, karena lebar border kiri adalah 7
		maksimal 59, karena 59 adalah posisi bagian kiri mobil
	*/
	LoveX[index] = 7 + rand() % (43);
}

//Menggambar Love
void drawLove(int index){
	if(LoveFlag[index] == 1){
		textcolor(PINK);
		gotoxy(LoveX[index], LoveY[index]);
		cout << " ** ** ";
		gotoxy(LoveX[index], LoveY[index] + 1);
		cout << " ** ";
		gotoxy(LoveX[index], LoveY[index] + 2);
		cout << "****";
		gotoxy(LoveX[index], LoveY[index] + 3);
		cout << " ** ";
		textcolor(WHITE);
}



int main (){
	setcursor(0,0);
	srand((unsigned)time(NULL));

	do {

		system("cls");
		textcolor(YELLOW);
		gotoxy(10,5);
		cout <<" _                      _    _             _";
		gotoxy(10,6);
 		cout <<"| |                    | |  | |           | |";    
		gotoxy(10,7);
 		cout <<"| |     _____   _____  | |__| |_   _ _ __ | |_ ___ _ __ ";
 		gotoxy(10,8);
 		cout <<"| |    / _ \\ \\ / / _ \\ |  __  | | | | '_ \\| __/ _ \\ '__|";
		gotoxy(10,9);
 		cout <<"| |___| (_) \\ V /  __/ | |  | | |_| | | | | ||  __/ |";
		gotoxy(10,10);
 		cout <<"|______\\___/ \\_/ \\___| |_|  |_|\\__,_|_| |_|\\__\\___|_|";
		gotoxy(10,13);
		cout <<"1. Play Game";
		gotoxy(10,14);
		cout <<"2. Tutorial";
		gotoxy(10,15);
		cout <<"3. Leaderboard";
		gotoxy(10,16);
		cout <<"4. Exit Game";
		textcolor(WHITE);
		char select = getchar();
		
		if (select == '4'){
			
		}
	}while (true);

    return 0;
}
