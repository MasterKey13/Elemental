
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "engine.h"

Engine::Engine()
{
  setEvasion(0);
  setArmorPiece(nullptr);
  setMaxWeight(0.0f);
}

//! Initialize an item with given parameters
/*!
\param evasion how much evasion this item provides
\param max_weight the maximum amount of weight this engine can safely move (kg)
*/
void Engine::init(int evasion, float max_weight)
{
  setEvasion(evasion);
  setMaxWeight(max_weight);
}

//! Initialize an item by ID (load from item definition file items.json)
/*!
\param ID ID of the item
*/
void Engine::init(std::string ID)
{
  //load file to buffer
  file::buffer bf;
  file::read("json/engines.json", bf);

  //parse
  Json::Reader reader;
  Json::Value value;
  reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), value, false);

  Json::Value items = value["engines"];

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

      //initialize the engine
      init(
        items[i]["evasion"].asInt(),
        items[i]["max_weight"].asFloat()
        );

      //load the defined elemental composition
      for (int j = 0; j < 50; j++)
      {
        setComposition(j, items[i]["composition"][std::to_string(j)].asInt());
      }
    }
  }
}

int Engine::getEvasion()
{
  return _evasion;
}

spArmor Engine::getArmorPiece()
{
  return _armor_piece;
}

float Engine::getMaxWeight()
{
  return _max_weight;
}

void Engine::setEvasion(int evasion)
{
  _evasion = evasion;
}

void Engine::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}

void Engine::setMaxWeight(float weight)
{
  _max_weight = weight;
}
