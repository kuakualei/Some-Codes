#pragma once
#include <vector>
#include <list>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <cmath>
#include "../acllib.h"
#include "../GameConfig.h"

enum Direction
{
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};

enum SpriteKind
{
	USER_SPRITE = 0,
	AUTO_SPRITE = 1,
	AUTO_CLEVER_SPRITE = 2,
	DEMON_SPRITE = 3
};

class SpriteClass
{
protected:
	rect position;       //����ĵ�ǰλ�ã��������Ͻǵ����� x, y ��ͼƬ�ĳ��� width, height
	int dx, dy;          //�ƶ����ٶ�
	ACL_Image * imgArray;//ͼƬ��Ϣ����һ�����飬�洢�˾��鲻ͬ�����ͼƬ
	Direction currentImg;             //��ǰ����״̬��ͼƬ�±꣬ 0�� 1�� 2�� 3��
	int score;

	virtual int getImgN() = 0;        //���麯��ʵ�֣�ʹ�ø����ܵõ������ͼƬ�������ж��Ƿ�Խ��

	void positionCheck();              //�������꣨��ֹ�����ƶ�����ʹ����Ϸ�
	void positionCheck2();             //�������꣨ͨ����ǽ����ʹ����Ϸ�
public:
	SpriteClass(const rect & _position, int _dx, int _dy, ACL_Image* _imgArray, int _score);
	SpriteClass(); //��������ľ���
	~SpriteClass();

	virtual SpriteKind getSpriteKind() = 0;

	void paintSprite();

	rect getPosition();
	int getScore();
	bool collision(const rect & position2);   //�ж����������Ƿ��ཻ��true ��ʾ�ཻ
	float distance(const rect & position2);

	virtual int move(const rect & userPosition) = 0;
	//���� -1 ��ʾ�з�����ײ������ 0 ��ʾ����ײ
};

