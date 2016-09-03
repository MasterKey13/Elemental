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
*/
void Location::init(int x, int y)
{
	setCoordinates(x,y); //set coordinates
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

void Location::doUpdate(const UpdateState &us)
{
	
}