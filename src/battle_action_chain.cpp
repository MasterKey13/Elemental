/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle_action_chain.h"

BattleActionChain::BattleActionChain()
{
  //set everything to null pointers
  setHead(nullptr);
  setTail(nullptr);
  setCurrent(nullptr);
}

void BattleActionChain::setHead(spBattleAction head)
{
  _head = head;
}

void BattleActionChain::setTail(spBattleAction tail)
{
  _tail = tail;
}

void BattleActionChain::setCurrent(spBattleAction curr)
{
  _current = curr;
}

spBattleAction BattleActionChain::getHead()
{
  return _head;
}

spBattleAction BattleActionChain::getTail()
{
  return _tail;
}

spBattleAction BattleActionChain::getCurrent()
{
  return _current;
}

//! Adds a new battle action to the doubly linked list (chain)
/*!
\param action smart pointer to the action to add to the battle action chain
*/
void BattleActionChain::addAction(spBattleAction action)
{
  //if the linked list is not empty, add the new action to the tail
  if (getHead())
  {
    getTail()->setNext(action);
    action->setPrevious(getTail());
    setTail(action);
  }
  else //if it's empty, set the new action as the head, tail and current action
  {
    setHead(action);
    setTail(action);
    setCurrent(action);
  }
}