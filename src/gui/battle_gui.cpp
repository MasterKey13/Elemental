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
  _hull_text = "";
}

//! Initialize a battle GUI (create all required objects)
/*!
\param player smart pointer to the player's ship
\param enemy smart pointer to the enemy's ship
*/
void BattleGui::init(spShip player, spShip enemy)
{
  _player = player;
  _enemy = enemy;

  _battle_bar = new Sprite();
  _battle_bar->attachTo(this);

  _action_points = new ColorRectSprite();
  _action_points->attachTo(_battle_bar);

  _action_points_text = new TextField();
  _action_points_text->attachTo(_battle_bar);

  _item_info_bar = new Sprite();
  _item_info_bar->attachTo(_battle_bar);
  _item_info_bar->setAlpha(0);

  _item_info_text = new TextField();
  _item_info_text->attachTo(_item_info_bar);

  //resize vectors
  _equip_slots.resize(_player->getHull()->getMaxEquip());
  _action_slots.resize(_player->getHull()->getBattery()->getActionSlotsMax());

  //set up equipment and action slots
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

  //attach equipment onto the GUI
  for (size_t i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _player->getHull()->getEquipment()[i]->attachTo(_equip_slots[i]);
  }

  //set up stat sprites
  for (int i = 0; i < 3; i++)
  {
    _player_stats[i] = new ColorRectSprite();
    _player_stats[i]->attachTo(this);

    _player_stats_text[i] = new TextField();
    _player_stats_text[i]->attachTo(this);

    _enemy_stats[i] = new ColorRectSprite();
    _enemy_stats[i]->attachTo(this);

    _enemy_stats_text[i] = new TextField();
    _enemy_stats_text[i]->attachTo(this);
  }

  addShipEventListeners();
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

  //draw equipment info piece
  drawEquipmentInfo();

  //draw action points
  drawActionPoints();

  //draw stats
  drawStats();
}

//! Draw the action slots
void BattleGui::drawActionSlots()
{
  int x_offset = 4;

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

    _action_slots[i]->setPosition((float)x_offset, 4.0f);
    x_offset += 4 + (int)_action_slots[i]->getWidth();
  }
}


//! Draw the equipment slots
void BattleGui::drawEquipmentSlots()
{
  int x_offset = 4;

  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots[i]->setResAnim(resources::battle_ui.getResAnim("item_slot"));
    _equip_slots[i]->setPosition((float)x_offset, _battle_bar->getHeight() - _equip_slots[i]->getHeight() - 4.0f);

    x_offset += 4 + (int)_equip_slots[i]->getWidth();
  }
}

//! Draw the equipment
void BattleGui::drawEquipment()
{
  for (size_t i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _player->getHull()->getEquipment()[i]->setVisible(true);
    _player->getHull()->getEquipment()[i]->setPosition(1, 1);
    _player->getHull()->getEquipment()[i]->removeAllEventListeners();

    //add roll over event listener for detailed info on equipment
    _player->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailEquipmentShow));

    //add roll over event listener for detailed info on equipment
    _player->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailHide));

    //add click event listener to use equipment
    _player->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::CLICK, CLOSURE(this, &BattleGui::useEquipment));
  }
}

//! Draw the action points
void BattleGui::drawActionPoints()
{ 
  float percent = (float)_player->getHull()->getBattery()->getActionPoints() /
    (float)_player->getHull()->getBattery()->getActionPointsMax();

  //progress bar shows how much action points we have left
  _action_points->setColor(Color::Blue);
  _action_points->setSize(_battle_bar->getWidth() * percent, 4);
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
void BattleGui::addShipEventListeners()
{
  //click events for targeting
  _player->getHull()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickHull));
  _enemy->getHull()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickHull));

  _player->getHull()->getEngine()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEngine));
   _enemy->getHull()->getEngine()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEngine));

  _player->getHull()->getBattery()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickBattery));
  _enemy->getHull()->getBattery()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickBattery));

  //roll over/out events for detailed info bar
  _player->getHull()->addEventListener
    (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailHullShow));
  _player->getHull()->addEventListener
    (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailHide));

  _enemy->getHull()->addEventListener
    (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailHullShow));
  _enemy->getHull()->addEventListener
    (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailHide));

  _player->getHull()->getBattery()->addEventListener
    (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailBatteryShow));
  _player->getHull()->getBattery()->addEventListener
    (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailPartHide));

  _enemy->getHull()->getBattery()->addEventListener
    (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailBatteryShow));
  _enemy->getHull()->getBattery()->addEventListener
    (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailPartHide));

  _player->getHull()->getEngine()->addEventListener
    (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailEngineShow));
  _player->getHull()->getEngine()->addEventListener
    (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailPartHide));

  _enemy->getHull()->getEngine()->addEventListener
    (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailEngineShow));
  _enemy->getHull()->getEngine()->addEventListener
    (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailPartHide));
}

