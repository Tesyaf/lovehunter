#include <iostream>
#include <fstream>
#include <conio.h>
#include <direct.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 29
#define WIN_WIDTH 70

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define DARKYELLOW 6
#define WHITE 7
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define PINK 13
#define YELLOW 14

#define KEY_LEFT 75
#define KEY_RIGHT 77

HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

using namespace std;

string crush;
int lovemove = 0;
int moving = 0;
int LoveY[2];
int LoveX[2];
bool LoveSpawn[2];
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
	textcolor(LIGHTGREEN);
	// bikin border kiri dan kanan
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < 10; j++)
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

	textcolor(LIGHTCYAN);
	gotoxy(WIN_WIDTH + 4, 2);
	cout << "Love Hunter";
	gotoxy(WIN_WIDTH + 4, 4);
	cout << "-----------";
	gotoxy(WIN_WIDTH + 4, 6);
	cout << "-----------";
	gotoxy(WIN_WIDTH + 5, 12);
	cout << "Control ";
	gotoxy(WIN_WIDTH + 4, 13);
	cout << "---------- ";
	gotoxy(WIN_WIDTH + 3, 14);
	cout << " A Key - Left";
	gotoxy(WIN_WIDTH + 3, 15);
	cout << " D Key - Right";

}


//Memunculkan Love secara random
void genLove(int index)
{
	/*
		bikin posisi Love di koordinat horizontal x
		minimal di x = 10, karena lebar border kiri adalah 10
		maksimal 50, karena 50 adalah posisi bagian kiri mobil
	*/
	LoveX[index] = 10 + 4*(rand() % (10));
}

//Menggambar Love
void drawLove(int index){
	if(LoveSpawn[index] == true){
		textcolor(PINK);
		gotoxy(LoveX[index], LoveY[index]);
		cout << " \xdb\xdb \xdb\xdb ";
		gotoxy(LoveX[index], LoveY[index] + 1);
		cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
		gotoxy(LoveX[index], LoveY[index] + 2);
		cout << " \xdb\xdb\xdb\xdb\xdb ";
		gotoxy(LoveX[index], LoveY[index] + 3);
		cout << "   \xdb   ";
		textcolor(WHITE);
	}
}


//hapus bekas pergerakan love
void EraseLove(int ind){

	if (LoveSpawn[ind] == true)
	{
		gotoxy(LoveX[ind], LoveY[ind]);
		cout << "       ";
		gotoxy(LoveX[ind], LoveY[ind] + 1);
		cout << "       ";
		gotoxy(LoveX[ind], LoveY[ind] + 2);
		cout << "       ";
		gotoxy(LoveX[ind], LoveY[ind] + 3);
		cout << "        ";
	}
}

void resetLove(int ind)
{
	EraseLove(ind);
	LoveY[ind] = 1;
	genLove(ind);
}

void drawPlayer()
{
	textcolor(DARKYELLOW);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoxy(j + playerPosX, i + playerPosY);
			cout << player[i][j];
		}
	}
	textcolor(WHITE);
}

void erasePlayer(){
	/*
		hapus bekas pergeseran player
	*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoxy(j + playerPosX, i + playerPosY);
			cout << " ";
		}
	}
}

bool collision(int ind)
{
	/*
		kalau player menangkap love return true, else false
	*/

	// klo posisi love ke-0, berada pada baris tempat mobil
	// berada, terdapat kemungkinan love tertangkap
	if (LoveY[ind] + 4 - playerPosY >= 0 && LoveY[ind] + 4 - playerPosY < 7)
	{
		if (LoveX[ind] + 4 - playerPosX >= 0 && LoveX[ind] + 4 - playerPosX < 9)
		{
			return true;
		}
	}
	return false;
}

void gameover()
{
	string text;

	ofstream LeadBoard("game.dat", ios_base::app);

	system("cls");
	textcolor(CYAN);
	cout << endl;
	cout << "\t\t|-----------------------------------|" << endl;
	cout << "\t\t  Anda Mendapat "<< score <<" Cinta Dari " << crush << endl;
	cout << "\t\t|-----------------------------------|" << endl << endl;
	cout << "\t\tNama Anda: ";
	cin >> text;
	LeadBoard << text << " " << score << endl;
	cout << "\t\tPress any key to go back to menu.";
	textcolor(WHITE);
	getch();

	LeadBoard.close();
}

