/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "battle.h"

Battle::Battle()
{
  _battle_gui = new BattleGui(this);
  _battle_gui->attachTo(this);

  _AI = new BattleAI();
  
  _finished = false;
}

//! Initialization function for a battle
/*!
\param smart pointer to the game GUI
\param player a smart pointer to the player's ship
\param enemy a smart pointer to the enemy's ship
\param player_turn true if player initiated the battle
*/
void Battle::init(spGameGui game_gui, spShip player, spShip enemy, bool player_turn)
{
  _battle_gui->init(game_gui, player, enemy);
  _game_gui = game_gui;
  _player = player;
  _enemy = enemy;

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
    
    requestEnemyTurn();
  }

  resetTurnStats(_attacker);

  _battle_gui->drawGUI();
  _game_gui->drawGUI();
}

//! Add an action to the action list
/*!
\param action a smart pointer to the action performed
\param equipment a smart pointer to the equipment piece used in the action
\param target a regular pointer to the target of the action
*/
void Battle::addAction(spBattleAction action, spEquipment equipment, Target* target)
{
  if (isPlayerTurn())
  {
    log::messageln("ADDED PLAYER ACTION");
    _player_actions.push_back(action);
    Target* t = target;
    action->process(_player, equipment, t);
  }
  else
  {
    log::messageln("ADDED ENEMY ACTION");
    _enemy_actions.push_back(action);
    Target* t = target;
    action->process(_enemy, equipment, t);
  }

  _battle_gui->drawGUI();
  _game_gui->drawGUI();

  checkStatus();
}

//! Ends the turn by switching roles
void Battle::endTurn()
{  
  //add remaining AP to engine escape pool
  _attacker->getHull()->getEngine()->setAPEscapePool(
    _attacker->getHull()->getEngine()->getAPEscapePool() +
    (_attacker->getHull()->getBattery()->getActionPointsMax() -
      _attacker->getHull()->getBattery()->getActionPoints() /
      _attacker->getHull()->getBattery()->getActionPointsMax()));

  if (isPlayerTurn())
  {
    //switch roles
    _attacker = _enemy;
    _defender = _player;
  }
  else
  {
    //switch roles
    _attacker = _player;
    _defender = _enemy;
  }

  resetTurnStats(_attacker);

  _battle_gui->drawGUI();
  _game_gui->drawGUI();
}

//! Checks if the turn or the battle ended and handle accordingly
void Battle::checkStatus()
{
  //defender OR attacker are dead
  if (!(_attacker->isAlive()) || !(_defender->isAlive()) || isBattleFinished())
  {
    finishBattle();
  }
}

//! Finishes battle by hiding battle GUI and other stuff
void Battle::finishBattle()
{
  setBattleFinished(true);
  _battle_gui->detach();

  log::messageln("BATTLE FINISHED; GUI HIDDEN");
}

//! Reset the action slots and points for the ship at the start of the ship's turn
/*!
\param ship a smart pointer to the ship which to reset turn for
*/
void Battle::resetTurnStats(spShip ship)
{
  ship->getHull()->getBattery()->setActionPoints(ship->getHull()->getBattery()->getActionPointsMaxAvailable());
  ship->getHull()->getBattery()->setActionSlots(ship->getHull()->getBattery()->getActionSlotsMax());
}

void Battle::requestEnemyTurn()
{
  spNPC _enemy_NPC = safeSpCast<NPC>(_enemy->getPilot());
  _AI->think(_enemy, _player, _enemy_NPC, this);
}

void Battle::setBattleFinished(bool finished)
{
  _finished = finished;
}

spShip Battle::getDefender()
{
  return _defender;
}

spShip Battle::getAttacker()
{
  return _attacker;
}

bool Battle::isPlayerTurn()
{
  return (_player == _attacker) ? true : false;
}

bool Battle::isBattleFinished()
{
  return _finished;
}
