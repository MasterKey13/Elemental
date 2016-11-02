/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle.h"
#include "item.h"

Battle::Battle()
{

}

//! Initialization function for a battle
/*!
\param attacker a smart pointer to the attacking ship
\param defender a smart pointer to the defending ship
*/
void Battle::init(spShip attacker, spShip defender)
{
  _attacker = attacker;
  _defender = defender;

  _attacker_actions = new BattleActionChain();
  _attacker_actions->init();

  _defender_actions = new BattleActionChain();
  _defender_actions->init();

  //debugging
  spItem armor = new Item();
  armor->init(4);

  spItem weap = new Item();
  weap->init(3);

  log::messageln("Engine HP: %d", attacker->getEngine()->getHitPoints());

  _attacker_actions->addAction(new BattleAction());
  _attacker_actions->getHead()->process(weap, attacker->getEngine(), armor);

  log::messageln("Engine HP: %d", attacker->getEngine()->getHitPoints());
}