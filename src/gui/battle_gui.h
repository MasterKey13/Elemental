/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "../battle.h"
#include "../resources.h"
#include "../ship.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleGui, spBattleGui);
DECLARE_SMART(Ship, spShip);

class BattleGui : public Actor
{
  public:
    BattleGui();

    void init(spShip player);

    void drawGUI();
    void drawActionSlots();
    void drawEquipmentSlots();
    void drawEquipment();

  private:
    int _x_offset;
    spShip _player;
    spSprite _battle_bar;
    std::vector<spSprite> _equip_slots;
    std::vector<spSprite> _equipment;
    std::vector<spSprite> _action_slots;
};