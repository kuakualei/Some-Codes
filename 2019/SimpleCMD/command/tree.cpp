#include"tree.h"

using namespace std;

//���� Byte Ϊ��λ��ʾ���ļ���С int ת��Ϊ��ʽ���� string
string int2FileSize(double sz)
{
	//�ú��ʵĵ�λ��ʾ���� 1000 �����۽�λ��1000B ��ʾΪ 0.98KB
	const int sizeUnitArraySize = 6;
	const string sizeUnitArray[] = { " B", "KB", "MB", "GB", "TB", "PB" };
	int currentUnitIndex = 0;
	while (sz >= 1000 && currentUnitIndex < sizeUnitArraySize - 1)
	{
		sz /= 1024;
		currentUnitIndex++;
	}
	
	char s[20];
	sprintf_s(s, 20, "%6.2f%s", sz, sizeUnitArray[currentUnitIndex].c_str());
	return s;

	/*
	��ʽ��������� C ���Ե� printf һ�׷��㣬���ǰ�ԭ�� C++ �汾��ע�͵���

	ostringstream outputStringStream;
	//��֤С������룬������λǰ��ӿո�
	if (sz < 10)
		outputStringStream << "  ";
	else if (sz < 100)
		outputStringStream << " ";

	outputStringStream << int(sz) << ".";

	//�õ�С������λ������ȡ��
	int decimalPart = int((sz - int(sz)) * 100);
	if (decimalPart < 10)
		outputStringStream << "0";
	outputStringStream << decimalPart << sizeUnitArray[currentUnitIndex];

	return outputStringStream.str();
	
	*/
}

//�ݹ飨���򣩱������ļ��в������������ļ��д�С
int TraverseDirectory(const string& directoryName, fileTreeNodeClass* fileTreeNode);

//�ݹ飨���򣩰���ʽ����ļ����ļ��еĴ�С
//�ݹ��ÿһ���������ǰ�ļ����µ��ļ��У���ǰ�ļ����У���Ӧ���ϲ�ݹ������
void printFileTree(ostream& out, string outputFormat, int fatherIsLast, const fileTreeNodeClass* currentFileTreeNode);

//��ʾ��ǰ�ļ��е��������ļ��м��ļ�
int Command_TREE(ostream& out, const vector<string>& argument)
{
	fileTreeClass fileTree; //�ļ���
	string directoryName = (argument.empty() ? "." : argument[0]);
	char directoryFullName[MAX_PATH];

	//�õ�Ŀ���ļ��е�����·�����洢�ڸ����
	GetFullPathName(directoryName.c_str(), MAX_PATH, directoryFullName, NULL);
	fileTree.root->fileName = directoryFullName;

	//�ݹ�������ļ��в������������ļ��д�С
	TraverseDirectory(directoryName, fileTree.root);

	//���
	printFileTree(out, "", -1, fileTree.root);

	return 0;
}

