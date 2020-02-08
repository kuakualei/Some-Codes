//���������������

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cctype>
#include<string>
#include<cassert>
#include<Windows.h>

#define ll long long
#define ull unsigned long long 

using namespace std;

class BigInteger
{
private:
	static const ll section = (int)1e9;   //ѹλ�����ݴ�С
	static const ll sectionN = 9;    //ѹλ�ĳ���
	bool positive;
	vector <ll> num;

	void format(); //����δ�淶�Ľ�λ
public:
	BigInteger();
	BigInteger(long long n); //�� long long תΪ BigInteger
	BigInteger(string str); //�� string תΪ BigInteger
	void rand(size_t n);//������� n λ�������

	static int comp(const BigInteger& a, const BigInteger& b);  //������ strcmp, a<b ���� -1��a>b ���� 1�� a==b ���� 0
	static int abscomp(const BigInteger& a, const BigInteger& b, ll n = 0); //�Ƚ������ľ���ֵ������֧�ֵڶ��������Ƶ����
	bool operator == (const BigInteger& b) const;
	bool operator != (const BigInteger& b) const;
	bool operator > (const BigInteger& b) const;
	bool operator < (const BigInteger& b) const;
	bool operator <= (const BigInteger& b) const;
	bool operator >= (const BigInteger& b) const;

	bool Minus(const BigInteger& b, ll n = 0); //������ֱ����ԭ���ϲ���������֧�ֵڶ��������Ƶ����
	BigInteger absDivide(BigInteger b); //������ֱ����ԭ���ϲ�����ԭ����Ϊ��������������
	BigInteger operator + (const BigInteger& b) const;
	BigInteger operator - (const BigInteger& b) const;
	BigInteger operator * (const BigInteger& b) const;
	BigInteger operator / (const BigInteger& b) const;
	BigInteger operator % (const BigInteger& b) const;


	friend ostream& operator << (ostream& out, const BigInteger& b);
	friend istream& operator >> (istream& in, BigInteger& b);
};

void BigInteger::format() //����δ�淶�Ľ�λ����λ����λΪ 0
{
	ll lasti = num.size() - 1;
	for (ll i = 0; i < lasti; i++)
	{
		num[i + 1] += num[i] / section;
		num[i] = num[i] % section;
		if (num[i] < 0)
		{
			num[i] += section;
			num[i + 1]--;
		}
	}
	assert(num[lasti] >= 0); //���λ��Ӧ��С�� 0
	if (num[lasti] >= section)
	{
		num.push_back(num[lasti] / section);
		num[lasti] %= section;
	}

	for (ll i = num.size() - 1; i > 0 && num[i] == 0; i--) //ɾ����λ�� 0
	{
		num.pop_back();
	}

	if (num.size() == 1 && num[0] == 0) //�� -0 Ϊ +0
		positive = true;
}

BigInteger::BigInteger()
{
	positive = true;
	num.clear();
}
BigInteger::BigInteger(long long n)
{
	positive = (n >= 0);
	num.clear();
	n = abs(n);

	while (n > 0)
	{
		num.push_back(n % section);
		n /= section;
	}

	if (num.empty())
		num.push_back(0);
}
BigInteger::BigInteger(string str)
{
	long long last = str.length();
	if (str[0] != '-')
		positive = true;
	else
	{
		positive = false;
		str = str.substr(1);
		last--;
	}
	while (last - sectionN >= 0)
	{
		num.push_back(
			stoll(
				str.substr(last - sectionN, sectionN))); //string to long long
		last -= sectionN;
	}
	if (last != 0)
		num.push_back(
			stoll(str.substr(0, last)));
}
void BigInteger::rand(size_t n)//������� n λ�������
{
	positive = rand() & 1;
	num.clear();
	while (n >= sectionN)
	{
		num.push_back(ull(std::rand()) * std::rand() % section);
		n -= sectionN;
	}
	if (n > 0)
		num.push_back(ull(std::rand()) * std::rand() % (ull)pow(10, n));
}

