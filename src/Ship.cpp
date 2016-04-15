/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "ship.h"

Ship::Ship()
{

}

/*
Initialize a Ship
  (string) name of the ship
  (int) starting x location of the ship
  (int) starting y location of the ship
  (string) serial number of the ship - UNIQUE!
*/
void Ship::init(std::string name, int x, int y, std::string serial)
{
	setName(name); //set ship name (default)
	setCoordinates(x, y); //set default coordinates of the ship
	setCaptain(nullptr); //set no captain at start
	_serial = serial; //ship's unique serial number
}

void Ship::setName(std::string name)
{
	_name = name;
}

void Ship::setCoordinates(int x, int y)
{	
	_x = x;
	_y = y;
}

void Ship::setCaptain(spCharacter *captain)
{
	_captain = captain;
}

std::string Ship::getSerial()
{
	return _serial;
}

std::string Ship::getName()
{
	return _name;
}

void Ship::doUpdate(const UpdateState &us)
{
	//display ship name (debug)
	DebugActor::instance->addDebugString("%s [%s]\n", this->_name.c_str(), this->_serial.c_str());
}