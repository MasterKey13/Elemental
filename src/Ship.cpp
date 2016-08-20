/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "ship.h"

Ship::Ship()
{

}

/*
Initialize a Ship
  (string) name of the ship
  (int) starting x location of the ship
  (int) starting y location of the ship
  (int) evasion level of the ship
  (int) maximum inventory capacity
  (int) maximum fuel capacity
  (int) starting fuel level
  (spCharacter) captain of the ship (nullptr if not provided)
*/
void Ship::init(std::string name, int x, int y, int evasion, int inventory_cap, float fuel_cap, float fuel_level, spCharacter captain)
{
	setName(name);
  setEvasion(evasion);
  setInventoryCap(inventory_cap);
  setFuelCap(fuel_cap);
  setFuelLevel(fuel_level);
  setCaptain(captain);
  setCoordinates(x, y);

	//log ship creation
  log::messageln("\n[NEW SHIP]\nName: %s\nFuel: %.2f/%.2f\nEvasion: %d",
    this->getName().c_str(),
    this->getFuelLevel(),
    this->getFuelCap(),
    this->getEvasion());

  if (_captain)
  {
    log::message("Captain: %s %s", 
      this->getCaptain()->getFirstName().c_str(),
      this->getCaptain()->getLastName().c_str());
  }
  else 
  {
    log::message("Captain: none");
  }

  log::message("\n\n");
}

void Ship::setName(std::string name)
{
	_name = name;
}

void Ship::setCoordinates(int x, int y)
{	
	_xPos = x;
	_yPos = y;

  //log location update
  log::messageln("\n[NEW COORDINATES]\n%d, %d\n", _xPos, _yPos);
}

void Ship::setEvasion(int evasion)
{
  _evasion = evasion;
}

void Ship::setInventoryCap(int inventory_cap)
{
  _inventory_cap = inventory_cap;
}

void Ship::setFuelCap(float fuel_cap)
{
  _fuel_cap = fuel_cap;
}

void Ship::setFuelLevel(float fuel_level)
{
  _fuel_level = fuel_level;
}

void Ship::setCaptain(spCharacter captain)
{
  _captain = captain;
}

std::string Ship::getName()
{
	return _name;
}

float Ship::getFuelLevel()
{
  return _fuel_level;
}

float Ship::getFuelCap()
{
  return _fuel_cap;
}

int Ship::getEvasion()
{
  return _evasion;
}

spCharacter Ship::getCaptain()
{
  return _captain;
}

int Ship::getXPos()
{
  return _xPos;
}

int Ship::getYPos()
{
  return _yPos;
}

void Ship::travelTo(int x, int y)
{
  float travelCost = sqrt((float)(pow((_xPos - x), 2) + pow((_yPos - y), 2)));

  if (travelCost < getFuelLevel())
  {
    setCoordinates(x,y);
    setFuelLevel(getFuelLevel() - travelCost);

    //log travel success and display ship info again
    log::messageln("\n[SHIP TRAVEL]\nName: %s\nFuel: %.2f/%.2f\nEvasion: %d\n",
      this->getName().c_str(),
      this->getFuelLevel(),
      this->getFuelCap(),
      this->getEvasion());
  }
  else
  {
    log::message("\nThe ship cannot travel that far!\n\n");
  }
}

void Ship::doUpdate(const UpdateState &us)
{

}