void updateScore()
{
	gotoxy(WIN_WIDTH + 5, 5);
	textcolor(CYAN);
	cout << "Score: " << score << endl;
	textcolor(WHITE);
}

void namacrush()
{
	system ("cls");
	textcolor(LIGHTBLUE);
	gotoxy(20,7);
	cout << "Masukan nama crushmu : ";
	cin >> crush;
}

void level()
{
	system("cls");
	textcolor(LIGHTBLUE);
	gotoxy(10,5);
	cout << "Choose your level !!!";
	gotoxy(10,6);
	cout << "------------------------";
	textcolor(BLUE);
	gotoxy(10,7);
	cout << "1. Easy ";
	textcolor(WHITE);
	gotoxy(10,8);
	cout << "2. Medium ";
	textcolor(RED);
	gotoxy(10,9);
	cout << "3. Hard ";

	char op = getche();

	if (op == '1')
	{
		moving = 5;
		lovemove = 1;
	}
	else if (op == '2')
	{
		moving = 4;
		lovemove = 1;
	}
	else if (op == '3')
	{
		moving = 4;
		lovemove = 2;
	}
}

void leaderboard(void)
{
	string text;

	ifstream LeadBoard("game.dat");

	system("cls");
	textcolor(CYAN);
	cout << "LEADERBOARD";
	cout << "\n----------------";
	while (LeadBoard >> text)
	{
		cout << "\n " << text;
	}
	cout << "\n\nPress any key to go back to menu";
	textcolor(WHITE);
	getch();
	LeadBoard.close();
}

void play()
{
	playerPosX = -1 + WIN_WIDTH / 2;
	playerPosY = 25;
	score = 0;
	LoveSpawn[0] = true;
	LoveSpawn[1] = false;
	LoveY[0] = LoveY[1] = 1;

	system("cls");
	drawBorder();
	updateScore();
	// muncul love ke 0
	genLove(0);
	// muncul love ke 1
	genLove(1);
	gotoxy(18, 10);
	cout << "Press any key to start";
	getch();
	gotoxy(17, 10);
	cout << "                          ";

	while (true)
	{
		if (kbhit())
		{
			char ch = getch();
			if (ch == 'a' || ch == 'A' || ch == KEY_LEFT)
			{
				// 10 adalah batas border kiri
				if ( playerPosX == 14)
				{
					playerPosX = 10;
				}
				else if ( playerPosX > 10)
				{
					playerPosX -= moving;
				}
			}
			else if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT)
			{
				// 60 adalah batas border kanan
				// 55 karena lebar player 5 jadi dikurang 5
				if (playerPosX == 53){
					playerPosX = 54;
				}
				else if (playerPosX == 52){
					playerPosX = 54;
				}
				else if (playerPosX < 54){
					playerPosX += moving;
				}
			}
		
			// kalo pencet ESC, kembali ke menu utama
			else if (ch == 27)
			{
				break;
			}
		}

		// gambar player
		drawPlayer();

		// gambar player ke-i klo ada
		for (int i = 0; i < 2; i++)
		{
			drawLove(i);
		}

		// cek jika player menangkap love, maka score bertamah
		for (int i = 0; i < 2; i++)
		{
			if (collision(i) == true)
			{
				resetLove(i);
				score++;
				updateScore();
			}
		}

		Sleep(120);

		// hapus gambar player
		erasePlayer();

		// hapus gambar love
		for (int i = 0; i < 2; i++)
		{
			EraseLove(i);
		}

		// jika posisi love ke-0 berada pada vertikal 11
		if (LoveY[0] == 11)
			// jika Love ke-1 tidak ada, maka buat jadi ada
			if (LoveSpawn[1] == false)
				LoveSpawn[1] = true;
                                     
		// jalankan love ke-i, 1 vertikal ke bawah
		for (int i = 0; i < 2; i++)
		{
			if (LoveSpawn[i] == true)
				LoveY[i] += lovemove;
		}

		//love ke-i sampe batas bawah screen maka gameover
		for (int i = 0; i < 2; i++)
		{
			if (LoveY[i] > SCREEN_HEIGHT - 4)
			{
				gameover();
				return;
			}
		}
	}
}

int main ()
{
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
		textcolor(BLACK);
		char select = getche();
		
		if (select == '1'){
			namacrush();
			level();
			play();
		}
		else if (select == '2')
		{
			/* code */
		}
		else if (select == '3'){
			leaderboard();
		}
		else if (select == '4'){
			exit(0);
		}
	}while (true);

    return 0;
}