//! Clear the target pointer
void BattleGui::clearTarget()
{
  _target = nullptr;
}

//! Draw the hitpoint bars for hull, battery and engine of both player and enemy
void BattleGui::drawStats()
{
  int x_offset = 6;
  int y_offset = 6;

  for (int i = 0; i < 3; i++)
  { 
    //player stats go on the left top corner
    _player_stats[i]->setSize(512, 16);
    _player_stats[i]->setAnchor(0.0f, 0.0f);
    _player_stats[i]->setPosition((float)x_offset, (float)y_offset);

    _player_stats_text[i]->setAlign(TextStyle::VerticalAlign::VALIGN_MIDDLE, TextStyle::HorizontalAlign::HALIGN_MIDDLE);

    //enemy stats go on the top right corner
    _enemy_stats[i]->setSize(512, 16);
    _enemy_stats[i]->setAnchor(1.0f, 0.0f);
    _enemy_stats[i]->setPosition(
      getStage()->getWidth() - (float)x_offset, 
      (float)y_offset);

    _enemy_stats_text[i]->setAlign(TextStyle::VerticalAlign::VALIGN_MIDDLE, TextStyle::HorizontalAlign::HALIGN_MIDDLE);

    y_offset += (int)_player_stats[i]->getHeight() + 6;
  }

  updateHitpointStats();
}

