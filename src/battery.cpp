
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

  _sprite = new Sprite();
  _sprite->attachTo(this);
  _sprite->setPosition(0, 0);
  addChild(_sprite);

  computeBounds();
}

//! Initialize a battery with given parameters
/*!
\param ballistic_res resistance to ballistic damage of this armor
\param electrical_res resistance to electrical damage of this armor
\param chemical_res resistance to chemical damage of this armor
\param action_slots action slots this battery provides
\param action_points action slots this battery provides
*/
void Battery::init(
  int ballistic_res, 
  int electrical_res, 
  int chemical_res,
  int action_slots, 
  int action_points
  )
{
  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);

  setActionSlots(action_slots);
  setActionSlotsMax(action_slots);

  setActionPoints(action_points);
  setActionPointsMax(action_points);
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
    if (ID.compare(items[i]["id"].asString()) == 0)
    {
      //initialize the item
      Item::init(
        ID,
        items[i]["volume"].asFloat(),
        items[i]["weight"].asFloat(),
        items[i]["name"].asString(),
        items[i]["desc"].asString(),
        items[i]["brand"].asString()
        );

      //initialize the target
      Target::init(
        items[i]["hitpoints"].asInt(),
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt()
        );

      //initialize the battery
      init(
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt(),
        items[i]["action_slots"].asInt(),
        items[i]["action_points"].asInt()
        );

      //load the sprite
      _sprite->setResAnim(resources::batteries.getResAnim(getID()));
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

int Battery::getActionPointsMaxAvailable()
{
  return _action_points_max - 
    (_action_points_max * 
      (getHitPointsMax() - getHitPoints()) / 
      (3.4 * getHitPointsMax()));
}

spSprite Battery::getSprite()
{
  return _sprite;
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