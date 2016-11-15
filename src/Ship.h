/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "character.h"
#include "item.h"

#include <string>
#include <cmath>
#include <vector>

using namespace oxygine;

#define MAX_ELEMENTS 50

//Declare smart pointers
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Item, spItem);

class Ship : public Actor
{
  public:
	  Ship();

    void init(
      std::string name,

      spItem hull,
      spItem battery,
      spItem engine);

    void log();
	 
    //SETTERS
    void setName(std::string name);

    void setHull(spItem hull);
    void setBattery(spItem battery);
    void setEngine(spItem engine);

    //GETTERS
	  std::string getName();

    spItem getHull();
    spItem getBattery();
    spItem getEngine();

  private:
	  void doUpdate(const UpdateState &us);

    std::string _name;

    spItem _hull;
    spItem _battery;
    spItem _engine;

};