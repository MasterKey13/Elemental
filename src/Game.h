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
#include "celestial_body.h"
#include "synthesizer.h"
#include "battle.h"
#include "gui/battle_gui.h"
#include "equipment.h"
#include "npc.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Game, spGame);
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Location, spLocation);
DECLARE_SMART(Character, spCharacter);
DECLARE_SMART(Item, spItem);
DECLARE_SMART(CelestialBody, spCelestialBody);
DECLARE_SMART(Synthesizer, spSynthesizer);
DECLARE_SMART(Battle, spBattle);
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Mine, spMine);

class Game : public Actor
{
  public:
	  Game();

	  void init();

  private:
	  void doUpdate(const UpdateState &us);

	  spShip _player_ship; 
    spHull _hull;
    spEngine _engine;
    spBattery _battery;
    spEquipment _weapon;

    spNPC _eric;
    spShip _enemy_ship;
    spHull _hull2;
    spEngine _engine2;
    spBattery _battery2;
    spEquipment _weapon2;

    spBattle _battle;
};