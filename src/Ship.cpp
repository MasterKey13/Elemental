/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "ship.h"

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
  spHull hull,
  spBattery battery,
  spEngine engine)
{
  setName(name);

  setHull(hull);
  setBattery(battery);
  setEngine(engine);
}

void Ship::setName(std::string name)
{
	_name = name;
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

void Ship::doUpdate(const UpdateState &us)
{

}