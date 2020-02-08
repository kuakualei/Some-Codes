#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cctype>
#include<string>
#include<cassert>
#include<algorithm>
#include<stack>

using namespace std;

const int INF = 0x3f3f3f3f, maxCity = 1000, maxLength = 1000;

int dist[maxCity][maxCity], path[maxCity][maxCity];

char getChoice()
{
	char tempstr[1000];
	char choice;
	for (;;)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> tempstr;
		choice = tolower(tempstr[0]);
		if (choice == 'y' || choice == 'n')
			break;
		cout << "����������������롣(y/n)";
	}
	return choice;
}

string getPath(int a, int b)
{
	if (path[a][b] == INF)
		return "";
	
	char str[10];
	sprintf_s(str,10, " %d ", path[a][b]);
	return getPath(a, path[a][b]) + str + getPath(path[a][b], b);
}

int main()
{
	int city, road;
	for (;;)
	{
		cout << "���������������˫�򣩵�·����\n";
		cin >> city >> road;
		if (city <= 0)
			cout << "��������Ҫ���� 0������������\n";
		else if (city > maxCity)
			cout << "��������ҪС�� " << maxCity << "�����������롣\n";
		else if (road < 0)
			cout << "��·����Ҫ���� 0�����������롣\n";
		else if (road > city* (city - 1) / 2)
			cout << "��������ҪС�� " << city * (city - 1) / 2 << "�����������롣\n";
		else
			break;
	}

	memset(dist, 0x3f, sizeof(dist));
	memset(path, 0x3f, sizeof(path));

	cout << "��Ҫ���������·�� ����Ҫ�������� y���������� n��Ȼ���ֶ����롣(y/n)";

	if (getChoice() == 'y')
	{
		vector<pair<int, int> > sequence; //�������бߵ�����
		for (int i = 0; i < city; i++)
			for (int j = i + 1; j < city; j++)
				sequence.push_back({ i,j });

		for (int i = 1; i < sequence.size(); i++)
			swap(sequence[i], sequence[rand() % sequence.size()]); //ʹ�� Fisher�CYates Shuffle Algorithm �����Ϊ�������

		for (int i = 0; i < road; i++) //ȡǰ road ������õ�������� road ����
			dist[sequence[i].first][sequence[i].second] = dist[sequence[i].second][sequence[i].first] = rand() % maxLength;
	}
	else
	{
		cout << "���������� " << road << " �У�ÿһ���������֣��ֱ�����·�������˵� �� ���ȣ�\n";
		int Inputted = 0;
		while (Inputted != road)
		{
			int a, b, l;
			cin >> a >> b >> l;
			if (cin.fail() || a < 0 || b < 0 || l < 0 || a >= city || b >= city)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "��һ�����벻�Ϸ���������������һ��\n";
			}
			else
			{
				dist[a][b] = dist[b][a] = l;
				Inputted++;
			}
		}
	}

	cout << "������ϡ��Ƿ���ʾ����ͼ�ľ��󣿣�y/n��";

	if (getChoice() == 'y')
	{
		cout << "����ͼ�ľ���Ϊ��\n";
		for (int i = 0; i < city; i++)
		{
			for (int j = 0; j < city; j++)
			{
				if (dist[i][j] == INF)
					cout << "INF\t";
				else
					cout << dist[i][j] << "\t";
			}
			cout << "\n";
		}
		cout << endl;
	}

	for (int k = 0; k < city; k++)
		for (int i = 0; i < city; i++)
			for (int j = 0; j < city; j++)
				if (dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j], path[i][j] = k;

	cout << "�Ѽ������������������·���Ƿ���ʾ���·�ľ��󣿣�y/n��";

	if (getChoice() == 'y')
	{
		cout << "���·�ľ���Ϊ��\n";
		for (int i = 0; i < city; i++)
		{
			for (int j = 0; j < city; j++)
			{
				if (dist[i][j] == INF)
					cout << "INF\t";
				else
					cout << dist[i][j] << "\t";
			}
			cout << "\n";
		}
		cout << endl;
	}


	for (;;)
	{
		cout << "����������ı�ţ���0-" << city-1 << "��";

		int a, b;
		cin >> a >> b;

		if (dist[a][b] == INF)
			cout << a << " �� " << b << " ֮��û��ͨ·��";
		else
			cout << a << " �� " << b << " ֮��ľ���Ϊ��" << dist[a][b] << "��·��Ϊ��" << a << " " << getPath(a, b) << " " << b << endl;

		cout << endl;
	}
	return 0;
}