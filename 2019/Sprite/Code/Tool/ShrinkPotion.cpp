#include "ShrinkPotion.h"
#include "../GameStatus.h"

using namespace std;

ShrinkPotionClass::ShrinkPotionClass(ACL_Image * _img, ACL_Sound * _potionSound) : ToolClass()
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
	potionSound = _potionSound;
}

int ShrinkPotionClass::getVirtualKey()       //�ͷŵ��ߵİ�����Virtual Key�������ڴ�������
{
	return 'X';
}
const char * ShrinkPotionClass::getVirtualKeyString() //�ͷŵ��ߵİ������ַ�������������ʾ����Ļ��
{
	return "X";
}

int ShrinkPotionClass::getNextAppearTime()
{
	return nextAppearTime;
}

bool ShrinkPotionClass::gain()
{
	assert(status == ONBOARD);

	status = INBAG;

	//ʹ�õ��߳��������½�
	position.x = 125;
	position.y = 500;

	return true;
}

static int paintingReleasingTimeCurrent;

bool ShrinkPotionClass::release(GameStatusStruct * gameStatus) //�ͷŵ��߲�����Ч��
{
	if (status != INBAG)
		return false;

	status = RELEASING;

	//����Ǿ������򲥷���Ч
	if (gameStatus->musicSwitchMode == 0)
		playSound(*potionSound, 0);

	//���Ѿ���Ⱦ�Ĵ�������
	paintingReleasingTimeCurrent = 0;

	//�������
	rect userPosition = gameStatus->userSprite->getPosition();
	userPosition.width /= 2;
	userPosition.height /= 2;
	gameStatus->userSprite->setPosition(userPosition);

	nextAppearTime = gameStatus->gameClock * 2; //�������ɵĵ�������
	return true;
}

void ShrinkPotionClass::paint(GameStatusStruct * gameStatus)
{
	//ֻ���� RELEASING ģʽ�²ŵ��ü̳���ĺ���
	if (status != RELEASING)
	{
		ToolClass::paint(gameStatus);
		return;
	}

	paintingReleasingTimeCurrent++;

	if (PaintingReleasingTimeConst == paintingReleasingTimeCurrent)
	{
		status = INVALID;

		//ʱ�䵽�Ժ󣬵ðѳߴ�Ļ���

		rect userPosition = gameStatus->userSprite->getPosition();
		userPosition.width *= 2;
		userPosition.height *= 2;
		gameStatus->userSprite->setPosition(userPosition);
	}
}