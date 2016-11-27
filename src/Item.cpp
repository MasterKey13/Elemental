/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "item.h"

Item::Item()
{
  //set all values to default (0, false, empty strings and nullptrs)
  setID("");
  setSize(0);
  setName("");
  setDescription("");
  setBrand("");
  setHitPoints(0);
  setHitPointsMax(0);

  setCompositionDefault();
}

//! Initialize an item with given parameters
/*!
\param ID ID of the item
\param size size of the item
\param name name of the item
\param desc description of the item
\param brand the brand name of the item
\param hitpoints the amount of hitpoints the item has (health)
*/
void Item::init(
  std::string ID,
  int size,
  std::string name,
  std::string desc,
  std::string brand,
  int hitpoints
  )
{
  setID(ID);
  setSize(size);

  setName(name);
  setDescription(desc);
  setBrand(brand);

  setHitPoints(hitpoints);
  setHitPointsMax(hitpoints);
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Item::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/items.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["items"];

  //go through the json file and find the item by ID
  for (int i = 0; i < items.size(); i++)
  {
    if (ID.compare(items[i]["id"].asCString()) == 0)
    {
      //initialize the item
      init(
        ID,
        items[i]["size"].asInt(),
        items[i]["name"].asCString(),
        items[i]["desc"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["hitpoints"].asInt()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Item::log()
{
 
}

void Item::setID(std::string ID)
{
  _itemID = ID;
}

void Item::setName(std::string name)
{
  _name = name;
}

void Item::setDescription(std::string desc)
{
  _desc = desc;
}

void Item::setBrand(std::string brand)
{
  _brand = brand;
}

void Item::setSize(int size)
{
  _size = size;
}

void Item::setComposition(int element, int abundance)
{
  _composition[element] = abundance;
}

void Item::setCompositionDefault()
{
  for (int i = 0; i < MAX_ELEMENTS; i++)
  {
    _composition[i] = 0;
  }
}

std::string Item::getID()
{
  return _itemID;
}

std::string Item::getName()
{
  return _name;
}

std::string Item::getDescription()
{
  return _desc;
}

std::string Item::getBrand()
{
  return _brand;
}

int Item::getSize()
{
  return _size;
}

int Item::getComposition(int element)
{
  return _composition[element];
}

int Item::getHitPoints()
{
  return _hitpoints;
}

int Item::getHitPointsMax()
{
  return _hitpoints_max;
}

void Item::setHitPoints(int hitpoints)
{
  _hitpoints = hitpoints;
}

void Item::setHitPointsMax(int hitpoints_max)
{
  _hitpoints_max = hitpoints_max;
}