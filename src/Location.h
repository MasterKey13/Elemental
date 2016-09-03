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

	  void init(int x, int y);

    //SETTERS
    void setCoordinates(int x, int y); //sets the coordinates

    //GETTERS
    int getXCoordinate();
    int getYCoordinate();

  private:
	  void doUpdate(const UpdateState &us);

	  int _x, _y;
	  int _ship_count = 0; //keeps track of how many ships there are at the location

    spShip* _ships[10];
};