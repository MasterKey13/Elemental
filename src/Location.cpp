/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "location.h"

Location::Location()
{

}

/*
Initialize a Location
  (int) x coordinate of the location
  (int) y coordinate of the location
  (int) maximum number of ships that can be at this location
*/
void Location::init(int x, int y, int shipLimit)
{
	_setCoordinates(x,y); //set coordinates
	_ship_limit = shipLimit; //set the ship limit variable
	_ships = new spShip[_ship_limit]; //create Ship slots at this location
	_ship_count = 0; //set the counter to 0
}	

void Location::doUpdate(const UpdateState &us)
{
	
}

void Location::_setCoordinates(int x, int y)
{
	_x = x;
	_y = y;
}

/*
Add a new ship to this location
  (spShip *) ship to add
*/
void Location::addShip(spShip *ship)
{
	if (_ship_count >= _ship_limit - 1)
	{
		
	}
	else
	{
		_ships[_ship_count] = *ship;
		_ship_count++;
	}

}