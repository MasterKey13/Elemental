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
#include "../game.h"

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
    void drawBattleBar();
    void drawBattleBarEnemy();
    void drawActionSlots();
    void drawEquipmentSlotsPlayer();
    void drawEquipmentSlotsEnemy();
    void drawEquipmentPlayer();
    void drawEquipmentEnemy();
    void drawActionPoints();
    void drawStats();
    void updateHitpointStats();
    void drawEquipmentInfo();
    void drawEndTurnButton();
    void drawEscapeBattleButton();
    void drawEscapeAPStatus();

    //event handlers
    void clickEquipment(Event* ev);
    void clickHull(Event* ev);
    void clickBattery(Event* ev);
    void clickEngine(Event* ev);
    void detailEquipmentShow(Event* ev);
    void detailHide(Event* ev);
    void detailEngineShow(Event* ev);
    void detailBatteryShow(Event* ev);
    void detailHullShow(Event* ev);
    void detailPartHide(Event* ev);
    void endTurn(Event* ev);
    void escapeBattle(Event* ev);

    //misc methods
    Color getHitpointColor(float hitpoints);
    bool isPlayerEquipment(spEquipment eq);
    void deselectEquipment();

    //event listeners
    void addShipEventListeners();

  private:
    spBattleAction _action;
    spBattle _battle;
    spEquipment _equipment;
    spShip _player;
    spShip _enemy;

    spSprite _battle_bar;
    std::vector<spSprite> _equip_slots;
    std::vector<spSprite> _action_slots;
    spColorRectSprite _action_points;
    spColorRectSprite _action_points_penalty;
    spTextField _action_points_text;

    spColorRectSprite _player_hp_stats[3];
    spColorRectSprite _player_armor_stats[3];
    std::vector<spColorRectSprite> _player_equipment_stats;
    spColorRectSprite _enemy_hp_stats[3];
    spColorRectSprite _enemy_armor_stats[3];
    std::vector<spColorRectSprite> _enemy_equipment_stats;
    spTextField _player_hp_stats_text[3];
    spTextField _enemy_hp_stats_text[3];
    int _player_hp_stats_total[3];
    int _enemy_hp_stats_total[3];

    spSprite _item_info_bar;
    spTextField _item_info_text;
    std::string _hull_text;
    spSprite _end_turn_button;
    spSprite _escape_battle_button;
    spTextField _escape_battle_ap;
    spSprite _pre_escape_battle;

    spSprite _battle_bar_enemy;
    std::vector<spSprite> _equip_slots_enemy;

    Color _damage_color;
};