#include "stdafx.h"
#include "MeBullet.h"

MeBullet::MeBullet(int x, int y)
{
	wndWidth = 725;  // frame also has width, which is about 25.
	wndHeight = 945;  //  frame also has height, which is about 55.
	image.Load(L"res/meBullet.bmp");
//	image.GetWidth();
//	imageWidth = 10;
	imageWidth = image.GetWidth();
	imageHeight = image.GetHeight();
	posX = x - 2;  // change the position a little 
	posY = y - imageHeight;
}


MeBullet::~MeBullet()
{

}
