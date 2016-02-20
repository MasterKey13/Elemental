#include "Space.h"

Space::Space()
{

}

void Space::init(int x, int y)
{
	//set some starting location
	_setCoordinates(x, y);
}

void Space::doUpdate(const UpdateState & us)
{
	//display the current loaded space location
	DebugActor::instance->addDebugString("x: %d y: %d\n", this->_currentX, this->_currentY);
}

int Space::getX()
{
	return _currentX;
}

int Space::getY()
{
	return _currentY;
}

void Space::_setCoordinates(int x, int y)
{
	//set the coordinates
	_currentX = x;
	_currentY = y;
}