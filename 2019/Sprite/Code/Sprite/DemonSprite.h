#pragma once
#include "AutoSprite.h"

class DemonSpriteClass : public AutoSpriteClass
{
	int getImgN() { return 2; } //���ص�ǰ���ͼƬ������֮����д�ɺ��������� const int����Ϊ���ڻ�����ó�Ա����ʱ���ܵ��ø��麯��
public:
	DemonSpriteClass(rect _position, int _dx, int _dy, ACL_Image* _imgArray, int _score);
	DemonSpriteClass(ACL_Image* _imgArray); //�������һ�����鲢��ͼƬ

	~DemonSpriteClass();

	virtual SpriteKind getSpriteKind() { return DEMON_SPRITE; }

	virtual int move(const rect & userPosition);
};