#include "Header.h"
extern wstring* stopWord;
extern int nStpW;
//Function check whether wstring s exist in queue q
bool isExit(wstring s, queue q) {
    while (!isEmpty(q)) {
        if (s.compare(Front(q)) == 0)
            return true;
        pop(q);
    }
    return false;
}
//Function check whether a wstring is token
bool isTokens(wstring text, int idx, int l) {
    if (idx == 0 || idx == l - 1)
        return true;
    wchar_t preC = text[idx - 1];//previos character
    wchar_t nextC = text[idx + l];//next character
    if ((preC == L' ' || preC == L'.' || preC == L',' || preC == L';' || preC == L':') && (nextC == L' ' || nextC == L'.' || nextC == L',' || nextC == L';' || nextC == L':'))
        return true;
    return false;
}
//Function remove all stop word in a wstring text
void removeStopWord(wstring& text, wstring* q, int n) {
    for (int i = 0; i < n; i++) {
        int idx = text.find(q[i]);//find the index of stop word in text
        int l = q[i].length();
        while (idx != -1 && isTokens(text, idx, l)) {
            if (idx == 0) {//if index=0
                text.erase(idx, q[i].length() + 1);
                idx = text.find(q[i]);
                l = q[i].length();
            }
            else if (idx == l - 1) {//if index =l-1
                text.erase(idx - 1, q[i].length());
                idx = text.find(q[i]);
                l = q[i].length();
            }
            else {//the remaining case
                text.erase(idx - 1, q[i].length() + 1);
                idx = text.find(q[i]);
                l = q[i].length();
            }

        }
    }
}
//Function convert queue wstring to list string
void convertString(queue token, list& res)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    wstring_convert<convert_type, wchar_t> converter;
    while (!isEmpty(token)) {//loop over the queue
        string temp = "";
        temp = converter.to_bytes(Front(token));
        for (int i = 0; i < temp.length(); i++) {//Lower case all token
            if (temp[i] >= 'A' && temp[i] <= 'Z')
                temp[i] += 32;
        }
        res = addHead(res, temp);//add the token to the result
        pop(token);
    }
}
//Function remove Vietnamese Tone in a wstring text
wstring RemoveVietnameseTone(const wstring& text) {
    wstring result(text);
    result = regex_replace(result, wregex(L"à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ|/g"), L"a");
    result = regex_replace(result, wregex(L"À|Á|Ạ|Ả|Ã|Â|Ầ|Ấ|Ậ|Ẩ|Ẫ|Ă|Ằ|Ắ|Ặ|Ẳ|Ẵ|/g"), L"A");
    result = regex_replace(result, wregex(L"è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ|/g"), L"e");
    result = regex_replace(result, wregex(L"È|É|Ẹ|Ẻ|Ẽ|Ê|Ề|Ế|Ệ|Ể|Ễ|/g"), L"E");
    result = regex_replace(result, wregex(L"ì|í|ị|ỉ|ĩ|/g"), L"i");
    result = regex_replace(result, wregex(L"Ì|Í|Ị|Ỉ|Ĩ|/g"), L"I");
    result = regex_replace(result, wregex(L"ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ|/g"), L"o");
    result = regex_replace(result, wregex(L"Ò|Ó|Ọ|Ỏ|Õ|Ô|Ồ|Ố|Ộ|Ổ|Ỗ|Ơ|Ờ|Ớ|Ợ|Ở|Ỡ|/g"), L"O");
    result = regex_replace(result, wregex(L"ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ|/g"), L"u");
    result = regex_replace(result, wregex(L"Ù|Ú|Ụ|Ủ|Ũ|Ư|Ừ|Ứ|Ự|Ử|Ữ|/g"), L"U");
    result = regex_replace(result, wregex(L"ỳ|ý|ỵ|ỷ|ỹ|/g"), L"y");
    result = regex_replace(result, wregex(L"Ỳ|Ý|Ỵ|Ỷ|Ỹ|/g"), L"y");
    result = regex_replace(result, wregex(L"đ"), L"d");
    result = regex_replace(result, wregex(L"Đ"), L"D");
    return result;
}
//Function remove Vietnamese tone in a wstring queue
queue removeTone(queue token) {
    queue res;
    initQueue(res);
    while (!isEmpty(token)) {
        wstring temp = RemoveVietnameseTone(Front(token));//Remove Vietnamese tone in a wstring
        push(res, temp);
        pop(token);
    }
    return res;//return result
}
//Function split wstring into tokens
queue splitSearchWord(wstring s)
{
    queue res;
    initQueue(res);
    wregex word_regex(L"(\\w+)");
    auto words_begin =
        wsregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::wsregex_iterator();
    for (wsregex_iterator i = words_begin; i != words_end; ++i) {
        wsmatch match = *i;
        wstring match_str = match.str();
        push(res, match_str);
    }
    return res;
}
//Function swap value a & b
void swapCountArray(int& a, int& b)
{
    int temp = b;
    b = a;
    a = temp;
}
//Function swap wstring a and b
void swapWstring(wstring& a, wstring& b)
{
    wstring temp = b;
    b = a;
    a = temp;
}
//Function get list token from wstring array
void getListToken(list& res, wstring* line, int nLine, wstring* stopWord, int nStpW) {
    queue token;
    initQueue(token);
    for (int i = 0; i < nLine; i++) {
        removeStopWord(line[i], stopWord, nStpW);//remove stop word in a line
        token = splitSearchWord(line[i]);//split line to tokens
        token = removeTone(token);//remove Vietnamese tone
        convertString(token, res);//convert from wstring to string
    }
}
//Function evalute the importance of token in a string
void important(list& q, int n)
{
    int size = n;
    int i = 0, j;
    nodeString* p = q.head;
    nodeString* temp;
        while (p != NULL)
        {
            temp = p;
            j = i + 1;
            while ((temp->next != NULL))
            {
                if (p->data == (temp->next)->data)//if is exist another token in list like the current, then delete that token and update the amount of current token  
                {
                    nodeString* newTemp = temp->next;
                    temp->next = newTemp->next;
                    newTemp = NULL;
                    delete newTemp;
                    p->count++;
                }
                else {
                    temp = temp->next;
                    j++;
                }
            }
            i++;
            p = p->next;
        }
    // Calculate the frequency
    nodeString* h = q.head;
    while (h != NULL)
    {
        h->count = (h->count) / size;
        h = h->next;
    }
}
//Function remove token is not important in text
list removeNotImportant(list q, double start, double end)
{
    list ress;
    init(ress);
    nodeString* p = q.head;
    while (p != NULL)//Loop iterating over list
    {
        if (((p->count) > start) && ((p->count) < end))//if the frequency of a token is greater than start and lower than end, then add it to the list result
        {
            ress = addHead(ress, p->data);
        }
        p = p->next;
    }
    return ress;//return result
}

