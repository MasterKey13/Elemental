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
  _enemy = enemy;

  _battle_bar = new Sprite();
  _battle_bar->attachTo(this);

  _action_points = new ColorRectSprite();
  _action_points->attachTo(_battle_bar);

  _action_points_text = new TextField();
  _action_points_text->attachTo(_battle_bar);

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

    //add event listener to weapon button
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
  log::messageln("Adding event listeners to ships...");

  _player->getHull()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickHull));
  _enemy->getHull()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickHull));

  _player->getHull()->getEngine()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEngine));
   _enemy->getHull()->getEngine()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEngine));

  _player->getHull()->getBattery()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickBattery));
   _enemy->getHull()->getBattery()->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickBattery));
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
    _player_stats[i]->setPosition(x_offset, y_offset);

    _player_stats_text[i]->setAlign(TextStyle::VerticalAlign::VALIGN_MIDDLE, TextStyle::HorizontalAlign::HALIGN_MIDDLE);

    //enemy stats go on the top right corner
    _enemy_stats[i]->setSize(512, 16);
    _enemy_stats[i]->setAnchor(1.0f, 0.0f);
    _enemy_stats[i]->setPosition(
      getStage()->getWidth() - x_offset, 
      y_offset);

    _enemy_stats_text[i]->setAlign(TextStyle::VerticalAlign::VALIGN_MIDDLE, TextStyle::HorizontalAlign::HALIGN_MIDDLE);

    y_offset += _player_stats[i]->getHeight() + 6;
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

void BattleGui::useEquipment(Event* ev)
{
  spEquipment eq = safeSpCast<Equipment>(ev->currentTarget);

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
    log::messageln("No target selected!");
  }
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