int BigInteger::comp(const BigInteger& a, const BigInteger& b) //������ strcmp, a<b ���� -1��a>b ���� 1�� a==b ���� 0
{
	int signal = a.positive ? 1 : -1;
	if (a.positive != b.positive)
		return signal;
	return signal * abscomp(a, b);
}
int BigInteger::abscomp(const BigInteger& a, const BigInteger& b, ll n /* = 0*/) //�Ƚ������ľ���ֵ������֧�ֵڶ��������Ƶ����
{
	if (a.num.size() != b.num.size() + n)
		return ((a.num.size() < b.num.size() + n) ? -1 : 1);
	else
		for (ll i = a.num.size() - 1; i >= n; i--)
			if (a.num[i] != b.num[i - n])
				return ((a.num[i] < b.num[i - n]) ? -1 : 1);
	for (ll i = n - 1; i >= 0; i--)
		if (a.num[i] != 0)
			return 1;
	return 0;
}
bool BigInteger::operator < (const BigInteger& b) const
{
	return comp(*this, b) == -1;
}
bool BigInteger::operator == (const BigInteger& b) const
{
	return comp(*this, b) == 0;
}
bool BigInteger::operator > (const BigInteger& b) const
{
	return comp(*this, b) == 1;
}
bool BigInteger::operator != (const BigInteger& b) const
{
	return comp(*this, b) != 0;
}
bool BigInteger::operator <= (const BigInteger& b) const
{
	return comp(*this, b) != 1;
}
bool BigInteger::operator >= (const BigInteger& b) const
{
	return comp(*this, b) != -1;
}

BigInteger BigInteger::operator + (const BigInteger& b) const //ֻ������ͬ������ӣ����������������
{
	if (positive ^ b.positive) //�����ţ�ת��Ϊ����
	{
		if (abscomp(*this, b) == 1)
		{
			BigInteger newb = b;
			newb.positive = positive;
			return *this - newb;
		}
		else
		{
			BigInteger newa = *this;
			newa.positive = b.positive;
			return b - newa;
		}
	}
	if (num.size() < b.num.size()) // ��֤ *this �� b ��
		return b + *this;

	BigInteger ret;
	ret.positive = positive;
	for (int i = 0; i < b.num.size(); i++)
	{
		ret.num.push_back(num[i] + b.num[i]);
	}
	for (ull i = b.num.size(); i < num.size(); i++)
	{
		ret.num.push_back(num[i]);
	}

	ret.format();

	return ret;
}
bool BigInteger::Minus(const BigInteger& b, ll n /* = 0*/) //������ֱ����ԭ���ϲ���������֧�ֵڶ��������Ƶ����
{
	if ((positive ^ b.positive) || abscomp(*this, b, n) == -1) //�����Ż��߱���������ֵС�ڣ���λ��ģ��������򷵻� false
		return false;

	for (ull i = 0; i < b.num.size(); i++)
	{
		num[i + n] = num[i + n] - b.num[i];
	}

	this->format();

	return true;
}
BigInteger BigInteger::operator - (const BigInteger& b) const
{
	if (positive ^ b.positive) //�����ţ�ת��Ϊ�ӷ�
	{
		BigInteger newb = b;
		newb.positive = positive;
		return *this + newb;
	}

	if (abscomp(*this, b) == -1) //��֤����������ֵ���ڼ���
	{
		BigInteger newans = b - *this;
		newans.positive = !newans.positive;
		return newans;
	}

	BigInteger ret = *this;
	ret.Minus(b);

	return ret;
}
BigInteger BigInteger::operator * (const BigInteger& b) const
{
	BigInteger ret;
	ret.positive = !(positive ^ b.positive);

	ret.num.resize(num.size() + b.num.size());

	for (ull i = 0; i < num.size(); i++) //���� for �ĳ˷�
	{
		for (ull j = 0; j < b.num.size(); j++)
		{
			ret.num[i + j] += num[i] * b.num[j];
			if (ret.num[i + j] > section* section) //���һ�� num ������ݹ����ٿ��ǽ�λ����������ֹ��λ������ֽ��ͽ�λ��Ƶ�ʣ�ʹ�ó�����죨�������Խ�λ������𣿣�
			{
				ret.num[i + j + 1] += ret.num[i + j] / section;
				ret.num[i + j] %= section;
			}
		}
	}

	ret.format();

	return ret;
}
BigInteger BigInteger::absDivide(BigInteger b) //������ֱ����ԭ���ϲ�����ԭ����Ϊ��������������
{
	//�Ȱѱ�������������Ϊ�������ٴ���
	bool apositive = positive, bpositive = b.positive;
	positive = b.positive = true;

	if (*this < b)
		return 0;

	BigInteger quotient;
	quotient.positive = true;
	quotient.num.resize(num.size() - b.num.size() + 1);

	for (ll n = quotient.num.size() - 1; n >= 0; n--) //��λ������
	{
		//����������һλ��ֵ
		ll base = 1ll << int(log2(section));
		while (base > 0)
		{
			if (this->Minus(b * BigInteger(base), n) == true)  //ͨ�����ϵĳ˷����������������ֵ
			{
				quotient.num[n] += base;
			}
			base >>= 1;
		}
	}
	
	quotient.format();

	//���̺������ķ��Ÿ�Ϊ��ȷ�ķ���
	quotient.positive = !(apositive ^ bpositive);
	positive = apositive;
	return quotient;
}
BigInteger BigInteger::operator / (const BigInteger& b) const
{
	BigInteger a = *this;
	return a.absDivide(b);
}
BigInteger BigInteger::operator % (const BigInteger& b) const
{
	BigInteger a = *this;
	a.absDivide(b);
	return a;
}

