#include "AutoSprite.h"

AutoSpriteClass::AutoSpriteClass(rect _position, int _dx, int _dy, ACL_Image* _imgArray, int _score) :
	SpriteClass(_position, _dx, _dy, _imgArray, _score)
{
	;
}
AutoSpriteClass::AutoSpriteClass(ACL_Image* _imgArray) : 
	SpriteClass()
{
	position.x = rand() % WINDOW_WIDTH - DEFAULT_SPRITE_WIDTH;
	if (position.x < 0)
		position.x = 0;
	position.y = rand() % WINDOW_HEIGHT - DEFAULT_SPRITE_HEIGHT;
	if (position.y < 0)
		position.y = 0;
	dx = rand() % 5 + 1;
	dy = rand() % 5 + 1;
	currentImg = RIGHT; //Ĭ������
	score = 1;
	imgArray = _imgArray;
}

AutoSpriteClass::~AutoSpriteClass()
{
	;
}

int AutoSpriteClass::move(const rect & userPosition) 
{
	//����߽��Ժ�ת��
	if (position.x<0 || position.x + position.width > WINDOW_WIDTH)
	{
		dx *= -1;
		currentImg = Direction((LEFT + RIGHT) - currentImg); // �����໥�л�
	}
	if (position.y<0 || position.y + position.height > WINDOW_HEIGHT) 
		dy *= -1;
	position.x += dx;
	position.y += dy;

	if (collision(userPosition))
		return -1;
	//����Ҫ���߽�
	else
		return 0;
}