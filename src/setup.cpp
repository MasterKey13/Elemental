/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "oxygine-framework.h"
#include <functional>
#include "game.h"
#include "resources.h"
using namespace oxygine;

void setup_preinit()
{

}

//called from entry_point.cpp
void setup_init()
{
	//load xml file with resources definition
	resources::load();

	//create new Game
	spGame game = new Game;
	game->init();
	game->attachTo(getStage());
}


//called each frame from entry_point.cpp
void setup_update()
{

}

//called each frame from entry_point.cpp
void setup_destroy()
{
  //free previously loaded resources
	resources::free();
}