//�ݹ飨���򣩱������ļ��в������������ļ��д�С
int TraverseDirectory(const string& directoryName, fileTreeNodeClass* currentFileTreeNode)
{
	WIN32_FIND_DATA fileData;
	HANDLE fileHandle = INVALID_HANDLE_VALUE;
	string directoryNameWithStar = directoryName + "\\*"; //����Ҫ�������ļ��е�Ŀ¼ Ϊ "����·��\*"

	//�ҵ��ļ����еĵ�һ���ļ�
	fileHandle = FindFirstFile(directoryNameWithStar.c_str(), &fileData);

	//��� fileHandle �������ʧ�ܣ����������Ϣ
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(fileHandle);
		return 0;
	}
	else
	{
		//�����ļ����У���û�е���ʱ
		//do ... while (FindNextFile(fileHandle, &fileData) != 0);
		do
		{
			if (strcmp(fileData.cFileName, ".") == 0 || strcmp(fileData.cFileName, "..") == 0) //����� "." �� ".."
			{
				continue;
			}
			else
			{
				//Ϊ���������ļ����У��½���㲢����
				fileTreeNodeClass * subFileTreeNode = new fileTreeNodeClass;
				currentFileTreeNode->addSon(subFileTreeNode);
				subFileTreeNode->fileName = fileData.cFileName;

				if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)//������ļ���
				{
					//ƴ�ӵõ����ļ��е�����·��,Ȼ��ʼ�ݹ����
					string newDirectory = directoryName + string("\\") + string(fileData.cFileName);
					TraverseDirectory(newDirectory, subFileTreeNode);
					//�����ļ��еĴ�С�Ѿ���¼���µĽ���У�������븸�ļ���
					currentFileTreeNode->fileSize += subFileTreeNode->fileSize;
				}
				else //������ļ�
				{
					//��ȡ��С���洢�ڽ����,Ȼ����븸�ļ���
					subFileTreeNode->fileSize = (long long)fileData.nFileSizeLow + (long long(fileData.nFileSizeHigh) << 32);
					currentFileTreeNode->fileSize += subFileTreeNode->fileSize;
				}
			}
		}
		while (FindNextFile(fileHandle, &fileData) != 0);
		//�����ļ����У���û�е���ʱ
		
		FindClose(fileHandle);
	}
	return 0;
}

//�ݹ飨���򣩰���ʽ����ļ����ļ��еĴ�С
//����ĸ�ʽģ�� cmd �Դ��� tree���ɼ��ں�����
//ע�����������ʽ�У�ÿ����������ʽ��ȡ���������ף��Լ����׵ĸ��ס����������Լ���״̬
//�����ײ�ͬ������������ʽҲ�᲻ͬ
//���Ǵ��ݵĲ����У��������׵�״̬��תΪ���ַ��� outputFromat�����Լ��Լ���״̬�����ӿ������� fatherIsLast��
void printFileTree(ostream& out, string outputFormat, int IsLasSon, const fileTreeNodeClass* currentFileTreeNode)
{
	string currentOutputFormat;
	//���ǽ����׵�״̬תΪ�ַ��������뵽�Լ��������
	switch (IsLasSon) //-1��ר�Ÿ���Ŀ¼ʹ�õģ���Ϊ��Ŀ¼�����΢��һ������
	{
	case 0: currentOutputFormat = "����"; break;
	case 1: currentOutputFormat = "����"; break;
	case -1: currentOutputFormat = "";  break;
	default: assert(0); //��Ӧ�ó����������
	}

	//�ݹ�����ĺ������
	out << int2FileSize((double)currentFileTreeNode->fileSize) << " " 
		<< outputFormat << currentOutputFormat
		<< currentFileTreeNode->fileName << endl;
	
	//���ǽ����׵�״̬תΪ�ַ��������뵽����������
	//�������������ʽ��Ϊ����� fatherIsLast
	switch (IsLasSon)
	{
	case 0: outputFormat += "��  "; break;
	case 1: outputFormat += "   "; break;
	case -1: outputFormat += "";  break;
	default: assert(0); //��Ӧ�ó����������
	}

	//��ǰ�ļ������ļ����У�������
	const int fileNumber = (int)currentFileTreeNode->sonList.size();

	//��ʼ������ǰ�ļ������ļ����У�
	for (int i = 0; i < fileNumber; i++)
	{
		if (i != fileNumber - 1)
			printFileTree(out, outputFormat, 0, currentFileTreeNode->sonList[i]);
		else
			printFileTree(out, outputFormat, 1, currentFileTreeNode->sonList[i]);
	}
	return;
}

