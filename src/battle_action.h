/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleAction, spBattleAction);
DECLARE_SMART(Item, spItem);

class BattleAction : public Actor
{
  public:
    BattleAction();

    //battle action damage calculation functions
    void process(spItem item, spItem target, spItem armor);
    int calculateDamageArmor(spItem armor, spItem weapon, Item::DamageType type);
    int calculateDamageTarget(spItem armor, spItem weapon, spItem target, Item::DamageType type);

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