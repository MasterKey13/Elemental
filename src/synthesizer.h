/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "ship.h"

using namespace oxygine;

#define MAX_ELEMENTS 50

//Declare smart pointers
DECLARE_SMART(Synthesizer, spSynthesizer);
DECLARE_SMART(Ship, spShip);

class Synthesizer : public Item
{
public:
  Synthesizer();

  //SETTERS
  void setHostShip(spShip host);
  void setSize(int size);

  //GETTERS
  int getSize();

  void decomposeItem(spItem item);
  void synthesizeItem(int ID);

private:
  spShip _host_ship;
  int _size;
};