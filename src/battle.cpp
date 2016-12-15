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
  _gui = new BattleGui(this);
  _gui->attachTo(this);
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
    spTarget t = getDefender()->getHull();
    action->process(_attacker, equipment, t);
  }
  else
  {
    _defender_actions.push_back(action);
    spTarget t = getDefender()->getHull();
    action->process(_defender, equipment, t);
  }

  log::messageln("ATTACKER:");
  _attacker->log();
  log::messageln("DEFENDER:");
  _defender->log();
}

//! Ends the turn and switches roles
void Battle::endTurn()
{
  _attacker_turn = !(_attacker_turn);
  
  spShip temp = _attacker;
  _attacker = _defender;
  _defender = temp;
}

//! Checks whether the battle ended and handle accordingly
void Battle::checkStatus()
{
  //defender OR attacker are dead
  if (!(_attacker->isAlive()) || !(_defender->isAlive()))
  {
    _gui->detach();

    log::messageln("BATTLE GUI HIDDEN");
  }
}

spShip Battle::getDefender()
{
  return _defender;
}

spShip Battle::getAttacker()
{
  return _attacker;
}
