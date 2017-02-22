/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "game_gui.h"
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
DECLARE_SMART(GameGui, spGameGui);

class BattleGui : public Actor
{
  public:
    BattleGui(spBattle battle);

    void init(spGameGui game_gui, spShip player, spShip enemy);

    //drawing methods
    void drawGUI();
    void drawBattleBar();
    void drawActionSlots();
    void drawActionPoints();
    void drawEscapeBattleButton();
    void drawEscapeAPStatus();

    //event handlers
    void clickEquipment(Event* ev);
    void clickHull(Event* ev);
    void clickBattery(Event* ev);
    void clickEngine(Event* ev);
    void endTurn(Event* ev);
    void escapeBattle(Event* ev);
    void resetColors(Event* ev);

    //misc methods
    bool isPlayerEquipment(spEquipment eq);
    void deselectEquipment();

    //event listeners
    void addShipEventListeners();

  private:
    spGameGui _game_gui;
    spShip _player;
    spShip _enemy;

    spBattleAction _action;
    spBattle _battle;
    spEquipment _equipment;

    //battle bar
    spSprite _battle_bar;
    spColorRectSprite _action_points;
    spColorRectSprite _action_points_penalty;
    spTextField _action_points_text;
    std::vector<spSprite> _action_slots;

    std::string _hull_text;
    spSprite _escape_battle_button;
    spTextField _escape_battle_ap;
    spSprite _pre_escape_battle;

    Color _damage_color;
};