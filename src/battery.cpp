/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battery.h"
#include "item.h"

Battery::Battery()
{

}

//! Manual initalization function for custom ship batteries used for debugging
/*!
\param ID unique item ID
\param size size of the item
\param power initial battery power level
\param power_cap maximum battery power level
\param hitpoints initial amount of hitpoints the battery has
\param hitpoints_cap maximum amount of hitpoints the battery can have
\param name name of the item
\param desc description of the item
\param brand brandname of the battery
\param craftable whether the item is craftable
*/
void Battery::init(
  int ID,
  int size,
  int power,
  int power_cap,
  int hitpoints,
  int hitpoints_cap,
  bool craftable,
  std::string name,
  std::string desc,
  std::string brand)
{
  setID(ID);
  setName(name);
  setSize(size);
  setPower(power);
  setPowerCap(power_cap);
  setHitPoints(hitpoints);
  setHitPointsCap(hitpoints_cap);
  setCompositionDefault();
  setCraftable(craftable);
  setDescription(desc);

  if (brand.length() > 0)
  {
    setBrand(brand);
  }

  log();
}

void Battery::initByID(int ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/batteries.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value batteries = value["batteries"];

  //go through the json file and find the item by ID
  for (int i = 0; i < batteries.size(); i++)
  {
    if (batteries[i]["id"].asInt() == ID)
    {
      //initialize the item
      init(
        ID,
        batteries[i]["size"].asInt(),
        batteries[i]["power"].asInt(),
        batteries[i]["power"].asInt(),
        batteries[i]["hitpoints"].asInt(),
        batteries[i]["hitpoints"].asInt(),
        batteries[i]["craftable"].asBool(),
        batteries[i]["name"].asCString(),
        batteries[i]["description"].asCString(),
        batteries[i]["brand"].asCString()
      );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, batteries[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Battery::log()
{
  log::messageln("\n[BATTERY]\nID: %d\nName: %s\nDescription: %s\nSize: %d\nBrand: %s\nPower: %d/%d\nHP: %d/%d\n",
    getID(),
    getName().c_str(),
    getDescription().c_str(),
    getSize(),
    getBrand().c_str(),
    getPower(),
    getPowerCap(),
    getHitPoints(),
    getHitPointsCap());
}

int Battery::getHitPoints()
{
  return _hitpoints;
}

int Battery::getHitPointsCap()
{
  return _hitpoints_cap;
}

int Battery::getPower()
{
  return _power;
}

int Battery::getPowerCap()
{
  return _power_cap;
}

//! Return a smart pointer to the armor piece covering the battery (nullptr if none)
spArmor Battery::getArmor()
{
  if (_armor) { return _armor; }
  else { return nullptr; }
}

void Battery::setHitPoints(int hitpoints)
{
  _hitpoints = hitpoints;
}

void Battery::setHitPointsCap(int hitpoints_cap)
{
  _hitpoints_cap = hitpoints_cap;
}

void Battery::setPower(int power)
{
  _power = power;
}

void Battery::setPowerCap(int power_cap)
{
  _power_cap = power_cap;
}

void Battery::setArmor(spArmor armor)
{
  _armor = armor;
}
