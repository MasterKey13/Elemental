/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "ship.h"
#include "target.h"
#include "npc.h"

using namespace oxygine;

DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Engine, spEngine);
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Target, spTarget);
DECLARE_SMART(NPC, spNPC);

class BattleAI
{
  public:
    BattleAI();

    void chooseTarget(spShip self, spNPC self_AI, spShip enemy);
    std::vector<int> scanEquipmentDamage(spShip ship);

  private:
    std::map<std::string, float> _choice_scores;
    std::string _decision;
};