ostream& operator << (ostream& out, const BigInteger& b)
{
	if (!b.positive)
		out << "-";

	for (ll i = b.num.size() - 1; i >= 0; i--)
	{
		//���������ʱ���㣬ע�������ͷһ���Ͳ��ò�����
		if (i != b.num.size() - 1)
		{
			ll sz = BigInteger::section / 10;
			while (b.num[i] < sz && sz >= 10)
			{
				sz /= 10;
				out << '0';
			}
		}
		out << b.num[i];
	}
	return out;
}
istream& operator >> (istream& in, BigInteger& b)
{
	string str;
	in >> str;
	b = str;
	b.format();
	return in;
}

inline ll bigRand()
{
	return ((ll)rand() << 30) + ((ll)rand() << 15) + rand();
}

int testModule()
{
	srand(unsigned int(time(0)));
	const ll testcases = (ll)4e7;
	time_t startTime = clock();
	for (ll i = 1; i < testcases; i++)
	{
		ll a = bigRand(), b = bigRand();
		BigInteger A = a, B = b;
		BigInteger C = A - B;
		ll c = a - b;
		if (BigInteger(c) != C)
		{
			cout << "Wrong situation detected." << endl
				<< "a: " << a << endl
				<< "A: " << A << endl
				<< "b: " << b << endl
				<< "B: " << B << endl
				<< "c: " << c << endl
				<< "C: " << C << endl;
			system("pause");
			return -1;
		}
		if (i % (testcases / 100) == 0)
			cout << "o"; //������
	}
	time_t endTime = clock();
	cout << endl << testcases << " cases Accepted. Use time: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s.";
	return 0;
}

int testModule2()
{
	srand(unsigned int(time(0)));
	const ll testcases = (ll)1e7;
	time_t startTime = clock();
	for (ll i = 1; i < testcases; i++)
	{
		ll a = bigRand(), b = bigRand();
		BigInteger A = a, B = b;
		BigInteger C = A * B;
		BigInteger Q1 = C / B, Q2 = C / A;
		BigInteger R1 = C % B, R2 = C % A;
		ll c = a - b;
		if (Q1 != A || Q2 != B || R1 != 0 || R2 != 0)
		{
			cout << "Wrong situation detected." << endl
				<< "A: " << A << endl
				<< "B: " << B << endl
				<< "C: " << C << endl
				<< "Q1: " << Q1 << endl
				<< "Q2: " << Q2 << endl
				<< "R1: " << R1 << endl
				<< "R2: " << R2 << endl;
			system("pause");
			return -1;
		}
		if (i % (testcases / 100) == 0)
			cout << "o"; //������
	}
	time_t endTime = clock();
	cout << endl << testcases << " cases Accepted. Use time: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s.";
	return 0;
}

void UserInterface()
{
	for (;;)
	{
		SetConsoleTitleA("���������������");
		cout << "������ = �Լ��㣨�� \" = 123456 * 234567\" ���� 123456 * 234567������ǰ����Ҫ�пո�" << endl
			<< "������Ӣ�� ? ��ͷ��ʾ����������ּ��㣨�� \"? 30 * 70\" ��ʾ������ 30 λ���� 70 λ�����������" << endl
			<< "������ q ���˳�" << endl;
		char choice, oper;
		BigInteger A, B, C;
		bool wrongInput = false;

		cin >> choice;
		if (choice == '=')
		{
			cin >> A >> oper >> B;
		}
		else if (choice == '?') //-93 �Ƕ������ʺŵĽ��
		{
			int a, b;
			cin >> a >> oper >> b;
			if (a <= 0 || b <= 0)
				wrongInput = true;
			A.rand(a);
			B.rand(b);
		}
		else if (choice == 'q')
			return;
		else wrongInput = true;

		if (!wrongInput)
		{
			switch (oper)
			{
			case '+': C = A + B; break;
			case '-': C = A - B; break;
			case '*': C = A * B; break;
			case '/': C = A / B; break;
			default: wrongInput = true;
			}
		}

		if (wrongInput)
		{
			cout << "�����ʽ����ȷ�����������롣";

			//������һ�ֿ��ܵĴ�������
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else
		{
			cout << A << " " << oper << " " << B << " = " << endl
				<< C << endl << endl;
		}
		system("pause & cls");
	}
}

int main()
{
	UserInterface();
}

