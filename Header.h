#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "dirent.h"
#include <iostream>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <codecvt>
#include <locale>
#include<fstream>
#include <stack>
#include <wchar.h>
#include <corecrt_wstring.h>
#include <regex>
#include <iterator>
#include <string>
#include <time.h>
#include <iomanip>
using namespace std;
struct nodeString {
	string data;
	double count;
	nodeString* next;
};
struct nodeWstring {
	wstring data;
	nodeWstring* next;
};
struct list {
	nodeString* head;
	nodeString* tail;
};
struct queue {
	nodeWstring* head;
	nodeWstring* tail;
};
struct dataFile {
	string name;
	int amount;
	char** token;
};
void init(list& l);
bool checkEmpty(list l);
nodeString* createNodeString(string x);
int getSize(list l);
list addHead(list l, string x);
list addTail(list& l, nodeString* Source);
void initQueue(queue& q);
bool isEmpty(const queue& q);
nodeWstring* createNodeWstring(wstring x);
bool push(queue& q, wstring x);
bool pop(queue& q);
wstring Front(const queue q);
void output(list l);
typedef basic_string<wchar_t> wstring;
bool isExit(wstring s, queue q);
void removeStopWord(wstring& text, wstring* q, int n);
void convertString(queue token, list& res);
wstring RemoveVietnameseTone(const wstring& text);
queue splitSearchWord(wstring s);
queue removeTone(queue token);
bool isTokens(wstring text, int idx, int l);
void sortDecrease(wstring*& q, int n);
void swapWstring(wstring& a, wstring& b);
void swapCountArray(int& a, int& b);
void getListToken(list& res, wstring* line, int nLine, wstring* stopWord, int nStpW);
void deleteNode(list& l, nodeString* p);
void important(list& q, int n);
list removeNotImportant(list q, double start, double end);
list splitString(string str);
bool isExistInFile(list input, dataFile& data, double& freq);
void mergeList(list a, list b, list& c);
void mergeSortList(list& a);


void merge(wstring*& array, int const left, int const mid, int const right);
void mergeSortWstring(wstring*& array, int const begin, int const end);

void measuringTimeExcution(clock_t start, clock_t end);