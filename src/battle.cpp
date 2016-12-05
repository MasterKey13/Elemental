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

  _gui = new BattleGui(this);
}

//! Initialization function for a battle
/*!
\param player a smart pointer to the player's ship
\param enemy a smart pointer to the enemy's ship
\param player_turn true if player initiated the battle
*/
void Battle::init(spShip player, spShip enemy, bool player_turn)
{
  _gui->init(player);

  //determine who attacked first
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
}

//! Add an action to the action list
/*!
\param action a smart pointer to the action performed
*/
void Battle::addAction(spBattleAction action, spEquipment equipment)
{
  if (_attacker_turn)
  {
    _attacker_actions.push_back(action);
    action->process(_attacker, equipment, getDefender()->getHull());
  }
  else
  {
    _defender_actions.push_back(action);
    action->process(_defender, equipment, getDefender()->getHull());
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

spShip Battle::getDefender()
{
  return _defender;
}

spShip Battle::getAttacker()
{
  return _attacker;
}
