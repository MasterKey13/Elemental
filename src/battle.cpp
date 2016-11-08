/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle.h"
#include "item.h"

Battle::Battle()
{
  _is_active = false;
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
  _defender_actions = new BattleActionChain();

  _is_active = true;
  _attacker_turn = true;

  int i = 0;

  while (_is_active)
  {
    if (_attacker_turn)
    {
      //request action from attacker
      
    }
    else
    {
      //request action from defender
      
    }

    //check if the battle ends (either dies, escapes or surrenders)
    break;

    //switch turn roles
    _attacker_turn = !(_attacker_turn);
  }
}

void Battle::setActive(bool activity)
{
  _is_active = activity;
}

bool Battle::getActive()
{
  return _is_active;
}
