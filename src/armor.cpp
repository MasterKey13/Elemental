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

void Armor::init(
  int ID,
  std::string name, 
  int size, 
  int rarity,
  int ballistic_res,
  int electrical_res,
  int radioactive_res,
  int chemical_res,
  std::string brand, 
  std::string model)
{
  this->setID(ID);
  this->setName(name);
  this->setSize(size);
  this->setRarity(rarity);
  this->setCompositionDefault();

  setDamageResistance(Ballistic, ballistic_res);
  setDamageResistance(Electrical, electrical_res);
  setDamageResistance(Radioactive, radioactive_res);
  setDamageResistance(Chemical, chemical_res);

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

void Armor::log()
{
  log::messageln("\n[ARMOR]\nID: %d\nName: %s\nSize: %d\nRarity: %d\nBrand: %s\nModel: %s\nBallRes: %d\nElectrRes: %d\nRadRes: %d\nChemRes: %d\n",
    this->getID(),
    this->getName().c_str(),
    this->getSize(),
    this->getRarity(),
    this->getBrand().c_str(),
    this->getModel().c_str(),
    this->getDamageResistance(Ballistic),
    this->getDamageResistance(Electrical),
    this->getDamageResistance(Radioactive),
    this->getDamageResistance(Chemical));
}

int Armor::getDamageResistance(DamageType damage_type)
{
  return _damage_resistance[damage_type];
}

void Armor::setDamageResistance(DamageType damage_type, int damage_resistance)
{
  _damage_resistance[damage_type] = damage_resistance;
}