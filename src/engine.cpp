/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "engine.h"
#include "item.h"

Engine::Engine()
{

}

//! Initialize a custom ship engine
/*!
\param ID ID of the item
\param size size of the engine
\param hitpoints starting amount of hitpoints
\param hitpoints_cap maximum hitpoints capacity
\param name name of the item
\param brand brand name of the engine
\param craftable whether the item is craftable
*/
void Engine::init(
  int ID,
  int size,
  int hitpoints,
  int hitpoints_cap,
  bool craftable,
  std::string name,
  std::string brand)
{
  setID(ID);
  setName(name);
  setSize(size);
  setHitPoints(hitpoints);
  setHitPointsCap(hitpoints_cap);
  setCompositionDefault();
  setCraftable(craftable);

  if (brand.length() > 0)
  {
    setBrand(brand);
  }

  log();
}

void Engine::log()
{
  log::messageln("\n[ENGINE]\nID: %d\nName: %s\nSize: %d\nBrand: %s\nHP: %d/%d\n",
    getID(),
    getName().c_str(),
    getSize(),
    getBrand().c_str(),
    getHitPoints(),
    getHitPointsCap());
}

int Engine::getHitPoints()
{
  return _hitpoints;
}

int Engine::getHitPointsCap()
{
  return _hitpoints_cap;
}

//! Return the armor piece covering the engine, if one exists, otherwise return nullptr
spArmor Engine::getArmor()
{
  if (_armor) { return _armor; }
  else { return nullptr; }
}

void Engine::setHitPoints(int hitpoints)
{
  _hitpoints = hitpoints;
}

void Engine::setHitPointsCap(int hitpoints_cap)
{
  _hitpoints_cap = hitpoints_cap;
}

void Engine::setArmor(spArmor armor)
{
  _armor = armor;
}
