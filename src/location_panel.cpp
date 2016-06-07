/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "location_panel.h"

LocationPanel::LocationPanel()
{

}

/*
Initialize a LocationPanel (panel that holds travel box, map and location info)
*/
void LocationPanel::init()
{
  _panelSetUp();
  _travelBoxSetUp();
  _panelButtonSetUp();

  //set its size to the panel border size for GUI placement
  setSize(_panel->getSize());
}

//set up the panel itself
void LocationPanel::_panelSetUp()
{
  _panel = new ColorRectSprite;
  _panel->setSize(GRID_SIZE * 14 + 11, GRID_SIZE * 15 + 11);
  _panel->setColor(Color::LightGray);

  addChild(_panel);
}

//set up the travel box
void LocationPanel::_travelBoxSetUp()
{
  _travelBox = new TravelBox;
  _travelBox->init(GRID_SIZE);
  _travelBox->setPosition(GRID_SIZE, GRID_SIZE * 2);

  _panel->addChild(_travelBox);
}

//set up the buttons on the top of the panel (map/travel and location info)
void LocationPanel::_panelButtonSetUp()
{
  _map_button = new ColorRectSprite;
  _travel_button = new ColorRectSprite;
  _location_info_button = new ColorRectSprite;

  //map button setup
  _map_button->setSize(GRID_SIZE * 6 + 5, GRID_SIZE);
  _map_button->setColor(Color::DarkGray);
  _map_button->setPosition(GRID_SIZE, GRID_SIZE / 2);

  addChild(_map_button);

  //location button setup
  _location_info_button->setSize(GRID_SIZE * 6 + 5, GRID_SIZE);
  _location_info_button->setColor(Color::DarkGray);
  _location_info_button->setPosition(GRID_SIZE * 7 + 8, GRID_SIZE / 2);

  addChild(_location_info_button);
}