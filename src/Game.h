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
#include "item.h"
#include "hull.h"
#include "armor.h"
#include "battery.h"
#include "engine.h"
#include "weapon.h"
#include "celestial_body.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Game, spGame);
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Location, spLocation);
DECLARE_SMART(Character, spCharacter);
DECLARE_SMART(Item, spItem);
DECLARE_SMART(Armor, spArmor);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Engine, spEngine);
DECLARE_SMART(Weapon, spWeapon);
DECLARE_SMART(CelestialBody, spCelestialBody);

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
    spItem _item;

    spHull _hull;
    spArmor _armor;
    spEngine _engine;
    spBattery _battery;
    spWeapon _weapon;

    spCelestialBody _star;
};