#include "stdafx.h"
#include "ExtraElement.h"

ExtraElement::ExtraElement()
{
	wndWidth = 725;  // frame also has width, which is about 25.
	wndHeight = 945;  //  frame also has height, which is about 55.
	int random = rand() % 7;
	if (random == 0)
	{
		image.Load(L"res/superSuperShoot.bmp");
		extraElementType = 3;
	}
	else if (random % 2 == 1)
	{
		image.Load(L"res/superShoot.bmp");
		extraElementType = 2;
	}
	else
	{
		image.Load(L"res/blood.bmp");
		extraElementType = 1;
	}
	//	image.GetWidth();
	//	imageWidth = 10;
	imageWidth = image.GetWidth();
	imageHeight = image.GetHeight();
	posX = rand() % (wndWidth - imageWidth);
	posY = 0 - imageHeight;
}


ExtraElement::~ExtraElement()
{
}

void ExtraElement::move(bool &disappear)
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
		posY += 1;
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