/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"
#include "battle_action.h"
#include "gui/battle_gui.h"
#include "target.h"

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

    //GETTERS
    spShip getDefender();
    spShip getAttacker();

  private:
    spShip _attacker;
    spShip _defender;

    std::list<spBattleAction> _attacker_actions;
    std::list<spBattleAction> _defender_actions;

    bool _attacker_turn;

    spBattleGui _gui;
};