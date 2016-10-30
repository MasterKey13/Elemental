/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"
#include "battle_action.h"
#include "battle_action_chain.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Battle, spBattle);

class Battle : public Actor
{
  public:
    Battle();

    void init(spShip attacker, spShip defender);

  private:
    spShip _attacker;
    spShip _defender;
    spBattleActionChain _attacker_actions;
    spBattleActionChain _defender_actions;
};