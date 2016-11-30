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
  setInventoryVolume(0.0f);
}

//! Initialize a battery with given parameters
/*!
\param ballistic_res resistance to ballistic damage of this armor
\param electrical_res resistance to electrical damage of this armor
\param chemical_res resistance to chemical damage of this armor
\param inventory_volume the maximum volume in m^3 of items this ship can store
*/
void Hull::init(
  int ballistic_res,
  int electrical_res,
  int chemical_res,
  float inventory_volume
  )
{
  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);

  setInventoryVolume(inventory_volume);
  setMaxInventoryVolume(inventory_volume);
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

      //initialize the hull
      init(
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt(),
        items[i]["inventory_volume"].asFloat()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

void Hull::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}

void Hull::setInventoryVolume(float volume)
{
  _inventory_volume = volume;
}

void Hull::setMaxInventoryVolume(float volume)
{
  _max_inventory_volume = volume;
}

spArmor Hull::getArmorPiece()
{
  return _armor_piece;
}

float Hull::getInventoryVolume()
{
  return _inventory_volume;
}

float Hull::getMaxInventoryVolume()
{
  return _max_inventory_volume;
}

std::vector<spItem> Hull::getInventory()
{
  return _inventory;
}