//! Updates the scale and color of hitpoints stats
void BattleGui::updateHitpointStats()
{
  //update hitpoints of hulls
  _player_stats[0]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getHitPoints() /
    (float)_player->getHull()->getHitPointsMax()
    ), 500);

  _enemy_stats[0]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getHitPoints() /
    (float)_enemy->getHull()->getHitPointsMax()
    ), 500);

  _player_stats[0]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()));

  _enemy_stats[0]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()));

  _player_stats_text[0]->setText(
    "Hull: " + 
    std::to_string(_player->getHull()->getHitPoints()) + 
    "/" + 
    std::to_string(_player->getHull()->getHitPointsMax()));

  _enemy_stats_text[0]->setText(
    "Hull: " +
    std::to_string(_enemy->getHull()->getHitPoints()) +
    "/" +
    std::to_string(_enemy->getHull()->getHitPointsMax()));

  _player_stats_text[0]->setPosition(
    _player_stats[0]->getX() + _player_stats[0]->getWidth() / 2, 
    _player_stats[0]->getY() + _player_stats[0]->getHeight() / 2);

  _enemy_stats_text[0]->setPosition(
    _enemy_stats[0]->getX() - _enemy_stats[0]->getWidth() / 2, 
    _enemy_stats[0]->getY() + _enemy_stats[0]->getHeight() / 2);

  //update hitpoints of batteries
  _player_stats[1]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getBattery()->getHitPoints() /
    (float)_player->getHull()->getBattery()->getHitPointsMax()
    ), 500);

  _enemy_stats[1]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getBattery()->getHitPoints() /
    (float)_enemy->getHull()->getBattery()->getHitPointsMax()
    ), 500);

  _player_stats[1]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getBattery()->getHitPoints() /
      (float)_player->getHull()->getBattery()->getHitPointsMax()));

  _enemy_stats[1]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getBattery()->getHitPoints() /
      (float)_enemy->getHull()->getBattery()->getHitPointsMax()));

  _player_stats_text[1]->setText(
    "Battery: " +
    std::to_string(_player->getHull()->getBattery()->getHitPoints()) +
    "/" +
    std::to_string(_player->getHull()->getBattery()->getHitPointsMax()));

  _enemy_stats_text[1]->setText(
    "Battery: " +
    std::to_string(_enemy->getHull()->getBattery()->getHitPoints()) +
    "/" +
    std::to_string(_enemy->getHull()->getBattery()->getHitPointsMax()));

  _player_stats_text[1]->setPosition(
    _player_stats[1]->getX() + _player_stats[1]->getWidth() / 2,
    _player_stats[1]->getY() + _player_stats[1]->getHeight() / 2);

  _enemy_stats_text[1]->setPosition(
    _enemy_stats[1]->getX() - _enemy_stats[1]->getWidth() / 2, 
    _enemy_stats[1]->getY() + _enemy_stats[1]->getHeight() / 2);

  //update hitpoints of engines
  _player_stats[2]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getEngine()->getHitPoints() /
    (float)_player->getHull()->getEngine()->getHitPointsMax()
    ), 500);

  _enemy_stats[2]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getEngine()->getHitPoints() /
    (float)_enemy->getHull()->getEngine()->getHitPointsMax()
    ), 500);

  _player_stats[2]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getEngine()->getHitPoints() /
      (float)_player->getHull()->getEngine()->getHitPointsMax()));

  _enemy_stats[2]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getEngine()->getHitPoints() /
      (float)_enemy->getHull()->getEngine()->getHitPointsMax()));

  _player_stats_text[2]->setText(
    "Engine: " +
    std::to_string(_player->getHull()->getEngine()->getHitPoints()) +
    "/" +
    std::to_string(_player->getHull()->getEngine()->getHitPointsMax()));

  _enemy_stats_text[2]->setText(
    "Engine: " +
    std::to_string(_enemy->getHull()->getEngine()->getHitPoints()) +
    "/" +
    std::to_string(_enemy->getHull()->getEngine()->getHitPointsMax()));

  _player_stats_text[2]->setPosition(
    _player_stats[2]->getX() + _player_stats[2]->getWidth() / 2,
    _player_stats[2]->getY() + _player_stats[2]->getHeight() / 2);

  _enemy_stats_text[2]->setPosition(
    _enemy_stats[2]->getX() - _enemy_stats[2]->getWidth() / 2, 
    _enemy_stats[2]->getY() + _enemy_stats[2]->getHeight() / 2);
}

//! Draw the window above the battle bar that displays detailed equipment info
void BattleGui::drawEquipmentInfo()
{
  _item_info_bar->setResAnim(resources::battle_ui.getResAnim("equipment_info_bar"));
  _item_info_bar->setPosition(0, -(_item_info_bar->getHeight() + 30));

  _item_info_text->setPosition(5, 5);
}

//! Handles functionality when equipment is clicked on
void BattleGui::useEquipment(Event* ev)
{
  spEquipment eq = safeSpCast<Equipment>(ev->currentTarget);

  if (_battle->isPlayerTurn())
  {
    if (_target)
    {
      if (BattleAction::canPerform(_player, eq, _target))
      {
        _battle->addAction(_action, eq, _target);
        _battle->checkStatus();

        drawGUI();
      }
    }
    else
    {
      log::messageln("No target selected");
    }
  }
  else
  {
    log::messageln("It is not your turn yet");
  }
}

void BattleGui::clickHull(Event* ev)
{
  spHull t = safeSpCast<Hull>(ev->currentTarget);
  _target = t.get();

  //stops event propagation so it doesn't target what's behind it
  ev->stopImmediatePropagation();

  log::messageln("[TARGET ACQUIRED] %s!", t.get()->getID().c_str());
}

void BattleGui::clickBattery(Event* ev)
{
  spBattery b = safeSpCast<Battery>(ev->currentTarget);
  _target = b.get();

  //stops event propagation so it doesn't target what's behind it
  ev->stopImmediatePropagation();

  log::messageln("[TARGET ACQUIRED] %s!", b.get()->getID().c_str());
}

