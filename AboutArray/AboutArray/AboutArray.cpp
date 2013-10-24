// AboutArray.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

/*
// 题目1：数组数据全正，寻找和为k的子数组
// 提示：不能假定初始sum = 0, 假设数组中元素全为负，sum = 0就会出错，sum为第一个元素较好

//brute method
void BruteSearch(int *arr, int N, int k)
{
	for(int i = 0; i < N; i++)             //每个元素作为首元素的一系列子数组
	{
		int sum = arr[i];                  //初始第一个元素作为初始和
		for(int j = i+1; j <= N; j++)      // 一定为 <= ,否则最后一个元素为首元素的子数组没法进该子循环 
		{
			if(sum == k)                   //由于已经有一个元素作为和了，所以进来后先进行判断
			{
				cout << "start: " << i+1 << "  end: " << j << endl;   //输出的是以1开始的下标，由于j已经自增，所以直接输j即可
				break;                                                //由于数组全正，递增，找到一个即可跳出
			}
			if( j < N)                                                // 判断条件为<=, 防止溢出，进行控制
				sum += arr[j];

		}
	}
}
// 时间复杂度 O（N * N）

// 线性扫描
//思路：维持一块区间，当增加一个元素超过k后，减掉区间头部，维持区间和 <= k
//      当小于k的时候，增加区间长度
void LineSearch(int *arr, int N, int k)
{
	int sum   = arr[0];
	int start = 0;
	for(int i = 1; i <= N; i++)
	{
		while( sum > k && start < i - 1)    //start 不能无限增加, 此时的区间处于 [start, i)，
		{                                   //因为i此时没有加入区间，而i-1加入
			sum -= arr[start];
			start++;
		}
		
		if(sum == k)                        //先处理 sum > k，后进行判断，因为可能减掉头后，等于k了
		{
			cout << "start: " << start+1 << "  end: " << i << endl;
		}

		if( i < N )
			sum += arr[i];
	}
}
//先判断（ sum == k），后加（sum += arr[i]）这种形式，都要<= N, 因为后加以后，要转回来在进行判断
//比如 i = N - 1后，sum += arr[i]以后，当在进入循环，才能进行判断是否（sum == k)
//参考：http://www.youtube.com/watch?v=A7xC2Ngxpuk

int main(int argc, char* argv[])
{
	int arr[] = {1,5,2,7,5,3,4,8,6};
	int len   = sizeof(arr) / sizeof(int);
	int k     = 14;

	cout << "brute serach" << endl;
	BruteSearch(arr, len, k);
	cout <<  endl;
	cout << "line search" << endl;
	LineSearch(arr, len, k);

	system("pause");
	return 0;
}
*/


/*
//题目2:数组有正有负，值为0

//思路：
//1.暴力破解
//2.高效法

//高效法
//step1: 用一个数组prefix记录各个元素的累加和
//step2: 若prefix含有0(0在prefix数组下标j)，则array中从0 - j和为0
//step3：如果没有0，则相等的两个元素A,B（下标i,j），从A后加入若干后又变成A（A，B值等）,中间元素值为0（i+1,j）

// 1,2,3,-1,-2,4,1,-5,6
// 1,3,6, 5, 3,7,8, 3,9
// 无0， 有相等元素3,则2 - 4为0
//

void EffectiveMethod(int *arr, int N)
{
	int *prefix = new int[N];
	prefix[0] = arr[0];
	for(int i = 1; i < N; i++)
		prefix[i] = prefix[i-1] + arr[i];

	//index for array prefix
	int *index = new int[N];
	for(int i = 0; i < N; i++)
		index[i] = i;

	//insert sort
	for(int i = 1; i < N; i++)
	{
		int tmp = prefix[i];
		int tmpIndex = index[i];
		int j;
		for(j = i; j > 0 && tmp < prefix[j - 1]; j--)
		{
			prefix[j] = prefix[j-1];
			index[j] = index[j-1];
		}
		prefix[j]   = tmp;
		index[j] = tmpIndex;
	}


	
	for(int i = 0; i < N; i++)
	{
		if(prefix[i] == 0)                                                 //处理单独0的情况，若有多个0，则每个0算一种：从开头到0处，
			cout << "start: " << 1 << "  end: " << index[i] + 1 << endl;   //另外，两个0之间也算一种，由内部for循环处理

		for(int j = i + 1; j < N; j++)
		{
			if(prefix[i] == prefix[j])
			{
				cout << "start: " << index[i] + 1 << "  end: " << index[j] + 1 << endl;
			}
			else
				break;
		}
	}
	
	delete [] index;
	delete [] prefix;
}


int main()
{
	int arr[] = {1,2,3,-1,-2,4,1,-5,6, -4, -5};
	int len   = sizeof(arr) / sizeof(int);

	EffectiveMethod(arr, len);

	system("pause");
	return 0;
}
*/


//题目3：有正有负，值为k
//类似于题目2，只是prefix数组中两数相减得k
//那如何做呢

//1. i = 1, j = 1, s = 0;
//2. if prefix[j] – prefix[i] == k then you’ve found the solution.// and of course index[j] >= index[ i]
//3. else if, prefix[j] – prefix[i] < k then j++ and go to step 2.
//4. else, i++ and go to step 2.

//题目4:有正有负，值为k，但求最长子数组
//法1：如果采用插入排序，则插入排序具有稳定性，比如等于k，则prefix中间距最大
//法2：如果采用不稳定排序，


/*
//题目5：最大子数组和

void MaxSubArr(int *arr, int N)
{
	int maxSoFar = 0;
	int maxSum   = 0;
	int start    = 0;
	int end      = 0;
	for(int i = 0, j = 0; j < N; j++)
	{
		maxSoFar += arr[j];
		if(maxSoFar > maxSum)
		{
			maxSum = maxSoFar;
			start  = i;
			end    = j;
		}
		else if(maxSoFar < 0)
		{
			maxSoFar = 0;
			i    = j + 1;   //为j的时候，sum小于0，则可能起始点为j+1
		}
	}

	cout << "start: " << start+1 << " end: " << end+1 << endl;
	cout << "max sum:" << maxSum << endl;
}

void MaxSubArrAllNegative(int *arr, int N)
{
	int maxSoFar = 0;
	int maxSum   = 0;
	int start    = 0;
	int end      = 0;
	int maxVal   = arr[0];
	int maxIndex = 0;
	for(int i = 0, j = 0; j < N; j++)
	{
		maxSoFar += arr[j];
		if(maxSoFar > maxSum)
		{
			maxSum = maxSoFar;
			start  = i;
			end    = j;
		}
		else if(maxSoFar < 0)
		{
			maxSoFar = 0;
			i    = j + 1;   //为j的时候，sum小于0，则可能起始点为j+1
		}

		if(maxVal < arr[j])
		{
			maxVal   = arr[j];
			maxIndex = j;
		}
	}

	if(maxVal < 0)
	{
		start = end = maxIndex;
		maxSum = maxVal;
	}

	cout << "start: " << start+1 << " end: " << end+1 << endl;
	cout << "max sum:" << maxSum << endl;
}

int main()
{
	int arr[] = {-2 ,-5 ,-3 ,-6 ,-4 ,-1 ,-6};
	int len   = sizeof(arr) / sizeof(int);

	MaxSubArrAllNegative(arr, len);

	system("pause");
	return 0;
}
//注意：
//i j表示当前正在处理的区间，start， end表示当前最大子序列和 
//全负的情况，如果要求返回最大负数，则需要进行记录

*/