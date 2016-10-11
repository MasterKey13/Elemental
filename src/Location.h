/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"
#include "celestial_body.h"

using namespace oxygine;

#define MAX_SHIPS 10

//Declare smart pointers
DECLARE_SMART(Location, spLocation);
DECLARE_SMART(CelestialBody, spCelestialBody);
DECLARE_SMART(Ship, spShip);

class Location : public Actor
{
  public:
	  Location();

	  void init(int x, int y);

    //SETTERS
    void setCoordinates(int x, int y);

    //GETTERS
    int getXCoordinate();
    int getYCoordinate();

    //Ship-related public methods and variables
    void addShip(spShip ship);
    spShip getShip(int index);

    //generate stars, planets and ships at this location
    void generateLocation();

  private:
	  void doUpdate(const UpdateState &us);

	  int _x, _y;

    //Ship-related private methods and variables
	  int _ship_count = 0;
    spShip _ships[MAX_SHIPS];

    //Space body-related private methods and variables (stars/planets)
    spCelestialBody _space_body;
};