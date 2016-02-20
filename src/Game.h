#pragma once
#include "oxygine-framework.h"
#include "Space.h"
#include "Ship.h"
#include "Location.h"
#include "Character.h"
#include "Player.h"
#include "TravelBar.h"
using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Game, spGame);
DECLARE_SMART(Space, spSpace);
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Location, spLocation);
DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(TravelBar, spTravelBar);

class Game : public Actor
{
public:
	Game();

	void init();

private:
	void doUpdate(const UpdateState &us);

	spSpace _space;
	spShip _playerShip;
	spLocation _location;
	spCharacter _player;
	spTravelBar _travelBar;
};