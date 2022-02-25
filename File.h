#pragma once
#include "Header.h"
#include "dirent.h"
void readFile(string address, wstring*& strArr, int& n);
list getListFileName();
bool readFolder(string address, list& fileNames);
void buildInDexFile(list& folder, list& fileName);
void buildMetaDataFile(list& folder, list& fileName);
bool deleteFromLib(string address, list& fileName, int& n);
bool addToMetaDataFile(string address);
bool addToIndexFile(string address, list& fileName, int& n);
list readMetaDataFile(string input, dataFile*& listData, int n);
void printContent(list res, int page, int pos);
