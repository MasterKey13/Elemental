/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "character.h"
#include "hull.h"
#include "battery.h"
#include "engine.h"
#include "equipment.h"

#include <string>
#include <cmath>
#include <vector>

using namespace oxygine;

#define MAX_ELEMENTS 50

//Declare smart pointers
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Engine, spEngine);
DECLARE_SMART(Equipment, spEquipment);

class Ship : public Actor
{
  public:
	  Ship();

    void init(
      std::string name,
      spHull hull,
      spBattery battery,
      spEngine engine);

	 
    //SETTERS
    void setName(std::string name);
    void setHull(spHull hull);
    void setBattery(spBattery battery);
    void setEngine(spEngine engine);

    //GETTERS
	  std::string getName();
    spHull getHull();
    spBattery getBattery();
    spEngine getEngine();

  private:
	  void doUpdate(const UpdateState &us);

    //main components
    std::string _name;
    spHull _hull;
    spBattery _battery;
    spEngine _engine;

};