#pragma once
#include"../CmdCommand.h"

using namespace std;

//��ʾ��ǰ�ļ��е��������ļ��м��ļ�
int Command_TREE(ostream& out, const vector<string>& argument);

class fileTreeNodeClass //�ļ��Ľṹ��һ�������ú��ӱ�ʾ�����д洢
{
public:
	string fileName;
	long long fileSize; //������ļ��У��������µ������ļ��Ĵ�С
	vector<fileTreeNodeClass*> sonList; //�ӽڵ�
	fileTreeNodeClass() : fileSize(0){}
	~fileTreeNodeClass() //ɾ��������ֱ�ӵ��ø�������������������
	{
		for (fileTreeNodeClass* son : sonList)
			delete son;
	}
	void addSon(fileTreeNodeClass * sonNode)
	{
		sonList.push_back(sonNode);
	}
};

class fileTreeClass
{
public:
	fileTreeNodeClass* root;
	fileTreeClass() : root(new fileTreeNodeClass){}
	~fileTreeClass()
	{
		delete root;
	};
};


