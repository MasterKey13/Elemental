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
