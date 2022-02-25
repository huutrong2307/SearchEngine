#include "File.h"
#include "Header.h"
#include "graphic.h"
extern wstring* stopWord;
extern int nStpW;
//Function get file name from a folder
bool readFolder(string address, list& fileNames) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(address.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            string temp = string(ent->d_name);
            if (temp != "." && temp != "..")
                fileNames = addHead(fileNames, temp);
            /* printf("%s\n", ent->d_name);*/
        }
        closedir(dir);
    }
    else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
}
//Function to get all line in file and save in wstring array
void readFile(string address, wstring*& strArr, int& n) {
    _setmode(_fileno(stdin), _O_U16TEXT);//Set u16tf mode
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::wifstream src;
    src.imbue(std::locale(src.getloc(),
        new std::codecvt_utf16<wchar_t, 0x10FFFE, std::codecvt_mode::little_endian >));
    src.open(address, ios_base::in);
    if (src.fail())
    {
        wcout << "Can't open this file!";
        return;
    }
    else {
        wcout.imbue(std::locale(src.getloc(),
            new std::codecvt_utf16<wchar_t, 0x10FFFE, std::codecvt_mode::little_endian>));
        wcin.imbue(std::locale(src.getloc(),
            new std::codecvt_utf16<wchar_t, 0x10FFFE, std::codecvt_mode::little_endian >));
        int flag = 0;
        strArr = NULL;
        n = 0;
        while (!src.eof()) {// loop to get the number of line
            wstring temp;
            getline(src, temp);
            n++;
        }
        src.close();
        src.open(address, ios_base::in);
        strArr = new wstring[n];
        int i = 0;
        while (!src.eof()) {//loop to get line by line of wstring and lower case all characters
            wstring temp = L"";
            getline(src, temp);
            if (flag == 0) {
                temp.erase(0, 1);
                flag = 1;
            }
            if (temp.length() && temp[temp.length() - 1] == '\r')
                temp.erase(temp.length() - 1, 1);//Delete '\r'
            if (temp[0] >= 'A' && temp[0] <= 'Z')//lower case
                temp[0] = temp[0] + 32;
            strArr[i] = temp;
            i++;
        }
    }

}

