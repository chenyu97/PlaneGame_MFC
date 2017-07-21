#include "stdafx.h"
#include "MePlane.h"
#include "MainFrm.h"
#include "superPlaneDoc.h"
#include "superPlaneView.h"

MePlane::MePlane()
{
	wndWidth = 725;  // frame also has width, which is about 25.
	wndHeight = 945;  //  frame also has height, which is about 55.
	image.Load(L"res/me.bmp");
	imageWidth = image.GetWidth();
	imageHeight = image.GetHeight();
	posX = (wndWidth - imageWidth) / 2;
	posY = wndHeight - imageHeight;
	speed = 12;
}

MePlane::~MePlane()
{
}

void MePlane::shoot()
{
//	int shoot = GetKeyState('J');
//	if (shoot < 0)
	{
//		MeBullet *bullet;
		MeBullet *bullet = new MeBullet(posX + imageWidth / 2, posY);
//		MeBullet *bullet = new MeBullet();
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		CsuperPlaneView* pView = (CsuperPlaneView*)pFrame->GetActiveView();
		pView->meBullets.push_back(bullet);
/*		MeBullet *newBullet = new MeBullet(posX, posY);
		p->meBullets.push_back(newBullet);
*/	}
	
}

void MePlane::superShoot()
{
//	int shoot = GetKeyState('K');
//	if (shoot < 0)
//	{
		for (int i = 0; i < wndWidth; i+=30)
		{
			MeBullet *bullet = new MeBullet(i, posY);


			CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
			CsuperPlaneView* pView = (CsuperPlaneView*)pFrame->GetActiveView();
			pView->meBullets.push_back(bullet);
			/*		MeBullet *newBullet = new MeBullet(posX, posY);
			p->meBullets.push_back(newBullet);
			*/
		}
//	}

}

void MePlane::superSuperShoot()
{

	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CsuperPlaneView* pView = (CsuperPlaneView*)pFrame->GetActiveView();

	vector<EnemyBullet *>::iterator iter2 = pView->enemyBullets.begin();
	for (; iter2 != pView->enemyBullets.end();)
	{
		delete (*iter2);
		iter2 = pView->enemyBullets.erase(iter2);
		(pView->score)++;
		if ((pView->score) >= 100)
		{
			pView->removeElements();
			pView->gameState = RUNNING2;
			return;
		}
	}

	vector<EnemyPlane *>::iterator iter3 = pView->enemyPlanes.begin();
	for (; iter3 != pView->enemyPlanes.end();)
	{
		delete (*iter3);
		iter3 = pView->enemyPlanes.erase(iter3);
	}
}



void MePlane::move()
{
	int up = GetKeyState('W');
	int down = GetKeyState('S');
	int left = GetKeyState('A');
	int right = GetKeyState('D');

	Dir direction = No;
	if (up < 0)
		direction = Up;
	else if (down < 0)
		direction = Down;
	else if (left < 0)
		direction = Left;
	else if (right < 0)
		direction = Right;

	if (direction == Up)
	{
		if (posY - speed < 0)
			posY = 0;
		else
			posY -= speed;
	}
	else if (direction == Down)
	{
		if (posY + speed > wndHeight - imageHeight)
			posY = wndHeight - imageHeight;
		else
			posY += speed;
	}
	else if (direction == Left)
	{
		if (posX - speed < 0)
			posX = 0;
		else
			posX -= speed;
	}
	else if (direction == Right)
	{
		if (posX + speed > wndWidth - imageWidth)
			posX = wndWidth - imageWidth;
		else
			posX += speed;
	}
}