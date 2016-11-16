
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "equipment.h"

Equipment::Equipment()
{

}

void Equipment::setArmorPiece(spItem armor)
{
  _armor_piece = armor;
}

int Equipment::getDamageResistance(Damage::Type type)
{
  return _damage_resistance[type];
}

int Equipment::getDamageAbsorbtion()
{
  return _damage_absorbtion;
}

spItem Equipment::getArmorPiece()
{
  if (_armor_piece)
  {
    return _armor_piece;
  }
}

//! Return the amount of damage the weapon deals for the given damage type
/*!
\param damage_type the damage type to return damage amount for
*/
int Equipment::getDamage(Damage::Type damage_type)
{
  return _damage[damage_type];
}

//! Set the amount of damage the weapon deals for given damage type
/*!
\param damage_type the damage type for which to the set the damage amount
\param damage the amount of damage it deals
*/
void Equipment::setDamage(Damage::Type damage_type, int damage)
{
  _damage[damage_type] = damage;
}

void Equipment::setDamageDefault()
{
  setDamage(Damage::Type::Ballistic, 0);
  setDamage(Damage::Type::Electrical, 0);
  setDamage(Damage::Type::Chemical, 0);
}
