#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

//С���� http://oi.cdshishi.net/contestoi/problem_show.php?pid=1338
//������ http://oi.cdshishi.net/dwoi/problem_show.php?pid=1145

using namespace std;


const int town=50000; 
int singleTownsmen[town]; //ָÿ����������� 
int townAndBelowMen[town]; //ָÿ���弰����Ĵ�������� 
int townNum,ans=0x7fffffff,sum=0;
vector<int> road[town];//town��ʾ��ʼ�� 
int findPeople(int,int);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	
	cin >> townNum;
	for (int i=0;i<townNum;i++)
	{
		cin >> singleTownsmen[i];
		sum+=singleTownsmen[i];
		townAndBelowMen[i]=0;
	}
	for (int i=0;i<townNum-1;i++)
	{
		int x,y;
		cin >> x >> y;
		x--;
		y--;
		road[x].push_back(y);
		road[y].push_back(x);
	}
	//�������
	
	for (int i=0;i<townNum;i++)
	{
		for(vector<int>::iterator iter=road[i].begin();iter<road[i].end();iter ++)
		{
			if (i>*iter)
			{
				int temp=abs(sum-2*findPeople(*iter,i)); //��һ�ߵĴ��������ʣ�µ����������ȡ����ֵ 
				ans=min(ans,temp); 
			}
		} 
	}
	cout << ans;
}

int findPeople(int startTown,int findTown)
{
	if (townAndBelowMen[findTown]!=0)
		return townAndBelowMen[findTown];
	int people=singleTownsmen[findTown];
	for(vector<int>::iterator iter=road[findTown].begin();iter<road[findTown].end();iter ++)
	{
		if(*iter!=startTown)
		{
			people+=findPeople(findTown,*iter);
		}
	}
	townAndBelowMen[findTown]=people;
	return people;
}
