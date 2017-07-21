#pragma once
#include "common.h"
#include "MeBullet.h"
#include "GameElement.h"
class CsuperPlaneView;
class MePlane :public GameElement
{
public:
	MePlane();
	~MePlane();
	void move();
	void shoot();
	void superShoot();
	void superSuperShoot();
private:
	int speed;
};

