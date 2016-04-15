#include "space.h"

Space::Space()
{

}

/*
Initialize the Space
  (int) starting x coordinate
  (int) starting y coordinate
*/
void Space::init(int x, int y)
{
	_setCoordinates(x, y);
}

void Space::doUpdate(const UpdateState & us)
{
	//display the current loaded space location (debug)
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
	_currentX = x;
	_currentY = y;
}