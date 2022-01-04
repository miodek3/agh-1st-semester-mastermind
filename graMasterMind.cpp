#include <iostream>
#include <windows.h>
#include <time.h>
#include  <string>
using namespace std;
char kolory_legenda[8] = { 'b', 'g', 'r', 'w', 'k','y', 'p','o' };
const int COLS = 4;
const int ROWS = 9;
const int COLORS_NO = 8;
const char NO_VALUE = '_';
const char TRAFIONY_KOLOR = '&';
const char TRAFIONE_POLE_KOLOR = '*';
char* podaj_kolory();
void uzupelnienieTablicy(char* kolory, char** board, int rowNo);
bool checkWin(char* kolory, char* wyl_kolor);
void printboard(char** board, char** hints);
char** initMatrix();
void printLegend();
char* analyzeColorsAndGetHints(char *kolory, char *wyl_kolor);



int main()
{
	char** hints = initMatrix();
	int* wyl_liczby = new int[4];
	char* wyl_kolor = new char[4];
	printLegend();
	srand(time(NULL));

	for (int i = 0; i < 4; i++)
	{
		wyl_liczby[i] = rand() % 8; //losowanie poprawnych kolorow przez komputer, kazda liczba odpowiada danemu kolorowi.
	}
	cout << "Wylosowane liczby to:" << endl;

	for (int i = 0; i < 4; i++)
	{
		wyl_kolor[i] = kolory_legenda[wyl_liczby[i]];
	}
	for (int i = 0; i < 4; i++)
	{
		cout << wyl_kolor[i] << " ";
	}
	cout << endl;

	bool guessed = false;
	int attempt = 0;

	char** board = initMatrix();
	printboard(board, hints);
	while (!guessed && attempt < 9)
	{
		cout << "Próba nr " << attempt + 1 << endl;

		char* kolory = podaj_kolory(); //tu sa przechowywane kolory podane przez uzytkownika
		uzupelnienieTablicy(kolory, board, attempt);
		char* currentHints = analyzeColorsAndGetHints(kolory, wyl_kolor);
		uzupelnienieTablicy(currentHints, hints, attempt);
		
		printboard(board, hints);
		attempt++;
		guessed = checkWin(kolory, wyl_kolor);
	}
	if (guessed == true) cout << "Brawo zgadles za " << attempt << " razem!" << endl;
	else cout << "Niestety przegrales" << endl;
	return 0;
}
char* podaj_kolory()
{
	char* kolory = new char[4];
	for (int i = 0; i < 4; i++)
	{
		cout << "Podaj " << i + 1 << " kolor(Podaj skrot!): ";
		cin >> kolory[i];
	}
	return kolory;
}

void uzupelnienieTablicy(char* symbole, char** tablica, int rowNr)
{
	for (int i = 0; i < COLS; i++)
	{
		tablica[rowNr][i] = symbole[i];
	}


}
bool checkWin(char* kolory, char* wyl_kolor) {
	int counter = 0;
	for (int i = 0; i < COLS; i++)
	{
		if (kolory[i] == wyl_kolor[i])
		{
			counter++;
		}
	}
	return counter == 4;
}
void printboard(char** board, char** hints)
{
	for (int i = 0; i < ROWS; i++)
	{
		cout << i+1 << ": ";
		for (int j = 0; j < COLS; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << " | ";
		for (int j = 0; j < COLS; j++)
		{
			cout << " " << hints[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl;
}
char** initMatrix()
{
	char** board = new char* [ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		board[i] = new char[COLS];
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = NO_VALUE;
		}
	}
	return  board;
}
void printLegend()
{
	cout << "Witaj w grze Mastermind! Na odgadniecie czterech kolorow masz 9 prob." << endl;
	cout << "Kazdy kolor ma swoj skrot:" << endl;
	cout << "blue - b" << endl;
	cout << "green - g" << endl;
	cout << "red- r" << endl;
	cout << "white - w" << "\t\t"<<"*-oznacza poprawny kolor i poprawnie podane miejsce"<<endl;
	cout << "pink - k" << "\t\t"<<"&-oznacza poprawny kolor, ale podany na zlym miejscu"<<endl;
	cout << "yellow - y" << endl;
	cout << "purple - p" << endl;
	cout << "orange - o" << endl;
}
char* analyzeColorsAndGetHints(char *kolory,char* wyl_kolor)
{
	int g = 0;
	int k = 0;
	char* currenthints = new char[COLS];
	for (int i = 0; i < COLS;i++)
	{
		currenthints[i] = NO_VALUE;
	}
	for (int i = 0;i < COLS;i++)
		
	{
		char kolor = wyl_kolor[i];
		for (int j = 0; j < COLS;j++)
		{
			if (kolory[j] == kolor)
			{
				currenthints[k] = TRAFIONY_KOLOR;
				k++;
				break;
			}
		}
		
	}
	for (int i = 0; i < COLS; i++)
	{
		if (kolory[i] == wyl_kolor[i])
		{
			currenthints[g] = TRAFIONE_POLE_KOLOR;
			g++;
		}
	}
	return currenthints;
}