void BattleGui::clickEngine(Event* ev)
{
  spEngine e = safeSpCast<Engine>(ev->currentTarget);
  _target = e.get();

  //stops event propagation so it doesn't target what's behind it
  ev->stopImmediatePropagation();

  log::messageln("[TARGET ACQUIRED] %s!", e.get()->getID().c_str());
}

void BattleGui::detailEquipmentShow(Event* ev)
{
  spEquipment eq = safeSpCast<Equipment>(ev->currentTarget);

  std::string info = "";
    info += "Name: ";
    info += eq->getName().c_str();
    info += " by ";
    info += eq->getBrand().c_str();
    info += "\nDescription: ";
    info += eq->getDescription();
    info += "\nAP Cost: ";
    info += std::to_string(eq->getAPCost());
    info += "\nDamage: ";
    info += std::to_string(eq->getDamage(Damage::Type::Ballistic));
    info += "/";
    info += std::to_string(eq->getDamage(Damage::Type::Electrical));
    info += "/";
    info += std::to_string(eq->getDamage(Damage::Type::Chemical));
    info += "\nResistances: ";
    info += std::to_string(eq->getDamageResistance(Damage::Type::Ballistic));
    info += "/";
    info += std::to_string(eq->getDamageResistance(Damage::Type::Electrical));
    info += "/";
    info += std::to_string(eq->getDamageResistance(Damage::Type::Chemical));

  _item_info_text->setText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 500);
}

void BattleGui::detailHide(Event* ev)
{
  _item_info_bar->addTween(Actor::TweenAlpha(0), 500);
}

void BattleGui::detailEngineShow(Event * ev)
{
  spEngine en = safeSpCast<Engine>(ev->currentTarget);

  std::string info = "";
  info += "Name: ";
  info += en->getName().c_str();
  info += " by ";
  info += en->getBrand().c_str();
  info += "\nDescription: ";
  info += en->getDescription();
  info += "\nResistances: ";
  info += std::to_string(en->getDamageResistance(Damage::Type::Ballistic));
  info += "/";
  info += std::to_string(en->getDamageResistance(Damage::Type::Electrical));
  info += "/";
  info += std::to_string(en->getDamageResistance(Damage::Type::Chemical));

  _item_info_text->setText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 500);
}

void BattleGui::detailBatteryShow(Event * ev)
{
  spBattery bt = safeSpCast<Battery>(ev->currentTarget);

  std::string info = "";
  info += "Name: ";
  info += bt->getName().c_str();
  info += " by ";
  info += bt->getBrand().c_str();
  info += "\nDescription: ";
  info += bt->getDescription();
  info += "\nResistances: ";
  info += std::to_string(bt->getDamageResistance(Damage::Type::Ballistic));
  info += "/";
  info += std::to_string(bt->getDamageResistance(Damage::Type::Electrical));
  info += "/";
  info += std::to_string(bt->getDamageResistance(Damage::Type::Chemical));

  _item_info_text->setText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 500);
}

void BattleGui::detailHullShow(Event * ev)
{
  spHull hl = safeSpCast<Hull>(ev->currentTarget);

  std::string info = "";
  info += "Name: ";
  info += hl->getName().c_str();
  info += " by ";
  info += hl->getBrand().c_str();
  info += "\nDescription: ";
  info += hl->getDescription();
  info += "\nResistances: ";
  info += std::to_string(hl->getDamageResistance(Damage::Type::Ballistic));
  info += "/";
  info += std::to_string(hl->getDamageResistance(Damage::Type::Electrical));
  info += "/";
  info += std::to_string(hl->getDamageResistance(Damage::Type::Chemical));

  _hull_text = info;
  _item_info_text->setText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 500);
}

void BattleGui::detailPartHide(Event* ev)
{
  _item_info_text->setText(_hull_text);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 500);
}

//! Returns color based on remaining hitpoints (from green->yellow->red)
/*!
\param hitpoints float percentage of hitpoints left (1.0f - 0.0f)
*/
Color BattleGui::getHitpointColor(float hitpoints)
{
  if (hitpoints >= 0.5f)
  {
    return Color((1.0f - hitpoints) * 400, 200, 0);
  }
  else if (hitpoints < 0.5f)
  {
    return Color(200, hitpoints * 400, 0);
  }
}
