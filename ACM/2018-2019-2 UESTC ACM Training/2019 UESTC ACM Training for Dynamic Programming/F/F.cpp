#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 17;

int init, k[maxn];
ll dp[1 << maxn]; //dp[state]��ʾ�Ѿ�ɱ�� state ��λΪ1�Ĺ��ޣ�ɱ��ʣ�µķ�����

int n;

void read(int & num)//�������� 
{
	num = 0;
	int i = 0;
	char c;
	while (i < n)
	{
		c = getchar();
		if (c < '0' || c > '9')
			continue;
		num = (num << 1) + c - '0';
		i++;
	}
}

ll dfs(int state)
{
	if (dp[state] != 0)
		return dp[state];
	if (state + 1 == (1 << n)) // all are killed
		return 1;
	
	int kill = init;
	for (int i = 0; i < n; i++)
		if (state&(1 << (n-i-1))) 
			kill |= k[i];
	//calculate now who we can kill �����ʵ����Ԥ���� 

	for (int next = 0; next < n; next++)
	{
		if ((state&(1<<(n-next-1)))==0&&(kill&(1<<(n-next-1)))) //next is not killed and we can kill
			dp[state] += dfs(state | (1 << (n-next-1)));//kill next!
	}
	return dp[state];
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		ll ans = 0;
		scanf("%d", &n);
		read(init);
		memset(dp, 0, sizeof(dp));
		for (int j = 0; j < n; j++)
		{
			read(k[j]);
		}
		printf("Case %d: %lld",i,dfs(0));//������case 
	}
	return 0;
}
