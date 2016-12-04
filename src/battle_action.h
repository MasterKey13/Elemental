/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "damage.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleAction, spBattleAction);
DECLARE_SMART(Item, spItem);

class BattleAction : public Actor
{
  public:
    BattleAction();

    void log();

    template <class Targetable>

    //battle action damage calculation functions
    void process(spItem item, Targetable target);
    int calculateDamageArmor(int weap_dmg, int armor_res);
    int calculateDamageTarget(int weap_dmg, int armor_res, int target_res);

  private:
    //damages for handling battle action processing
    int ballistic_dmg_to_armor;
    int ballistic_dmg_to_target;
    int electrical_dmg_to_armor;
    int electrical_dmg_to_target;
    int chemical_dmg_to_armor;
    int chemical_dmg_to_target;
};