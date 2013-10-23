// NQueen.cpp : Defines the entry point for the console application.
//
#include <cmath>
#include <iostream>
using namespace std;

bool place(int *vec, int col)
{
	for(int i = 1; i < col; i++)
	{
		if(vec[i] == vec[col] || abs(i - col) == abs(vec[i] - vec[col]) )
			return false;
	}
	return true;
}

void recursion(int *vec, int curcol, int N, int &total)
{
	if( curcol > N)
		total++;
	else
	{
		for(int row = 1; row <= N; row++)
		{
			vec[curcol] = row;
			if( place(vec, curcol) == true)
				recursion(vec, curcol + 1, N, total);
		}
	}
}

int queen(int N)
{
	int *vec = new int[N+1];
	
	int total = 0;
	recursion(vec, 1, N, total);
	delete [] vec;
	return total;

}

int main(int argc, char* argv[])
{
	int N = 8;
	cout << queen(N) << endl;

	system("pause");
	return 0;
}

