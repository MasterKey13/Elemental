/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"
#include "location.h"
#include "character.h"
#include "player.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Game, spGame);
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Location, spLocation);
DECLARE_SMART(Character, spCharacter);

class Game : public Actor
{
  public:
	  Game();

	  void init();

  private:
	  void doUpdate(const UpdateState &us);

	  spShip _player_ship; 
	  spLocation _location;
	  spCharacter _player; 
};