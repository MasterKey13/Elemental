/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "damageable.h"

Damageable::Damageable()
{
  setDamageResistanceDefault();
}

int Damageable::getDamageResistance(Damage::Type type)
{
  return _damage_resistance[type];
}

void Damageable::setDamageResistance(Damage::Type type, int resistance)
{
  _damage_resistance[type] = resistance;
}

void Damageable::setDamageResistanceDefault()
{
  setDamageResistance(Damage::Type::Ballistic, 0);
  setDamageResistance(Damage::Type::Electrical, 0);
  setDamageResistance(Damage::Type::Chemical, 0);
}