#define _CRT_SECURE_NO_WARNINGS
#include "graphic.h"
#include "Header.h"
//Function set text color
void textColor(int x) {
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}
//Function move the pointer to position (x,y)
void goToXY(int x, int y) {
	HANDLE hConsoleInput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleInput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleInput, Cursor_an_Pos);
}
//Function create a line
void line(int x,int y) {
	char c = char(176);
	for (int i = 3; i <= y; i++) {
		goToXY(x, i);
		cout << c;
	}
}
// Function disable resize window
void DisableResizeWindow()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
//Function disable control button
void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}