
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "engine.h"

Engine::Engine()
{
  setEvasion(0);
  setArmorPiece(nullptr);
}

//! Initialize an item with given parameters
/*!
\param evasion how much evasion this item provides
*/
void Engine::init(int evasion)
{
  setEvasion(evasion);
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
  for (int i = 0; i < items.size(); i++)
  {
    if (ID.compare(items[i]["id"].asCString()) == 0)
    {
      //initialize the item
      Item::init(
        ID,
        items[i]["size"].asInt(),
        items[i]["name"].asCString(),
        items[i]["desc"].asCString(),
        items[i]["brand"].asCString(),
        items[i]["hitpoints"].asInt()
        );

      //initialize the engine
      init(items[i]["evasion"].asInt());

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

void Engine::setEvasion(int evasion)
{
  _evasion = evasion;
}

void Engine::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}