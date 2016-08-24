/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "character.h"
#include "item.h"
#include "armor.h"

#include <string>
#include <cmath>
#include <vector>

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Character, spCharacter);
DECLARE_SMART(Item, spItem);
DECLARE_SMART(Armor, spArmor);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Engine, spEngine);

class Ship : public Item
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
      spHull hull,
      spBattery battery,
      spEngine engine,
      spCharacter captain = nullptr,
      spArmor armor = nullptr);
	 
    //SETTERS
    void setName(std::string name);
    void setCoordinates(int x, int y);
    void setChemCap(int chem_cap);
    void setInventoryCap(int inventory_cap);
    void setFuelCap(float fuel_cap);
    void setFuelLevel(float fuel_level);
    void setEvasion(int evasion);
    void setCaptain(spCharacter captain);
    void setArmor(spArmor armor);
    void setHull(spHull hull);
    void setBattery(spBattery battery);
    void setEngine(spEngine engine);

    //GETTERS
	  std::string getName();
    int getXPos();
    int getYPos();
    int getChemCap();
    float getFuelLevel();
    float getFuelCap();
    int getEvasion();
    spCharacter getCaptain();
    spArmor getArmor();
    spHull getHull();
    spBattery getBattery();
    spEngine getEngine();

    void travelTo(int x, int y); //travel the ship to a certain location

  private:
	  void doUpdate(const UpdateState &us);

	  int _xPos, _yPos; //coordinates of the ship
	  std::string _name; //name of the ship
	  spCharacter _captain; //captain of the ship
    int _evasion; //ship's evasion level
    int _chem_cap; //capacity of total atomic mass
    int _chem[120]; //chemical elements stored on the ship
    int _inventory_cap; //inventory capacity
    std::vector<spItem> _inventory; //inventory
    float _fuel_level; //fuel level of the ship
    float _fuel_cap; //fuel tank capacity (maximum)

    spArmor _armor; //ship's armor slot
    spHull _hull; //hull of the ship
    spBattery _battery; //battery of the ship
    spEngine _engine;//engine of the ship

    //weapons used by the ship
};