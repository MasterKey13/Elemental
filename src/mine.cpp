/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "mine.h"

Mine::Mine()
{
  setChemStorageCapacity(0);
  setStorageDefault();
  setEfficiency(0);
  setReliability(0);
  setCurrentTotalStorage(0);
  setHostBody(nullptr);
  setMaxTemp(0);
}

//! Initialize a battery with given parameters
/*!
\param chem_storage_max the maximum storage capacity
\param efficiency efficiency of the mine
\param reliability reliability of the mine
\param max_temp maximum temperature the mine can support
*/
void Mine::init(
  int chem_storage_max,
  int efficiency,
  int reliability,
  int max_temp
  )
{
  setChemStorageCapacity(chem_storage_max);
  setEfficiency(efficiency);
  setReliability(reliability);
  setMaxTemp(max_temp);
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Mine::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/mines.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["mines"];

  //go through the json file and find the item by ID
  for (int i = 0; i < items.size(); i++)
  {
    if (ID.compare(items[i]["id"].asCString()) == 0)
    {
      //initialize the item
      Item::init(
        ID,
        items[i]["size"].asInt(),
        items[i]["name"].asCString(),
        items[i]["desc"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["hitpoints"].asInt()
        );

      //initialize the hull
      init(
        items[i]["chem_storage_max"].asInt(),
        items[i]["efficiency"].asInt(),
        items[i]["reliability"].asInt(),
        items[i]["max_temp"].asInt()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
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
