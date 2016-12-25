/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle_action.h"

BattleAction::BattleAction()
{

}

void BattleAction::log()
{
  //log damage values and types for each attack
  log::messageln(
    "==============\n"
    "[DAMAGE REPORT]\n"
    "==============\n"
    "Ballistic to Armor: %d\n"
    "Ballistic to Target: %d\n"
    "Electric to Armor: %d\n"
    "Electric to Target: %d\n"
    "Chemical to Armor: %d\n"
    "Chemical to Target: %d\n"
    "==============",
    ballistic_dmg_to_armor,
    ballistic_dmg_to_target,
    electrical_dmg_to_armor,
    electrical_dmg_to_target,
    chemical_dmg_to_armor,
    chemical_dmg_to_target
    );
}


//! Process function for a battle action using a weapon
/*!
\param attacker smart ptr to the attacking ship
\param weapon smart ptr to equipment used in the attack
\param target smart ptr to target of the attack
*/
void BattleAction::process(spShip attacker, spEquipment weapon, Target* target)
{
  //reset all damages
  ballistic_dmg_to_armor = 0;
  ballistic_dmg_to_target = 0;
  electrical_dmg_to_armor = 0;
  electrical_dmg_to_target = 0;
  chemical_dmg_to_armor = 0;
  chemical_dmg_to_target = 0;
  
  //reset all armor resistances
  int armor_ballistic_res = 0;
  int armor_electrical_res = 0;
  int armor_chemical_res = 0;

  //handle armor piece damage resistances and damages
  if (target->hasArmor())
  {
    armor_ballistic_res = target->getArmorPiece()->getDamageResistance(Damage::Type::Ballistic);
    armor_electrical_res = target->getArmorPiece()->getDamageResistance(Damage::Type::Electrical);
    armor_chemical_res = target->getArmorPiece()->getDamageResistance(Damage::Type::Chemical);

    //calculate the damage dealt to each part for armor
    ballistic_dmg_to_armor = calculateDamageArmor(
      weapon->getDamage(Damage::Type::Ballistic),
      armor_ballistic_res
      );

    electrical_dmg_to_armor = calculateDamageArmor(
      weapon->getDamage(Damage::Type::Electrical),
      armor_electrical_res
      );

    chemical_dmg_to_armor = calculateDamageArmor(
      weapon->getDamage(Damage::Type::Chemical),
      armor_chemical_res
      );
  }

  //calculate the damage dealt to each part for target
  ballistic_dmg_to_target = calculateDamageTarget(
    weapon->getDamage(Damage::Type::Ballistic),
    armor_ballistic_res,
    target->getDamageResistance(Damage::Type::Ballistic));

  electrical_dmg_to_target = calculateDamageTarget(
    weapon->getDamage(Damage::Type::Electrical),
    armor_electrical_res,
    target->getDamageResistance(Damage::Type::Electrical));

  chemical_dmg_to_target = calculateDamageTarget(
    weapon->getDamage(Damage::Type::Chemical),
    armor_chemical_res,
    target->getDamageResistance(Damage::Type::Chemical));
  
  //deal all of the damage to the armor and target
  if (target->getArmorPiece())
  {
    target->getArmorPiece()->setHitPoints(
      target->getArmorPiece()->getHitPoints() -
      ballistic_dmg_to_armor -
      electrical_dmg_to_armor -
      chemical_dmg_to_armor);
  }

  target->setHitPoints(
    target->getHitPoints() -
    ballistic_dmg_to_target -
    electrical_dmg_to_target -
    chemical_dmg_to_target);

  //remove the action points and a slot
  attacker->getHull()->getBattery()->setActionPoints(
    attacker->getHull()->getBattery()->getActionPoints() - weapon->getAPCost());

  attacker->getHull()->getBattery()->setActionSlots(
    attacker->getHull()->getBattery()->getActionSlots() - 1);
}

//! Helper function to calculate damage to the armor piece
/*!
\param weap_dmg amount of damage the weapon does
\param armor_res damage resistance of the armor piece
*/
int BattleAction::calculateDamageArmor(int weap_dmg, int armor_res)
{
  //damage = weapon damage - damage resistance
  int dmg = weap_dmg - armor_res;

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
  int dmg = weap_dmg - armor_res - ballistic_dmg_to_armor - target_res;

  if (dmg > 0)
  {
    return dmg;
  }
  else
  {
    return 0;
  }
}

//! Check if the ship can perform the action
/*!
\param ship ship using the equipment
\param equipment the equipment being used
\param target of the equipment
*/
bool BattleAction::canPerform(spShip ship, spEquipment equipment, Target* target)
{
  //check if target is dead
  if (target->getHitPoints() == 0)
  {
    log::messageln("Cannot perform this action on dead target.");
    return false;
  }

  //check if the ship's battery has enough action points
  if (ship->getHull()->getBattery()->getActionPoints() >= equipment->getAPCost() &&
      ship->getHull()->getBattery()->getActionSlots() >= 1)
  {
    //handle self-targeting
    if (!equipment->isSelfTargetable() &&
        ship->find(target))
    {
      log::messageln("This equipment cannot target its own ship!");
      return false;
    }

    return true;
  }
  
  log::messageln("Not enough action points or slots to perform this action!");
  return false;
}