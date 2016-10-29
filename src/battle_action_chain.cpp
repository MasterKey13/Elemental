/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle_action_chain.h"

BattleActionChain::BattleActionChain()
{

}

void BattleActionChain::init()
{
  setHead(nullptr);
  setTail(nullptr);
  setCurrent(nullptr);
  setNext(nullptr);
  setPrevious(nullptr);
}

void BattleActionChain::addAction(spBattleAction action)
{

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

spBattleAction BattleActionChain::getNext()
{
  return _next;
}

spBattleAction BattleActionChain::getPrevious()
{
  return _previous;
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

void BattleActionChain::setNext(spBattleAction next)
{
  _next = next;
}

void BattleActionChain::setPrevious(spBattleAction prev)
{
  _previous = prev;
}
