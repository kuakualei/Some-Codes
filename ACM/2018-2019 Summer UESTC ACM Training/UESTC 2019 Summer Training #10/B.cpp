#include<bits/stdc++.h>
//#define _CRT_SECURE_NO_WARNINGS
#define ld long double 
#define ll long long 
#define int ll
#define eps 1e-11
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef pair<int, int> P;
const int maxn = 4000, mod = 1e9 + 7;

signed main()
{
	fastio;
	int T;
	cin >> T;
	while (T--)
	{
		int a, b;
		cin >> a >> b;
		cout << (a >= b ? "FunkyMonkeys" : "WeWillEatYou") << endl;
	}
}
