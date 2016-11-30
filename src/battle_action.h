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

    template <class Targetable>

    //battle action damage calculation functions
    void process(spItem item, Targetable target);
    int calculateDamageArmor(int weap_dmg, int armor_res);
    int calculateDamageTarget(int weap_dmg, int armor_res, int target_res);

    //SETTERS
    void setPrevious(spBattleAction previous);
    void setNext(spBattleAction next);

    //GETTERS
    spBattleAction getPrevious();
    spBattleAction getNext();

    bool hasNext();
    bool hasPrevious();

    //damages for handling battle action processing
    int _ballistic_dmg_to_armor;
    int _ballistic_dmg_to_target;
    int _electrical_dmg_to_armor;
    int _electrical_dmg_to_target;
    int _chemical_dmg_to_armor;
    int _chemical_dmg_to_target;

  private:
    spBattleAction _prev;
    spBattleAction _next;
};