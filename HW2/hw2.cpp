/**
*  Author：范真瑋
*  Date：Oct. 7, 2016
*  Purpose：製作一個「集合」類別 (set class)，使其能進行「屬於」、「聯集」、
*          「交集」、「差集」、「包含」等五種運算。
*/

#include <iostream>
#include <string>
#include <algorithm>  //sort
#define L 256  //陣列長度
using namespace std;

class TSet  //集合
{
    public:
        TSet();  //default constructor
        TSet(string str);  //for setting its name
        ~TSet();  //destructor
        void setSet(char* ch);  //設定集合元素
        char* getSet() const;  //回傳集合資料
        void setName(string str);  //set its name
        string getName() const;  //return its name
        TSet& in(char& ch);  //belong to
        static int count;  //統計次數改變輸出格式
        friend istream& operator >> (istream& in, TSet& A);  //operator overloading
        friend ostream& operator << (ostream& out, TSet& A);
        TSet& operator +(const TSet& B);  //union
        TSet& operator *(const TSet& B);  //intersection
        TSet& operator -(const TSet& B);  //difference
        TSet& operator >=(const TSet& B);  //contain
    private:
        char* chSet;  //集合資料
        string name;  //its name
};

int TSet::count = 0;  //初始為0

int main(void)
{
    int N = 0;  //測資數量

    cin >> N;
    for(int i = 0; i < N; i++)
    {
        char x;  //元素
        /* Initial a Set and set its name */
        TSet A("A"), B("B");

        cin.ignore();
        cin >> A >> B;  //輸入集合元素
        cin.get(x);  //輸入元素

        TSet C, D;
        C = A + B;  //union
        D = A * B;  //intersection

        cout << "Test Case " << (i+1) << ":" << endl;  //印出運算結果
        cout << A << endl;  //A
        cout << B << endl;  //B
        cout << C << endl;  //A+B
        cout << D << endl;  //A*B
        cout << (A - B) << endl;  //difference
        cout << (B - A) << endl;
        cout << (A >= B) << endl;  //contain
        cout << (B >= A) << endl;
        cout << A.in(x) << endl;  //belong to
        cout << B.in(x) << endl;

        cout << endl;
        TSet::count = 0;  //次數歸零
    }

    return 0;
}

TSet::TSet()  //default constructor
{
    name = "";
    chSet = new char[L];
    for(int i = 0; i < L; i++)
        chSet[i] = '\0';
}

TSet::TSet(string str)  //for setting its name
{
    name = str;
    chSet = new char[L];
    for(int i = 0; i < L; i++)
        chSet[i] = '\0';
}

TSet::~TSet()  //destructor
{
    delete[] chSet;
    name = "";
}

void TSet::setSet(char* ch)  //設定集合元素
{
    char temp[L] = {'\0'};
    for(int i = 0; i < L; i++)
        chSet[i] = '\0';

    for(int i = 0; ch[i] != '\0'; i++)
        temp[i] = ch[i];

    int index;

    index = 0;
    while(temp[index] != '\0')
        index++;
    sort(temp, temp+index);
    index = 0;
    chSet[0] = temp[0];
    for(int i = 0; temp[i] != '\0'; i++)  //重複的字母只放入一次
    {
        if(chSet[index] == temp[i])
            continue;
        else
        {
            index++;
            chSet[index] = temp[i];
        }
    }
}

char* TSet::getSet() const  //回傳集合資料
{
    return chSet;
}

void TSet::setName(string str)  //set its name
{
    name = "";
    name = str;
}

string TSet::getName() const  //return its name
{
    return name;
}

TSet& TSet::in(char& ch)  //belong to
{
    TSet* temp = new TSet();
    char* ch1 = getSet();
    bool check = false;
    string symbol = "";  //for ‘
    string name = "";

    for(int i = 0; ch1[i] != '\0'; i++)  //checking
    {
        if(ch == ch1[i])
        {
            check = true;
            break;
        }
    }
    if(check)  //in
    {
        symbol = "‘";
        name = symbol + ch + "’ is in " + getName();
        (*temp).setName(name);
    }
    else  //not in
    {
        symbol = "‘";
        name = symbol + ch + "’ is not in " + getName();
        (*temp).setName(name);
    }

    return *temp;
}

