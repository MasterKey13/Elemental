/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "battle_gui.h"

BattleGui::BattleGui(spBattle battle)
{
  _battle = battle;
  _action = new BattleAction();
  _target = nullptr;
}

//! Initialize a battle GUI (create all required objects)
/*!
\param player smart pointer to the player's ship
\pararm enemy smart pointer to the enemy's ship
*/
void BattleGui::init(spShip player, spShip enemy)
{
  _player = player;

  _battle_bar = new Sprite();
  _battle_bar->attachTo(this);

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

  _action_points = new ProgressBar();
  _action_points->attachTo(_battle_bar);

  _action_points_text = new TextField();
  _action_points_text->attachTo(_battle_bar);

  addEventListeners(player, enemy);
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

  //draw action points
  drawActionPoints();
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

    _equipment[i]->removeAllEventListeners();

    //add event listener to weapon button
    _equipment[i]->addEventListener(TouchEvent::CLICK, [&, i](Event*) 
    {
      if (_target)
      {
        if (BattleAction::canPerform(_player, _player->getHull()->getEquipment()[i]))
        {
          _battle->addAction(_action, _player->getHull()->getEquipment()[i], _target);
          _battle->checkStatus();

          drawGUI();
        }
      }
      else
      {
        log::messageln("No target selected!");
      }
    });

  }
}

//! Draw the action points
void BattleGui::drawActionPoints()
{ 
  //progress bar shows how much action points we have left
  _action_points->setProgress(
    (float)_player->getHull()->getBattery()->getActionPoints() /
    (float)_player->getHull()->getBattery()->getActionPointsMax()
    );
  _action_points->setResAnim(resources::battle_ui.getResAnim("action_point"));
  _action_points->setScaleX(_battle_bar->getWidth() / _action_points->getWidth());
  _action_points->setPosition(0, -(_action_points->getHeight()));

  //text tells us exactly how much we have left
  std::string ap = 
    std::to_string(_player->getHull()->getBattery()->getActionPoints())
    + "/" +
    std::to_string(_player->getHull()->getBattery()->getActionPointsMax());

  _action_points_text->setText(ap);
  _action_points_text->setPosition(_battle_bar->getWidth() / 2 - _action_points_text->getWidth() / 2, -20);
}

//!Set up event handling on the ship pieces for targeting
/*!
\param player smart pointer to the player's ship
\pararm enemy smart pointer to the enemy's ship
*/
void BattleGui::addEventListeners(spShip player, spShip enemy)
{
  player->getHull()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickHull));
  enemy->getHull()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickHull));

  player->getHull()->getEngine()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEngine));
  enemy->getHull()->getEngine()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEngine));

  player->getHull()->getBattery()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickBattery));
  enemy->getHull()->getBattery()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickBattery));
}

void BattleGui::clickHull(Event* ev)
{
  spHull t = safeSpCast<Hull>(ev->currentTarget);
  _target = t.get();

  //stops event propagation so it doesn't target what's behind it
  ev->stopPropagation(); 

  log::messageln("[TARGET ACQUIRED] %s!", t.get()->getID().c_str());
}

void BattleGui::clickBattery(Event* ev)
{
  spBattery b = safeSpCast<Battery>(ev->currentTarget);
  _target = b.get();

  //stops event propagation so it doesn't target what's behind it
  ev->stopPropagation();

  log::messageln("[TARGET ACQUIRED] %s!", b.get()->getID().c_str());
}

void BattleGui::clickEngine(Event* ev)
{
  spEngine e = safeSpCast<Engine>(ev->currentTarget);
  _target = e.get();

  //stops event propagation so it doesn't target what's behind it
  ev->stopPropagation();

  log::messageln("[TARGET ACQUIRED] %s!", e.get()->getID().c_str());
}