//Function split a string to a list of token
list splitString(string str) {
    string temp = "";
    list res;
    init(res);
    for (int i = 0; i < str.length(); i++) {
        temp = temp + str[i];
        if (str[i + 1] == ' ' ||str[i+1]=='.' || str[i + 1] == ',' || i == str.length() - 1) {
            res = addHead(res, temp);
            temp = "";
            i++;
        }
    }
    return res;
}
//Function check whether a string input is exist in file or not
bool isExistInFile(list input, dataFile& data, double& freq) {
    nodeString* p = input.head;
    double nExist = 0;
    double nToken = 0;
    while (p) {
        int flag = 0;
        for (int i = 0; i < data.amount; i++) {
            if (p->data == data.token[i])
                flag = 1;
        }
        if (flag == 1)
            nExist++;
        nToken++;
        p = p->next;
    }
    freq = nExist / nToken;//frequency = amount exist token / total amount in file
    if (freq >= 0.5)//if frequency is greater than 0.5, return true, else return false
        return true;
    return false;

}
//Function compound 2 decrease list into another list  
void mergeList(list a, list b, list& c) {
    nodeString* p1 = a.head;
    nodeString* p2 = b.head;
    init(c);
    while (p1 && p2) {
        if (p1->count > p2->count) {
            addTail(c, p1);
            p1 = p1->next;
        }
        else {
            addTail(c, p2);
            p2 = p2->next;
        }
    }
    while (p1) {
        addTail(c, p1);
        p1 = p1->next;
    }
    while (p2) {
        addTail(c, p2);
        p2 = p2->next;
    }
    delete p1, p2;
}
//Decrease merge sort list function 
void mergeSortList(list& a) {
    if (getSize(a) == 1 || getSize(a) == 0)
        return;
    else {
        int n = getSize(a) / 2;
        list a1, a2;
        nodeString* p = a.head;
        for (int i = 0; i < n - 1; i++) {
            p = p->next;
        }
        a1.head = a.head;
        a2.head = p->next;
        p->next = NULL;
        mergeSortList(a1);
        mergeSortList(a2);
        list temp;
        mergeList(a1, a2, temp);
        a = temp;

    }
}
//Function sort decrease wstring array from index mid to right
void merge(wstring*& array, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;


    auto* leftArray = new wstring[subArrayOne],
        * rightArray = new wstring[subArrayTwo];


    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}
