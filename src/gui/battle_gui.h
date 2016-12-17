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
#include "../target.h"

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

    void init(spShip player, spShip enemy);

    //drawing methods
    void drawGUI();
    void drawActionSlots();
    void drawEquipmentSlots();
    void drawEquipment();
    void drawActionPoints();
    void addEventListeners();
    void drawStats();
    void updateHitpointStats();

    //event handlers
    void useEquipment(Event* ev);
    void clickHull(Event* ev);
    void clickBattery(Event* ev);
    void clickEngine(Event* ev);

    Color getHitpointColor(float hitpoints);

  private:
    spBattleAction _action;
    spBattle _battle;
    Target* _target;

    spShip _player;
    spShip _enemy;
    spSprite _battle_bar;
    std::vector<spSprite> _equip_slots;
    std::vector<spSprite> _action_slots;
    spColorRectSprite _action_points;
    spTextField _action_points_text;
    spColorRectSprite _player_stats[3];
    spColorRectSprite _enemy_stats[3];
    spTextField _player_stats_text[3];
    spTextField _enemy_stats_text[3];
};