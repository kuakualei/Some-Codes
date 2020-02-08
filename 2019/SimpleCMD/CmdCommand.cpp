#include"CmdCommand.h"

//#define ENABLE_ESCAPE_MODE
using namespace std;

const int maxDirectoryStringLength = 1000;
const int maxCommandStringLength = 1000;

//�� std::map ���ַ����ͺ�����Ӧ�������Ϳ���ʵ�����ַ���ʶ�������Ӷ�������һ��� if ������
const map<string,
	int (*) (ostream&, const vector<string>&) > commandString2Function =
{
{"cd", Command_CD},
{"tree", Command_TREE},
{"exit", Command_EXIT},
{"help", Command_HELP}
};

//��������н���������ʶ�����ʶ����������� int (*&commandFunction)(ostream&, const vector<string>&) �Ǻ���ָ�������
int AnalyseInputCommand(const string& commandStringFull, int (*&commandFunction)(ostream&, const vector<string>&), vector<string>& argumentVector, string& outputFileName);


//������������ʾ���У���ʾ��ǰ�ļ��У�����ʾ��������Ĺ���
void WaitUserInput()
{
	char currentDirectoryString[maxDirectoryStringLength];
	char command[maxCommandStringLength];
	while (true)
	{
		int dwRet = GetCurrentDirectoryA(maxDirectoryStringLength, currentDirectoryString);

		if (dwRet == 0)
		{
			cout << "�޷���ȡ��ǰ�ļ��У�������룺" << GetLastError() << "�������򼴽��˳���\n\n";
			system("pause");
			return;
		}

		cout << currentDirectoryString << ">";
		cin.getline(command, maxCommandStringLength);
		UserInputCommand(command);
	}
	return;
}

//�û�����������г���������ʱ���ж��﷨���󡢷��͸���Ӧ���������
int UserInputCommand(const string& commandString)
{
	int startTime = clock();  //��ʼ��ʱ

	int returnValue = 0;

	string outputFileName;
	vector<string> argumentVector; //��ÿ����������ΪΪһ�� string����ԭ�������Ϊ string ����
	ostream * outStreamPointer = &cout;
	ofstream fileOutStream;
	int (*commandFunction)(ostream&, const vector<string>&) = NULL;

	//��������н���������ʶ�����ʶ�����
	returnValue = AnalyseInputCommand(commandString, commandFunction, argumentVector, outputFileName);
	if (returnValue == COMMAND_ERROR)
	{
		returnValue = system(commandString.c_str());
	}
	else if (returnValue == ARGUMENT_ERROR)
	{
		cout << "������ʽ����ȷ��\n\n";
		returnValue =  ARGUMENT_ERROR;
	}
	else
	{
		//��������ļ����������ָ���ļ�
		if (!outputFileName.empty())
		{
			fileOutStream.open(outputFileName);
			if (!fileOutStream.is_open()) //�޷����ļ���
			{
				cout << "�޷�������ļ� " << outputFileName << "�������Ƿ���д��Ȩ�ޡ�\n\n";
				returnValue = REDIRECT_ERROR;
			}
			else
			{
				outStreamPointer = &fileOutStream; //�� outStreamPointer ָ���ļ�������������Ǳ�׼���
			}
		}

		//ִ������
		returnValue = commandFunction(*outStreamPointer, argumentVector);
	}
	//ֹͣ��ʱ
	int endTime = clock();
	cout << "��ʱ " << double((endTime) - double(startTime)) / CLOCKS_PER_SEC << " �롣" << endl;
	return returnValue;
}

