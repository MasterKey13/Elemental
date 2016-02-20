#include "setup.h"
#include "Location.h"

Location::Location()
{

}

void Location::init(int x, int y, int shipLimit)
{
	_setCoordinates(x,y); //set coordinates
	_shipLimit = shipLimit; //set the ship limit variable
	_ships = new spShip[_shipLimit]; //create Ship slots at this location
	_shipCount = 0; //set the counter to 0
}	

void Location::doUpdate(const UpdateState &us)
{
	
}

void Location::_setCoordinates(int x, int y)
{
	//set the coordinates of this location
	_x = x;
	_y = y;
}

void Location::addShip(spShip *ship)
{
	//check for limit
	if (_shipCount >= _shipLimit - 1)
	{
		//do nothing
	}
	else
	{
		_ships[_shipCount] = *ship; //add the ship to the array
		_shipCount++; //increase the shipCount
	}

}