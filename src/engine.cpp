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

void Engine::init(
  int ID,
  int size,
  int rarity,
  int hitpoints,
  int hitpoints_cap,
  std::string name,
  std::string brand,
  std::string model)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
  this->setRarity(rarity);
  this->setHitPoints(hitpoints);
  this->setHitPointsCap(hitpoints_cap);
  this->setCompositionDefault();

  if (brand.length() > 0)
  {
    this->setBrand(brand);
  }

  if (model.length() > 0)
  {
    this->setModel(model);
  }

  //log hull creation
  log::messageln("\n[NEW ENGINE]\nID: %d\nName: %s\nSize: %d\nRarity: %d\nBrand: %s\nModel: %s\nHP: %d/%d\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getRarity(),
    this->getBrand().c_str(),
    this->getModel().c_str(),
    this->getHitPoints(),
    this->getHitPointsCap());
}

int Engine::getHitPoints()
{
  return _hitpoints;
}

int Engine::getHitPointsCap()
{
  return _hitpoints_cap;
}

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
