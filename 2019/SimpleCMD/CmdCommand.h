#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<Windows.h>
#include<time.h>
#include<string>
#include<vector>
#include<map>
#include<cassert>
#include"Command/cd.h"    //���ĵ�ǰĿ¼
#include"Command/exit.h"  //�˳�
#include"Command/help.h"  //��������
#include"Command/tree.h"  //��ʾ��ǰ�ļ��е��������ļ��м��ļ�

//���󷵻�ֵ�ĺ���
#define COMMAND_ERROR -1
#define REDIRECT_ERROR -2
#define ARGUMENT_ERROR -3
#define PRIVILEDGE_ERROR -4

using namespace std;

//������������ʾ���У���ʾ��ǰ�ļ��У�����ʾ��������Ĺ���
void WaitUserInput();

//�û�����������г���������ʱ���ж��﷨������͸���Ӧ���������
int UserInputCommand(const string& command);