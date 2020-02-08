#pragma once
#include "Tool.h"

//��Сҩˮ����ʹ��ҵĴ�С��Сһ��ʱ�䣬���ѱ���ħ���鲶׽
class ShrinkPotionClass : public ToolClass
{
	friend class ToolManagerClass;
private:
	ACL_Sound * potionSound;
	int nextAppearTime; //��һ�γ��ֵ�ʱ�䣬�� 40ms Ϊ��λ
	const int PaintingReleasingTimeConst = 400;  //�ͷŵ�ʱ����� 400 �Σ��� 16000 ms

	int getVirtualKey();       //�ͷŵ��ߵİ�����Virtual Key�������ڴ�������
	const char * getVirtualKeyString(); //�ͷŵ��ߵİ������ַ�������������ʾ����Ļ��

	int getNextAppearTime();
	bool gain();
	bool release(GameStatusStruct * gameStatus); //�ͷŵ��߲�����Ч��
	void paint(GameStatusStruct * gameStatus);
public:
	ShrinkPotionClass(ACL_Image * _img, ACL_Sound * _potionSound);
};