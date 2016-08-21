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

//Declare smart pointers
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Character, spCharacter);
DECLARE_SMART(Item, spItem);

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
      spCharacter captain = nullptr);
	 
    //SETTERS
    void setName(std::string name);
    void setCoordinates(int x, int y);
    void setChemCap(int chem_cap);
    void setInventoryCap(int inventory_cap);
    void setFuelCap(float fuel_cap);
    void setFuelLevel(float fuel_level);
    void setEvasion(int evasion);
    void setCaptain(spCharacter captain);

    //GETTERS
	  std::string getName();
    int getXPos();
    int getYPos();
    int getChemCap();
    float getFuelLevel();
    float getFuelCap();
    int getEvasion();
    spCharacter getCaptain();

    void travelTo(int x, int y); //travel the ship to a certain location

  private:
	  void doUpdate(const UpdateState &us);

	  int _xPos, _yPos; //coordinates of the ship
	  std::string _name; //name of the ship
	  spCharacter _captain; //captain of the ship
    int _evasion; //ship's evasion level
    int _chem_cap; //capacity of total atomic mass
    int _chem[10]; //chemical elements stored on the ship
    int _inventory_cap; //inventory capacity
    std::vector<spItem> _inventory; //inventory
    float _fuel_level; //fuel level of the ship
    float _fuel_cap; //fuel tank capacity (maximum)

    //weapons used by the ship
    //hull of the ship
    //battery of the ship
    //engine of the ship
};