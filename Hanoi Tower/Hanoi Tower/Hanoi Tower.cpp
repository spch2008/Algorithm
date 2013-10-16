// Hanoi Tower.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

int hanoi(int n, int frompeg, int topeg)
{
	if( n == 1)
	{
		cout << frompeg << " --> " << topeg << endl;
		return 1;
	}
	else
	{
		int helppeg  = 6 - frompeg - topeg;  //frompeg + helppeg + topeg = 6

		int preSteps = hanoi(n-1, frompeg, topeg);
		cout << frompeg << " --> " << topeg << endl;
		int postSteps = hanoi(n-1, helppeg, topeg);
		
		return preSteps + 1 + postSteps;
	}
}


int main(int argc, char* argv[])
{
	int n = 4;
	cout << "Total Steps :" << hanoi(n, 1, 3) << endl;

	return 0;
}

