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
*/
void BattleGui::init(spShip player)
{
  _player = player;

  _battle_bar = new Sprite();
  _battle_bar->attachTo(getStage());

  //resize vectors
  _equip_slots.resize(_player->getHull()->getMaxEquip());
  _action_slots.resize(_player->getHull()->getBattery()->getActionSlotsMax());
  _equipment.resize(_player->getHull()->getEquipment().size());

  //fill the vectors up with blank sprites according to the ship's capabilities
  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots[i] = new Sprite();
    _equip_slots[i]->attachTo(_battle_bar);
  }

  for (int i = 0; i < _player->getHull()->getBattery()->getActionSlotsMax(); i++)
  {
    _action_slots[i] = new Sprite();
    _action_slots[i]->attachTo(_battle_bar);
  }

  for (int i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _equipment[i] = new Sprite();
    _equipment[i]->attachTo(_equip_slots[i]);
  }

  drawGUI();
}

//! Draw the GUI on screen (refresh the entire GUI with new information)
void BattleGui::drawGUI()
{
  //battle bar is the piece that holds all of the slots
  _battle_bar->setResAnim(resources::battle_ui.getResAnim("battle_bar"));
  _battle_bar->setPosition(getStage()->getWidth() / 2 - _battle_bar->getWidth() / 2, getStage()->getHeight() - _battle_bar->getHeight());

  //draw action slots
  drawActionSlots();

  //draw equipment slots
  drawEquipmentSlots();

  //draw the equipment on the screen
  drawEquipment();
}

//! Draw the action slots
void BattleGui::drawActionSlots()
{
  _x_offset = 4;

  //set up action slots
  //count how many of these slots are available (ie. active)
  int _active_slots = _player->getHull()->getBattery()->getActionSlots();

  for (int i = 0; i < _player->getHull()->getBattery()->getActionSlotsMax(); i++)
  {
    //if they're active, make them green, if inactive - gray
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


//! Draw the equipment slots
void BattleGui::drawEquipmentSlots()
{
  _x_offset = 4;

  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots[i]->setResAnim(resources::battle_ui.getResAnim("item_slot"));
    _equip_slots[i]->setPosition(_x_offset, _battle_bar->getHeight() - _equip_slots[i]->getHeight() - 4);

    _x_offset += 4 + _equip_slots[i]->getWidth();
  }
}

//! Draw the equipment
void BattleGui::drawEquipment()
{
  for (int i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _equipment[i]->setResAnim(resources::equipment.getResAnim(_player->getHull()->getEquipment()[i]->getID()));
    _equipment[i]->setPosition(1, 1);

    //add event listener to weapon button
    _equipment[i]->addEventListener(TouchEvent::CLICK, [&, i](Event*) 
    {
      log::messageln("%s was clicked!", _player->getHull()->getEquipment()[i]->getID().c_str());
    });
  }
}
