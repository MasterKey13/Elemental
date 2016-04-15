/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

//constants for maximum travelable space (0-999 in x and y)
#define X_MAX 999
#define Y_MAX 999

//Declare smart pointers
DECLARE_SMART(Space, spSpace);

class Space : public Actor
{
  public:
	  Space();

	  void init(int x, int y);

	  int getX(); //gets the current X coordinate
	  int getY(); //gets the current Y coordinate

  private:
	  void doUpdate(const UpdateState &us); //update function
	  void _setCoordinates(int x, int y); //set the default location

	  int _currentX, _currentY; //current coordinates
};