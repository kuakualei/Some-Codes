//B
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<queue>
#define ld long double 
#define ll long long
#define lll __int128 
//#define int ll
#define eps 1e-11
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef pair<int, int> P;

const int maxn = 1e3 + 5;

int getAns(int a, int b, int ia, int ib)
{
	if (ia && ib)
		return 0;
	int ans = 0;
	if (a)
	{
		if (!ia)
			ans = max(ans, getAns(a - 1, b, 1, ib) + 1);//��A�գ���A���
		else
			ans = max(ans, getAns(0, b, 1, ib) + a * (2-ib));//��A�գ���A
	}
	if (b)
	{
		if (!ib)
			ans = max(ans, getAns(a, b - 1, ia, 1) + (2 - ia));//��B�գ���B���
		else
			ans = max(ans, getAns(a, 0, ia, 1) + b * (2 - ia));//��B�գ���B
	}
	return ans;
}

signed main()
{
	fastio;
	int a,  b;
	cin >> a >> b;
	cout << getAns(a - 39, b - 39, 0, 0) + 39 * 3;
}
