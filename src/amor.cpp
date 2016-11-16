/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "armor.h"

Armor::Armor()
{

}

int Armor::getDamageResistance(Damage::Type type)
{
  return _damage_resistance[type];
}

int Armor::getDamageAbsorbtion()
{
  return _damage_absorbtion;
}

void Armor::setDamageResistance(Damage::Type type, int resistance)
{
  _damage_resistance[type] = resistance;
}

void Armor::setDamageResistanceDefault()
{
  setDamageResistance(Damage::Type::Ballistic, 0);
  setDamageResistance(Damage::Type::Electrical, 0);
  setDamageResistance(Damage::Type::Chemical, 0);
}

void Armor::setDamageAbsorbtion(int absorb)
{
  _damage_absorbtion = absorb;
}