//Function readfile index.txt and get list file name saved
list getListFileName() {
    fstream f;
    f.open("Documents/index.txt", ios_base::in);//open file index.txt
    list fileName;
    init(fileName);
    while (!f.eof()) {
        string temp;
        getline(f, temp, '\n');//Copy file name in file index to variable temp
        if (temp.compare("") != 0)
            fileName = addHead(fileName, temp);//add file name into list
    }
    f.close();//close file
    return fileName;//return list
}
//Function write new data to file metadata.txt 
void writeToMetaData(string folder, string fileName, list data) {
    fstream f;
    f.seekg(ios::end);// move the pointer to the end of file
    f.open("metadata.txt", ios_base::out | ios_base::app);
    f << "Documents/new train/" << folder << '/' << fileName << '\n';// write the path to the file name into file metadata.txt
    f << getSize(data) << '\n';//write the number of token into file metadata.tx
    nodeString* p = data.head;
    while (p) {// write all tokens to file
        f << p->data << " ";
        p = p->next;
    }
    f << '\n';
    f.close();
}
//Function build data in file index.txt
void buildInDexFile(list& folder, list& fileName) {
    string address;
    _setmode(_fileno(stdin), _O_TEXT);
    _setmode(_fileno(stdout), _O_TEXT);
    address = "Documents\\new train\\";
    init(folder);
    readFolder(address, folder);//read folder new train in documents and save in variable folder
    init(fileName);
    fstream f;
    f.open("Documents/index.txt", ios_base::out);
    nodeString* p = folder.head;
    nodeString* pre = NULL;
    while (p && p->data != ".." && p->data != ".") {//Loop iterating through list folder
        string temp = "Documents\\new train\\" + p->data + "\\";
        readFolder(temp, fileName);//read folder inside new train folder and save list file name in variable fileName
        nodeString* q = fileName.head;
        p->count = 0;
        while (q != pre && q->data != ".." && q->data != ".") {//Loop iterating through list file name
            if (p->data != ".." && p->data != ".")
                f << "Documents/new train/" << p->data << '/' << q->data << '\n';//write file name into file index.txt
            q = q->next;
            p->count++;
        }
        pre = fileName.head;
        p = p->next;
    }
    cout << "Completely!" << endl;
    f.close();
}
//Function build data to  file metadata.txt
void buildMetaDataFile(list& folder, list& fileName) {
    list Data;
    nodeString* p = folder.head;
    nodeString* q = fileName.head;
    while (p) {//loop iterating through list folder inside new train folder
        for (int i = 1; i <= p->count; i++) {//loop iterating through list file name in folder
            init(Data);
            string temp = "Documents/new train/" + p->data + '/' + q->data;
            wstring* line;
            int nLine;
            readFile(temp, line, nLine);//get all line in file and save in wstring array line
            getListToken(Data, line, nLine, stopWord, nStpW);//get list  processed token from wstring array line
            int n = getSize(Data);
            _setmode(_fileno(stdin), _O_TEXT);
            _setmode(_fileno(stdout), _O_TEXT);
            important(Data, n);
            Data = removeNotImportant(Data, 0.0088, 1);//remove word not important and return to list Data
            writeToMetaData(p->data, q->data, Data);//Write path to that file and all tokens in list Data to file metadata.txt
            delete[] line;
            q = q->next;
        }
        p = p->next;
    }
    cout << "Completely!" << endl;
}
// Function add new data to file metadata.txt
bool addToMetaDataFile(string address) {
    wstring* Line;
    int nLine;
    readFile(address, Line, nLine);//get all line in file and save in wstring array line
    list Data;
    init(Data);
    getListToken(Data, Line, nLine, stopWord, nStpW);//get list  processed token from wstring array line
    int n = getSize(Data);//get the amount of processed tokens in list Data
    if (n != 0) {
        _setmode(_fileno(stdin), _O_TEXT);
        _setmode(_fileno(stdout), _O_TEXT);
        important(Data, n);
        Data = removeNotImportant(Data, 0.0088, 1);//remove word not important and return to list Data
        fstream f;
        f.open("metadata.txt", ios_base::app);
        n = getSize(Data);
        f << address << endl;//write the path into file
        f << n << endl;//write the amount of tokens in list to file
        nodeString* p = Data.head;
        while (p) {//Loop iterating through list Data
            f << p->data << " ";//write token into file
            p = p->next;
        }
        f << endl;
        f.close();
    }
    delete[] Line;
    return true;
}
bool addToIndexFile(string address, list& fileName, int& n) {
    fstream f1;
    f1.open(address);
    if (f1.fail()) {//check address input whether possible or not
        cout << "Your file you input don't exist!" << endl;
        f1.close();
        return false;
    }
    fileName = getListFileName();//get list file name from file index.txt 
    nodeString* p = fileName.head;
    while (p) {//loop iterating through list and check whether address has already been in file index.txt or not
        while (p) {
            if (address.compare(p->data) == 0) {
                goToXY(52, 6);
                cout << "File has already added in library!" ;
                goToXY(52, 7);
                return false;
            }
            p = p->next;
        }
    }
    //if not, add to the end of file index.txt
    fstream f;
    f.open("Documents/index.txt", ios_base::app);
    f << address << endl;
    addHead(fileName, address);
    n++;
    f.close();
    return true;
}
//Function delete file from library
bool deleteFromLib(string address, list& fileName, int& n) {
    nodeString* p = fileName.head;
    while (p) {//Loop iterating through list fileName
        if (address.compare(p->data) == 0) {
            deleteNode(fileName, p);//Delete address from list
            n--;
            //Update the data in file index.txt
            nodeString* q = fileName.head;
            fstream f;
            f.open("Documents/index.txt", ios_base::out);
            while (q) {
                f << q->data << '\n';
                q = q->next;
            }
            f.close();
            //Update the data in metadata.txt
            fstream f1, f2;
            f1.open("metadata.txt", ios_base::in);
            f2.open("temp.txt", ios_base::out);
            while (!f1.eof()) {// Copy the data except deleted data from metadata.txt to temp.txt
                string st;
                getline(f1, st);
                if (st != address && st != "")
                    f2 << st << endl;
                else {
                    string tmp1;
                    getline(f1, tmp1);
                    getline(f1, tmp1);
                }
            }
            f1.close();
            f2.close();
            remove("metadata.txt");//Delete file metadata.txt and remove temp.txt to metadata.txt
            rename("temp.txt", "metadata.txt");
            delete p;
            return true;
        }
        p = p->next;
    }
    return false;
}
//Function read data from file metadata.txt 
list readMetaDataFile(string input, dataFile*& listData, int n) {
    fstream f;
    f.open("metadata.txt", ios_base::in);
    listData = new dataFile[n];
    //Lower case the input string
    for (int i = 0; i < input.length(); i++) {
        if (input[i] >= 'A' && input[i] <= 'Z')
            input[i] += 32;
   }
    list dataInput = splitString(input);// Split the input string to tokens and save in a list
    list res;
    init(res);
    int count = 1;
    int i = 0;
    while (!f.eof()) {//Loop iterating over file metadata.txt
        string temp1, temp2, temp3;
        getline(f, temp1);
        if (temp1 != "") {
            listData[i].name = temp1;//Get the saved file name in file metadata.txt
            getline(f, temp2);
            int amount = atoi(temp2.c_str());
            listData[i].amount = amount;//Get the amount of tokens saved
            listData[i].token = new char* [amount];
            for (int j = 0; j < amount; j++) {//Loop to get all tokens in file
                listData[i].token[j] = new char[10];
                getline(f, temp3, ' ');
                strcpy(listData[i].token[j], temp3.c_str());
            }
            double freq = 0;
            //Check whether input exist in file or not
            if (isExistInFile(dataInput, listData[i], freq))
            {
                res = addHead(res, listData[i].name);//If exist, add to the result
                res.head->count = freq;
            }
        }
        getline(f, temp3);
        i++;
    }
    mergeSortList(res);//Sort decrease the list result by the amount of existed token in input string
    return res;
}
void printContent(list res, int page, int pos) {
    textColor(15);
    nodeString* p = res.head;
    for (int i = 0; i < (page - 1) * 10; i++) {//Loop to get the next page
        if (p) {
            p = p->next;
        }
        else break;
    }
    for (int i = 0; i < pos - 1; i++) {//Get the index of the page
        p = p->next;
    }
    string address = p->data;
    textColor(12);
    goToXY(30, 0);
    cout <<"                                 "<< address << endl << endl;
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::wifstream src;
    src.imbue(std::locale(src.getloc(),
        new std::codecvt_utf16<wchar_t, 0x10FFFE, std::codecvt_mode::little_endian >));
    src.open(address, ios_base::in);//Open the file need to read the content
    if (src.fail())
        wcout << "Can't open this file!";
    else {
        textColor(15);
        wchar_t line[10000];
        wcout.imbue(std::locale(src.getloc(),
            new std::codecvt_utf16<wchar_t, 0x10FFFE, std::codecvt_mode::little_endian>));
        wcin.imbue(std::locale(src.getloc(),
            new std::codecvt_utf16<wchar_t, 0x10FFFE, std::codecvt_mode::little_endian >));
        while (!src.eof()) {//Loop to the end of file to print data in file.
            wstring temp;
            getline(src, temp);
            wcout << temp;
        }
        wcout << endl;
    }
}