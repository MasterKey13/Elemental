/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "../resources.h"
#include "../ship.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Game, spGame);
DECLARE_SMART(Ship, spShip);

class GameGui : public Actor
{
  public:
    GameGui();
   
    static spSprite cursor;
    void updateCursor(Event* ev);

    void init(spShip player);
    void init(spShip player, spShip enemy);

    //draw equipment and health
    void drawGUI();
    void drawStatsPlayer();
    void drawStatsEnemy();
    void updateHitpointStatsPlayer();
    void updateHitpointStatsEnemy();
    void drawEquipmentBarPlayer();
    void drawEquipmentBarEnemy();
    void drawEquipmentSlotsPlayer();
    void drawEquipmentSlotsEnemy();

    int getYMargin();

  private:
    spShip _player;
    spShip _enemy;

    //equipment bar
    spSprite _equipment_bar_player;
    spSprite _equipment_bar_enemy;
    std::vector<spSprite> _equip_slots_player;
    std::vector<spSprite> _equip_slots_enemy;

    //health stats
    spColorRectSprite _player_hp_stats[3];
    spColorRectSprite _enemy_hp_stats[3];
    spColorRectSprite _player_armor_stats[3];
    spColorRectSprite _enemy_armor_stats[3];
    std::vector<spColorRectSprite> _player_equipment_stats;
    std::vector<spColorRectSprite> _enemy_equipment_stats;
    spTextField _player_hp_stats_text[3];
    spTextField _enemy_hp_stats_text[3];
    int _player_hp_stats_total[3];
    int _enemy_hp_stats_total[3];
    int _x_margin;
    int _y_margin;

    //misc
    Color getHitpointColor(float hitpoints);
    Color _armor_color;
};