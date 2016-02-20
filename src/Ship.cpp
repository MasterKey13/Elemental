#include "Ship.h"

Ship::Ship()
{

}

void Ship::init(char *name, int x, int y, char *serial)
{
	_name = new char[NAME_MAX_CHAR]; //initialize ship name
	setName(name); //set ship name (default)
	setCoordinates(x, y); //set default coordinates of the ship
	setCaptain(nullptr); //set no captain at start
	_serial = serial; //ship's unique serial number
}

void Ship::setName(char *name)
{
	//set the ship name, cut off at 20 characters
	strncpy(_name, name, NAME_MAX_CHAR);
	_name[NAME_MAX_CHAR - 1] = '\0';
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

char *Ship::getSerial()
{
	return _serial;
}

char *Ship::getName()
{
	return _name;
}

void Ship::doUpdate(const UpdateState &us)
{
	//display ship name
	DebugActor::instance->addDebugString("%s [%s]\n", this->_name, this->_serial);
}