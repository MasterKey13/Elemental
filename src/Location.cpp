/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "location.h"

Location::Location()
{

}

//! Initializes a custom location at given x and y coordinates
/*!
\param x x-coordinate
\param y y-coordinate
*/
void Location::init(int x, int y)
{
	setCoordinates(x,y);
}

void Location::setCoordinates(int x, int y)
{
  _x = x;
  _y = y;
}

int Location::getXCoordinate()
{
  return _x;
}

int Location::getYCoordinate()
{
  return _y;
}

//! Add a ship to the location
/*!
\param ship smart pointer to the ship to add to the current location
*/
void Location::addShip(spShip ship)
{
  if (_ship_count < MAX_SHIPS)
  {
    _ships[_ship_count] = ship;
    _ship_count++;
  }
}

//! Return ship at this location at the given index
/*!
\param index index at which the ship is located
*/
spShip Location::getShip(int index)
{
  if (index < MAX_SHIPS && _ships[index])
  {
    return _ships[index];
  }

  return nullptr;
}

//! Randomly generate a location and its contents (stars, planets, ships, etc)
void Location::generateLocation()
{
  //65.0% chance that star or planet will be generated
  int gen_star_planet_chance = rand() % 1000;

  if (gen_star_planet_chance < 650)
  {
    //95.0% chance to generate star
    int gen_star = rand() % 1000;
    _space_body = new CelestialBody;

    if (gen_star < 950)
    {
      _space_body->generateStar();
    }
    else //5.0% chance to generate planet
    {
      _space_body->generatePlanet(0);
    }
  }
}

void Location::doUpdate(const UpdateState &us)
{
	
}