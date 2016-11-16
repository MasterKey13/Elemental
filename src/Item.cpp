/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "item.h"

Item::Item()
{
  //set all values to default (0, false, empty strings and nullptrs)
  setID(0);
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

\param battery_power battery power this item provides
\param action_slots action slots this item provides
\param evasion how much evasion this item provides
\param ballistic_dmg amount of ballistic damage this item does
\param electrical_dmg amount of electrical damage this item does
\param chemical_dmg amount of chemical damage this item does
\param ballistic_res resistance to ballistic damage of this item
\param electrical_res resistance to electrical damage of this item
\param chemical_res resistance to chemical damage of this item
\param damage_absorbtion maximum amount of damage the armor item can absorb
\param mining_efficiency the mining efficiency of this item
\param mining_reliability how reliably this item can mine for elements
\param storage_capacity the maximum amount of elements this item can store
\param max_temp maximum temperature this item can endure
*/
void Item::init(
  int ID,
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
void Item::init(int ID)
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
    if (items[i]["id"].asInt() == ID)
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

void Item::setID(int ID)
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

int Item::getID()
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