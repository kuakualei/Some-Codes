#include<iostream>

using namespace std;

const int size = 30;
long long tot[size+1]; //tot[j]��ʾj����50Ԫ������� 

long long dp(int m, int n)
{
	for (int j = 0; j <= m; j++) tot[j] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= m; j++)
			tot[j] += tot[j-1];
			
	return tot[m];
			
}

int main()
{
	cin.sync_with_stdio(false);
	cin.tie(0);
	
	int m,n;
	cin >> m >> n;
	cout << dp(m,n);
}

/* 
��̬�滮��

��Ȼ����һ��100Ԫǰ���������һ��50Ԫ��
��һ��int tot[i][j]������
��ʾ���i+j�����г���i��100Ԫ��j��50Ԫ���ж��������
(i=j=0ʱ) tot[i][j] = 1 
(i<jʱ) tot[i][j] = tot[i][j-1] + tot[i-1][j]
(i=jʱ) tot[i][j] = tot[i][j-1]
��������Ϊtot[n][n]�� 
ʱ�临�Ӷ� O(n^2)


���������н�ά��
��Ȼ����ÿ��totʱֻ��Ҫ�󷽺��Ϸ��ĸ��ӣ����Կ���ʡ��i
����i = 1 ~ n��ѭ����
��������j<i�� tot[j] += tot[j-1]����Ҫ�����㣩
����Ϊ����tot[n]��

���⣬��j��ά��Ҳ�ǿ��Եġ�
*/ 
