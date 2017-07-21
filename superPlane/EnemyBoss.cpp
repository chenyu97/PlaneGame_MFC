#include "stdafx.h"
#include "EnemyBoss.h"
#include "MainFrm.h"
#include "superPlaneDoc.h"
#include "superPlaneView.h"

EnemyBoss::EnemyBoss()
{
	wndWidth = 725;  // frame also has width, which is about 25.
	wndHeight = 945;  //  frame also has height, which is about 55.
	image.Load(L"res/boss.bmp");
	imageWidth = image.GetWidth();
	imageHeight = image.GetHeight();
	posX = wndWidth / 3;
	posY = 0 - imageHeight;
}


EnemyBoss::~EnemyBoss()
{
}
void EnemyBoss::shoot()
{
	//	int shoot = GetKeyState('J');
	//	if (shoot < 0)
	{
		//		MeBullet *bullet;
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		CsuperPlaneView* pView = (CsuperPlaneView*)pFrame->GetActiveView();

		EnemyBullet *bullet = new EnemyBullet(posX + imageWidth / 2, posY + imageHeight,-1);
		//		MeBullet *bullet = new MeBullet();
		pView->enemyBullets.push_back(bullet);
		
		bullet = new EnemyBullet(posX + imageWidth / 2  - 80, posY + imageHeight,-1);
		pView->enemyBullets.push_back(bullet);

		bullet = new EnemyBullet(posX + imageWidth / 2 + 80, posY + imageHeight,-1);
		pView->enemyBullets.push_back(bullet);

		bullet = new EnemyBullet(posX + imageWidth / 2 - 40, posY + imageHeight,-1);
		pView->enemyBullets.push_back(bullet);


		bullet = new EnemyBullet(posX + imageWidth / 2 + 40, posY + imageHeight,-1);
		pView->enemyBullets.push_back(bullet);

		/*		MeBullet *newBullet = new MeBullet(posX, posY);
		p->meBullets.push_back(newBullet);
		*/	}

}
void EnemyBoss::move()
{
	Dir direction = No;

	if (posY < wndHeight / 5)
		direction = Down;
	else
	{
		int random = rand() % 2;
		int left = 0, right = 0;
		if (random == 0)
			left = -1;
		else if (random == 1)
			right = -1;

		if (left < 0)
			direction = Left;
		else if (right < 0)
			direction = Right;
	}

	if (direction == Down)
	{
		if (posY + 20 < wndHeight / 5)
			posY += 20;
		else
			posY = wndHeight / 5;
	}
	else if (direction == Left)
	{
		if (posX - 20 < 0)
			posX = 0;
		else
			posX -= 20;
	}
	else if (direction == Right)
	{
		if (posX + 20 > wndWidth - imageWidth)
			posX = wndWidth - imageWidth;
		else
			posX += 20;
	}
}