#include "stdafx.h"
#include "EnemyPlane.h"
#include "MainFrm.h"
#include "superPlaneDoc.h"
#include "superPlaneView.h"

EnemyPlane::EnemyPlane()
{
	wndWidth = 725;  // frame also has width, which is about 25.
	wndHeight = 945;  //  frame also has height, which is about 55.
	int random = rand() % 3;
	if (random == 0)
	{
		image.Load(L"res/enemy.bmp");
		planeType = 1;
	}
	else if (random == 1)
	{
		image.Load(L"res/enemy2.bmp");
		planeType = 2;
	}
	else
	{
		image.Load(L"res/enemy3.bmp");
		planeType = 3;
	}
	imageWidth = image.GetWidth();
	imageHeight = image.GetHeight();
	posX = rand() % (wndWidth - imageWidth);
	posY = 0 - imageHeight;
}


EnemyPlane::~EnemyPlane()
{
}

void EnemyPlane::shoot()
{
	//	int shoot = GetKeyState('J');
	//	if (shoot < 0)
	//		MeBullet *bullet;
	EnemyBullet *bullet = new EnemyBullet(posX + imageWidth / 2, posY + imageHeight,planeType);
	//		MeBullet *bullet = new MeBullet();

	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CsuperPlaneView* pView = (CsuperPlaneView*)pFrame->GetActiveView();
	pView->enemyBullets.push_back(bullet);
	/*		MeBullet *newBullet = new MeBullet(posX, posY);
	p->meBullets.push_back(newBullet);
	*/	

}
void EnemyPlane::move(bool &disappear)
{
	int random = rand() % 5;
	int left = 0, down = 0, right = 0;
	if (random == 0)
		left = -1;
	else if (random == 1)
		right = -1;
	else
		down = -1;

	Dir direction = No;
	/*		if (down < 0)
	direction = Down;
	else if (left < 0)
	direction = Left;
	else if (right < 0)
	direction = Right;
	*/
	direction = Down;
	if (direction == Down)
	{
		posY += 3;
		if (posY > wndHeight)
			disappear = 1;
	}
	else if (direction == Left)
	{
		if (posX - 5 < 0)
			posX = 0;
		else
			posX -= 5;
	}
	else if (direction == Right)
	{
		if (posX + 5 > wndWidth - imageWidth)
			posX = wndWidth - imageWidth;
		else
			posX += 5;
	}
}