#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

//Declare smart pointers

class TravelBar : public Actor
{
public:
	TravelBar();

	void init();


private:
	spSprite _bar;
};