int AnalyseInputCommand(const string& commandStringFull, int (*&commandFunction)(ostream&, const vector<string>&), vector<string>& argumentVector, string& outputFileName)
{
	istringstream commandStringStream(commandStringFull);
	outputFileName.clear();
	string command;

	commandStringStream >> command;

	//�� map ��Ѱ������
	map<string,
		int (*) (ostream&, const vector<string>&) >::const_iterator commandString2FunctionIterator =
		commandString2Function.find(command);
	if (commandString2FunctionIterator == commandString2Function.end()) //û���ҵ�������������ϵͳִ������
	{
		return COMMAND_ERROR;
	}

	//commandFunction ���������Ӧ�ĺ���
	commandFunction = (commandString2FunctionIterator->second);

	//���濪ʼ�Բ������н���
	//������֧���� "\" ����ת�壬���Ƿ��� cmd ����֧�֣����ԸĻ�����
	//֧�ֵĻ������´���������壺tree D:\ >a.txt
	//���� \ ��Ŀո�Ӧ�ñ���Ϊ����ת�塱��
	string argumentTemp("");
	char charTemp;
#ifdef ENABLE_ESCAPE_MODE
	bool escapeMode = false; //ת��ģʽ��Ϊ true ��ʾ��һ���ַ���ת����� "\"
#endif
	bool quoteMode = false; //����ģʽ��Ϊ true ��ʾһ�����Ż�û�н���

	while (commandStringStream.get(charTemp) && charTemp != '\0')
	{
#ifdef ENABLE_ESCAPE_MODE
		if (escapeMode)
		{
			argumentTemp += charTemp;
			escapeMode = false;
		}
		else 
#endif 
		if (charTemp == '\"')
		{
			argumentTemp += charTemp;
			quoteMode = !quoteMode;
		}
#ifdef ENABLE_ESCAPE_MODE
		else if (charTemp == '\\')
		{
			escapeMode = true;
		}
#endif
		else if (charTemp == ' ')//���������
		{
			if (argumentTemp.empty()) //���ַ�����ֱ�Ӻ���
			{
				;
			}
			else if (quoteMode) //һ�����Ż�û�н���
			{
				argumentTemp += charTemp;
			}
			else //�����־�ò�������
			{
				argumentVector.push_back(argumentTemp);
				argumentTemp.clear();
			}
		}
		else
		{
			argumentTemp += charTemp;
		}
	}

	//��������ģʽ�Ƿ����
	//�����������Ϊ���һ���ַ���δ��ת��� \ ����ȷ���﷨����Ϊ "cd D:\" �������﷨����ȷ�� 
	//if (escapeMode || quoteMode)
	if (quoteMode)
	{
		return ARGUMENT_ERROR;
	}
	if (!argumentTemp.empty()) //���һ���ַ����������Ϊ�գ���û�б����� ArgumentVector ��
	{
		argumentVector.push_back(argumentTemp);
		argumentTemp.clear();
	}

	//�����ķָ���ɣ������Ƿ����ض���
	//0.û�в����Ŀ���ֱ�ӷ�����
	size_t argumentVectorSize = argumentVector.size();
	if (argumentVectorSize != 0)
	{
		//1.�ȰѲ����е� '>' ȥ���������������
		size_t lastArgumentStringSize = argumentVector[argumentVectorSize - 1].size();
		if (argumentVectorSize >= 1 && argumentVector[argumentVectorSize - 1][0] == '>')	//�������һ�������� '>test.txt' �����
		{
			outputFileName = argumentVector[argumentVectorSize - 1].substr(1, lastArgumentStringSize - 1);
			argumentVector.pop_back();
			lastArgumentStringSize--;
		}
		else if (argumentVectorSize >= 2 && argumentVector[argumentVectorSize - 2] == ">") // ����������������� '>' 'test.txt' �����
		{
			outputFileName = argumentVector[argumentVectorSize - 1];
			argumentVector.pop_back();
			argumentVector.pop_back();
		}
		//���� if û��������Ϊû�в����ǡ��ض���

		//2.�ٰѲ����е���β " ������У�ȥ��
		if (!outputFileName.empty() && outputFileName[0] == '"')
		{
			assert(outputFileName[lastArgumentStringSize - 1] == '"'); //���һ���ַ�ҲӦ���� "��������ԣ�Ӧ�������淵��
			outputFileName = outputFileName.substr(1, lastArgumentStringSize - 2);
		}
	}

	return 0;
}
