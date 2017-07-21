#pragma once
#include "common.h"
#include "EnemyBullet.h"
#include "GameElement.h"
class EnemyPlane:public GameElement
{
public:
	EnemyPlane();
//	EnemyPlane(int x,int y);
	~EnemyPlane();
	virtual void move(bool &disappear);
	virtual void shoot();
public:
	int planeType;
};

