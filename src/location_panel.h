#pragma once
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "travel_box.h"

using namespace oxygine;

//Declare constants
#define GRID_SIZE 20

//Declare smart pointers
DECLARE_SMART(LocationPanel, spLocationPanel);

class LocationPanel : public Actor
{
public:
  LocationPanel();
  void init();

private:
  spTravelBox _travelBox;
  spColorRectSprite _panel;
  spColorRectSprite _map_button;
  spColorRectSprite _travel_button;
  spColorRectSprite _location_info_button;

  void _panelSetUp();
  void _travelBoxSetUp();
  void _panelButtonSetUp();
};