/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "synthesizer.h"

Synthesizer::Synthesizer()
{

}

void Synthesizer::setHostShip(spShip host)
{
  _host_ship = host;
}

void Synthesizer::setSize(int size)
{
  _size = size;
}

int Synthesizer::getSize()
{
  return _size;
}

//! Decompose an item into its most basic elements
/*!
\param item smart pointer to item which to decompose
*/
void Synthesizer::decomposeItem(spItem item)
{
  if (getSize() >= item->getSize())
  {
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
      for (int j = 0; j < item->getComposition(i); j++)
      {
        _host_ship->setChemAmount(i, _host_ship->getChemAmount(i) + 1);
      }
    }
  }
}

//! Synthesize a new item based on item ID and place it in the ship's inventory
/*!
\param ID ID of item to synthesize
*/
void Synthesizer::synthesizeItem(int ID)
{
  //TODO: implement this after item loading from file by ID is done
}
