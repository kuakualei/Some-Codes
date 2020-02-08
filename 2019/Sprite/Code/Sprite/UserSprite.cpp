#include "UserSprite.h"

UserSpriteClass::UserSpriteClass(rect _position, int _dx, int _dy, ACL_Image* _img, int _score /* = 0 */) :
	SpriteClass(_position, _dx, _dy, _img, _score)
{
	;
}
UserSpriteClass::UserSpriteClass(ACL_Image* _img)
{
	position.x = rand() % WINDOW_WIDTH - DEFAULT_SPRITE_WIDTH;
	if (position.x < 0)
		position.x = 0;
	position.y = rand() % WINDOW_HEIGHT - DEFAULT_SPRITE_HEIGHT;
	if (position.y < 0)
		position.y = 0;
	dx = 5;
	dy = 5;
	imgArray = _img;
	score = 0;
}
UserSpriteClass::~UserSpriteClass()
{
	;
}

void UserSpriteClass::setPosition(const rect & _position) //��������ʹ�С
{
	position = _position;
	positionCheck();
}
int UserSpriteClass::move(int key)  //�����ƶ�
{
	int speedRatio = 1; //���ٱ���

#ifdef SHIFT_SPEED_UP
	if (GetKeyState(VK_SHIFT) & 0x80) //���������٣��� Shift ������
		speedRatio = 2;
#endif

	if (key == VK_UP)
		position.y -= speedRatio * dy, currentImg = UP;
	else if (key == VK_DOWN)
		position.y += speedRatio * dy, currentImg = DOWN;
	else if (key == VK_LEFT)
		position.x -= speedRatio * dx, currentImg = LEFT;
	else if (key == VK_RIGHT)
		position.x += speedRatio * dx, currentImg = RIGHT;
	positionCheck();

	return 0;
}

//���������������Զ���ᱻ���ã�ֻ��Ϊ���ܹ�ʵ��������ʵ���˸�����麯����
int UserSpriteClass::move(const rect & rectangle)
{
	assert(0);
	return 0;
}

void UserSpriteClass::addSpeed(int bonus)
{
	dx += bonus;
	dy += bonus;
}
void UserSpriteClass::addScore(int bouns)
{
	score += bouns;
}

//���������Զ����飬���Ƿ�����ײ�ģ�����У���Ҫ���ۼӷ֡�ɾ������Ϸ��������Ϸ����ʱ���� -1
int UserSpriteClass::settleScore(std::list<AutoSpriteClass*>& autoSpriteList)
{
	auto autoSpriteIter = autoSpriteList.begin();
	while (autoSpriteIter != autoSpriteList.end())
	{
		if (this->collision((*autoSpriteIter)->getPosition()))
		{
			int bouns = (*autoSpriteIter)->getScore();
			if ((*autoSpriteIter)->getSpriteKind() == DEMON_SPRITE)  //���ײ�����Ƕ�ħ���ͽ�����Ϸ
				return -1;
			this->addScore(bouns);
			delete* autoSpriteIter;
			autoSpriteIter = autoSpriteList.erase(autoSpriteIter);
		}
		else
		{
			autoSpriteIter++;
		}
	}
	return 0;
}