/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "armor.h"
#include "damageable.h"

Armor::Armor()
{
  setDamageResistanceDefault();
}

//! Initialize an armor piece with given parameters
/*!
\param ballistic_res resistance to ballistic damage of this armor
\param electrical_res resistance to electrical damage of this armor
\param chemical_res resistance to chemical damage of this armor
*/
void Armor::init(
  int ballistic_res,
  int electrical_res,
  int chemical_res
  )
{
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
        items[i]["brand"].asString(),
        items[i]["hitpoints"].asInt()
        );

      //initialize the armor piece
      init(
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