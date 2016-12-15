/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "armor.h"
#include "target.h"

Armor::Armor()
{
  setDamageResistanceDefault();
}

//! Initialize an armor piece with given parameters
/*!
\param hitpoints the amount of hitpoints this armor piece has
\param ballistic_res resistance to ballistic damage of this armor
\param electrical_res resistance to electrical damage of this armor
\param chemical_res resistance to chemical damage of this armor
*/
void Armor::init(
  int hitpoints,
  int ballistic_res,
  int electrical_res,
  int chemical_res
  )
{
  setHitPoints(hitpoints);
  setHitPointsMax(hitpoints);

  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);
}

//! Initialize an armor piece by ID (load from item definition file armor.json)
/*!
\param ID ID of the armor piece
*/
void Armor::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/armors.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["armors"];

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

      //initialize the armor piece
      init(
        //initialize the target
        items[i]["hitpoints"].asInt(),
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

int Armor::getHitPoints()
{
  return _hitpoints;
}

int Armor::getHitPointsMax()
{
  return _hitpoints_max;
}

void Armor::setHitPoints(int hitpoints)
{
  if (hitpoints < 0)
  {
    hitpoints = 0;
  }

  _hitpoints = hitpoints;
}

void Armor::setHitPointsMax(int hitpoints_max)
{
  if (hitpoints_max <= 0)
  {
    hitpoints_max = 1;
  }

  _hitpoints_max = hitpoints_max;
}

int Armor::getDamageResistance(Damage::Type type)
{
  return _damage_resistance[type];
}

void Armor::setDamageResistance(Damage::Type type, int resistance)
{
  _damage_resistance[type] = resistance;
}

void Armor::setDamageResistanceDefault()
{
  setDamageResistance(Damage::Type::Ballistic, 0);
  setDamageResistance(Damage::Type::Electrical, 0);
  setDamageResistance(Damage::Type::Chemical, 0);
}