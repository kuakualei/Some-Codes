//H
#include<bits/stdc++.h>
#define ld long double 
#define ll long long
#define lll BigInteger 
//#define int ll
#define eps 1e-11
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef pair<int, int> P;

const ll maxn = 10005, infty = 100000, mod = 1125899839733759;

struct BigInteger
{
	typedef unsigned long long LL;
	static const int BASE = 100000000; //压位
	static const int WIDTH = 8;
	vector<int> s;

	BigInteger& clean()
	{
		while (!s.back() && s.size() > 1)s.pop_back(); return *this;
	}
	BigInteger(LL num = 0) { *this = num; }
	BigInteger(string s) { *this = s; }
	BigInteger& operator = (long long num)
	{
		s.clear();
		do {
			s.push_back(num % BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}
	BigInteger& operator = (const string& str)
	{
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;
		for (int i = 0; i < len; i++) {
			int end = str.length() - i * WIDTH;
			int start = max(0, end - WIDTH);
			sscanf(str.substr(start, end - start).c_str(),
				"%d", &x);
			s.push_back(x);
		}
		return (*this).clean();
	}
	BigInteger operator + (const BigInteger& b) const
	{
		BigInteger c; c.s.clear();
		for (int i = 0, g = 0; ; i++) {
			if (g == 0 && i >= s.size() && i >= b.s.size())
				break;
			int x = g;
			if (i < s.size()) x = x + s[i];
			if (i < b.s.size()) x = x + b.s[i];
			c.s.push_back(x % BASE);
			g = x / BASE;
		}
		return c;
	}
	BigInteger operator - (const BigInteger& b) const
	{
		BigInteger c; c.s.clear();
		for (int i = 0, g = 0; ; i++)
		{
			if (g == 0 && i >= s.size() && i >= b.s.size())
				break;
			int x = s[i] + g;
			if (i < b.s.size()) x = x - b.s[i];
			if (x < 0) { g = -1; x = x + BASE; }
			else g = 0;
			c.s.push_back(x);
		}
		return c.clean();
	}
	BigInteger operator * (const BigInteger& b) const
	{
		int i, j; LL g;
		vector<LL> v(s.size() + b.s.size(), 0);
		BigInteger c; c.s.clear();
		for (i = 0; i < s.size(); i++)
			for (j = 0; j < b.s.size(); j++)
				v[i + j] = v[i + j] + LL(s[i])*b.s[j];
		for (i = 0, g = 0; ; i++)
		{
			if (g == 0 && i >= v.size()) break;
			LL x = v[i] + g;
			c.s.push_back(x % BASE);
			g = x / BASE;
		}
		return c.clean();
	}
	BigInteger operator / (const BigInteger& b) const
	{
		BigInteger c = *this;
		// 商:主要是让c.s和(*this).s的vector一样大
		BigInteger m;               // 余数:初始化为0
		for (int i = s.size() - 1; i >= 0; i--)
		{
			m = m * BASE + s[i];
			c.s[i] = bsearch(b, m);
			m = m - b * c.s[i];
		}
		return c.clean();
	}
	BigInteger operator % (const BigInteger& b) const
	{
		BigInteger c = *this;
		BigInteger m;
		for (int i = s.size() - 1; i >= 0; i--)
		{
			m = m * BASE + s[i];
			c.s[i] = bsearch(b, m);
			m = m - b * c.s[i];
		}
		return m;
	}
	// 二分法找出满足bx<=m的最大的x
	int bsearch(const BigInteger& b, const BigInteger& m) const
	{
		int L = 0, R = BASE - 1, x;
		while (1)
		{
			x = (L + R) >> 1;
			if (b*x <= m)
			{
				if (b*(x + 1) > m)
					return x;
				else L = x;
			}
			else R = x;
		}
	}
	bool operator < (const BigInteger& b) const
	{
		if (s.size() != b.s.size())
			return s.size() < b.s.size();
		for (int i = s.size() - 1; i >= 0; i--)
			if (s[i] != b.s[i]) return s[i] < b.s[i];
		return false;
	}
	bool operator >(const BigInteger& b) const
	{
		return b < *this;
	}
	bool operator<=(const BigInteger& b) const
	{
		return !(b < *this);
	}
	bool operator>=(const BigInteger& b) const
	{
		return !(*this < b);
	}
	bool operator!=(const BigInteger& b) const
	{
		return b < *this || *this < b;
	}
	bool operator==(const BigInteger& b) const
	{
		return !(b < *this) && !(b > *this);
	}
};
ostream& operator << (ostream& out, const BigInteger& x)
{
	out << x.s.back();
	for (int i = int(x.s.size()) - 2; i >= 0; i--)
	{
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for (int j = 0; j < strlen(buf); j++) out << buf[j];
	}
	return out;
}
istream& operator >> (istream& in, BigInteger& x)
{
	string s;
	if (!(in >> s)) return in;
	x = s;
	return in;
}


struct matrix
{
	lll v[2][2];
	lll * operator[](int i)
	{
		return v[i];
	}
};

matrix operator * (const matrix &a, const matrix &b)
{
	matrix c;
	memset(c.v, 0, sizeof(c.v));
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
				c.v[i][j] = c[i][j] + a.v[i][k] * b.v[k][j] % mod;
			c[i][j] = c[i][j] % mod;
		}
	return c;
}

matrix quickpow(matrix base, lll n) {
	matrix ans;
	memset(ans.v, 0, sizeof(ans.v));
	for (int i = 0; i < 2; i++)
		ans.v[i][i] = 1;
	while (n != 0) {
		if (n % 2 == 1) ans = ans * base;
		n = n/2;
		base = base * base;
	}
	return ans;
}

matrix baseM =
{
	{{1,1},
	{1,0}}
};


lll quickpow(lll base, lll n) {
	lll ans = 1;
	while (n != 0) {
		if (n % 2 == 1) ans = ans * base % (mod-1);
		n = n / 2;
		base = base * base % (mod-1);
	}
	return ans;
}


signed main()
{
	fastio;
	int T;
	cin >> T;
	while (T--)
	{
		ll n;
		cin >> n;
		lll t = quickpow(2, n);
		lll ans = quickpow(baseM, t)[1][0];
		cout << ans << endl;
	}
	return 0;
}
