/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battery.h"
#include "item.h"

Battery::Battery()
{

}

void Battery::init(
  int ID,
  int size,
  int rarity,
  int power,
  int power_cap,
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
  this->setPower(power);
  this->setPowerCap(power_cap);
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

void Battery::log()
{
  log::messageln("\n[BATTERY]\nID: %d\nName: %s\nSize: %d\nRarity: %d\nBrand: %s\nModel: %s\nPower: %d/%d\nHP: %d/%d\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getRarity(),
    this->getBrand().c_str(),
    this->getModel().c_str(),
    this->getPower(),
    this->getPowerCap(),
    this->getHitPoints(),
    this->getHitPointsCap());
}

int Battery::getHitPoints()
{
  return _hitpoints;
}

int Battery::getHitPointsCap()
{
  return _hitpoints_cap;
}

int Battery::getPower()
{
  return _power;
}

int Battery::getPowerCap()
{
  return _power_cap;
}

spArmor Battery::getArmor()
{
  if (_armor) { return _armor; }
  else { return nullptr; }
}

void Battery::setHitPoints(int hitpoints)
{
  _hitpoints = hitpoints;
}

void Battery::setHitPointsCap(int hitpoints_cap)
{
  _hitpoints_cap = hitpoints_cap;
}

void Battery::setPower(int power)
{
  _power = power;
}

void Battery::setPowerCap(int power_cap)
{
  _power_cap = power_cap;
}

void Battery::setArmor(spArmor armor)
{
  _armor = armor;
}
