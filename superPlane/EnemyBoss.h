#pragma once
#include "common.h"
#include "EnemyBullet.h"
#include "GameElement.h"
class EnemyBoss:public GameElement
{
public:
	EnemyBoss();
	~EnemyBoss();
	void shoot();
	void move();
};