/*���Ч�����£�

800.96MB C:\Users\liu\Desktop\SimpleCMD
 29.36KB ����.git
  0.00 B ��  ����branches
 13.00 B ��  ����COMMIT_EDITMSG
280.00 B ��  ����config
 73.00 B ��  ����description
 23.00 B ��  ����HEAD
 18.40KB ��  ����hooks
478.00 B ��  ��  ����applypatch-msg.sample
896.00 B ��  ��  ����commit-msg.sample
  3.24KB ��  ��  ����fsmonitor-watchman.sample
189.00 B ��  ��  ����post-update.sample
424.00 B ��  ��  ����pre-applypatch.sample
  1.60KB ��  ��  ����pre-commit.sample
  1.31KB ��  ��  ����pre-push.sample
  4.78KB ��  ��  ����pre-rebase.sample
544.00 B ��  ��  ����pre-receive.sample
  1.45KB ��  ��  ����prepare-commit-msg.sample
  3.52KB ��  ��  ����update.sample
  1.42KB ��  ����index
240.00 B ��  ����info
240.00 B ��  ��  ����exclude
467.00 B ��  ����logs
161.00 B ��  ��  ����HEAD
306.00 B ��  ��  ����refs
161.00 B ��  ��      ����heads
161.00 B ��  ��      ��  ����master
145.00 B ��  ��      ����remotes
145.00 B ��  ��          ����origin
145.00 B ��  ��              ����master
  8.38KB ��  ����objects
161.00 B ��  ��  ����0f
161.00 B ��  ��  ��  ����14913f3c72094bb7b1e695e153ade04b17d5b0
341.00 B ��  ��  ����18
341.00 B ��  ��  ��  ����064631b2ca8fb1a98148a6e187d0ec529eed0a
235.00 B ��  ��  ����1a
235.00 B ��  ��  ��  ����1eb8ba7066273c25b51d9468d9d6f84892a267
  2.43KB ��  ��  ����21
  2.43KB ��  ��  ��  ����605d35aa85e9739b83479bf2f221e7aad8afae
153.00 B ��  ��  ����24
153.00 B ��  ��  ��  ����3a2b2bd430ae21a9d7bc6d1902f9c4602dcc3e
152.00 B ��  ��  ����2d
152.00 B ��  ��  ��  ����d7611e51d2d37844c9d15101a828f2f869a77a
174.00 B ��  ��  ����32
174.00 B ��  ��  ��  ����6aa2dd0771b6706ec4656f92ea5b3bad00510b
 34.00 B ��  ��  ����3c
 34.00 B ��  ��  ��  ����b1fb0b38d45b508772f9f625c41aca716822ce
581.00 B ��  ��  ����51
581.00 B ��  ��  ��  ����ce1cdf47d9aed59a6ad0c22924c776eccb2c0a
245.00 B ��  ��  ����53
245.00 B ��  ��  ��  ����6acda1ca22c307fbc232b3e94c3493986f9079
507.00 B ��  ��  ����79
507.00 B ��  ��  ��  ����ca7676f8067c8575ac5af3aac2482512712d1f
239.00 B ��  ��  ����8f
239.00 B ��  ��  ��  ����aa88262f6456d132a70ba797333ff49ac63464
270.00 B ��  ��  ����92
270.00 B ��  ��  ��  ����2c2652f945e717d4311ba521b57816cf61cd48
145.00 B ��  ��  ����a8
145.00 B ��  ��  ��  ����767a123b6d726b8a3490f3f3438a071643a416
166.00 B ��  ��  ����ce
166.00 B ��  ��  ��  ����a4bfd7779e4e4c825370c27aa36a773e04f2d7
616.00 B ��  ��  ����d1
616.00 B ��  ��  ��  ����9d1d9d1718aa263d5a1e06a2a497168b657710
480.00 B ��  ��  ����e0
480.00 B ��  ��  ��  ����4b3954ab3ae2b00454fb7a25dc235c558ee9be
128.00 B ��  ��  ����e5
128.00 B ��  ��  ��  ����76e66c5fb83bbeca1930fec1843bdc20869647
  1.31KB ��  ��  ����fc
  1.31KB ��  ��  ��  ����89c58b098d71ecf9bf04ccc250cab65ac178e7
117.00 B ��  ��  ����fd
117.00 B ��  ��  ��  ����bdefce87217f2eb941828724ccddfcc065ecc3
  0.00 B ��  ��  ����info
  0.00 B ��  ��  ����pack
 82.00 B ��  ����refs
 41.00 B ��      ����heads
 41.00 B ��      ��  ����master
 41.00 B ��      ����remotes
 41.00 B ��      ��  ����origin
 41.00 B ��      ��      ����master
  0.00 B ��      ����tags
 18.00 B ����.gitignore
792.28MB ����.vs
792.28MB ��  ����SimpleCMD
792.28MB ��      ����v16
 70.50KB ��          ����.suo
 36.33MB ��          ����Browse.VC.db
 30.00 B ��          ����Browse.VC.opendb
755.87MB ��          ����ipch
755.87MB ��              ����AutoPCH
 79.31MB ��                  ����24c7c421d4d500da
 79.31MB ��                  ��  ����TREE.ipch
 82.81MB ��                  ����29d95a5aaa6d7ca1
 82.81MB ��                  ��  ����CMDCOMMAND.ipch
 79.31MB ��                  ����45273a7bec86ff9d
 79.31MB ��                  ��  ����HELP.ipch
 31.56MB ��                  ����4751296ce7b38572
 31.56MB ��                  ��  ����CMDCOMMAND.ipch
 79.31MB ��                  ����48eb88b5e9be98f7
 79.31MB ��                  ��  ����EXIT.ipch
 79.31MB ��                  ����70999ecc9a83c30
 79.31MB ��                  ��  ����CD.ipch
 79.31MB ��                  ����a66b3b64c613b158
 79.31MB ��                  ��  ����SIMPLECMD.ipch
 79.31MB ��                  ����b23f150314e0f60e
 79.31MB ��                  ��  ����HELP.ipch
 82.81MB ��                  ����c094254ddbbb3d19
 82.81MB ��                  ��  ����TREE.ipch
 82.81MB ��                  ����d5ec20b8da8a57df
 82.81MB ��                      ����MAIN.ipch
  5.81KB ����CmdCommand.cpp
738.00 B ����CmdCommand.h
  9.11KB ����command
318.00 B ��  ����cd.cpp
150.00 B ��  ����cd.h
166.00 B ��  ����exit.cpp
144.00 B ��  ����exit.h
664.00 B ��  ����help.cpp
144.00 B ��  ����help.h
  6.77KB ��  ����tree.cpp
806.00 B ��  ����tree.h
  8.22MB ����Debug
 86.75KB ��  ����cd.obj
932.74KB ��  ����CmdCommand.obj
 58.73KB ��  ����exit.obj
187.03KB ��  ����help.obj
 58.12KB ��  ����main.obj
213.50KB ��  ����SimpleCMD.exe
  2.55MB ��  ����SimpleCMD.ilk
 90.00 B ��  ����SimpleCMD.log
 45.13KB ��  ����SimpleCMD.obj
  2.01MB ��  ����SimpleCMD.pdb
272.30KB ��  ����SimpleCMD.tlog
  4.58KB ��  ��  ����CL.command.1.tlog
253.27KB ��  ��  ����CL.read.1.tlog
  7.61KB ��  ��  ����CL.write.1.tlog
  1.71KB ��  ��  ����link.command.1.tlog
  4.06KB ��  ��  ����link.read.1.tlog
878.00 B ��  ��  ����link.write.1.tlog
198.00 B ��  ��  ����SimpleCMD.lastbuildstate
397.77KB ��  ����tree.obj
635.00KB ��  ����vc142.idb
852.00KB ��  ����vc142.pdb
107.00 B ����main.cpp
  0.00 B ����output.txt
816.00 B ����readme.md
  1.40KB ����SimpleCMD.sln
  7.82KB ����SimpleCMD.vcxproj
  2.09KB ����SimpleCMD.vcxproj.filters
168.00 B ����SimpleCMD.vcxproj.user
  0.00 B ����test.txt
206.37KB ����ʵ���.docx
208.29KB ������׼ʵ�鱨��_ģ��.docx
*/
