#pragma once
#include "common.h"
#include "GameElement.h"
class ExtraElement :public GameElement
{
public:
	ExtraElement();
	~ExtraElement();
	virtual void move(bool &disappear);
public:
	int extraElementType;
};

