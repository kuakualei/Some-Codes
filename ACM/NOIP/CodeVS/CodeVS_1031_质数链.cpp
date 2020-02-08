//http://codevs.cn/problem/1031/
#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

const int prime[] = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
bool isPrime[34] = { false };
//ֻ���õ�34֮�ڵ����� 

int array[18] = { 0 , 1}; //�ٶ����ַ��� 
bool isUsed[18] = { false, true , false}; //n������������Щ������ 

int main()
{
	
	for (int i = 0; i < sizeof(prime) / sizeof(int); i++)
		isPrime[ prime[i] ] = true;
	int n, point = 2;
	cin >> n;
	if (n % 2 == 1) return 0; //�������б�Ȼ��ż�������� 
		for (int i = 2; i <= n; i++)
	{
		array[i] = i % 2 + 2;
	}
	while(point > 1)
	{
		if (array[point] > n) // ������������� n ��point�ͻ���ǰ�ƶ�1��ͬʱɾȥ���� 
		{
			isUsed[ array[point - 1] ] = false;
			point--;
			array[point] += 2;
			//isUsed[ array[point] ] = true;
			continue; 
		}
		if (isUsed[ array[point] ]) // ��������ظ����� +2 �������һ�� while 
		{
			//isUsed[ array[point] ] = false;
			array[point] += 2;
			//isUsed[ array[point] ] = true; 
			continue;
		}
		if (!isPrime[ array[point] + array[point-1] ]) //���������ǰһ��֮�Ͳ����������� +2 �������һ�� while 
		{
			//isUsed[ array[point] ] = false;
			array[point] += 2;
			//isUsed[ array[point] ] = true; 
			continue;
		}
		
		if (point == n)
		{
			if (isPrime[ array[n] + array[1] ]) // ����������һ����Ҳ���㣬����� 
			{
				cout << array[1];
				for (int i = 2; i <= n; i++)
					cout << " " << array[i];
				cout << endl;
			}
			isUsed[ array[point - 1] ] = false;
			point--;
			array[point] += 2;
			continue;
		}
		isUsed[ array[point] ] = true;
		point++; //point����ƶ�һ�񣬲���ʼ������ָ�����
		//for (int i = point % 2 + 2; isUsed[i]; i += 2)
			array[point] = point % 2 + 2;
		//isUsed[ array[point] ] = true; 
	}
}

