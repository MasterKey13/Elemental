/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "gui.h"

GUI::GUI()
{

}

void GUI::init()
{
  //set up the bottom right location (travel) panel
  _locationPanel = new LocationPanel();
  _locationPanel->init();
  _locationPanel->setPosition(getStage()->getWidth() - 
                              _locationPanel->getWidth(), 
                              getStage()->getHeight() - 
                              _locationPanel->getHeight());

  addChild(_locationPanel);
}