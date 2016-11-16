/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "mine.h"

Mine::Mine()
{

}

void Mine::setChemStorageCapacity(int cap)
{
  _storage_capacity = cap;
}

void Mine::setChemStorage(int element, int amount)
{
  _storage[element] = amount;
}

void Mine::setEfficiency(int efficiency)
{
  _mining_efficiency = efficiency;
}

void Mine::setReliability(int reliability)
{
  _mining_reliability = reliability;
}

void Mine::setStorageDefault()
{
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    _storage[i] = 0;
  }

  setCurrentTotalStorage(0);
}

void Mine::setCurrentTotalStorage(int amount)
{
  _current_total_storage = amount;
}

void Mine::setHostBody(spCelestialBody host)
{
  _host = host;
}

void Mine::setMaxTemp(int temp)
{
  _max_temp = temp;
}

//! Returns a smart pointer to the CelestialBody on which it is installed
spCelestialBody Mine::getHostBody()
{
  return _host;
}

int Mine::getMaxTemp()
{
  return _max_temp;
}

int Mine::getChemStorageCapacity()
{
  return _storage_capacity;
}

int Mine::getChemStorage(int element)
{
  return _storage[element];
}

int Mine::getMiningEfficiency()
{
  return _mining_efficiency;
}

int Mine::getMiningReliability()
{
  return _mining_reliability;
}

int Mine::getCurrentChemStorage()
{
  return _current_total_storage;
}

//! Extracts elements from its host body based on its attributes
void Mine::extract()
{
  if (getHostBody() != NULL)
  {
    /*
    for every element go over the host body's composition
    for that element, and using the mine's reliability
    and efficiency attributes add those composition amounts
    to the mine's storage
    */
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
      for (int j = 0; j < getHostBody()->getComposition(i); j++)
      {
        int extractGen = rand() % 10000;

        //determine if the mine will mine this element (by reliability attribute)
        //and check if mine has enough storage space
        if ((extractGen <= getMiningReliability()) &&
          ((getChemStorageCapacity() - getCurrentChemStorage()) >= getMiningEfficiency()))
        {
          setChemStorage(i, getChemStorage(i) + getMiningEfficiency());
          setCurrentTotalStorage(getCurrentChemStorage() + getMiningEfficiency());
        }
      }

      log::messageln("Extracted %d of element [%d] from host body",
        getChemStorage(i), i);
    }

    log::messageln("Mine capacity: %d/%d",
      getCurrentChemStorage(), getChemStorageCapacity());
  }
}
