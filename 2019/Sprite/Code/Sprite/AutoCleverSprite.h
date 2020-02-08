#pragma once
#include "AutoSprite.h"

class AutoCleverSpriteClass : public AutoSpriteClass
{
protected:
	bool danger(const rect & userPosition); //�����ܣ��ж��û��Ƿ�����Χ
	int getImgN() { return 2; }     //���ص�ǰ���ͼƬ������֮����д�ɺ��������� const int����Ϊ���ڻ�����ó�Ա����ʱ���ܵ��ø��麯��
public:
	AutoCleverSpriteClass(rect _position, int _dx, int _dy, ACL_Image* _imgArray, int _score);
	AutoCleverSpriteClass(ACL_Image* _imgArray);
	~AutoCleverSpriteClass();

	virtual SpriteKind getSpriteKind() { return AUTO_CLEVER_SPRITE; }

	int move(const rect & userPosition);
};