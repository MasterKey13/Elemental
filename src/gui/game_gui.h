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
    spSprite getEquipmentBarPlayer();
    spSprite getEquipmentBarEnemy();

  private:
    spShip _player;
    spShip _enemy;

    //equipment bar
    spSprite _equipment_bar_player;
    spSprite _equipment_bar_enemy;
    std::vector<spSprite> _equipment_slots_player;
    std::vector<spSprite> _equipment_slots_enemy;
    std::vector<spSprite> _equipment_sprites_player;
    std::vector<spSprite> _equipment_sprites_enemy;

    //health stats
    spColorRectSprite _hp_stats_player[3];
    spColorRectSprite _hp_stats_enemy[3];
    spColorRectSprite _armor_stats_player[3];
    spColorRectSprite _armor_stats_enemy[3];
    std::vector<spColorRectSprite> _equipment_stats_player;
    std::vector<spColorRectSprite> _equipment_stats_enemy;
    spTextField _hp_stats_text_player[3];
    spTextField _hp_stats_text_enemy[3];
    int _hp_stats_total_player[3];
    int _hp_stats_total_enemy[3];
    int _x_margin;
    int _y_margin;

    //misc
    Color getHitpointColor(float hitpoints);
    Color _armor_color;
};