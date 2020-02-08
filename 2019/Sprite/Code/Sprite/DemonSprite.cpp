#include "DemonSprite.h"

DemonSpriteClass::DemonSpriteClass(rect _position, int _dx, int _dy, ACL_Image* _imgArray, int _score) :
	AutoSpriteClass(_position, _dx, _dy, _imgArray, _score)
{
	;
}
DemonSpriteClass::DemonSpriteClass(ACL_Image* _imgArray) :
	AutoSpriteClass(_imgArray)//�������һ�����鲢��ͼƬ
{
	dx = dy = 2; //�� UserSpriteClass ������Ȼ����Ϸ̫������
	score = 0;
}
DemonSpriteClass::~DemonSpriteClass()
{
	;
}

inline int sign(int x)
{
	if (x == 0)
		return 0;
	else if (x > 0)
		return 1;
	else
		return -1;
}

int DemonSpriteClass::move(const rect & userPosition)
{
	//�趨Ϊ�����������
	if (position.x > userPosition.x + dx)  // ������� dx, ���ߵĲ������������֮�䷴�����������¿��������ת��
		currentImg = LEFT; //����Ϊ������̬
	else
		currentImg = RIGHT; //����Ϊ������̬

	position.x += dx * sign(userPosition.x - position.x);
	position.y += dy * sign(userPosition.y - position.y);

	positionCheck2();

	if (collision(userPosition))
		return -1;
	else
		return 0;
}