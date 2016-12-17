/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

#include "character.h"
#include "hull.h"
#include "target.h"

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

    //SETTERS
    void setName(std::string name);
    void setHull(spHull hull);
    void setShipPosition(POSITION pos);
    bool find(Target* part);

    //GETTERS
	  std::string getName();
    spHull getHull();

  private:
    std::string _name;
    spHull _hull;
};