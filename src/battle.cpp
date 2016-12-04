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
  _attacker_turn = true;
  _is_active = true;
  _end_turn = false;
}

//! Initialization function for a battle
/*!
\param player a smart pointer to the player's ship
\param enemy a smart pointer to the enemy's ship
\param player_turn true if player initiated the battle
*/
void Battle::init(spShip player, spShip enemy, bool player_turn)
{
  _gui = new BattleGui();
  _gui->init(player);

  if (player_turn)
  {
    _attacker = player;
    _defender = enemy;
  }
  else
  {
    _attacker = enemy;
    _defender = player;
  }

  int turn_count = 0;

  //battle loop
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