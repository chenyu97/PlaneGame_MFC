#pragma once
class GameElement
{
public:
	GameElement();
	~GameElement();
	void draw(CDC *pDC)
	{
		image.Draw(pDC->m_hDC, posX, posY);
	}
	int getIW(){ return imageWidth; }
	int getIH(){ return imageHeight; }
	int getX(){ return posX; }
	int getY(){ return posY; }
	int getWW(){ return wndWidth; }
	int getWH(){ return wndHeight; }
	void setPosition(int x, int y){ posX = x; posY = y; }
protected:
	int wndWidth;
	int wndHeight; //clientWnd
	CImage image;
	int imageWidth;
	int imageHeight;
	int posX;
	int posY;
};

