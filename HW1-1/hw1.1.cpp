/**
*  Author�G�S�u޳
*  Date�GSep. 17, 2016
*  Purpose�GTo construct an NxN magic square (for odd N)
*/

#include <iostream>
#include <iomanip>  //setw
using namespace std;

int main()
{
	int number, x, y, lastX, lastY, size = 3;  //number �Ʀr, x�By�y��
	                                          //lastX�BlastY�W�ӼƦr���y��, size���N�� 
	int** square;  //magic square
	
	cout << "Magic Square of size 1\n"  //�@��
		 << "  1\n\n";
	
	while(size <= 9)  //�L��E�� 
	{		
		cout << "Magic Square of size " << size << endl;
		
		square = new int*[size];  //�ʺA�t�m�G���}�C
		for(int s = 0; s < size; s++)
			square[s] = new int[size];
		
		for(int i = 0; i < size; i++)  //������l��-1 
		{
			for(int j = 0; j < size; j++)
				square[i][j] = -1;
		}
		
		x = 0;
		y = size / 2;
		square[x][y] = 1;  //�̤W����row�̤����B��1
		number = 2;		
		while(number <= size*size)  //����size^2����
		{
			lastX = x;  //�O��W�ӼƦr����m
			lastY = y;
			x--;        //�����W�������� 
			y--;
			if(x < 0)  //�W�U���k�����۳s
				x = size - 1;
			if(y < 0)
				y = size - 1;
			if(square[x][y] == -1)
				square[x][y] = number;
			else                       //�Y���W�����w�g����m�Ʀr
			{
				x = ++lastX;  //�\��b�W�ӼƦr�U�褧���
				y = lastY;
				if(x > size-1)
					x = 0;
				square[x][y] = number;
			}
			number++;
		}
		
		for(int i = 0; i < size; i++)  //�L�X 
		{
			for(int j = 0; j < size; j++)
				cout << setw(3) << square[i][j];
			cout << endl;
		}
		cout << endl;
		
		for(int s = 0; s < size; s++)  //����O�ЪŶ�
			delete[] square[s];
		delete[] square;
		size += 2;
	}
	
	return 0;
}
