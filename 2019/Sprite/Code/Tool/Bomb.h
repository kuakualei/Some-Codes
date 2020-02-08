#pragma once
#include "Tool.h"

//ը�����ߣ�����ը��ͬ�С�ͬ�еľ���
class BombClass : public ToolClass
{
	friend class ToolManagerClass;
private:
	int nextAppearTime; //��һ�γ��ֵ�ʱ��
	ACL_Image * explodeImg;
	ACL_Sound * explodeSound;
	const int PaintingReleasingTimeConst = 15;  //�ͷŵ�ʱ����� 15 �Σ��� 600ms

	int getVirtualKey();       //�ͷŵ��ߵİ�����Virtual Key�������ڴ�������
	const char * getVirtualKeyString(); //�ͷŵ��ߵİ������ַ�������������ʾ����Ļ��

	int getNextAppearTime();
	bool gain();
	bool release(GameStatusStruct * gameStatus); //�ͷŵ��߲�����Ч��
	void paint(GameStatusStruct * gameStatus);

public:
	BombClass(ACL_Image * _img, ACL_Sound * _explodeSound);
};