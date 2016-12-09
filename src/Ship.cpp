/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "ship.h"

Ship::Ship()
{
  setName("");
  setHull(nullptr);
}

//! Initialize a custom ship with given parameters
/*!
\param name name of the ship
\param hull hull of the ship
*/
void Ship::init(
  std::string name,
  spHull hull
  )
{
  setName(name);
  setHull(hull);
}

void Ship::log()
{
  log::messageln(
    "=============\n"
    "Name: %s\n"
    "Status: %s\n"
    "Hull HP: %d/%d\n"
    "Engine HP: %d/%d\n"
    "Battery HP: %d/%d"
    "\n=============",
    getName().c_str(),
    (isAlive() ? "alive" : "dead"),
    getHull()->getHitPoints(),
    getHull()->getHitPointsMax(),
    getHull()->getEngine()->getHitPoints(),
    getHull()->getEngine()->getHitPointsMax(),
    getHull()->getBattery()->getHitPoints(),
    getHull()->getBattery()->getHitPointsMax()
    );
}

bool Ship::isAlive()
{
  //the ship is considered "alive" as long as the hull is not destroyed and either
  //one of the battery or engine is not destroyed
  if (getHull()->getHitPoints() != 0 &&
    (getHull()->getBattery()->getHitPoints() != 0 ||
     getHull()->getEngine()->getHitPoints() != 0))
  {
    return true;
  }

  return false;
}

void Ship::setName(std::string name)
{
	_name = name;
}

void Ship::setHull(spHull hull)
{
  _hull = hull;
}
std::string Ship::getName()
{
	return _name;
}

spHull Ship::getHull()
{
  return _hull;
}