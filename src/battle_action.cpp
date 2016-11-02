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
  _ballistic_dmg_to_armor = calculateDamageArmor(armor, weapon, Item::DamageType::Ballistic);
  _ballistic_dmg_to_target = calculateDamageTarget(armor, weapon, target, Item::DamageType::Ballistic);
  _electrical_dmg_to_armor = calculateDamageArmor(armor, weapon, Item::DamageType::Electrical);
  _electrical_dmg_to_target = calculateDamageTarget(armor, weapon, target, Item::DamageType::Electrical);
  _chemical_dmg_to_armor = calculateDamageArmor(armor, weapon, Item::DamageType::Chemical);
  _chemical_dmg_to_target = calculateDamageTarget(armor, weapon, target, Item::DamageType::Chemical);

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

int BattleAction::calculateDamageArmor(spItem armor, spItem weapon, Item::DamageType type)
{
  if (armor)
  {
    return std::min(weapon->getDamage(type) -
                    armor->getDamageResistance(type),
                    armor->getDamageAbsorbtion());
  }
  else
  {
    return 0;
  }
}

int BattleAction::calculateDamageTarget(spItem armor, spItem weapon, spItem target, Item::DamageType type)
{
  return weapon->getDamage(type) - 
         armor->getDamageResistance(type) -
         _ballistic_dmg_to_armor -
         target->getDamageResistance(type);
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