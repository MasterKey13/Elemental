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

//! Initialize a custom ship hull with given parameters
/*!
\param ID ID of the item (hull)
\param size size of the item (hull)
\param hitpoints the starting amount of hitpoints
\param hitpoints_cap the maximum amount of hitpoints
\param name name of the item (hull)
\param brand the brand name of the hull
\pram model model name of the hull
*/
void Hull::init(
  int ID,
  int size,
  int hitpoints,
  int hitpoints_cap,
  std::string name,
  std::string brand,
  std::string model)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
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

  log();
}

void Hull::log()
{
  log::messageln("\n[HULL]\nID: %d\nName: %s\nSize: %d\nBrand: %s\nModel: %s\nHP: %d/%d\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
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
//! Return the armor piece covering the hull, if one exists, otherwise return nullptr
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
