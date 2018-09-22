/**
*  Author：范真瑋
*  Date：Sep. 17, 2016
*  Purpose：Print 1! to N!
*/

#include <iostream>
#define L 100  //設最多100位數
using namespace std;

int main()
{
	int n, front, back;  //n 輸入的整數, front 數字頭, back 數字尾
	int fac[L];  //用整數陣列存放資料
	bool first = true;  //檢查是否輸入過第一筆資料 
	
	while(cin >> n)
	{
		if(n == 0)  //測試資料結束 
			break;
		
		for(int i = 1; i < L; i++)  //歸零 
			fac[i] = 0;		
		fac[0] = 1;
		
		if(!first)
			cout << endl;  //不同的n之間，以一個空白列隔開
		first = false;  //輸入過第一筆資料
		for(int count = 1; count <= n; count++)  //1到n
		{
			front = L - 1;
			back = 0;
			while(fac[front] == 0)  //找數字頭
				front--;
			while(back != front+1)  //乘法 
				fac[back++] *= count;
			
			for(int i = 0; i < L; i++)  //進位 
			{
				if(fac[i] >= 10)
				{					
					fac[i+1] += fac[i]/10;
					fac[i] %= 10;
				}
			}
			front = L - 1;
			while(fac[front] == 0)  //找數字頭
				front--;
			cout << count << "!=";  //印出 
			while(front >= 0)
				cout << fac[front--];
			cout << endl;
		}		
	}
	
	return 0;
}
