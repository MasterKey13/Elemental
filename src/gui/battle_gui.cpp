/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "battle_gui.h"
#include "../battle.h"

BattleGui::BattleGui()
{
  _item_slot = new Sprite();

  _item_slot->setResAnim(resources::battle_ui.getResAnim("item_slot"));
  _item_slot->attachTo(getStage());
  _item_slot->setPosition(getStage()->getSize() / 2 - _item_slot->getSize() / 2);
}