#pragma once
#include "acllib.h"

#include "Sprite/AutoSprite.h"
#include "Sprite/UserSprite.h"

class ToolManagerClass; //ǰ������

enum ProgressStatus
{
	INVALID_STATUS,
	WELCOME_STATUS,
	GAMING_STATUS,
	PAUSE_STATUS,
	GAME_OVER_STATUS
};

struct GameStatusStruct               //����ÿһ����Ϸ״̬�Ĳ���
{
	int musicSwitchMode;             //�������ؼ���״̬��0 ��ʾ����1 ��ʾ�أ�
	int exitSwitchMode;              //exit ���ص�״̬
	ProgressStatus progress;         //Ŀǰ��Ϸ����
	COLORREF scoreColor;             //��ʾ��������ɫ
	int demonSpriteN;                //���ϵĶ�ħ��
	int gameClock;                   //��Ϸ��ʱ�ӣ�ÿ 40ms Ϊһ�� CLOCK������һ���ƶ������㡢���
	UserSpriteClass* userSprite;     //�û��ľ���
	std::list<AutoSpriteClass*> autoSpriteList; //�Զ��������������Ԫ��Ϊָ�룬�ſ��Խ��ж�̬��̬
	ToolManagerClass* toolManager;   //������ߵ���

	GameStatusStruct();
	~GameStatusStruct();
};