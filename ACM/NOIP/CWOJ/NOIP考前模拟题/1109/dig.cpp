//һ¥�׸�t123yh������CWOJ�Ͽ�Դ�Ĵ���
//��¥�׸�����Ⱥϲ����������������
#include<iostream>
#include<queue>
using namespace std;

char s[5];
int girlN, length, v;
double nowt = 0, nowd = 0;
int tgirlN = 0, dgirlN = 0;

struct cmp{
	bool operator ()(int & a, int & b)
	{
		return a > b;
	}
};
priority_queue<int, vector<int>, cmp> tgirl, dgirl;

int main()
{
	freopen("dig.in","r", stdin);
	//freopen("dig.out", "w", stdout); 
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin >> girlN >> length;
	for (int i = 1; i <= girlN; i++)
	{
		int temp;
		cin >> s >> temp;
		if (s[0] == 'T')
		{
			tgirl.push(temp);
		}
		else
		{
			dgirl.push(temp);
		}
	}
	
	for (v = 1; v <= girlN; v++)
	{
		double t;
		if (tgirl.empty())
		{
			t = (dgirl.top() - nowd) * v; //������һ��d���ҵ�ʱ��
			dgirl.pop();
		}
		else if (dgirl.empty())
		{
			t = (tgirl.top() - nowt);  //������һ��t���ҵ�ʱ��
			tgirl.pop();
		}
		else
		{
			int td = (dgirl.top() - nowd) * v;
			int tt = (tgirl.top() - nowt);
			if (tt < td)
			{
				t = tt;
				tgirl.pop();
			}
			else
			{
				t = td;
				tgirl.pop();
			}
		}
		
		nowt += t;
		nowd += t / v;
	}
	
	cout << (long long)(nowt + (length-nowd)*v);
}
