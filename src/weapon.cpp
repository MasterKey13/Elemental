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

//! Initialize a custom weapon with given parameters
/*!
\param ID ID of the item (weapon)
\param size size of the mine
\param hitpoints the amount of hitpoints the weapon starts with
\param hitpoints_cap the maximum amount of hitpoints
\param ballistic_dmg the amount of ballistic damage the weapon deals
\param electrical_dmg the amount of electrical damage the weapon deals
\param radioactive_dmg the amount of radioactive damage the weapon deals
\param chemical_dmg the amount of chemical damage the weapon deals
\param name name of the item (weapon)
\param brand the brand name of the mine
\pram model model name of the mine
*/
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

//! Return the amount of damage the weapon deals for the given damage type
/*!
\param damage_type the damage type to return damage amount for
*/
int Weapon::getDamage(DamageType damage_type)
{
  return _damage[damage_type];
}

//! Set the amount of damage the weapon deals for given damage type
/*!
\param damage_type the damage type for which to the set the damage amount
\param damage the amount of damage it deals
*/
void Weapon::setDamage(DamageType damage_type, int damage)
{
  _damage[damage_type] = damage;
}
