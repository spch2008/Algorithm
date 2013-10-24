// AboutArray.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

/*
// ��Ŀ1����������ȫ����Ѱ�Һ�Ϊk��������
// ��ʾ�����ܼٶ���ʼsum = 0, ����������Ԫ��ȫΪ����sum = 0�ͻ����sumΪ��һ��Ԫ�ؽϺ�

//brute method
void BruteSearch(int *arr, int N, int k)
{
	for(int i = 0; i < N; i++)             //ÿ��Ԫ����Ϊ��Ԫ�ص�һϵ��������
	{
		int sum = arr[i];                  //��ʼ��һ��Ԫ����Ϊ��ʼ��
		for(int j = i+1; j <= N; j++)      // һ��Ϊ <= ,�������һ��Ԫ��Ϊ��Ԫ�ص�������û��������ѭ�� 
		{
			if(sum == k)                   //�����Ѿ���һ��Ԫ����Ϊ���ˣ����Խ������Ƚ����ж�
			{
				cout << "start: " << i+1 << "  end: " << j << endl;   //���������1��ʼ���±꣬����j�Ѿ�����������ֱ����j����
				break;                                                //��������ȫ�����������ҵ�һ����������
			}
			if( j < N)                                                // �ж�����Ϊ<=, ��ֹ��������п���
				sum += arr[j];

		}
	}
}
// ʱ�临�Ӷ� O��N * N��

// ����ɨ��
//˼·��ά��һ�����䣬������һ��Ԫ�س���k�󣬼�������ͷ����ά������� <= k
//      ��С��k��ʱ���������䳤��
void LineSearch(int *arr, int N, int k)
{
	int sum   = arr[0];
	int start = 0;
	for(int i = 1; i <= N; i++)
	{
		while( sum > k && start < i - 1)    //start ������������, ��ʱ�����䴦�� [start, i)��
		{                                   //��Ϊi��ʱû�м������䣬��i-1����
			sum -= arr[start];
			start++;
		}
		
		if(sum == k)                        //�ȴ��� sum > k��������жϣ���Ϊ���ܼ���ͷ�󣬵���k��
		{
			cout << "start: " << start+1 << "  end: " << i << endl;
		}

		if( i < N )
			sum += arr[i];
	}
}
//���жϣ� sum == k������ӣ�sum += arr[i]��������ʽ����Ҫ<= N, ��Ϊ����Ժ�Ҫת�����ڽ����ж�
//���� i = N - 1��sum += arr[i]�Ժ󣬵��ڽ���ѭ�������ܽ����ж��Ƿ�sum == k)
//�ο���http://www.youtube.com/watch?v=A7xC2Ngxpuk

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
//��Ŀ2:���������и���ֵΪ0

//˼·��
//1.�����ƽ�
//2.��Ч��

//��Ч��
//step1: ��һ������prefix��¼����Ԫ�ص��ۼӺ�
//step2: ��prefix����0(0��prefix�����±�j)����array�д�0 - j��Ϊ0
//step3�����û��0������ȵ�����Ԫ��A,B���±�i,j������A��������ɺ��ֱ��A��A��Bֵ�ȣ�,�м�Ԫ��ֵΪ0��i+1,j��

// 1,2,3,-1,-2,4,1,-5,6
// 1,3,6, 5, 3,7,8, 3,9
// ��0�� �����Ԫ��3,��2 - 4Ϊ0
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
		if(prefix[i] == 0)                                                 //������0����������ж��0����ÿ��0��һ�֣��ӿ�ͷ��0����
			cout << "start: " << 1 << "  end: " << index[i] + 1 << endl;   //���⣬����0֮��Ҳ��һ�֣����ڲ�forѭ������

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


//��Ŀ3�������и���ֵΪk
//��������Ŀ2��ֻ��prefix���������������k
//���������

//1. i = 1, j = 1, s = 0;
//2. if prefix[j] �C prefix[i] == k then you��ve found the solution.// and of course index[j] >= index[ i]
//3. else if, prefix[j] �C prefix[i] < k then j++ and go to step 2.
//4. else, i++ and go to step 2.

//��Ŀ4:�����и���ֵΪk�������������
//��1��������ò��������������������ȶ��ԣ��������k����prefix�м�����
//��2��������ò��ȶ�����


/*
//��Ŀ5������������

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
			i    = j + 1;   //Ϊj��ʱ��sumС��0���������ʼ��Ϊj+1
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
			i    = j + 1;   //Ϊj��ʱ��sumС��0���������ʼ��Ϊj+1
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
//ע�⣺
//i j��ʾ��ǰ���ڴ�������䣬start�� end��ʾ��ǰ��������к� 
//ȫ������������Ҫ�󷵻������������Ҫ���м�¼

*/