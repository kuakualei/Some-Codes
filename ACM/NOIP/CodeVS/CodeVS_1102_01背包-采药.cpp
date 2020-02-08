//http://codevs.cn/problem/1102/ 
#include<iostream>

using namespace std;

int t, m, NeedTime[105], EveryValue[105]; //����
int ValueCanGet[1001][101]; //ValueCanGet[i][j] ��ʾ�� i ʱ�����ǰ j �ò�ҩ���ܵõ��ļ�ֵ
//int getPlant(int,int,int);

int main()
{
	cin >> t >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> NeedTime[i] >> EveryValue[i];
	}

	for (int i = 1; i <= m; i++)
	{
		ValueCanGet[i][0] = 0; //��ǰ 0 �ò�ҩ��ʱ�ò�������
	}
	for (int timeRemaining = 1; timeRemaining <= t; timeRemaining++)
	{
		for (int n = 1; n <= m; n++)
		{
			int value = ValueCanGet[timeRemaining][n-1];
			//�ò����� n �ò�ҩ���͵�ͬ���� n - 1 �ò�ҩ�����
			if (timeRemaining >= NeedTime[n] 
			//������õ��� n �ò�ҩ
			&& value < ValueCanGet[timeRemaining - NeedTime[n]][n - 1] + EveryValue[n])
			//�����õ� n �òݺ�ļ�ֵ���۳��õ� n �òݵ�ʱ������õ��Ĳݵļ�ֵ�ӵ� n �òݵļ�ֵ���������õļ�ֵ
				value = ValueCanGet[timeRemaining - NeedTime[n]][n - 1] + EveryValue[n];
			ValueCanGet[timeRemaining][n] = value;
		}
	}
	cout << ValueCanGet[t][m];
	return 0;
}


