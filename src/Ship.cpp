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
\param name name of the ship
\param hull hull of the ship
\param battery battery of the ship
\param engine engine of the ship
*/
void Ship::init(
  std::string name,

  spItem hull,
  spItem battery,
  spItem engine)
{
  setHull(hull);
  setBattery(battery);
  setEngine(engine);

  log();
}

void Ship::log()
{
  
}

void Ship::setName(std::string name)
{
	_name = name;
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

std::string Ship::getName()
{
	return _name;
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

void Ship::doUpdate(const UpdateState &us)
{

}