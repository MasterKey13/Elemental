/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "hull.h"
#include "item.h"

Hull::Hull()
{

}

void Hull::init(
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
  log::messageln("\n[NEW HULL]\nID: %d\nName: %s\nSize: %d\nRarity: %d\nBrand: %s\nModel: %s\nHP: %d/%d\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getRarity(),
    this->getBrand().c_str(),
    this->getModel().c_str(),
    this->getHitPoints(),
    this->getHitPointsCap());
}

int Hull::getHitPoints()
{
  return _hitpoints;
}

int Hull::getHitPointsCap()
{
  return _hitpoints_cap;
}

spArmor Hull::getArmor()
{
  if (_armor) { return _armor; }
  else { return nullptr; }
}

void Hull::setHitPoints(int hitpoints)
{
  _hitpoints = hitpoints;
}

void Hull::setHitPointsCap(int hitpoints_cap)
{
  _hitpoints_cap = hitpoints_cap;
}

void Hull::setArmor(spArmor armor)
{
  _armor = armor;
}
