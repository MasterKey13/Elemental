
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "engine.h"

Engine::Engine()
{
  setEvasion(0);
  setArmorPiece(nullptr);
  setAPThreshold(0);
  setAPEscapePool(0);
  setMaxWeight(0.0f);

  _sprite = new Sprite();
  _sprite->attachTo(this);
  _sprite->setPosition(0, 0);
  _sprite->setColor(Color::White);
  addChild(_sprite);

  computeBounds();
}

//! Initialize an item with given parameters
/*!
\param evasion how much evasion this item provides
\param ap_threshold the amount of action points required to escape a battle
\param max_weight the maximum amount of weight this engine can safely move (kg)
*/
void Engine::init(int evasion, int ap_threshold, float max_weight)
{
  setEvasion(evasion);
  setAPThreshold(ap_threshold);
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
        items[i]["brand"].asString()
        );

      //initialize the target
      Target::init(
        items[i]["hitpoints"].asInt(),
        items[i]["ballistic_res"].asInt(),
        items[i]["electrical_res"].asInt(),
        items[i]["chemical_res"].asInt()
        );


      //initialize the engine
      init(
        items[i]["evasion"].asInt(),
        items[i]["ap_threshold"].asInt(),
        items[i]["max_weight"].asFloat()
        );

      //load the sprite
      _sprite->setResAnim(resources::engines.getResAnim(getID()));
    }
  }
}

int Engine::getEvasion()
{
  return _evasion;
}

int Engine::getAPThreshold()
{
  return _ap_threshold;
}

float Engine::getMaxWeight()
{
  return _max_weight;
}

int Engine::getAPEscapePool()
{
  return _ap_escape_pool;
}

spSprite Engine::getSprite()
{
  return _sprite;
}

void Engine::setEvasion(int evasion)
{
  _evasion = evasion;
}

void Engine::setAPThreshold(int threshold)
{
  _ap_threshold = threshold;
}

void Engine::setMaxWeight(float weight)
{
  _max_weight = weight;
}

void Engine::setAPEscapePool(int pool)
{
  _ap_escape_pool = pool;
}
