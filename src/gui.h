/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "travel_box.h"
#include "location_panel.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(GUI, spGUI);

class GUI : public Actor
{
public:
  GUI();
  void init();

private:
  spLocationPanel _locationPanel;
};