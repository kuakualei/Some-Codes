#include "Bomb.h"
#include "../GameStatus.h"

using namespace std;

BombClass::BombClass(ACL_Image * _img, ACL_Sound * _explodeSound): ToolClass()
{
#ifdef DEBUG_TOOL
	nextAppearTime = 0;
#else
#ifdef MORE_TOOL
	nextAppearTime = 100 - rand() % 50;
#else
	nextAppearTime = 500 - rand() % 100;
#endif
#endif

	img = _img;
	explodeImg = _img + 1;
	explodeSound = _explodeSound;
}


int BombClass::getVirtualKey()       //�ͷŵ��ߵİ�����Virtual Key�������ڴ�������
{
	return 'Z';
}
const char * BombClass::getVirtualKeyString() //�ͷŵ��ߵİ������ַ�������������ʾ����Ļ��
{
	return "Z";
}

int BombClass::getNextAppearTime()
{
	return nextAppearTime;
}

bool BombClass::gain()
{
	assert(status == ONBOARD);

	status = INBAG;

	//ʹ�õ��߳��������½�
	position.x = 20;
	position.y = 500;

	return true;
}

static int paintingReleasingTimeCurrent;

bool BombClass::release(GameStatusStruct * gameStatus) //�ͷŵ��߲�����Ч��
{
	if (status != INBAG)
		return false;

	status = RELEASING;

	//����Ǿ������򲥷���Ч
	if (gameStatus->musicSwitchMode == 0)
		playSound(*explodeSound, 0);

	//���Ѿ���Ⱦ�Ĵ�������
	paintingReleasingTimeCurrent = 0;

	//����ɱ��ͬ�С�ͬ�е����й������ǿ�ƽ����ħ
	rect userPosi = gameStatus->userSprite->getPosition();
	auto autoSpriteIter = gameStatus->autoSpriteList.begin();
	while (autoSpriteIter != gameStatus->autoSpriteList.end())
	{
		rect autoPosi = (*autoSpriteIter)->getPosition();
		if (
			(userPosi.x <= autoPosi.x && autoPosi.x <= userPosi.x + userPosi.width) ||
			(autoPosi.x <= userPosi.x && userPosi.x <= autoPosi.x + autoPosi.width) ||
			(userPosi.y <= autoPosi.y && autoPosi.y <= userPosi.y + userPosi.height) ||
			(autoPosi.y <= userPosi.y && userPosi.y <= autoPosi.y + autoPosi.height)
			) // ���� x ���� �� y ���꣬�ཻ��
		{
			int bouns = (*autoSpriteIter)->getScore();
			gameStatus->userSprite->addScore(bouns);
			delete *autoSpriteIter;
			autoSpriteIter = gameStatus->autoSpriteList.erase(autoSpriteIter);
		}
		else
		{
			autoSpriteIter++;
		}
	}

	nextAppearTime = gameStatus->gameClock * 2; //�������ɵĵ�������
	return true;
}

void BombClass::paint(GameStatusStruct * gameStatus)
{
	//ֻ���� RELEASING ģʽ�²ŵ��ü̳���ĺ���
	if (status != RELEASING)
	{
		ToolClass::paint(gameStatus);
		return;
	}

	rect userPosi = gameStatus->userSprite->getPosition();

	putImageScale(explodeImg, 0, userPosi.y, WINDOW_WIDTH, userPosi.height);
	putImageScale(explodeImg, userPosi.x, 0, userPosi.width, WINDOW_HEIGHT);

	paintingReleasingTimeCurrent++;

	if (PaintingReleasingTimeConst == paintingReleasingTimeCurrent)
		status = INVALID;

}