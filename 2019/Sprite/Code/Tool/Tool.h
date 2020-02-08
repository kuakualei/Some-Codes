#pragma once
#include <list>
#include "../Acllib.h"
#include "../GameConfig.h"

#include "../Sprite/UserSprite.h"
#include "../Sprite/AutoSprite.h"

enum ToolStatus
{
	INVALID,
	ONBOARD,  //�ڳ��ϣ���û�еõ���
	INBAG,    //�ڰ���
	RELEASING //�ͷ���
};

class ToolManagerClass; //ǰ������
struct GameStatusStruct;

class ToolClass
{
	friend class ToolManagerClass;
protected:
	ToolStatus status;          //���ߵ�״̬
	rect position;              //���ߵ�����
	ACL_Image* img;             //���ߵ�ͼ��


	ToolStatus getStatus();

	rect getPosition();
	bool collision(const rect & position2);

	virtual int getVirtualKey() = 0;       //�ͷŵ��ߵİ�����Virtual Key�������ڴ�������
	virtual const char * getVirtualKeyString() = 0; //�ͷŵ��ߵİ������ַ�������������ʾ����Ļ��

	virtual int getNextAppearTime() = 0;
	bool appear();                  //���߳���
	virtual bool gain() = 0;        //�õ����ߣ������漰���ڱ����е����꣬��˻�����Ϊ�麯�����ɼ�����ʵ��
	virtual bool release(GameStatusStruct * gameStatus) = 0; //�ͷŵ��߲�����Ч��

	virtual void paint(GameStatusStruct * gameStatus); //�� Acllib.h ��ĺ������ͼ�񣨺����½ǵ�ʾ�ⴥ����ĸ��

public:
	ToolClass();
};

class ToolManagerClass   //�����������ڹ������е���
{
private:
	std::vector<ToolClass*> toolList;
public:
	ToolManagerClass();
	ToolManagerClass(const std::vector<ToolClass*> & _toolList);
	~ToolManagerClass();

	void putToolOnBoard(int gameClock); //������Ϸʱ��͸����ߵ� nextTime�����Խ����߷��ڳ���
	void settleTool(const rect & userPosition); //��������Ƿ��õ���
	bool use(int virtualKey, GameStatusStruct * gameStatus);  //����ʹ�õ��ߣ������ⰴ����ʶ�𣩣��ɹ����� true��ʧ�ܷ��� false
	void paint(GameStatusStruct * gameStatus);  //��ӡ����

};