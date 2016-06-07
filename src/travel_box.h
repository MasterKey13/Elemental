/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "resources.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(TravelBox, spTravelBox);

class TravelBox : public Actor
{
public:
  TravelBox();
  void init(int grid);
  int grid_size;

private:
  spColorRectSprite _box;
  spSprite _grid[10][10];
  spColorRectSprite _nav_buttons[4];
  void _boxSetUp();
  void _gridSetUp();
  void _navButtonSetUp();

  //offset (key) used to calculate the location which the sprites represent
  int _key_y;
  int _key_x;
};