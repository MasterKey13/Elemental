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
  _locationPanel = new LocationPanel();
  _locationPanel->init();

  addChild(_locationPanel);
}