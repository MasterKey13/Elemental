/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"
#include "battle_action.h"
#include "battle_action_chain.h"
#include "gui/battle_gui.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Battle, spBattle);

class Battle : public Actor
{
  public:
    Battle();

    void init(spShip player, spShip enemy, bool player_turn);

    //SETTERS
    void setActive(bool activity);

    //GETTERS
    bool getActive();

    void processTurn(spShip ship);
    void drawGUI(spShip player, spShip enemy);

  private:
    spShip _attacker;
    spShip _defender;
    spBattleActionChain _attacker_actions;
    spBattleActionChain _defender_actions;

    bool _is_active;
    bool _attacker_turn;
    bool _end_turn;

    spBattleGui _gui;
};