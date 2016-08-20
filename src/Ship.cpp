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
  (spCharacter) captain of the ship (null if not provided)
*/
void Ship::init(std::string name, int x, int y, int evasion, int inventory_cap, int fuel_cap, int fuel_level, spCharacter captain)
{
	setName(name);
	setCoordinates(x, y);
  setEvasion(evasion);
  setInventoryCap(inventory_cap);
  setFuelCap(fuel_cap);
  setFuelLevel(fuel_level);
  setCaptain(captain);

	//log ship creation
  log::messageln("\n[NEW SHIP]\nName: %s\nFuel: %d/%d\nEvasion: %d",
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
	_x = x;
	_y = y;
}

void Ship::setEvasion(int evasion)
{
  _evasion = evasion;
}

void Ship::setInventoryCap(int inventory_cap)
{
  _inventory_cap = inventory_cap;
}

void Ship::setFuelCap(int fuel_cap)
{
  _fuel_cap = fuel_cap;
}

void Ship::setFuelLevel(int fuel_level)
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

int Ship::getFuelLevel()
{
  return _fuel_level;
}

int Ship::getFuelCap()
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

void Ship::travelTo(int x, int y)
{
  
}

void Ship::doUpdate(const UpdateState &us)
{

}