istream& operator >> (istream& in, TSet& A)  //operator overloading
{
    char ch[L];

    in.getline(ch, L);  //集合的內容可能含有空白字元或其他符號，但不含換行字元
    A.setSet(ch);

    return in;
}

ostream& operator << (ostream& out, TSet& A)
{
    if(TSet::count < 6)  //檢查次數決定輸出格式
    {
        char* ch = A.getSet();

        cout << A.getName() << ": {";  //印出集合元素
        for(int i = 0; ch[i] != '\0'; i++)
            cout << ch[i];
        cout << "}";
    }
    else
        cout << A.getName();

    TSet::count++;  //統計次數+1

    return out;
}

TSet& TSet::operator +(const TSet& B)  //union
{
    TSet* temp = new TSet();
    char* ch1 = getSet();
    char* ch2 = B.getSet();
    char ch[L] = {'\0'};
    int i, j, index = 0;

    while(ch1[index] != '\0')  //複製元素
    {
        ch[index] = ch1[index];
        index++;
    }

    for(i = 0, j = index; ch2[i] != '\0'; i++, j++)  //串接元素
        ch[j] = ch2[i];
    sort(ch, ch+j);
    (*temp).setName("A+B");
    (*temp).setSet(ch);

    return *temp;
}

TSet& TSet::operator *(const TSet& B)  //intersection
{
    TSet* temp = new TSet();
    char* ch1 = getSet();
    char* ch2 = B.getSet();
    char ch[L] = {'\0'};
    int index = 0;

    for(int i = 0; ch1[i] != '\0'; i++)
    {
        for(int j = 0; ch2[j] != '\0'; j++)
        {
            if(ch1[i] == ch2[j])  //找到相同元素放入ch
            {
                ch[index] = ch1[i];
                index++;
            }
        }
    }
    (*temp).setName("A*B");
    (*temp).setSet(ch);

    return *temp;
}

TSet& TSet::operator -(const TSet& B)  //difference
{
    TSet* temp = new TSet();
    char* ch1 = getSet();
    char* ch2 = B.getSet();
    char ch[L] = {'\0'};
    int index = 0;
    bool check;  //檢查是否有相同的元素
    string name = getName()+"-"+B.getName();  //its name

    for(int i = 0; ch1[i] != '\0'; i++)
    {
        check = true;  //初始為true
        for(int j = 0; ch2[j] != '\0'; j++)
        {
            if(ch1[i] == ch2[j])
                check = false;  //有相同的元素
        }
        if(check)
        {
            ch[index] = ch1[i];  //不相同的元素放入ch
            index++;
        }
    }

    (*temp).setName(name);
    (*temp).setSet(ch);

    return *temp;
}

TSet& TSet::operator >=(const TSet& B)  //contain
{
    TSet* temp = new TSet();
    char* ch1 = getSet();
    char* ch2 = B.getSet();
    bool check;  //檢查是否有相同的元素
    string name1 = getName();
    string name2 = B.getName();
    string str = "";  //for setting its name

    for(int i = 0; ch2[i] != '\0'; i++)  //檢查ch1是否包含ch2
    {
        check = false;  //初始為false
        for(int j = 0; ch1[j] != '\0'; j++)
        {
            if(ch2[i] == ch1[j])
            {
                check = true;  //有相同的元素
                break;
            }
        }
        if(!check)  //有不相同的元素
            break;
    }
    if(check)  //contains
    {
        str = name1 + " contains " + name2;  //its name
        (*temp).setName(str);
    }
    else  //does not contain
    {
        str = name1 + " does not contain " + name2;  //its name
        (*temp).setName(str);
    }


    return *temp;
}
