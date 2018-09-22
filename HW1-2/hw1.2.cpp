/**
*  Author�G�S�u޳
*  Date�GSep. 17, 2016
*  Purpose�GPrint 1! to N!
*/

#include <iostream>
#define L 100  //�]�̦h100���
using namespace std;

int main()
{
	int n, front, back;  //n ��J�����, front �Ʀr�Y, back �Ʀr��
	int fac[L];  //�ξ�ư}�C�s����
	bool first = true;  //�ˬd�O�_��J�L�Ĥ@����� 
	
	while(cin >> n)
	{
		if(n == 0)  //���ո�Ƶ��� 
			break;
		
		for(int i = 1; i < L; i++)  //�k�s 
			fac[i] = 0;		
		fac[0] = 1;
		
		if(!first)
			cout << endl;  //���P��n�����A�H�@�ӪťզC�j�}
		first = false;  //��J�L�Ĥ@�����
		for(int count = 1; count <= n; count++)  //1��n
		{
			front = L - 1;
			back = 0;
			while(fac[front] == 0)  //��Ʀr�Y
				front--;
			while(back != front+1)  //���k 
				fac[back++] *= count;
			
			for(int i = 0; i < L; i++)  //�i�� 
			{
				if(fac[i] >= 10)
				{					
					fac[i+1] += fac[i]/10;
					fac[i] %= 10;
				}
			}
			front = L - 1;
			while(fac[front] == 0)  //��Ʀr�Y
				front--;
			cout << count << "!=";  //�L�X 
			while(front >= 0)
				cout << fac[front--];
			cout << endl;
		}		
	}
	
	return 0;
}
