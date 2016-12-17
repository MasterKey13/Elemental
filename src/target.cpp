/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "target.h"

Target::Target()
{
  setHitPoints(0);
  setHitPointsMax(0);

  setDamageResistanceDefault();
}

void Target::init(
  int hitpoints, 
  int ballistic_res, 
  int electrical_res, 
  int chemical_res
  )
{
  setHitPoints(hitpoints);
  setHitPointsMax(hitpoints);

  setDamageResistance(Damage::Type::Ballistic, ballistic_res);
  setDamageResistance(Damage::Type::Electrical, electrical_res);
  setDamageResistance(Damage::Type::Chemical, chemical_res);
}

int Target::getHitPoints()
{
  return _hitpoints;
}

int Target::getHitPointsMax()
{
  return _hitpoints_max;
}

void Target::setHitPoints(int hitpoints)
{
  if (hitpoints < 0)
  {
    hitpoints = 0;
  }

  _hitpoints = hitpoints;
}

void Target::setHitPointsMax(int hitpoints_max)
{
  if (hitpoints_max <= 0)
  {
    hitpoints_max = 1;
  }

  _hitpoints_max = hitpoints_max;
}

int Target::getDamageResistance(Damage::Type type)
{
  return _damage_resistance[type];
}

void Target::setDamageResistance(Damage::Type type, int resistance)
{
  _damage_resistance[type] = resistance;
}

void Target::setDamageResistanceDefault()
{
  setDamageResistance(Damage::Type::Ballistic, 0);
  setDamageResistance(Damage::Type::Electrical, 0);
  setDamageResistance(Damage::Type::Chemical, 0);
}

void Target::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}

spArmor Target::getArmorPiece()
{
  return _armor_piece;
}

bool Target::hasArmor()
{
  if (getArmorPiece()) { return true; }
  else { return false; }
}
