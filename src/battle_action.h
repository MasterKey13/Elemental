/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "damage.h"
#include "equipment.h"
#include "ship.h"
#include "hull.h"
#include "battery.h"
#include "engine.h"
#include "armor.h"
#include "target.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleAction, spBattleAction);
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Target, spTarget);

class BattleAction : public Actor
{
  public:
    BattleAction();

    void log();

    //battle action damage calculation functions
    void process(spShip attacker, spEquipment item, spTarget target);
    int calculateDamageArmor(int weap_dmg, int armor_res);
    int calculateDamageTarget(int weap_dmg, int armor_res, int target_res);

    static bool canPerform(spShip ship, spEquipment equipment);

  private:
    //damages for handling battle action processing
    int ballistic_dmg_to_armor;
    int ballistic_dmg_to_target;
    int electrical_dmg_to_armor;
    int electrical_dmg_to_target;
    int chemical_dmg_to_armor;
    int chemical_dmg_to_target;
};