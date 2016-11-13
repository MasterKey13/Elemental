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

    spItem _hull;
    spItem _armor;
    spItem _engine;
    spItem _battery;
    spItem _weapon;

    spCelestialBody _star;
    spCelestialBody _planet;
    spItem _mine;

    spSynthesizer _synth;

    spItem _file_item;

    spBattle _battle;

    spBattleGui _battle_gui;
};