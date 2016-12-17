
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "equipment.h"

Equipment::Equipment()
{
  setDamageDefault();
  setArmorPiece(nullptr);

  _sprite = new Sprite();
  _sprite->setPosition(0, 0);
  addChild(_sprite);
  setVisible(false);
}

//! Initialize an equipment with given parameters
/*!
\param ballistic_res resistance to ballistic damage of this equipment
\param electrical_res resistance to electrical damage of this equipment
\param chemical_res resistance to chemical damage of this equipment
\param ballistic_dmg the amount of ballistic damage this equipment inflicts
\param electrical_dmg the amount of ballistic damage this equipment inflicts
\param chemical_dmg the amount of ballistic damage this equipment inflicts
\param action_point_cost how much action points it costs to use this equipment
\param self_targetable whether the equipment can target it's owner's parts
*/
void Equipment::init(
  int ballistic_res,
  int electrical_res,
  int chemical_res,
  int ballistic_dmg,
  int electrical_dmg,
  int chemical_dmg,
  int action_point_cost,
  bool self_targetable
  )
{
  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);

  setDamage(Damage::Type::Ballistic, ballistic_dmg);
  setDamage(Damage::Type::Electrical, electrical_dmg);
  setDamage(Damage::Type::Chemical, chemical_dmg);

  setAPCost(action_point_cost);

  setSelfTargetable(self_targetable);
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Equipment::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/equipment.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["equipment"];

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


      //initialize the equipment
      init(
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt(),
        items[i]["ballistic_dmg"].asInt(),
        items[i]["electrical_dmg"].asInt(),
        items[i]["chemical_dmg"].asInt(),
        items[i]["action_point_cost"].asInt(),
        items[i]["self_targetable"].asBool()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }

      //load the sprite
      _sprite->setResAnim(resources::equipment.getResAnim(getID()));
    }
  }
}

int Equipment::getDamageResistance(Damage::Type type)
{
  return _damage_resistance[type];
}

int Equipment::getAPCost()
{
  return _action_point_cost;
}

bool Equipment::isSelfTargetable()
{
  return _self_targetable;
}

//! Return the amount of damage the weapon deals for the given damage type
/*!
\param damage_type the damage type to return damage amount for
*/
int Equipment::getDamage(Damage::Type damage_type)
{
  return _damage[damage_type];
}

//! Set the amount of damage the weapon deals for given damage type
/*!
\param damage_type the damage type for which to the set the damage amount
\param damage the amount of damage it deals
*/
void Equipment::setDamage(Damage::Type damage_type, int damage)
{
  _damage[damage_type] = damage;
}

void Equipment::setDamageDefault()
{
  setDamage(Damage::Type::Ballistic, 0);
  setDamage(Damage::Type::Electrical, 0);
  setDamage(Damage::Type::Chemical, 0);
}

void Equipment::setDamageResistance(Damage::Type type, int resistance)
{
  _damage_resistance[type] = resistance;
}

void Equipment::setDamageResistanceDefault()
{
  setDamageResistance(Damage::Type::Ballistic, 0); 
  setDamageResistance(Damage::Type::Electrical, 0);
  setDamageResistance(Damage::Type::Chemical, 0);
}

void Equipment::setAPCost(int APcost)
{
  _action_point_cost = APcost;
}

void Equipment::setSelfTargetable(bool self_targetable)
{
  _self_targetable = self_targetable;
}
