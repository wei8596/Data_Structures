/**
*  Author�G�S�u޳
*  Date�GOct. 7, 2016
*  Purpose�G�s�@�@�ӡu���X�v���O (set class)�A�Ϩ��i��u�ݩ�v�B�u�p���v�B
*          �u�涰�v�B�u�t���v�B�u�]�t�v�����عB��C
*/

#include <iostream>
#include <string>
#include <algorithm>  //sort
#define L 256  //�}�C����
using namespace std;

class TSet  //���X
{
    public:
        TSet();  //default constructor
        TSet(string str);  //for setting its name
        ~TSet();  //destructor
        void setSet(char* ch);  //�]�w���X����
        char* getSet() const;  //�^�Ƕ��X���
        void setName(string str);  //set its name
        string getName() const;  //return its name
        TSet& in(char& ch);  //belong to
        static int count;  //�έp���Ƨ��ܿ�X�榡
        friend istream& operator >> (istream& in, TSet& A);  //operator overloading
        friend ostream& operator << (ostream& out, TSet& A);
        TSet& operator +(const TSet& B);  //union
        TSet& operator *(const TSet& B);  //intersection
        TSet& operator -(const TSet& B);  //difference
        TSet& operator >=(const TSet& B);  //contain
    private:
        char* chSet;  //���X���
        string name;  //its name
};

int TSet::count = 0;  //��l��0

int main(void)
{
    int N = 0;  //����ƶq

    cin >> N;
    for(int i = 0; i < N; i++)
    {
        char x;  //����
        /* Initial a Set and set its name */
        TSet A("A"), B("B");

        cin.ignore();
        cin >> A >> B;  //��J���X����
        cin.get(x);  //��J����

        TSet C, D;
        C = A + B;  //union
        D = A * B;  //intersection

        cout << "Test Case " << (i+1) << ":" << endl;  //�L�X�B�⵲�G
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
        TSet::count = 0;  //�����k�s
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

void TSet::setSet(char* ch)  //�]�w���X����
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
    for(int i = 0; temp[i] != '\0'; i++)  //���ƪ��r���u��J�@��
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

char* TSet::getSet() const  //�^�Ƕ��X���
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
    string symbol = "";  //for ��
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
        symbol = "��";
        name = symbol + ch + "�� is in " + getName();
        (*temp).setName(name);
    }
    else  //not in
    {
        symbol = "��";
        name = symbol + ch + "�� is not in " + getName();
        (*temp).setName(name);
    }

    return *temp;
}

istream& operator >> (istream& in, TSet& A)  //operator overloading
{
    char ch[L];

    in.getline(ch, L);  //���X�����e�i��t���ťզr���Ψ�L�Ÿ��A�����t����r��
    A.setSet(ch);

    return in;
}

ostream& operator << (ostream& out, TSet& A)
{
    if(TSet::count < 6)  //�ˬd���ƨM�w��X�榡
    {
        char* ch = A.getSet();

        cout << A.getName() << ": {";  //�L�X���X����
        for(int i = 0; ch[i] != '\0'; i++)
            cout << ch[i];
        cout << "}";
    }
    else
        cout << A.getName();

    TSet::count++;  //�έp����+1

    return out;
}

TSet& TSet::operator +(const TSet& B)  //union
{
    TSet* temp = new TSet();
    char* ch1 = getSet();
    char* ch2 = B.getSet();
    char ch[L] = {'\0'};
    int i, j, index = 0;

    while(ch1[index] != '\0')  //�ƻs����
    {
        ch[index] = ch1[index];
        index++;
    }

    for(i = 0, j = index; ch2[i] != '\0'; i++, j++)  //�걵����
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
            if(ch1[i] == ch2[j])  //���ۦP������Jch
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
    bool check;  //�ˬd�O�_���ۦP������
    string name = getName()+"-"+B.getName();  //its name

    for(int i = 0; ch1[i] != '\0'; i++)
    {
        check = true;  //��l��true
        for(int j = 0; ch2[j] != '\0'; j++)
        {
            if(ch1[i] == ch2[j])
                check = false;  //���ۦP������
        }
        if(check)
        {
            ch[index] = ch1[i];  //���ۦP��������Jch
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
    bool check;  //�ˬd�O�_���ۦP������
    string name1 = getName();
    string name2 = B.getName();
    string str = "";  //for setting its name

    for(int i = 0; ch2[i] != '\0'; i++)  //�ˬdch1�O�_�]�tch2
    {
        check = false;  //��l��false
        for(int j = 0; ch1[j] != '\0'; j++)
        {
            if(ch2[i] == ch1[j])
            {
                check = true;  //���ۦP������
                break;
            }
        }
        if(!check)  //�����ۦP������
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
