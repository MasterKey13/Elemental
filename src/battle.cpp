/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle.h"
#include "item.h"
#include "gui/battle_gui.h"

Battle::Battle()
{
  //set up the needed battle action chains, etc
  _attacker_actions = new BattleActionChain();
  _defender_actions = new BattleActionChain();

  _attacker_turn = true;
  _is_active = true;
  _end_turn = false;
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

  int turn_count = 0;

  while (_is_active)
  {
    if (_attacker_turn)
    {
      processTurn(_attacker);
    }
    else
    {
      processTurn(_defender);
    }

    //TODO: check if the battle ends (either dies, escapes or surrenders)
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

//! Turn processing function
/*!
\param ship the ship of the player for which to process turn
*/
void Battle::processTurn(spShip ship)
{
  //battle loop:
  //while the ship's battery has action slots and the turn wasn't manually ended 
  while ((ship->getHull()->getBattery()->getActionSlots() != 0) && (!_end_turn))
  {
    //TODO: adjust GUI for current turn
    break;
  }

  _end_turn = false;
}
