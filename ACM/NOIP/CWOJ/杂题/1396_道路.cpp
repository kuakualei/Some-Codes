//һ¥�׸�ѧ�� 
#include<iostream>
#include<cstdio>

using namespace std;

const int matrixSize = 150, inf = 0x7fffffff;
const int xadd[4]={1,0,0,-1}, yadd[4] = {0,-1,1,0};
int n, ans, matrix[matrixSize][matrixSize] = {{0}},numberSize = 0;
bool visited[matrixSize][matrixSize];

bool legal(int x, int y)
{
	return (x >=0 && y >= 0 && x < n && y < n);
}

bool dfs(int x, int y)
{
	visited[x][y] = true;
	for (int direct = 0; direct < 4; direct++)
	{
		int tx = x + xadd[direct], ty = y + yadd[direct];
		if (legal(tx,ty) && visited[tx][ty] == false)
		{
			if (tx + 1 == n && ty + 1 == n) return true;
			if (dfs(tx, ty)) return true;
		}
	}
	return false;
}

bool across(int min, int max)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[i][j] = (matrix[i][j] < min || matrix[i][j] > max); //�����Ϸ�Χ��ֱ�ӱ�Ϊtrue 
		}
	}
	return (!visited[0][0] && dfs(0,0));
}

int bs(int min, int l, int r) //ѧ����˵�Ķ��֡����ص���һ�����ʵ����ֵ��l��r���߶�����ȡ 
{
	if (l == r)
	{
		return across(min, l) ? l : inf;
	}
	int m = (l + r) / 2;
	if (across(min, m))
	{
		//cout << min << "~" << m << "is OK\n";
		return bs(min, l, m);
	}
	else
	{
		//cout << min << "~" << m << "is not OK\n";
		return bs(min, m+1, r);
	}
}

/*for (int max = min; max <= numberSize && max < ans + min; max++)
	{
		if (across(min,max))
			{
				if (max - min < ans)
				{
					ans = max - min;
					cout << min << "~" << max << "is OK\n"; 
					break;
				}
			}
			//else cout << min << "~" << max << "is not OK\n"; 
	}*/
int main()
{
	
	//freopen("road8.in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> matrix[i][j];
			numberSize = max(numberSize, matrix[i][j]);
		}
	}
	ans = numberSize;
	
	for (int min = 0; min <= numberSize; min++) //ѧ��˵��ö�� 
	{
		//�ܾ����ֵķ��� 
		/*for (int max = min; max <= numberSize && max < ans + min; max++)
		{
			if (across(min,max))
			{
				if (max - min < ans)
				{
					ans = max - min;
					cout << min << "~" << max << "is OK\n"; 
					break;
				}
			}
			//else cout << min << "~" << max << "is not OK\n"; 
		}*/
		
		//ѧ��˵�����ö���
		int t = bs(min, min, numberSize);
		if (t - min < ans) ans = t - min;
	}

	cout << ans;
}


