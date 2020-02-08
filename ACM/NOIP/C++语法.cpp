#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<vector>
#include<queue>
#include<limits>
#include<ctime>
#include<cstdlib>

using namespace std;

struct line{
	int d;
};

typedef int array[10][20];//array a;��Ϊ����int a[10][20]

int main(int argc, char *argv[]) //������test.exe a b c����argc==4,argv={"test.exe","a","b","c"}  
{
	
//cout�������С����ʽ(1) (��Ҫiomanip) 
cout << setiosflags(ios::fixed) << setprecision(3);

//cout�������С����ʽ(2)
cout.setf(ios_base::fixed, ios_base::floatfield);
cout.precision(4);

//�����ʼ��(��Ҫcstring)
int a[100];
memset(a,0,sizeof(a));

//���ļ����롢�����1�����ض���棬��Ҫcstdio��
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);

//���ļ����롢�����2����C++���԰棬��Ҫfstream��
int i;
ofstream output;
ifstream input;
output.open("output.txt");
input.open("input.txt");
input >> i;
output << i;

// ���ļ����롢�����3����C���԰棬��Ҫcstdio�� 
char* s;
FILE *fp1,*fp2;
fp1=fopen("input.txt","r");
fp2=fopen("output.txt","w");
fscanf(fp1,"%s",s);
fprintf(fp2,"Hello World! And \"input.txt\" is:%s",s);
fclose(fp1);
fclose(fp2); 

//��ʱ ��Ҫctime
int time = clock() / CLOCKS_PER_SEC;

// ����cin����
ios::sync_with_stdio(false);
cin.tie(0);

//vector��ʹ�÷�������Ҫvector��
vector<int> v; //����
v.push_back(1); //��1�ƽ�v����
for (vector<int>::iterator iter = v.begin(); iter < v.end(); iter++)
//��v��ÿ��Ԫ�ؽ���forѭ��

//queue��ʹ�÷�������Ҫqueue��
queue<int> q; //����
priority_queue<int> q2;//proirity_queue��������ǽ�������
q.push(1); //��1�ƽ�q����
i = q.front(); q.pop();//��q�ĵ�һ�����ó�����ֵΪn
q2.push(1);
i = q2.top(); q2.pop();

//int���ֵ����Ҫlimits��
cout << numeric_limits<int>().max();
cout << INT_MAX;

//���ַ���תΪ���� (��Ҫcstdlib)
int ia=atoi("132");
long la=atol("489432781657");
double d=atof("1.123");

//��̬�����ڴ�(��Ҫcstdlib)
int * p1 = (int*)(malloc(500*sizeof(int)));
free(p1);  
}

//���������
bool operator < (line& a, line& b)
{
	return a.d>b.d;
}

//gcd���������
int gcd(int a, int b)
{
	return a == 0 ? b : gcd(b , a%b);
}
