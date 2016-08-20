/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "character.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Character, spCharacter);

class Ship : public Actor
{
  public:
	  Ship();

	  void init(std::string name, int x, int y, int evasion, int inventoryCap, int fuelCap, int fuelLevel, spCharacter captain = nullptr);
	 
    //SETTERS
    void setName(std::string name);
	  void setCoordinates(int x, int y);
    void setEvasion(int evasion);
    void setInventoryCap(int inventoryCap);
    void setFuelCap(int fuelCap);
    void setFuelLevel(int fuelLevel);
    void setCaptain(spCharacter captain);

    //GETTERS
	  std::string getName();
    int getFuelLevel();
    int getFuelCap();
    int getEvasion();
    spCharacter getCaptain();

    void travelTo(int x, int y); //travel the ship to a certain location

  private:
	  void doUpdate(const UpdateState &us);

	  int _x, _y; //coordinates of the ship
	  std::string _name; //name of the ship
	  spCharacter _captain; //captain of the ship
    int _evasion; //ship's evasion level
    int _inventory_cap; //inventory capacity
    int _fuel_level; //fuel level of the ship
    int _fuel_cap; //fuel tank capacity (maximum)

    //items on the ship (inventory)
    //chemicals stored on the ship
    //weapons used by the ship
    //hull of the ship
    //battery of the ship
    //engine of the ship
};