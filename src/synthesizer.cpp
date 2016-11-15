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
  //TODO: reimplement this
}

//! Synthesize a new item based on item ID and place it in the ship's inventory
/*!
\param ID ID of item to synthesize
*/
void Synthesizer::synthesizeItem(int ID)
{
  //TODO: implement this
}
