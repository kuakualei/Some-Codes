#include"exit.h"

using namespace std;

//�˳�
int Command_EXIT(ostream& out, const vector<string>& argument)
{
	system("pause");
	exit(0);
	return 0;
}

