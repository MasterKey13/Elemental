/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "hull.h"

Hull::Hull()
{
  setArmorPiece(nullptr);
  setDamageResistanceDefault();

  _volume_remaining = 0.0f;
  _max_equip = 0;

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
\param max_equip the maximum number of equipment this ship can use
*/
void Hull::init(
  int ballistic_res,
  int electrical_res,
  int chemical_res,
  int max_equip
  )
{
  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);

  _equipment_pos.resize(max_equip * 2);
  
  setMaxEquip(max_equip);
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Hull::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/hulls.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["hulls"];

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

      //initialize the hull
      init(
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt(),
        items[i]["max_equip"].asInt()
        );

      //load storage bounds
      for (int k = 0; k < 3; k++)
      {
        _engine_bounds[k] = items[i]["engine_bounds"][k].asInt();
        _battery_bounds[k] = items[i]["battery_bounds"][k].asInt();
      }

      //load equipment positions
      for (int l = 0; l < _max_equip * 2; l++)
      {
        _equipment_pos[l] = items[i]["equipment_positions"][l].asInt();
      }

      //load the sprite
      _sprite->setResAnim(resources::hulls.getResAnim(getID()));
    }
  }
}

void Hull::setBattery(spBattery battery)
{
  _battery = battery;

  _battery->setScale(_battery_bounds[2] / _battery->getSprite()->getWidth());

  _battery->setPosition(
    (float)_battery_bounds[0],
    (float)_battery_bounds[1]
    );
}

void Hull::setEngine(spEngine engine)
{
  _engine = engine;

  _engine->setScale(_engine_bounds[2] / _engine->getSprite()->getWidth());

  _engine->setPosition(
    (float)_engine_bounds[0],
    (float)_engine_bounds[1]
    );
}

void Hull::setVolumeRemaining(float volume)
{
  _volume_remaining = volume;
}

void Hull::setMaxEquip(int max)
{
  _max_equip = max;
}

std::vector<spItem> Hull::getInventory()
{
  return _inventory;
}

std::vector<spEquipment> Hull::getEquipment()
{
  return _equipment;
}

spBattery Hull::getBattery()
{
  return _battery;
}

spEngine Hull::getEngine()
{
  return _engine;
}

float Hull::getVolumeRemaining()
{
  return _volume_remaining;
}

int Hull::getMaxEquip()
{
  return _max_equip;
}

spSprite Hull::getSprite()
{
  return _sprite;
}

int Hull::getEquipmentPos(int i)
{
  return _equipment_pos[i];
}

//! Attach a piece of equipment to the hull
/*!
\param eq the equipment piece to attach to the hull
*/
void Hull::addEquipment(spEquipment eq)
{
  //check for duplicate items first
  if (std::find(_equipment.begin(), _equipment.end(), eq) == _equipment.end())
  {
    //if the equipment item fits in the vector, add it in
    if (getEquipment().size() < (size_t)getMaxEquip())
    {
      _equipment.push_back(eq);

      //place equipment onto the hull
      eq->attachTo(this);
      eq->setPosition(
        _equipment_pos[std::distance(_equipment.begin(), 
          std::find(_equipment.begin(), _equipment.end(), eq))], 
        _equipment_pos[std::distance(_equipment.begin(),
          std::find(_equipment.begin(), _equipment.end(), eq)) + 1]);
      eq->setPriority(getPriority() - 1);
    }
    else
    {
      log::messageln("[DEBUG] Can't add equipment item to %s; no slots available!", getName().c_str());
    }
  }
  else
  {
    log::messageln("[DEBUG] This %s is already equipped!", eq->getID().c_str());
  }
}