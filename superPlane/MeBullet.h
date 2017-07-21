#pragma once
#include "GameElement.h"
class MeBullet :public GameElement
{
public:
	MeBullet(){ ; }
	MeBullet(int x, int y);
	~MeBullet();
	void move(bool &disappear)
	{
		posY -= 15;
		if (posY < 0)
			disappear = 1;
	}
};

