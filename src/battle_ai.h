/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "battle.h"
#include "ship.h"
#include "target.h"

using namespace oxygine;

#define DECISION_COUNT 5

DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Target, spTarget);
DECLARE_SMART(NPC, spNPC);
DECLARE_SMART(BattleAction, spBattleAction);
DECLARE_SMART(Battle, spBattle);

class BattleAI
{
  public:
    BattleAI();

    enum decisions
    {
      ESCAPE,
      ATTACK_HULL,
      ATTACK_BATTERY,
      ATTACK_ENGINE,
      ATTACK_EQUIPMENT
    };

    //custom sorting function (from highest to smallest)
    struct { bool operator() (int a, int b) { return a > b; } } biggerThan;

    //thinking-related methods
    void think(spShip self_ship, spShip enemy_ship, spNPC self_NPC, spBattle battle);
    void chooseTarget(spShip self_ship, spShip enemy_ship, spNPC self_NPC, spBattle battle);
    void makeFinalDecision();
    void validateDecisions(spShip self_ship);
    void executeDecision(spShip self_ship, spShip enemy_ship, spBattle battle);

    //utility methods
    std::vector<int> scanEquipmentDamage(spShip ship);
    void sortChoices();
    void resetChoices();
    void doNextBestChoice(spShip self_ship, spShip enemy_ship, spBattle battle);

private:
    static int _best_choice_index;
    float _choice_scores[DECISION_COUNT];
    int _decisions[DECISION_COUNT];
    int _final_decision;
};