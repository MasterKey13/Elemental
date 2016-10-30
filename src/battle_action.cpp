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

//! Initialization function for a battle action using a weapon
/*!
\param weapon smart ptr to weapon used to attack
\param target smart ptr to target of the attack
*/
void BattleAction::init(spWeapon weapon, spItem target)
{

}

//! Initialization function for a battle action using an item (equipment)
/*!
\param item smart ptr to item used
\param target smart ptr to the item's target
*/
void BattleAction::init(spItem item, spItem target)
{

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
