#pragma once
#include "Sprite.h"

class AutoSpriteClass : public SpriteClass
{
protected:
	int getImgN() { return 2; } //���ص�ǰ���ͼƬ������֮����д�ɺ��������� const int����Ϊ���ڻ�����ó�Ա����ʱ���ܵ��ø��麯��
public:
	AutoSpriteClass(rect _position, int _dx, int _dy, ACL_Image* _imgArray, int _score);
	AutoSpriteClass(ACL_Image* _imgArray); //�������һ�����鲢��ͼƬ

	~AutoSpriteClass();

	virtual SpriteKind getSpriteKind() { return AUTO_SPRITE; }
	virtual int move(const rect & userPosition);
};