#pragma once
#include "Sprite.h"
#include "AutoSprite.h"

class UserSpriteClass : public SpriteClass
{
	friend class ShrinkPotionClass;
protected:
	int getImgN() { return 4; }     //���ص�ǰ���ͼƬ������֮����д�ɺ��������� const int����Ϊ���ڻ�����ó�Ա����ʱ���ܵ��ø��麯��
	void setPosition(const rect & _position); //��������ʹ�С
	
public:
	UserSpriteClass(rect _position, int _dx, int _dy, ACL_Image* _imgArray, int _score = 0);
	UserSpriteClass(ACL_Image* _imgArray); //��������û����鲢��ͼƬ
	~UserSpriteClass();

	virtual SpriteKind getSpriteKind() { return USER_SPRITE; }

	int move(int key);               //�����ƶ�
	int move(const rect & userPosition);     //�麯����ʵ�֣�����

	void addSpeed(int bonus);
	void addScore(int bouns);
	int settleScore(std::list<AutoSpriteClass*> & autoSpriteList); //�û��ƶ��Ժ󣬶�ײ���ľ�����н��㣬��Ϸ����ʱ���� -1
};
