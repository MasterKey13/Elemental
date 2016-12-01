/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "battle_gui.h"
#include "../battle.h"

BattleGui::BattleGui()
{

}

void BattleGui::drawGUI()
{
  //battle bar is the piece that holds all of the slots
  _battle_bar = new Sprite();
  _battle_bar->attachTo(getStage());
  _battle_bar->setResAnim(resources::battle_ui.getResAnim("battle_bar"));
  _battle_bar->setPosition(getStage()->getWidth() / 2 - _battle_bar->getWidth() / 2, getStage()->getHeight() - _battle_bar->getHeight());

  _x_offset = 4;

  //set up each item slot
  for (int i = 0; i < 10; i++)
  {
    _item_slots[i] = new Sprite();

    _item_slots[i]->attachTo(_battle_bar);
    _item_slots[i]->setResAnim(resources::battle_ui.getResAnim("item_slot"));
    _item_slots[i]->setPosition(_x_offset, _battle_bar->getHeight() - _item_slots[i]->getHeight() - 4);

    _x_offset += 4 + _item_slots[i]->getWidth();
  }

  _x_offset = 4;

  //set up action points
  for (int i = 0; i < 18; i++)
  {
    _action_slots[i] = new Sprite();

    _action_slots[i]->attachTo(_battle_bar);
    _action_slots[i]->setResAnim(resources::battle_ui.getResAnim("action_slot"), 0);
    _action_slots[i]->setPosition(_x_offset, 4);

    _x_offset += 4 + _action_slots[i]->getWidth();
  }
}
