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
  _gui->init(player, enemy);
  _player = player;

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
\param equipment a smart pointer to the equipment piece used in the action
\param target a regular pointer to the target of the action
*/
void Battle::addAction(spBattleAction action, spEquipment equipment, Target* target)
{
  if (_attacker_turn)
  {
    _attacker_actions.push_back(action);
    Target* t = target;
    action->process(_attacker, equipment, t);
  }
  else
  {
    _defender_actions.push_back(action);
    Target* t = target;
    action->process(_defender, equipment, t);
  }

  //check if no more action points and switch turns
  if (_attacker->getHull()->getBattery()->getActionPoints() == 0 ||
    _attacker->getHull()->getBattery()->getActionSlots() == 0)
  {
    endTurn();
    log::messageln("Switching turns...");
  }
}

//! Ends the turn and switches roles
void Battle::endTurn()
{
  _attacker_turn = !(_attacker_turn);
  
  spShip temp = _attacker;
  _attacker = _defender;
  _defender = temp;

  //if the player is defending now, remove the ship event listeners
  if (_player == _defender)
  {
    log::messageln("Disabled touch events during enemy turn");

    _attacker->setTouchEnabled(false, false);
    _defender->setTouchEnabled(false, false);

    for (int i = 0; i < _player->getHull()->getEquipment().size(); i++)
    {
      _player->getHull()->getEquipment()[i]->setTouchEnabled(false, false);
    }
  }
  else
  {
    log::messageln("Enabled touch events during player turn");

    _attacker->setTouchEnabled(true, true);
    _defender->setTouchEnabled(true, true);

    for (int i = 0; i < _player->getHull()->getEquipment().size(); i++)
    {
      _player->getHull()->getEquipment()[i]->setTouchEnabled(true, true);
    }
  }
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