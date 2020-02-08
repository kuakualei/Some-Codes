//����׺��ʽ��1+2*3��תΪ��׺��ʽ��123*+���ټ����� 
#include<iostream>
#include<stack>
#include<vector>
#include<cstring>
#include<cmath>
using namespace std;


const char infix[100] = "12*(23+34*(45+56))";

stack<char> st;
vector<char> postfix;

int whatIs(char c)
{
	if (c >= '0' && c <= '9') return 0; // number
	if (c == '(' || c == ')') return 1; // ( or )
	if (c == '+' || c == '-') return 2; // + or -
	if (c == '*' || c == '/') return 3; // * or /
	if (c == '^') return 4; // ^
	return 233;
}

void GetPostfix()
{
	int il = strlen(infix);
	int i = 0;
	while(i < il)
	{
		if (infix[i] == '(')
		{
			st.push('(');
		}
		else if (infix[i] == ')')
		{
			while (st.top() != '(') // ����ǣ����Ͱ�st��ķ����ƶ���postfix�ֱ���� 
			{
				postfix.push_back(st.top());
				postfix.push_back(' ');
				st.pop();
			}
			st.pop();
		}
		else
		{
			int pre = whatIs(infix[i]);
			if (pre == 0) //������ֱ��ˢ��postfix 
			{
				while (whatIs(infix[i]) == 0)
				{
					postfix.push_back(infix[i]);
					i++;
				}
				postfix.push_back(' ');
				continue;
			}	
			else
			{
				while (!st.empty() && pre <= whatIs(st.top())) //���������ȼ�>=��ǰ���ŵķ����ƶ���postfix�� 
				{
					postfix.push_back(st.top());
					postfix.push_back(' ');
					st.pop();
				}
				st.push(infix[i]);
			}
		}
		i++;
	}
	
	while (!st.empty()) // ����ǣ����Ͱ�st��ķ����ƶ���postfix�ֱ���� 
	{
		postfix.push_back(st.top());
		postfix.push_back(' ');
		st.pop();
	}
	
	for (vector<char>::iterator iter = postfix.begin(); iter < postfix.end(); iter++)
		cout << *iter;
}


int ans()
{
	stack<int> num;
	for (vector<char>::iterator iter = postfix.begin(); iter < postfix.end(); iter++)
	{
		if (whatIs(*iter) == 0)
		{
			int t = 0;
			while (*iter >= '0' && *iter <= '9')
			{
				t = t * 10 + *iter - '0';
				iter++;
			}
			num.push(t);
		}
		else if (*iter != ' ')
		{
			int b = num.top();
			num.pop();
			int a = num.top();
			num.pop();
			
			int t;
			switch(*iter)
			{
				case ' ':continue;
				case '+': t = a + b; break;
				case '-': t = a - b; break;
				case '*': t = a * b; break;
				case '/': t = a / b; break;
				case '^': t = pow(a, b);
			}
			num.push(t);
		}	
	}
	return num.top();
}

int main()
{
	cout << "The Infix is: " << infix << endl;
	cout << "The Postfix is: ";
	GetPostfix();
	cout <<  "\nThe answer is: "<< ans();
}
