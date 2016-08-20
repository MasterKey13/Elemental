/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Location, spLocation);
DECLARE_SMART(Ship, spShip);

class Location : public Actor
{
  public:
	  Location();

	  void init(int x, int y, int shipLimit);

  private:
	  void doUpdate(const UpdateState &us);

	  //will have Solar Systems in here at some point

	  int _x, _y;
	  int _ship_count; //keeps track of how many ships there are at the location
	  int _ship_limit; //how many ships this location can hold
	  void _setCoordinates(int x, int y); //sets the coordinates
};