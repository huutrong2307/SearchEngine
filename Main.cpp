#include "Header.h"
#include "File.h" 
#include "Menu.h"
#include "graphic.h"
wstring* stopWord;
int nStpW;
int main() {
	SetConsoleTitle(L"SEARCH ENGINE");
	DisableResizeWindow();
	DisableCtrButton(0,1,1);
	readFile("stopword.txt", stopWord, nStpW);//get list stop word from file
	sortDecrease(stopWord, nStpW);
	list fileName;
	init(fileName);
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
	fileName = getListFileName();//Get list file name from file index.txt
	int n = getSize(fileName);//Get the amount of file name in file index.txt
	int selection = 1;
	while (selection) {//Loop until user want to exit
		menu();
		line(50, 30);
		selection = runMenu(selectMenu(), fileName, n);
		system("cls");
	}
	delete[] stopWord;
}