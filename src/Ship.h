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
DECLARE_SMART(Character, spCharacter);
DECLARE_SMART(Item, spItem);

class Ship : public Actor
{
  public:
	  Ship();

	  void init(
      std::string name, 
      int x, int y, 
      int chem_cap,
      int inventory_cap, 
      float fuel_cap, 
      float fuel_level, 
      int evasion,
      spItem hull,
      spItem battery,
      spItem engine,
      spCharacter captain = nullptr);

    void log();
	 
    //SETTERS
    void setName(std::string name);
    void setCoordinates(int x, int y);
    void setChemCap(int chem_cap);
    void setChemAmount(int element, int amount);
    void setChemDefault();
    void setInventoryCap(int inventory_cap);
    void setFuelCap(float fuel_cap);
    void setFuelLevel(float fuel_level);
    void setEvasion(int evasion);
    void setCaptain(spCharacter captain);
    void setHull(spItem hull);
    void setBattery(spItem battery);
    void setEngine(spItem engine);

    //GETTERS
	  std::string getName();
    int getXPos();
    int getYPos();
    int getChemCap();
    float getFuelLevel();
    float getFuelCap();
    int getEvasion();
    int getChemAmount(int element);
    spCharacter getCaptain();
    spItem getHull();
    spItem getBattery();
    spItem getEngine();

    void travelTo(int x, int y);

  private:
	  void doUpdate(const UpdateState &us);

	  int _xPos, _yPos;
	  std::string _name; 
	  spCharacter _captain;
    int _evasion; 
    int _chem_cap;
    int _chem[MAX_ELEMENTS];
    int _inventory_cap; 
    std::vector<spItem> _inventory; 
    float _fuel_level; 
    float _fuel_cap;

    spItem _hull;
    spItem _battery;
    spItem _engine;

    //TODO: weapons used by the ship
};