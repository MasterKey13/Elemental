/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "battle_gui.h"

BattleGui::BattleGui()
{

}

//! Initialize a battle GUI (create all required objects)
/*!
\param player smart pointer to the player's ship
\param enemy smart pointer to the enemy's ship
*/
void BattleGui::init(spShip player, spShip enemy)
{
  _battle_bar = new Sprite();

  //resize vectors
  _equip_slots.resize(player->getHull()->getMaxEquip());
  _action_slots.resize(player->getHull()->getBattery()->getActionSlotsMax());

  //fill the vectors up with sprites
  for (int i = 0; i < player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots[i] = new Sprite();
  }

  for (int i = 0; i < player->getHull()->getBattery()->getActionSlotsMax(); i++)
  {
    _action_slots[i] = new Sprite();
  }

  drawGUI(player, enemy);
}

//! Draw the GUI on screen (refresh the entire GUI with new information)
/*!
\param player smart pointer to the player's ship
\param enemy smart pointer to the enemy's ship
*/
void BattleGui::drawGUI(spShip player, spShip enemy)
{
  //battle bar is the piece that holds all of the slots
  _battle_bar->attachTo(getStage());
  _battle_bar->setResAnim(resources::battle_ui.getResAnim("battle_bar"));
  _battle_bar->setPosition(getStage()->getWidth() / 2 - _battle_bar->getWidth() / 2, getStage()->getHeight() - _battle_bar->getHeight());

  _x_offset = 4;

  //set up each item slot
  for (int i = 0; i < player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots[i]->attachTo(_battle_bar);
    _equip_slots[i]->setResAnim(resources::battle_ui.getResAnim("item_slot"));
    _equip_slots[i]->setPosition(_x_offset, _battle_bar->getHeight() - _equip_slots[i]->getHeight() - 4);

    _x_offset += 4 + _equip_slots[i]->getWidth();
  }

  _x_offset = 4;

  //set up action slots
  //count how many of these slots are available (ie. active)
  int _active_slots = player->getHull()->getBattery()->getActionSlots();

  for (int i = 0; i < player->getHull()->getBattery()->getActionSlotsMax(); i++)
  {
    _action_slots[i]->attachTo(_battle_bar);

    //if it's active, make it green. Otherwise they're gray
    if (i < _active_slots)
    {
      _action_slots[i]->setResAnim(resources::battle_ui.getResAnim("action_slot"), 0);
    } 
    else 
    {
      _action_slots[i]->setResAnim(resources::battle_ui.getResAnim("action_slot"), 1);
    }

    _action_slots[i]->setPosition(_x_offset, 4);

    _x_offset += 4 + _action_slots[i]->getWidth();
  }
}

void BattleGui::drawItems(std::vector<spEquipment> equipment)
{

}
