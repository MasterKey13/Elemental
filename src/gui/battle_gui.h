/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "../resources.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleGui, spBattleGui);

class BattleGui : public Actor
{
  public:
    BattleGui();

    void drawGUI();

  private:
    int _x_offset;
    spSprite _battle_bar;
    spSprite _item_slots[10];
    spSprite _action_slots[18];
};