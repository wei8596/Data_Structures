/**
*  Author：范真瑋
*  Date：Sep. 17, 2016
*  Purpose：To construct an NxN magic square (for odd N)
*/

#include <iostream>
#include <iomanip>  //setw
using namespace std;

int main()
{
	int number, x, y, lastX, lastY, size = 3;  //number 數字, x、y座標
	                                          //lastX、lastY上個數字的座標, size表示N階 
	int** square;  //magic square
	
	cout << "Magic Square of size 1\n"  //一階
		 << "  1\n\n";
	
	while(size <= 9)  //印到九階 
	{		
		cout << "Magic Square of size " << size << endl;
		
		square = new int*[size];  //動態配置二維陣列
		for(int s = 0; s < size; s++)
			square[s] = new int[size];
		
		for(int i = 0; i < size; i++)  //全部初始為-1 
		{
			for(int j = 0; j < size; j++)
				square[i][j] = -1;
		}
		
		x = 0;
		y = size / 2;
		square[x][y] = 1;  //最上面的row最中間處放1
		number = 2;		
		while(number <= size*size)  //直到size^2為止
		{
			lastX = x;  //記住上個數字的位置
			lastY = y;
			x--;        //往左上角的方格放 
			y--;
			if(x < 0)  //上下左右環狀相連
				x = size - 1;
			if(y < 0)
				y = size - 1;
			if(square[x][y] == -1)
				square[x][y] = number;
			else                       //若左上角方格已經有放置數字
			{
				x = ++lastX;  //擺放在上個數字下方之方格
				y = lastY;
				if(x > size-1)
					x = 0;
				square[x][y] = number;
			}
			number++;
		}
		
		for(int i = 0; i < size; i++)  //印出 
		{
			for(int j = 0; j < size; j++)
				cout << setw(3) << square[i][j];
			cout << endl;
		}
		cout << endl;
		
		for(int s = 0; s < size; s++)  //釋放記憶空間
			delete[] square[s];
		delete[] square;
		size += 2;
	}
	
	return 0;
}
