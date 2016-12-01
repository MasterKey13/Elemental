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
}

//! Initialize a battery with given parameters
/*!
\param ballistic_res resistance to ballistic damage of this armor
\param electrical_res resistance to electrical damage of this armor
\param chemical_res resistance to chemical damage of this armor
*/
void Hull::init(
  int ballistic_res,
  int electrical_res,
  int chemical_res
  )
{
  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);
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
        items[i]["brand"].asString(),
        items[i]["hitpoints"].asInt()
        );

      //initialize the hull
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

void Hull::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}

void Hull::setBattery(spBattery battery)
{
  _battery = battery;
}

void Hull::setEngine(spEngine engine)
{
  _engine = engine;
}

void Hull::setSynthesizer(spSynthesizer synth)
{
  _synthesizer = synth;
}

void Hull::setVolumeRemaining(float volume)
{
  _volume_remaining = volume;
}

spArmor Hull::getArmorPiece()
{
  return _armor_piece;
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

spSynthesizer Hull::getSynthesizer()
{
  return _synthesizer;
}

float Hull::getVolumeRemaining()
{
  return _volume_remaining;
}
