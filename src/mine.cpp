/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "mine.h"

Mine::Mine()
{

}

//! Initialize a custom mine with given parameters
/*!
\param ID ID of the item (mine)
\param name name of the item (mine)
\param size size of the mine
\param efficiency how efficiently the mine mines (2 mines twice as much as 1, 3 mines 3 times as much, etc)
\param reliability how reliable the mine is when it mines each element (0 mines nothing, 10000 mines 100.00%)
\param storage_capacity the capacity of the mine
\param brand the brand name of the mine
\param craftable whether the item is craftable
*/
void Mine::init(
  int ID,
  std::string name,
  int size,
  int efficiency,
  int reliability,
  int storage_capacity,
  int max_temp,
  std::string brand)
{
  setID(ID);
  setName(name);
  setSize(size);
  setEfficiency(efficiency);
  setReliability(reliability);
  setStorageCapacity(storage_capacity);
  setMaxTemp(max_temp);
  setBrand(brand);

  setStorageDefault();
  setHostBody(NULL);

  log();
}

void Mine::initByID(int ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/mines.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value mines = value["mines"];

  //go through the json file and find the weapon by ID
  for (int i = 0; i < mines.size(); i++)
  {
    if (mines[i]["id"].asInt() == ID)
    {
      //initialize the weapon
      init(
        ID,
        mines[i]["name"].asCString(),
        mines[i]["size"].asInt(),
        mines[i]["efficiency"].asInt(),
        mines[i]["reliability"].asInt(),
        mines[i]["storage_capacity"].asInt(),
        mines[i]["max_temperature"].asInt(),
        mines[i]["brand"].asCString()
      );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, mines[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Mine::log()
{
  log::messageln("\n[MINE]\nSize: %d\nEfficiency: %d\nReliability: %d\nStorage Cap: %d\nBrand: %s\n",
    getSize(),
    getEfficiency(),
    getReliability(),
    getStorageCapacity(),
    getBrand().c_str());
}

void Mine::setStorageCapacity(int cap)
{
  _storage_capacity = cap;
}

void Mine::setStorage(int element, int amount)
{
  _storage[element] = amount;
}

void Mine::setEfficiency(int efficiency)
{
  _efficiency = efficiency;
}

void Mine::setReliability(int reliability)
{
  _reliability = reliability;
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

int Mine::getStorageCapacity()
{
  return _storage_capacity;
}

int Mine::getStorage(int element)
{
  return _storage[element];
}

int Mine::getEfficiency()
{
  return _efficiency;
}

int Mine::getReliability()
{
  return _reliability;
}

int Mine::getCurrentStorage()
{
  return _current_total_storage;
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
        if ((extractGen <= getReliability()) && 
          ((getStorageCapacity() - getCurrentStorage()) >= getEfficiency()))
        {
          setStorage(i, getStorage(i) + getEfficiency());
          setCurrentTotalStorage(getCurrentStorage() + getEfficiency());
        }
      }

      log::messageln("Extracted %d of element [%d] from host body",
        getStorage(i), i);
    }

    log::messageln("Mine capacity: %d/%d",
      getCurrentStorage(), getStorageCapacity());
  }
}
