// 队列中取最大值操作.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
using namespace std;
const int INF = 9999999;
class stack
{
public:
	stack(int size = 20)
	{
		stackSize = size;
		stackItem = new int[stackSize];
		maxItem   = new int[stackSize];

		stackTop = -1;
		maxIndex = -1;
	}

	~stack()
	{
		delete [] stackItem;
		delete [] maxItem;
	}

	void push(int value)
	{
		if(stackTop == stackSize - 1)
			return;
		else
		{
			stackTop++;
			stackItem[stackTop] = value;

			maxItem[stackTop] = maxIndex;
			if(value > max())
				maxIndex = stackTop;
		}
	}

	int pop()
	{
		if(stackTop == -1)
			throw;

		if(stackItem[stackTop] == max() )
		{
			maxIndex = maxItem[stackTop];
		}

		return stackItem[stackTop--];
	}

	int max()
	{
		if(maxIndex >= 0)
			return stackItem[maxIndex];
		else
			return -INF;
	}

	bool empty()
	{
		return stackTop == -1;
	};

private:
	int stackSize;
	int *stackItem;
	int  stackTop;

	int *maxItem;
	int  maxIndex;
};


class queue
{
public:
	void EnQueue(int value)
	{
		B.push(value);
	};

	int DeQueue()
	{
		if(A.empty() == true)
		{
			while(B.empty() == false)
				A.push(B.pop());
		}

		return A.pop();
	};

	int MaxElement()
	{
		return A.max() > B.max() ? A.max() : B.max();
	};

private:
	stack A;
	stack B;
};


int main(int argc, char* argv[])
{
	stack s;

	s.push(4);
	s.push(3);
	s.push(2);
	s.push(8);
	s.push(6);

	cout << s.max() << endl;
	s.pop();
	cout << s.max() << endl;
	s.pop();
	cout << s.max() << endl;
	s.pop();
	cout << s.max() << endl;



	system("pause");
	return 0;
}

