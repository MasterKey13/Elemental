/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "../battle.h"
#include "../resources.h"
#include "../ship.h"
#include "../battle_action.h"
#include "../hull.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleGui, spBattleGui);
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Battle, spBattle);
DECLARE_SMART(BattleAction, spBattleAction);
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Hull, spHull);

class BattleGui : public Actor
{
  public:
    BattleGui(spBattle battle);

    void init(spShip player);

    void drawGUI();
    void drawActionSlots();
    void drawEquipmentSlots();
    void drawEquipment();
    void drawActionPoints();

  private:
    spBattleAction _action;
    spBattle _battle;
    int _x_offset;
    spShip _player;
    spSprite _battle_bar;
    std::vector<spSprite> _equip_slots;
    std::vector<spSprite> _equipment;
    std::vector<spSprite> _action_slots;
    spProgressBar _action_points;
    spTextField _action_points_text;
};