/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"
#include "item.h"
#include "battle_action.h"
#include "gui/battle_gui.h"
#include "target.h"
#include "battle_ai.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Battle, spBattle);
DECLARE_SMART(BattleGui, spBattleGui);
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Target, spTarget);

class Battle : public Actor
{
  public:
    Battle();

    void init(spShip player, spShip enemy, bool player_turn);

    void addAction(spBattleAction action, spEquipment equipment, Target* target);
    void endTurn();
    void checkStatus();
    void finishBattle();
    void resetTurnStats(spShip ship);
    void requestEnemyTurn();
    void setBattleFinished(bool finished);

    //GETTERS
    spShip getDefender();
    spShip getAttacker();

    bool isPlayerTurn();
    bool isBattleFinished();

  private:
    spShip _attacker;
    spShip _defender;
    spShip _player;
    spShip _enemy;

    std::list<spBattleAction> _player_actions;
    std::list<spBattleAction> _enemy_actions;

    bool _finished;

    spBattleGui _gui;
    BattleAI* _AI;
};