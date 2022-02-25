#pragma once
#include "Header.h"
#include "File.h"

void menu();
int selectMenu();
int runMenu(int cmd, list& fileName, int& n);
void menu2(list res, int n, int page,int flag);
int selectMenu2();
int runMenu2(list res, int cmd, int& page);