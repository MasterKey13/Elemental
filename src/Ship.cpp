/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "ship.h"
#include "item.h"

Ship::Ship()
{

}

//! Initialize a custom ship with given parameters
/*!
\param name name of the item (ship)
\param x starting x-coordinate of the ship
\param y starting y-coordinate of the ship
\param chem_cap maximum amount of chemical storage
\param fuel_cap maximum amount of fuel
\param fuel_level current amount of fuel
\param evasion chances to evade attacks
\param hull the hull of the ship
\param battery the battery of the ship
\param engine the engine of the ship
\param captain the captain of the ship
*/
void Ship::init(
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
  spCharacter captain)
{
	setName(name);
  setInventoryCap(inventory_cap);
  setChemCap(chem_cap),
  setChemDefault(),
  setFuelCap(fuel_cap);
  setFuelLevel(fuel_level);
  setEvasion(evasion);
  setHull(hull);
  setBattery(battery);
  setEngine(engine);
  setCaptain(captain);
  setCoordinates(x, y);

  log();
}

void Ship::log()
{
  log::messageln("\n[SHIP]\nName: %s\nChem Max: %d\nFuel: %.2f/%.2f\nEvasion: %d\nHull HP: %d/%d\nEngine HP: %d/%d\nBattery HP: %d/%d",
    this->getName().c_str(),
    this->getChemCap(),
    this->getFuelLevel(),
    this->getFuelCap(),
    this->getEvasion(),
    this->getHull()->getHitPoints(),
    this->getHull()->getHitPointsCap(),
    this->getEngine()->getHitPoints(),
    this->getEngine()->getHitPointsCap(),
    this->getBattery()->getHitPoints(),
    this->getBattery()->getHitPointsCap());

  if (_captain)
  {
    log::messageln("Captain: %s\n",
      this->getCaptain()->getFullName().c_str());
  }
  else
  {
    log::messageln("Captain: none\n");
  }
}

void Ship::setName(std::string name)
{
	_name = name;
}

void Ship::setCoordinates(int x, int y)
{	
	_xPos = x;
	_yPos = y;
}

void Ship::setChemCap(int chem_cap)
{
  _chem_cap = chem_cap;
}

void Ship::setChemAmount(int element, int amount)
{
  if (element <= MAX_ELEMENTS)
  {
    _chem[element] = amount;
  }
}

void Ship::setChemDefault()
{
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    _chem[i] = 0;
  }
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

void Ship::setHull(spItem hull)
{
  _hull = hull;
}

void Ship::setBattery(spItem battery)
{
  _battery = battery;
}

void Ship::setEngine(spItem engine)
{
  _engine = engine;
}

void Ship::setWeaponCap(int cap)
{
  _weapon_cap = cap;
}

void Ship::setEquipmentCap(int cap)
{
  _equipment_cap = cap;
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

int Ship::getChemAmount(int element)
{
  return _chem[element];
}

spCharacter Ship::getCaptain()
{
  return _captain;
}

spItem Ship::getHull()
{
  return _hull;
}

spItem Ship::getBattery()
{
  return _battery;
}

spItem Ship::getEngine()
{
  return _engine;
}

int Ship::getWeaponCap()
{
  return _weapon_cap;
}

int Ship::getEquipmentCap()
{
  return _equipment_cap;
}

int Ship::getXPos()
{
  return _xPos;
}

int Ship::getYPos()
{
  return _yPos;
}

int Ship::getChemCap()
{
  return _chem_cap;
}

//! Travel the ship to a given location, if exists and if there is enough fuel
/*!
\param x x-coordinate of the new location
\param y y-coordinate of the new location
*/
void Ship::travelTo(int x, int y)
{
  float travelCost = sqrt((float)(pow((_xPos - x), 2) + pow((_yPos - y), 2)));

  if (travelCost < getFuelLevel())
  {
    setCoordinates(x,y);
    setFuelLevel(getFuelLevel() - travelCost);

    //log travel success and display ship info again
    log::messageln("\n[SHIP TRAVEL]\nName: %s\nFuel: %.2f/%.2f\nCaptain: %s\n",
      this->getName().c_str(),
      this->getFuelLevel(),
      this->getFuelCap(),
      this->getCaptain()->getFullName().c_str());
  }
  else
  {
    log::message("\nThe ship cannot travel that far!\n");
  }
}

void Ship::doUpdate(const UpdateState &us)
{

}