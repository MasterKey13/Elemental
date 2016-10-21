/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "armor.h"
#include "item.h"

Armor::Armor()
{

}

//! Manual initalization function for custom armor pieces used for debugging
/*!
  \param ID unique item ID
  \param name name of the item
  \param size size of the item
  \param ballistic_res ballistic resistance
  \param electical_res electrical resistance
  \param chemical_res chemical resistance
  \param brand bran name
  \param craftable whether the item is craftable
*/
void Armor::init(
  int ID,
  std::string name, 
  int size,
  bool craftable,
  int ballistic_res,
  int electrical_res,
  int radioactive_res,
  int chemical_res,
  std::string brand)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
  this->setCompositionDefault();

  setDamageResistance(Ballistic, ballistic_res);
  setDamageResistance(Electrical, electrical_res);
  setDamageResistance(Radioactive, radioactive_res);
  setDamageResistance(Chemical, chemical_res);

  if (brand.length() > 0)
  {
    this->setBrand(brand);
  }

  log();
}

void Armor::log()
{
  log::messageln("\n[ARMOR]\nID: %d\nName: %s\nSize: %d\nBrand: %s\nBallRes: %d\nElectrRes: %d\nRadRes: %d\nChemRes: %d\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getBrand().c_str(),
    this->getDamageResistance(Ballistic),
    this->getDamageResistance(Electrical),
    this->getDamageResistance(Radioactive),
    this->getDamageResistance(Chemical));
}

int Armor::getDamageResistance(DamageType type)
{
  return _damage_resistance[type];
}

void Armor::setDamageResistance(DamageType type, int resistance)
{
  _damage_resistance[type] = resistance;
}