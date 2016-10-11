/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "weapon.h"
#include "item.h"

Weapon::Weapon()
{

}

void Weapon::init(
  int ID, 
  int size,
  int hitpoints, 
  int hitpoints_cap,
  int ballistic_dmg,
  int electrical_dmg,
  int radioactive_dmg,
  int chemical_dmg,
  std::string name, 
  std::string brand, 
  std::string model)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
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

void Weapon::log()
{
  log::messageln("\n[WEAPON]\nID: %d\nName: %s\nSize: %d\nBrand: %s\nModel: %s\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getBrand().c_str(),
    this->getModel().c_str());
}

int Weapon::getDamageResistance(DamageType damage_type)
{
  return _damage[damage_type];
}

void Weapon::setDamageResistance(DamageType damage_type, int damage)
{
  _damage[damage_type] = damage;
}
