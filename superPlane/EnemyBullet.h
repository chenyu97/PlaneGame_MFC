#pragma once
#include "common.h"
#include "EnemyBoss.h"
#include "GameElement.h"
class EnemyBullet :public GameElement
{
	friend class EnemyBoss;
public:
	EnemyBullet(){ ; }
	EnemyBullet(int x, int y);
	EnemyBullet(int x, int y, int  planeType);
	~EnemyBullet();
	void move(bool &disappear)
	{
		posY += 8;
		if (posY > wndHeight)
			disappear = 1;
	}
};

