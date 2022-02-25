#include "Menu.h"
#include "graphic.h"
//Function show menu to choose
void menu() {
	textColor(12);
	/*setFontSize(30);*/
	cout << "                                            SEARCH ENGINE" << endl << endl;
	textColor(3);
	//setFontSize(10);
	cout << "1.Find" << endl;
	cout << "2.Add file to library" << endl;
	cout << "3.Delete file from library" << endl;
	cout << "4.Information" << endl;
	cout << "5.Exit" << endl;
}
//Function select menu 
int selectMenu() {
	goToXY(1, 8);
	int cmd;
	int flag;
	do {
		cout << "Input your selection:" << endl;
		cin >> cmd;
		flag = 0;
		if (cin.fail()) {//if input is not a number
			cin.clear();
			cin.ignore(1000,'\n');
			flag = 1;
			cout << "Wrong. Please input again!" << endl;
		}
		else if (cmd < 0 || cmd>=6) {// if the value of input is out of range
			cout << "Wrong. Please input again!" << endl;
		}
	} while (cmd < 0 || cmd >= 6 || flag == 1);
	return cmd;
}
int runMenu(int cmd, list& fileName, int& n) {
	clock_t start, end;
	//if command =1, that means choice is finding word
	if (cmd == 1) {
		dataFile* listData;
		string input;
		goToXY(51, 3);
		textColor(12);
		cout << "Search Engine:";
		textColor(15);
		cin.ignore();
		getline(cin, input);
		start=clock();
		goToXY(52, 4);
		cout << "             Wait a moment!";
		list res;
		init(res);
		res = readMetaDataFile(input, listData, n);//Get list result
		int size = getSize(res);
		int choice = 1;
		int page = 1;
		end = clock();
		goToXY(54, 19);
		measuringTimeExcution(start, end);
		int flag = 0;
		do {
			_setmode(_fileno(stdin), _O_TEXT);
			_setmode(_fileno(stdout), _O_TEXT);
			menu2(res, size, page,flag);
			choice = runMenu2(res, selectMenu2(), page);
			flag = 1;
			system("cls");
		} while (choice != 0);
		delete[] listData;
		return 1;
	}
	else if (cmd == 2) {
		//if command=2, that means choice is adding file to library
		goToXY(52, 3);
		textColor(12);
		string address;
		cout << "Input the address of the file you want to add to library:";
		goToXY(52, 4);
		cin.ignore();
		textColor(15);
		getline(cin, address);
		start = clock();
		goToXY(52, 5);
		textColor(11);
		cout << "                             Wait a moment!";
		if (addToIndexFile(address, fileName, n) == 1) {
			addToMetaDataFile(address);
			end = clock();
			goToXY(52, 6);
			measuringTimeExcution(start, end);
			goToXY(52, 7);
			cout << "File has been added to library!" << endl;
		}
		fileName = getListFileName();//Update the list file name
		n = getSize(fileName);//Update the amount of file name
		goToXY(52, 8);
		system("pause");
		return 1;
	}
	else if (cmd == 3) {
		//If command=2, that means choice is deleting file from library
		string address;
		goToXY(52, 3);
		textColor(12);
		cout << "Input the address of the file you want to delete from library:";
		cin.ignore();
		textColor(15);
		goToXY(52, 4);
		getline(cin, address);
		start = clock();
		goToXY(52, 5);
		textColor(11);
		cout << "                            Wait a moment!";
		if (deleteFromLib(address, fileName, n) == true) {
			end = clock();
			goToXY(52, 6);
			measuringTimeExcution(start, end);
			goToXY(52, 7);
			cout << "File has been deleted from library!" << endl;
		}
		else {
			end = clock();
			goToXY(52, 6);
			measuringTimeExcution(start, end);
			goToXY(52, 7);
			cout << "File don't exist in library!" << endl;
		}	
		fileName = getListFileName();//Update the list of file name
		n = getSize(fileName);//Update the amount of file name
		goToXY(52, 8);
		system("pause");
		return 1;
	}
	else if (cmd == 4) {
		goToXY(70, 3);
		textColor(12);
		cout << " UNIVERSITY OF SCIENCE";
		goToXY(75, 6);
		textColor(9);
		cout << "DO AN MON HOC";
		goToXY(75, 7);
		cout << "SEARCH ENGINE";
		goToXY(60, 9);
		textColor(10);
		cout << "Lecturer: Vo Hoai Viet";
		goToXY(60, 10);
		cout << "Student: Le Huu Trong                            ID:20120607";
		goToXY(60, 11);
		cout << "Student: Le Ngoc Duc                             ID:20120059";
		goToXY(60, 13);
		textColor(15);
		system("pause");
		return 1;
	}
	else if (cmd == 5) {
	goToXY(60, 3);
	textColor(10);
		char kt = ' ';
		cout << "Press F to exit!";
		goToXY(60, 4);
		cin >> kt;
		if (kt == 'f' || kt == 'F')
			return 0;
		else return 1;
	}
}
//Function show menu 2
void menu2(list res, int n, int page,int flag) {
	int count = 0;
	nodeString* p = res.head;
	textColor(11);
	if(flag==0)
	goToXY(54, 5);
	cout << "0. Exit" << endl;
	for (int i = 0; i < (page - 1) * 10; i++) {//Loop to get the next page
		if (p) {
			p = p->next;
		}
		else break;
	}
	for (int i = 0; i < 10; i++) {//Print the possible choice 
		if (p) {
			if(flag==0)
			goToXY(54, 6+i);
			cout << i + 1 << ". " << p->data << endl;
			p = p->next;
		}
		else break;
	}
	if (n % 10 > 0) {
		n = n / 10 + 1;
	}
	if (page < n) {
		if (flag == 0)
		goToXY(54, 16);
		cout << "11. Next page" << endl;
	}
	if (page > 1 && page <= n) {
		if (flag == 0)
		goToXY(54, 17);
		cout << "12. Previous page" << endl;
	}
	if (flag == 0)
	goToXY(54, 18);
	cout << "............................................" << "page " << page << " / " << n << endl;
	if (flag == 0)
		goToXY(54, 20);
	cout << "Input your selection:";
}
//Function select menu 2
int selectMenu2() {
	int cmd;
	int flag;
	do {
		cin >> cmd;
		flag = 0;
		if (cin.fail()) {//if input is not a number
			cin.clear();
			cin.ignore(1000, '\n');
			flag = 1;
			cout << "Wrong. Please input again!" << endl;
		}
		else if (cmd < 0 || cmd > 12) {// if the value of input is out of range
			cout << "Wrong. Please input again!" << endl;
		}
	} while (cmd < 0 || cmd > 12 || flag == 1);
	return cmd;
}
//Function run menu 2
int runMenu2(list res, int cmd, int& page) {
	system("cls");
	if (cmd == 0) {
		return 0;
	}
	else if (cmd == 11) {
		page = page + 1;
		return 1;
	}
	else if (cmd == 12) {
		page = page - 1;
		return 1;
	}
	else {
		printContent(res, page, cmd);//Print the content of file
		system("pause");
		return 1;
	}
}