#include"help.h"

using namespace std;

const string helpDocument =
R"6(�鿴�������

cd D:\            ���ĵ�ǰ�ļ��е� D:\
cd cpp            ���ĵ�ǰ�ļ��е� cpp �ļ���
cd ..             ���ĵ�ǰ�ļ��е���һ��
tree              ��ʾ��ǰ�ļ��е��ļ������ļ��кʹ�С
tree D:\          ��ʾ D:\ ���ļ������ļ��кʹ�С
exit              �˳�����
help              ��ʾ�ð���
<Command> >a.txt  �� <Command> ������ض��� a.txt
<Ohter Command>   ���� CMD ִ������

��Ŀ��ַ�� https://github.com/lyh543/SimpleCMD
)6";


//��������
int Command_HELP(ostream& out, const vector<string>& argument)
{
	out << helpDocument << endl;
	return 0;
}
