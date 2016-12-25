/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

#include "character.h"
#include "hull.h"
#include "target.h"
#include "npc.h"
#include "battle.h"

#include <string>
#include <cmath>
#include <vector>

using namespace oxygine;

#define MAX_ELEMENTS 50

enum POSITION
{
  player,
  enemy
};

//Declare smart pointers
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Character, spCharacter);
DECLARE_SMART(Battle, spBattle);

class Ship : public Actor
{
  public:
	  Ship();

    void init(
      std::string name,
      spHull hull
      );

    void log();

    bool isAlive();
    bool find(Target* part);
    void processTurn(spBattle battle, spShip enemy);

    //SETTERS
    void setName(std::string name);
    void setHull(spHull hull);
    void setShipPosition(POSITION pos);
    void setPilot(spCharacter pilot);

    //GETTERS
	  std::string getName();
    spHull getHull();
    spCharacter getPilot();

  private:
    std::string _name;
    spHull _hull;
    spCharacter _pilot;
};