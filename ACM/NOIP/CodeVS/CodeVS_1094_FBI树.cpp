//http://codevs.cn/problem/1094/
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

char get_type(char * s, int start, int end)
{
	int i = start;
	char type = 'X';
	while (i <= end && type != 'F')
	{
		if (s[i] == '0')
			type = (type == 'I')?'F':'B';
		if (s[i] == '1')
			type = (type == 'B')?'F':'I';
		i++;
	}
	return type;
}

int build_tree(char * s, char * tree,int point, int start, int end, int go_on)
{
	tree[point] = get_type(s,start,end);
	//if (tree[point] == 'I')
	if (go_on != 0)
	{
		build_tree(s,tree,point*2,start,(start+end-1)/2,end-start); //�������������start==end����һ��Ͳ��ܵݹ��� 
		build_tree(s,tree,point*2+1,(start+end+1)/2,end,end-start); //��������
	}
}

int backward(char * s, int point, int l)
{
	if (point * 2 < l)
	{
		backward(s, point*2, l); //�ݹ���ڵ� 
		backward(s, point*2+1, l);//�ݹ��ҽڵ� 
	}
	cout << s[point]; // ������ڵ� 
}

int main()
{
	int n;
	cin >> n;
	char s[10000];
	cin >> s;
	char tree[10000];
	build_tree(s,tree,1,0,pow(2,n)-1,1);
	
	backward(tree,1,pow(2,n+1)-1); // tree�Ľڵ�������s�ĳ���*2-1 
} 
