
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "battery.h"

Battery::Battery()
{
  setActionSlots(0);
  setActionSlotsMax(0);
  setActionPoints(0);
  setActionPointsMax(0);
  setArmorPiece(nullptr);
}

//! Initialize a battery with given parameters
/*!
\param ballistic_res resistance to ballistic damage of this armor
\param electrical_res resistance to electrical damage of this armor
\param chemical_res resistance to chemical damage of this armor
\param damage_absorbtion maximum amount of damage the armor item can absorb
\param action_slots action slots this battery provides
\param action_points action slots this battery provides
*/
void Battery::init(
  int ballistic_res, 
  int electrical_res, 
  int chemical_res, 
  int damage_absorbtion, 
  int action_slots, 
  int action_points
  )
{
  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);

  setDamageAbsorbtion(damage_absorbtion);

  setActionSlots(action_slots);
  setActionSlotsMax(action_slots);

  setActionPoints(action_slots);
  setActionPointsMax(action_slots);
}

//! Initialize a battery by ID (load from item definition file battery.json)
/*!
\param ID ID of the battery
*/
void Battery::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/batteries.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["batteries"];

  //go through the json file and find the item by ID
  for (size_t i = 0; i < items.size(); i++)
  {
    if (ID.compare(items[i]["id"].asCString()) == 0)
    {
      //initialize the item
      Item::init(
        ID,
        items[i]["volume"].asFloat(),
        items[i]["weight"].asFloat(),
        items[i]["name"].asCString(),
        items[i]["desc"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["hitpoints"].asInt()
        );

      //initialize the battery
      init(
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt(),
        items[i]["damage_absorbtion"].asInt(),
        items[i]["action_slots"].asInt(),
        items[i]["action_slots"].asInt()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

int Battery::getActionSlots()
{
  return _action_slots;
}

int Battery::getActionSlotsMax()
{
  return _action_slots_max;
}

int Battery::getActionPoints()
{
  return _action_points;
}

int Battery::getActionPointsMax()
{
  return _action_points_max;
}

spArmor Battery::getArmorPiece()
{
  return _armor_piece;
}

void Battery::setActionSlots(int action_slots)
{
  _action_slots = action_slots;
}

void Battery::setActionSlotsMax(int action_slots_max)
{
  _action_slots_max = action_slots_max;
}

void Battery::setActionPoints(int action_points)
{
  _action_points = action_points;
}

void Battery::setActionPointsMax(int action_points_max)
{
  _action_points_max = action_points_max;
}

void Battery::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}