//Decrease merge sort wstring array function
void mergeSortWstring(wstring*& array, int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSortWstring(array, begin, mid);
    mergeSortWstring(array, mid + 1, end);
    merge(array, begin, mid, end);
}
//Sort decrese function
void sortDecrease(wstring*& q, int n)
{
    mergeSortWstring(q, 0, n - 1);
}
//Function initialize the value of list
void init(list& l) {
    l.head = NULL;
}
//Function check whether a list is emtpy or not
bool checkEmpty(list l) {
    return l.head == NULL;
}
//Funtion create a new node string
nodeString* createNodeString(string x) {
    nodeString* temp = new nodeString;
    if (temp == NULL) {
        cout << "No available memory!" << endl;
        return NULL;
    }
    temp->data = x;
    temp->next = NULL;
    temp->count = 1;
    return temp;
}
//Function get amount of element in a list
int getSize(list l) {
    if (checkEmpty(l))
        return 0;
    nodeString* p = l.head;
    int n = 0;
    while (p != NULL) {
        if (p->data != "")
            n++;
        p = p->next;
    }
    return n;
}
//Function add a string to the head of list
list addHead(list l, string x) {
    if (checkEmpty(l)) {
        l.head = l.tail = createNodeString(x);
        return l;
    }
    else if (l.head->next == NULL)
    {
        nodeString* temp = createNodeString(x);
        l.tail = l.head;
        l.head = temp;
        l.head->next = l.tail;
        return l;
    }
    else {
        nodeString* temp = createNodeString(x);
        temp->next = l.head;
        l.head = temp;
        return l;
    }
}
// Function add a string to the tail of list
list addTail(list& l, nodeString* Source) {
    string x = Source->data;
    double count = Source->count;
    if (checkEmpty(l)) {
        l.head = l.tail = createNodeString(x);
        l.head->count = l.tail->count = count;
        return l;
    }
    else if (l.head->next == NULL)
    {
        nodeString* temp = createNodeString(x);
        temp->count = count;
        l.tail = temp;
        l.head->next = l.tail;
        return l;
    }
    else {
        nodeString* p = l.tail;
        nodeString* temp = createNodeString(x);
        temp->count = count;
        p->next = temp;
        l.tail = temp;
        return l;
    }
}
//Function print all element of a list
void output(list l) {
    nodeString* p = l.head;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
}
//Function initialize a queue
void initQueue(queue& q) {
    q.head = NULL;
    q.tail = NULL;
}
//Function check whether a queue is empty or not
bool isEmpty(const queue& q) {
    if (q.head == NULL || q.tail == NULL)
        return true;
    return false;
}
//Function create a new node wstring
nodeWstring* createNodeWstring(wstring x) {
    nodeWstring* temp = new nodeWstring;
    temp->data = x;
    temp->next = NULL;
    return temp;
}
//Function push a wstring into a queue
bool push(queue& q, wstring x) {
    if (isEmpty(q) == true) {
        nodeWstring* temp = createNodeWstring(x);
        q.head = q.tail = temp;
    }
    else {
        nodeWstring* temp = createNodeWstring(x);
        q.tail->next = temp;
        q.tail = temp;
    }
    return true;
}
//Function pop a wstring from a queue
bool pop(queue& q) {
    if (isEmpty(q) == true) {
        return false;
    }
    nodeWstring* p = q.head;
    q.head = q.head->next;
    delete p;
    if (q.head == NULL)
        q.head = q.tail = NULL;
    return true;
}
//Function get a wstring in front of queue 
wstring Front(const queue q) {
    if (isEmpty(q) == true)
        return L"";
    wstring top = q.head->data;
    return top;
}
//Function delete node in a list
void deleteNode(list& q, nodeString* a)
{
    if (q.head->data == a->data)
    {
        nodeString* temp = q.head;
        q.head = q.head->next;
        temp->next = NULL;
        temp = NULL;
        delete temp;
    }
    else
    {
        nodeString* p = q.head;
        while ((p->next)->data != a->data)
            p = p->next;
        if ((p->next)->data == a->data)
        {
            nodeString* temp = p->next;
            p->next = temp->next;
            temp->next = NULL;
            temp = NULL;
            delete temp;
        }
    }
}
void measuringTimeExcution(clock_t start, clock_t end) {
    cout << "Time:" << fixed << setprecision(5) << double(end - start)/double(CLOCKS_PER_SEC) <<" s"<< endl;
}