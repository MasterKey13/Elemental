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

void Ship::doUpdate(const UpdateState &us)
{

}