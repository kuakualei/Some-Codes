#include<bits/stdc++.h>
#define LL long long
using namespace std;

const long long maxlength = 32;//30��WA��32��AC���е���
const long long maxTrieNode = 600000*maxlength; //����ÿ������������� maxlength �����

struct trieStruct {
    int nextNode[2] = { 0 };
    int cnt = 0;
    //���� tag ����ˣ���Ϊ������һ���ģ�30λ����ֻ��Ҫͳ�����������ж���û����߻���û����
}trie[maxTrieNode]; //û����ָ��ʵ��
int UsedTrieNode = 1;

int n;

int getMaxAns(int person)
{
    int curNode = 0, maxp = 0;
    for (int j = maxlength - 1; j > 0; j--) //get the (i+1)th bit
    {
        int next = 1 xor ((person >> (j - 1)) & 1);
        if (trie[curNode].nextNode[next] == 0 || trie[trie[curNode].nextNode[next]].cnt == 0)
        //node[next]==0 �� next node.cnt==0 �����ж�û���ӽڵ������
        //ǰ������Ϊ�ֵ����ĸ��� 0��
        {
            next = 1 xor next;
        }
        maxp = (maxp << 1) + next;
        curNode = trie[curNode].nextNode[next];
    }
    return maxp;
}

int getMinAns(int person)
{
    int curNode = 0, minp = 0;
    for (int j = maxlength - 1; j > 0; j--) //get the (i+1)th bit
    {
        int next = ((person >> (j - 1)) & 1);
        if (trie[curNode].nextNode[next] == 0 || trie[trie[curNode].nextNode[next]].cnt == 0)
        {
            next = 1 xor next;
        }
        minp = (minp << 1) + next;
        curNode = trie[curNode].nextNode[next];
    }
    return minp;
}

int dfs(int curNode, int curNum, int length)
//�������ã�������д��˵���
{
    if (length == 0)
    {
        for (int i = 0; i <trie[curNode].cnt; i++)
            cout << curNum << " ";
        return 0;
    }
    if (trie[curNode].nextNode[0])
        dfs(trie[curNode].nextNode[0], curNum << 1, length - 1);
    if (trie[curNode].nextNode[1])
        dfs(trie[curNode].nextNode[1], (curNum << 1)+1, length - 1);
    return 0;
}

int main()
{
    cin.sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int c, person;
        cin >> c;
        //OJֻ�� 1, 2, 3 �����룬4,5�ǹ�����
        //4������ֵ������������
        //5�����ʹ�� max �� min ��ԭʼֵ
        if (c == 1)
        {
            cin >> person;
            int curNode = 0;
            for (int j = maxlength-1; j > 0; j--) //get the (i+1)th bit
            {
                trie[curNode].cnt++;
                int next = (person >> (j - 1)) & 1;
                if (trie[curNode].nextNode[next] == 0)
                {
                    //�����ڴ棬��Ϊ�ڴ��ǰ�ѯ��ȫΪ����������������˵�
                    //�����˷�һ�㣬ɾ�˾Ͳ�Ҫ�ˣ�ֱ�Ӵ���û�з���� node �����
                    trie[curNode].nextNode[next] = UsedTrieNode;
                    UsedTrieNode++;
                }
                curNode = trie[curNode].nextNode[next];
            }
            trie[curNode].cnt++;
        }
        else if (c == 2)
        {
            cin >> person;
            int curNode = 0, lastNode = 0;
            for (int j = maxlength-1; j > 0; j--) //get the (j+1)th bit
            {
                trie[curNode].cnt--;
                int next = (person >> (j - 1)) & 1;//һ��һ����ÿ���ӽڵ� cnt - 1
                lastNode = curNode;
                curNode = trie[curNode].nextNode[next];
            }
            trie[curNode].cnt--;
        }
        else if (c == 3)
        {
            cin >> person;
            cout << (getMinAns(person) xor person) << " " << (getMaxAns(person) xor person) << "\n";
        }
        else if (c == 4)
        {
            cout << "d ";
            dfs(0, 0, maxlength - 1);
            cout << endl;
        }
        else if (c == 5)
        {
            cin >> person;
            cout << "p " << getMinAns(person) <<" "<< getMaxAns(person) << "\n";
            cout << "a " << (getMinAns(person) xor person) << " " << (getMaxAns(person) xor person) << "\n";

        }
    }
    return 0;
}

