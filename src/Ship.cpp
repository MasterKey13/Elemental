/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "ship.h"
#include "armor.h"
#include "hull.h"
#include "battery.h"
#include "engine.h"

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
  spHull hull,
  spBattery battery,
  spEngine engine,
  spCharacter captain)
{
	setName(name);
  setInventoryCap(inventory_cap);
  setChemCap(chem_cap),
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
    log::message("Captain: %s",
      this->getCaptain()->getFullName().c_str());
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

void Ship::setChemCap(int chem_cap)
{
  _chem_cap = chem_cap;
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

void Ship::setHull(spHull hull)
{
  _hull = hull;
}

void Ship::setBattery(spBattery battery)
{
  _battery = battery;
}

void Ship::setEngine(spEngine engine)
{
  _engine = engine;
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

spHull Ship::getHull()
{
  return _hull;
}

spBattery Ship::getBattery()
{
  return _battery;
}

spEngine Ship::getEngine()
{
  return _engine;
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