#include "stdafx.h"
#include "EnemyBullet.h"


EnemyBullet::EnemyBullet(int x, int y)
{
	wndWidth = 725;  // frame also has width, which is about 25.
	wndHeight = 945;  //  frame also has height, which is about 55.
	int random = rand() % 3;
	if (random == 0)
		image.Load(L"res/enemyBullet.bmp");
	else if (random == 1)
		image.Load(L"res/enemyBullet2.bmp");
	else
		image.Load(L"res/enemyBullet3.bmp");
	//	image.GetWidth();
	//	imageWidth = 10;
	imageWidth = image.GetWidth();
	imageHeight = image.GetHeight();
	posX = x - 8;  // change the position a little 
	posY = y;
}

EnemyBullet::EnemyBullet(int x, int y,int planeType)
{
	wndWidth = 725;  // frame also has width, which is about 25.
	wndHeight = 945;  //  frame also has height, which is about 55.
	if (planeType == 1)
	{
		image.Load(L"res/enemyBullet2.bmp");
	}
	else if (planeType == 3)
	{
		image.Load(L"res/enemyBullet3.bmp");
	}
	else
	{
		image.Load(L"res/enemyBullet.bmp");
	}
	//	image.GetWidth();
	//	imageWidth = 10;
	imageWidth = image.GetWidth();
	imageHeight = image.GetHeight();
	posX = x - 8;  // change the position a little 
	posY = y;
}

EnemyBullet::~EnemyBullet()
{
}
