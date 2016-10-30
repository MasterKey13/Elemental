/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle_action.h"
#include "weapon.h"

BattleAction::BattleAction()
{

}

//! Initialization function for a battle action
void BattleAction::init()
{
  setPrevious(nullptr);
  setNext(nullptr);
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
