/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle_action.h"

BattleAction::BattleAction()
{
  setPrevious(nullptr);
  setNext(nullptr);
}

//! Process function for a battle action using a weapon
/*!
\param item smart ptr to item used in the attack
\param target smart ptr to target of the attack
\param armor smart ptr to armor piece covering the target
*/
void BattleAction::process(spItem weapon, spItem target, spItem armor)
{
  //calculate the damage dealt to each part (armor and target)
  _ballistic_dmg_to_armor = calculateDamageArmor(
    weapon->getDamage(Item::DamageType::Ballistic), 
    armor->getDamageResistance(Item::DamageType::Ballistic),
    armor->getDamageAbsorbtion());

  _ballistic_dmg_to_target = calculateDamageTarget(
    weapon->getDamage(Item::DamageType::Ballistic),
    armor->getDamageResistance(Item::DamageType::Ballistic),
    target->getDamageResistance(Item::DamageType::Ballistic));

  _electrical_dmg_to_armor = calculateDamageArmor(
    weapon->getDamage(Item::DamageType::Electrical),
    armor->getDamageResistance(Item::DamageType::Electrical),
    armor->getDamageAbsorbtion());

  _electrical_dmg_to_target = calculateDamageTarget(
    weapon->getDamage(Item::DamageType::Electrical),
    armor->getDamageResistance(Item::DamageType::Electrical),
    target->getDamageResistance(Item::DamageType::Electrical));

  _chemical_dmg_to_armor = calculateDamageArmor(
    weapon->getDamage(Item::DamageType::Chemical),
    armor->getDamageResistance(Item::DamageType::Chemical),
    armor->getDamageAbsorbtion());

  _chemical_dmg_to_target = calculateDamageTarget(
    weapon->getDamage(Item::DamageType::Chemical),
    armor->getDamageResistance(Item::DamageType::Chemical),
    target->getDamageResistance(Item::DamageType::Chemical));

  //log damage values and types for each attack
  log::messageln("BA: %d\nBT: %d\nEA: %d\nET: %d\nCA: %d\nCT: %d",
    _ballistic_dmg_to_armor,
    _ballistic_dmg_to_target,
    _electrical_dmg_to_armor,
    _electrical_dmg_to_target,
    _chemical_dmg_to_armor,
    _chemical_dmg_to_target
    );
  
  //deal all of the damage to the armor and target
  armor->setHitPoints(armor->getHitPoints() -
    _ballistic_dmg_to_armor -
    _electrical_dmg_to_armor -
    _chemical_dmg_to_armor);

  target->setHitPoints(target->getHitPoints() -
    _ballistic_dmg_to_target -
    _electrical_dmg_to_target -
    _chemical_dmg_to_target);
}

//! Helper function to calculate damage to the armor piece
/*!
\param weap_dmg amount of damage the weapon does
\param armor_res damage resistance of the armor piece
\param armor_abs damage absorbtion of the armor piece
*/
int BattleAction::calculateDamageArmor(int weap_dmg, int armor_res, int armor_abs)
{
  //damage = weapon damage - damage resistance, limited by damage absorbtion
  int dmg = std::min(weap_dmg - armor_res, armor_abs);

  if (dmg > 0) 
  { 
    return dmg; 
  }
  else
  {
    return 0;
  }
}

//! Helper function to calculate damage to the target
/*!
\param weap_dmg amount of damage the weapon does
\param armor_res damage resistance of the armor piece
\param target_res damage resistance of the target
*/
int BattleAction::calculateDamageTarget(int weap_dmg, int armor_res, int target_res)
{
  //damage = weapon damage - armor damage resistance - damage negated by armor - target's damage resistance
  int dmg = weap_dmg - armor_res - _ballistic_dmg_to_armor - target_res;

  if (dmg > 0)
  {
    return dmg;
  }
  else
  {
    return 0;
  }
}

void BattleAction::setPrevious(spBattleAction previous)
{
  _prev = previous;
}

void BattleAction::setNext(spBattleAction next)
{
  _next = next;
}

spBattleAction BattleAction::getPrevious()
{
  return _prev;
}

spBattleAction BattleAction::getNext()
{
  return _next;
}

bool BattleAction::hasNext()
{
  return getNext() ? true : false;
}

bool BattleAction::hasPrevious()
{
  return getPrevious() ? true : false;
}