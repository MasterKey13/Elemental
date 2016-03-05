#include "Ship.h"

Ship::Ship()
{

}

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
	//set coordinates
	_x = x;
	_y = y;
}

void Ship::setCaptain(spCharacter *captain)
{
	//set the captain of the ship
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
	//display ship name
	DebugActor::instance->addDebugString("%s [%s]\n", this->_name.c_str(), this->_serial.c_str());
}