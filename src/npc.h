#pragma once
#include "oxygine-framework.h"
#include "Character.h"
using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(NPC, spNPC);

class NPC : public Character
{
public:
	NPC();
	void init();

private:

};