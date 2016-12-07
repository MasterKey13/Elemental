/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "item.h"

Item::Item()
{
  setID("");
  setVolume(0);
  setWeight(0);
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
\param volume volume of the item in m^3
\param weight weight of the item kg
\param name name of the item
\param desc description of the item
\param brand the brand name of the item
\param hitpoints the amount of hitpoints the item has (health)
*/
void Item::init(
  std::string ID,
  float volume,
  float weight,
  std::string name,
  std::string desc,
  std::string brand,
  int hitpoints
  )
{
  setID(ID);
  setVolume(volume);
  setWeight(weight);

  setName(name);
  setDescription(desc);
  setBrand(brand);

  setHitPoints(hitpoints);
  setHitPointsMax(hitpoints);

  log();
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
  for (size_t i = 0; i < items.size(); i++)
  {
    if (ID.compare(items[i]["id"].asString()) == 0)
    {
      //initialize the item
      init(
        ID,
        items[i]["volume"].asFloat(),
        items[i]["weight"].asFloat(),
        items[i]["name"].asString(),
        items[i]["desc"].asString(),
        items[i]["brand"].asString(),
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
  log::messageln(
    "==============\n[New %s]\nName: %s\nDesc: %s\nBrand: %s\nHP: %d\nWeight: %0.00f\nVolume: %0.00f",
    getID().c_str(),
    getName().c_str(), 
    getDescription().c_str(),
    getBrand().c_str(),
    getHitPoints(),
    getWeight(),
    getVolume()
    );
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

void Item::setVolume(float volume)
{
  _volume = volume;
}

void Item::setWeight(float weight)
{
  _weight = weight;
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

float Item::getVolume()
{
  return _volume;
}

float Item::getWeight()
{
  return _weight;
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
  if (hitpoints < 0)
  {
    hitpoints = 0;
  }

  _hitpoints = hitpoints;
}

void Item::setHitPointsMax(int hitpoints_max)
{
  if (hitpoints_max <= 0)
  {
    hitpoints_max = 1;
  }

  _hitpoints_max = hitpoints_max;
}