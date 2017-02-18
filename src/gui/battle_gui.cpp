/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "battle_gui.h"

BattleGui::BattleGui(spBattle battle)
{
  _battle = battle;
  _action = new BattleAction();
  _equipment = nullptr;
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
  _action_points->setSize(_battle_bar->getWidth(), 4);

  _action_points_penalty = new ColorRectSprite();
  _action_points_penalty->attachTo(_battle_bar);
  _action_points_penalty->setSize(0, 4);

  _action_points_text = new TextField();
  _action_points_text->attachTo(_battle_bar);

  _item_info_bar = new Sprite();
  _item_info_bar->attachTo(_battle_bar);
  _item_info_bar->setAlpha(0);

  _item_info_text = new TextField();
  _item_info_text->attachTo(_item_info_bar);

  _end_turn_button = new Sprite();
  _end_turn_button->attachTo(_battle_bar);

  _escape_battle_button = new Sprite();
  _escape_battle_button->attachTo(_battle_bar);

  _escape_battle_ap = new TextField();
  _escape_battle_ap->attachTo(_battle_bar);

  _pre_escape_battle = new Sprite();
  _pre_escape_battle->attachTo(_battle_bar);

  _battle_bar_enemy = new Sprite();
  _battle_bar_enemy->attachTo(this);

  _damage_color = Color(255, 175, 175);

  //resize vectors
  _equip_slots.resize(_player->getHull()->getMaxEquip());
  _action_slots.resize(_player->getHull()->getBattery()->getActionSlotsMax());
  _equip_slots_enemy.resize(_enemy->getHull()->getMaxEquip());
  _player_equipment_stats.resize(_player->getHull()->getMaxEquip());
  _enemy_equipment_stats.resize(_enemy->getHull()->getMaxEquip());

  //set up equipment and action slots
  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots[i] = new Sprite();
    _equip_slots[i]->attachTo(_battle_bar);
  }

  for (int i = 0; i < _enemy->getHull()->getMaxEquip(); i++)
  {
    _equip_slots_enemy[i] = new Sprite();
    _equip_slots_enemy[i]->attachTo(_battle_bar_enemy);
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
    _player_equipment_stats[i] = new ColorRectSprite();
    _player_equipment_stats[i]->attachTo(_equip_slots[i]);
  }

  for (size_t i = 0; i < _enemy->getHull()->getEquipment().size(); i++)
  {
    _enemy->getHull()->getEquipment()[i]->attachTo(_equip_slots_enemy[i]);
    _enemy_equipment_stats[i] = new ColorRectSprite();
    _enemy_equipment_stats[i]->attachTo(_equip_slots_enemy[i]);
  }

  //set up stat sprites
  for (int i = 0; i < 3; i++)
  {
    _player_hp_stats[i] = new ColorRectSprite();
    _player_hp_stats[i]->attachTo(this);

    _player_armor_stats[i] = new ColorRectSprite();
    _player_armor_stats[i]->attachTo(this);

    _player_hp_stats_text[i] = new TextField();
    _player_hp_stats_text[i]->attachTo(this);

    _enemy_hp_stats[i] = new ColorRectSprite();
    _enemy_hp_stats[i]->attachTo(this);

    _enemy_armor_stats[i] = new ColorRectSprite();
    _enemy_armor_stats[i]->attachTo(this);

    _enemy_hp_stats_text[i] = new TextField();
    _enemy_hp_stats_text[i]->attachTo(this);
  }

  addShipEventListeners();
  drawGUI();
}

void BattleGui::drawGUI()
{
  drawBattleBar();
  drawBattleBarEnemy();
  drawActionSlots();
  drawEquipmentSlotsPlayer();
  drawEquipmentSlotsEnemy();
  drawEquipmentPlayer();
  drawEquipmentEnemy();
  drawEquipmentInfo();
  drawActionPoints();
  drawStats();
  drawEndTurnButton();
  drawEscapeBattleButton();
  drawEscapeAPStatus();
}

void BattleGui::drawBattleBar()
{
  _battle_bar->setResAnim(resources::battle_ui.getResAnim("battle_bar"));
  _battle_bar->setPosition(getStage()->getWidth() / 2 - _battle_bar->getWidth() / 2, getStage()->getHeight() - _battle_bar->getHeight());
}

void BattleGui::drawBattleBarEnemy()
{
  _battle_bar_enemy->setResAnim(resources::battle_ui.getResAnim("battle_bar_enemy"));
  _battle_bar_enemy->setPosition(getStage()->getWidth() - _battle_bar_enemy->getWidth() - 6, 75);
}

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

void BattleGui::drawEquipmentSlotsPlayer()
{
  int x_offset = 4;

  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots[i]->setResAnim(resources::battle_ui.getResAnim("item_slot"));
    _equip_slots[i]->setPosition((float)x_offset, _battle_bar->getHeight() - _equip_slots[i]->getHeight() - 6.0f);

    x_offset += 4 + (int)_equip_slots[i]->getWidth();
  }
}

void BattleGui::drawEquipmentSlotsEnemy()
{
  int x_offset = 4;

  for (int i = 0; i < _enemy->getHull()->getMaxEquip(); i++)
  {
    _equip_slots_enemy[i]->setResAnim(resources::battle_ui.getResAnim("item_slot"));
    _equip_slots_enemy[i]->setPosition((float)x_offset, _battle_bar_enemy->getHeight() - _equip_slots_enemy[i]->getHeight() - 6.0f);

    x_offset += 4 + (int)_equip_slots_enemy[i]->getWidth();
  }
}

void BattleGui::drawEquipmentPlayer()
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
      (TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEquipment));

    //draw the hitpoint bar below the equipment
    _player_equipment_stats[i]->setPosition(0, _equip_slots[i]->getHeight());
    _player_equipment_stats[i]->addTween(Actor::TweenSize(_equip_slots[i]->getWidth() *
      (float)_player->getHull()->getEquipment()[i]->getHitPoints() /
      (float)_player->getHull()->getEquipment()[i]->getHitPointsMax(), 2
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));
    _player_equipment_stats[i]->setColor(getHitpointColor(
      ((float)_player->getHull()->getEquipment()[i]->getHitPoints() /
       (float)_player->getHull()->getEquipment()[i]->getHitPointsMax()
      )));
  }
}

void BattleGui::drawEquipmentEnemy()
{
  for (size_t i = 0; i < _enemy->getHull()->getEquipment().size(); i++)
  {
    _enemy->getHull()->getEquipment()[i]->setVisible(true);
    _enemy->getHull()->getEquipment()[i]->setPosition(1, 1);
    _enemy->getHull()->getEquipment()[i]->removeAllEventListeners();

    //add roll over event listener for detailed info on equipment
    _enemy->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::OVER, CLOSURE(this, &BattleGui::detailEquipmentShow));

    //add roll over event listener for detailed info on equipment
    _enemy->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::OUT, CLOSURE(this, &BattleGui::detailHide));

    //add click event listener to use equipment
    _enemy->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEquipment));

    //draw the hitpoint bar below the equipment
    _enemy_equipment_stats[i]->setPosition(0, _equip_slots[i]->getHeight());
    _enemy_equipment_stats[i]->addTween(Actor::TweenSize(_equip_slots[i]->getWidth() *
      (float)_enemy->getHull()->getEquipment()[i]->getHitPoints() /
      (float)_enemy->getHull()->getEquipment()[i]->getHitPointsMax(), 2
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));
    _enemy_equipment_stats[i]->setColor(getHitpointColor(
      ((float)_enemy->getHull()->getEquipment()[i]->getHitPoints() /
       (float)_enemy->getHull()->getEquipment()[i]->getHitPointsMax()
        )));
  }
}

void BattleGui::drawActionPoints()
{ 
  float percent = (float)_player->getHull()->getBattery()->getActionPoints() /
    (float)_player->getHull()->getBattery()->getActionPointsMax();

  float percent_penalty = ((
    (float)_player->getHull()->getBattery()->getActionPointsMax() - 
    (float)_player->getHull()->getBattery()->getActionPointsMaxAvailable()) / 
    (float)_player->getHull()->getBattery()->getActionPointsMax());

  //action points bar shows how many action points we have left
  _action_points->setColor(Color::Blue);
  _action_points->setPosition(0, -_action_points->getHeight());
  _action_points->addTween(Actor::TweenSize(
    _battle_bar->getWidth() * percent, 4), 
    TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));
  
  //action point penalty bar shows how many action points are unusable
  _action_points_penalty->setRotation(MATH_PI);
  _action_points_penalty->setColor(Color::Red);
  _action_points_penalty->setPosition(_battle_bar->getWidth(), 0);

  _action_points_penalty->addTween(Actor::TweenSize(
    _battle_bar->getWidth() * percent_penalty,
    _action_points->getHeight()),
    TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

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

//! Draw the hitpoint bars for hull, battery and engine of both player and enemy
void BattleGui::drawStats()
{
  Color armor_color = Color(100, 100, 130);

  int x_offset = 6;
  int y_offset = 6;

  for (int i = 0; i < 3; i++)
  { 
    //player stats go on the left top corner
    _player_hp_stats[i]->setSize(364, 16);
    _player_hp_stats[i]->setAnchor(0.0f, 0.0f);
    _player_hp_stats[i]->setPosition((float)x_offset, (float)y_offset);

    _player_armor_stats[i]->setSize(364, 16);
    _player_armor_stats[i]->setAnchor(0.0f, 0.0f);
    _player_armor_stats[i]->setPosition((float)x_offset, (float)y_offset);
    _player_armor_stats[i]->setColor(armor_color);

    _player_hp_stats_text[i]->setAlign(TextStyle::VerticalAlign::VALIGN_MIDDLE, TextStyle::HorizontalAlign::HALIGN_MIDDLE);

    //enemy stats go on the top right corner
    _enemy_hp_stats[i]->setSize(364, 16);
    _enemy_hp_stats[i]->setAnchor(1.0f, 0.0f);
    _enemy_hp_stats[i]->setPosition(
      getStage()->getWidth() - (float)x_offset, 
      (float)y_offset);

    _enemy_armor_stats[i]->setSize(364, 16);
    _enemy_armor_stats[i]->setAnchor(1.0f, 0.0f);
    _enemy_armor_stats[i]->setPosition(
      getStage()->getWidth() - (float)x_offset,
      (float)y_offset);
    _enemy_armor_stats[i]->setColor(armor_color);

    _enemy_hp_stats_text[i]->setAlign(TextStyle::VerticalAlign::VALIGN_MIDDLE, TextStyle::HorizontalAlign::HALIGN_MIDDLE);

    y_offset += (int)_player_hp_stats[i]->getHeight() + 6;
  }

  updateHitpointStats();
}

//! Updates the scale and color of hitpoints stats
void BattleGui::updateHitpointStats()
{
  //update hitpoints of hulls
  _player_hp_stats[0]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getHitPoints() /
    (float)_player->getHull()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _player_hp_stats[0]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()));

  _enemy_hp_stats[0]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getHitPoints() /
    (float)_enemy->getHull()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _enemy_hp_stats[0]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_player->getHull()->getArmorPiece())
  {
    _player_armor_stats[0]->addTween(Actor::TweenScaleX(
      (float)_player->getHull()->getArmorPiece()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _player_hp_stats_total[0] = 
      _player->getHull()->getHitPoints() + 
      _player->getHull()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _player_armor_stats[0]->setScaleX(0.0f);
    _player_hp_stats_total[0] = _player->getHull()->getHitPoints();
  }

  if (_enemy->getHull()->getArmorPiece())
  {
    _enemy_armor_stats[0]->addTween(Actor::TweenScaleX(
      (float)_enemy->getHull()->getArmorPiece()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _enemy_hp_stats_total[0] =
      _enemy->getHull()->getHitPoints() +
      _enemy->getHull()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _enemy_armor_stats[0]->setScaleX(0.0f);
    _enemy_hp_stats_total[0] = _enemy->getHull()->getHitPoints();
  }

  _player_hp_stats_text[0]->setPosition(
    _player_hp_stats[0]->getX() + _player_hp_stats[0]->getWidth() / 2,
    _player_hp_stats[0]->getY() + _player_hp_stats[0]->getHeight() / 2);

  _enemy_hp_stats_text[0]->setPosition(
    _enemy_hp_stats[0]->getX() - _enemy_hp_stats[0]->getWidth() / 2,
    _enemy_hp_stats[0]->getY() + _enemy_hp_stats[0]->getHeight() / 2);

  _player_hp_stats_text[0]->setText(
    "Hull: " +
    std::to_string(_player_hp_stats_total[0]) +
    "/" +
    std::to_string(_player->getHull()->getHitPointsMax()));

  _enemy_hp_stats_text[0]->setText(
    "Hull: " +
    std::to_string(_enemy_hp_stats_total[0]) +
    "/" +
    std::to_string(_enemy->getHull()->getHitPointsMax()));

  //update hitpoints of batteries
  _player_hp_stats[1]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getBattery()->getHitPoints() /
    (float)_player->getHull()->getBattery()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _enemy_hp_stats[1]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getBattery()->getHitPoints() /
    (float)_enemy->getHull()->getBattery()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _player_hp_stats[1]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getBattery()->getHitPoints() /
      (float)_player->getHull()->getBattery()->getHitPointsMax()));

  _enemy_hp_stats[1]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getBattery()->getHitPoints() /
      (float)_enemy->getHull()->getBattery()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_player->getHull()->getBattery()->getArmorPiece())
  {
    _player_armor_stats[1]->addTween(Actor::TweenScaleX(
      (float)_player->getHull()->getBattery()->getArmorPiece()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _player_hp_stats_total[1] =
      _player->getHull()->getBattery()->getHitPoints() +
      _player->getHull()->getBattery()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _player_armor_stats[1]->setScaleX(0.0f);
    _player_hp_stats_total[1] = _player->getHull()->getBattery()->getHitPoints();
  }

  if (_enemy->getHull()->getBattery()->getArmorPiece())
  {
    _enemy_armor_stats[1]->addTween(Actor::TweenScaleX(
      (float)_enemy->getHull()->getBattery()->getArmorPiece()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _enemy_hp_stats_total[1] =
      _enemy->getHull()->getBattery()->getHitPoints() +
      _enemy->getHull()->getBattery()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _enemy_armor_stats[1]->setScaleX(0.0f);
    _enemy_hp_stats_total[1] = _enemy->getHull()->getBattery()->getHitPoints();
  }

  _player_hp_stats_text[1]->setPosition(
    _player_hp_stats[1]->getX() + _player_hp_stats[1]->getWidth() / 2,
    _player_hp_stats[1]->getY() + _player_hp_stats[1]->getHeight() / 2);

  _enemy_hp_stats_text[1]->setPosition(
    _enemy_hp_stats[1]->getX() - _enemy_hp_stats[1]->getWidth() / 2, 
    _enemy_hp_stats[1]->getY() + _enemy_hp_stats[1]->getHeight() / 2);

  _player_hp_stats_text[1]->setText(
    "Battery: " +
    std::to_string(_player_hp_stats_total[1]) +
    "/" +
    std::to_string(_player->getHull()->getBattery()->getHitPointsMax()));

  _enemy_hp_stats_text[1]->setText(
    "Battery: " +
    std::to_string(_enemy_hp_stats_total[1]) +
    "/" +
    std::to_string(_enemy->getHull()->getBattery()->getHitPointsMax()));

  //update hitpoints of engines
  _player_hp_stats[2]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getEngine()->getHitPoints() /
    (float)_player->getHull()->getEngine()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _enemy_hp_stats[2]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getEngine()->getHitPoints() /
    (float)_enemy->getHull()->getEngine()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _player_hp_stats[2]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getEngine()->getHitPoints() /
      (float)_player->getHull()->getEngine()->getHitPointsMax()));

  _enemy_hp_stats[2]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getEngine()->getHitPoints() /
      (float)_enemy->getHull()->getEngine()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_player->getHull()->getEngine()->getArmorPiece())
  {
    _player_armor_stats[2]->addTween(Actor::TweenScaleX(
      (float)_player->getHull()->getEngine()->getArmorPiece()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _player_hp_stats_total[2] =
      _player->getHull()->getEngine()->getHitPoints() +
      _player->getHull()->getEngine()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _player_armor_stats[2]->setScaleX(0.0f);
    _player_hp_stats_total[2] = _player->getHull()->getEngine()->getHitPoints();;
  }

  if (_enemy->getHull()->getEngine()->getArmorPiece())
  {
    _enemy_armor_stats[1]->addTween(Actor::TweenScaleX(
      (float)_enemy->getHull()->getEngine()->getArmorPiece()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _enemy_hp_stats_total[2] =
      _enemy->getHull()->getEngine()->getHitPoints() +
      _enemy->getHull()->getEngine()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _enemy_armor_stats[2]->setScaleX(0.0f);
    _enemy_hp_stats_total[2] = _enemy->getHull()->getEngine()->getHitPoints();
  }

  _player_hp_stats_text[2]->setPosition(
    _player_hp_stats[2]->getX() + _player_hp_stats[2]->getWidth() / 2,
    _player_hp_stats[2]->getY() + _player_hp_stats[2]->getHeight() / 2);

  _enemy_hp_stats_text[2]->setPosition(
    _enemy_hp_stats[2]->getX() - _enemy_hp_stats[2]->getWidth() / 2, 
    _enemy_hp_stats[2]->getY() + _enemy_hp_stats[2]->getHeight() / 2);

  _player_hp_stats_text[2]->setText(
    "Engine: " +
    std::to_string(_player_hp_stats_total[2]) +
    "/" +
    std::to_string(_player->getHull()->getEngine()->getHitPointsMax()));

  _enemy_hp_stats_text[2]->setText(
    "Engine: " +
    std::to_string(_enemy_hp_stats_total[2]) +
    "/" +
    std::to_string(_enemy->getHull()->getEngine()->getHitPointsMax()));
}

//! Draw the window above the battle bar that displays detailed equipment info
void BattleGui::drawEquipmentInfo()
{
  _item_info_bar->setResAnim(resources::battle_ui.getResAnim("equipment_info_bar"));
  _item_info_bar->setPosition(0, -(_item_info_bar->getHeight() + 30));

  _item_info_text->setPosition(5, 5);
}

void BattleGui::drawEndTurnButton()
{
  _end_turn_button->setResAnim(resources::battle_ui.getResAnim("end_turn"));
  _end_turn_button->setPosition(_battle_bar->getWidth(), 0);
  _end_turn_button->removeAllEventListeners();
  _end_turn_button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::endTurn));

  if (_battle->isPlayerTurn())
  {
    _end_turn_button->setVisible(true);
  }
  else
  {
    _end_turn_button->setVisible(false);
  }
}

void BattleGui::drawEscapeBattleButton()
{
  _escape_battle_button->setResAnim(resources::battle_ui.getResAnim("escape_battle"));
  _escape_battle_button->setPosition(-(_escape_battle_button->getWidth()), 0);

  _escape_battle_button->setVisible(false);
  _escape_battle_ap->setVisible(true);
  _pre_escape_battle->setVisible(true);

  //if the player has enough Action Points saved up to escape, draw the button
  if (_player->getHull()->getEngine()->getAPEscapePool() >=
    _player->getHull()->getEngine()->getAPThreshold() + 
    (float)_player->getHull()->getEngine()->getHitPointsMax() -
    (float)_player->getHull()->getEngine()->getHitPoints())
  {
    _escape_battle_button->removeAllEventListeners();
    _escape_battle_button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &BattleGui::escapeBattle));
    
    _escape_battle_button->setVisible(true);
    _escape_battle_ap->setVisible(false);
    _pre_escape_battle->setVisible(false);
  }
}

void BattleGui::drawEscapeAPStatus()
{
  //draw the outline of the percentage place
  _pre_escape_battle->setResAnim(resources::battle_ui.getResAnim("pre_escape_battle"));
  _pre_escape_battle->setPosition(_escape_battle_button->getPosition());

  //build percentage string
  std::string ap = "";
              ap += std::to_string(_player->getHull()->getEngine()->getAPEscapePool());
              ap += "/";
              ap += std::to_string(_player->getHull()->getEngine()->getAPThreshold() +
                _player->getHull()->getEngine()->getHitPointsMax() -
                _player->getHull()->getEngine()->getHitPoints());
              ap += "<br/><br/>";
              ap += std::to_string((int)((float)_player->getHull()->getEngine()->getAPEscapePool() / 
                    ((float)_player->getHull()->getEngine()->getAPThreshold() + 
                    (float)_player->getHull()->getEngine()->getHitPointsMax() -
                    (float)_player->getHull()->getEngine()->getHitPoints()) * 100));
              ap += "%";

  //position the status on the screen
  _escape_battle_ap->setHtmlText(ap);
  _escape_battle_ap->setHAlign(TextStyle::HALIGN_MIDDLE);
  _escape_battle_ap->setVAlign(TextStyle::VALIGN_MIDDLE);
  _escape_battle_ap->setPosition(-(_escape_battle_button->getWidth()) / 2, _escape_battle_button->getHeight() / 2);
}

//! Handles functionality when equipment is clicked on
void BattleGui::clickEquipment(Event* ev)
{
  //clear the equipment if it's double clicked
  if (_equipment == safeSpCast<Equipment>(ev->currentTarget))
  {
    deselectEquipment();
  }
  else if (_equipment)
  {
    if (_battle->isPlayerTurn())
    {
      if (safeSpCast<Equipment>(ev->currentTarget).get() && _equipment)
      {
        if (BattleAction::canPerform(_player, _equipment, safeSpCast<Equipment>(ev->currentTarget).get()))
        {
          _battle->addAction(_action, _equipment, safeSpCast<Equipment>(ev->currentTarget).get());
          _equipment->getSprite()->addTween(Sprite::TweenColor(_damage_color), 350, 1, true, Tween::ease_inOutExpo);
        }
        else
        {
          log::messageln("That action cannot be performed!");
        }
      }
      else
      {
        log::messageln("Target/equipment pointer not found!");
      }
    }
    else
    {
      log::messageln("It is not the player's turn!");
    }

    //stops event propagation so it doesn't target what's behind it
    ev->stopImmediatePropagation();
  }
  else if (!_equipment && isPlayerEquipment(safeSpCast<Equipment>(ev->currentTarget)))
  {
    //make the cursor look like its targeting something
    Game::cursor->setResAnim(resources::game_ui.getResAnim("cursor_attack"));
    Game::cursor->addTween(Actor::TweenScale(0.8f), 1500, 0, true);
    Game::cursor->addTween(Actor::TweenRotation(MATH_PI), 6000, 0, false);

    _equipment = safeSpCast<Equipment>(ev->currentTarget);
    _equipment->getSprite()->setColor(Color(0,25,0));
  }
}

void BattleGui::clickHull(Event* ev)
{
  spHull t = safeSpCast<Hull>(ev->currentTarget);

  if (_battle->isPlayerTurn())
  {
    if (t.get() && _equipment)
    {
      if (BattleAction::canPerform(_player, _equipment, t.get()))
      {
        _battle->addAction(_action, _equipment, t.get());
        t->getSprite()->addTween(Sprite::TweenColor(_damage_color), 350, 1, true, Tween::ease_inOutExpo);
      }
      else
      {
        log::messageln("That action cannot be performed!");
      }
    }
    else
    {
      log::messageln("Target/equipment pointer not found!");
    }
  }
  else
  {
    log::messageln("It is not the player's turn!");
  }

  //stops event propagation so it doesn't target what's behind it
  ev->stopImmediatePropagation();
}

void BattleGui::clickBattery(Event* ev)
{
  spBattery b = safeSpCast<Battery>(ev->currentTarget);

  if (_battle->isPlayerTurn())
  {
    if (b.get() && _equipment)
    {
      if (BattleAction::canPerform(_player, _equipment, b.get()))
      {
        _battle->addAction(_action, _equipment, b.get());
        b->getSprite()->addTween(Sprite::TweenColor(_damage_color), 350, 1, true, Tween::ease_inOutExpo);
      }
      else
      {
        log::messageln("That action cannot be performed!");
      }
    }
    else
    {
      log::messageln("Target/equipment pointer not found!");
    }
  }
  else
  {
    log::messageln("It is not the player's turn!");
  }

  //stops event propagation so it doesn't target what's behind it
  ev->stopImmediatePropagation();
}

void BattleGui::clickEngine(Event* ev)
{
  spEngine e = safeSpCast<Engine>(ev->currentTarget);

  if (_battle->isPlayerTurn())
  {
    if (e.get() && _equipment)
    {
      if (BattleAction::canPerform(_player, _equipment, e.get()))
      {
        _battle->addAction(_action, _equipment, e.get());
        e->getSprite()->addTween(Sprite::TweenColor(_damage_color), 350, 1, true, Tween::ease_inOutExpo);
      }
      else
      {
        log::messageln("That action cannot be performed!");
      }
    }
    else
    {
      log::messageln("Target/equipment pointer not found!");
    }
  }
  else
  {
    log::messageln("It is not the player's turn!");
  }

  //stops event propagation so it doesn't target what's behind it
  ev->stopImmediatePropagation();
}

void BattleGui::detailEquipmentShow(Event* ev)
{
  spEquipment eq = safeSpCast<Equipment>(ev->currentTarget);
  TextStyle style;
  style.multiline = true;
  style.linesOffset = 2;
   
  std::string info = "";
    info += "<div c='00ff00'>Name:</div> ";
    info += eq->getName().c_str();
    info += " by ";
    info += eq->getBrand().c_str();
    info += "<br/><div c='00ff00'>Description:</div> ";
    info += eq->getDescription();
    info += "<br/><div c='00ff00'>AP Cost:</div> ";
    info += std::to_string(eq->getAPCost());
    info += "<br/><div c='00ff00'>Damage:</div> ";
    info += std::to_string(eq->getDamage(Damage::Type::Ballistic));
    info += "/";
    info += std::to_string(eq->getDamage(Damage::Type::Electrical));
    info += "/";
    info += std::to_string(eq->getDamage(Damage::Type::Chemical));
    info += "<br/><div c='00ff00'>Resistances:</div> ";
    info += std::to_string(eq->getDamageResistance(Damage::Type::Ballistic));
    info += "/";
    info += std::to_string(eq->getDamageResistance(Damage::Type::Electrical));
    info += "/";
    info += std::to_string(eq->getDamageResistance(Damage::Type::Chemical));

  _item_info_text->setStyle(style);
  _item_info_text->setSize(_item_info_bar->getWidth() - 6, _item_info_bar->getHeight() - 5);
  _item_info_text->setHtmlText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 100);
}

void BattleGui::detailHide(Event* ev)
{
  _item_info_bar->addTween(Actor::TweenAlpha(0), 100);
}

void BattleGui::detailEngineShow(Event * ev)
{
  spEngine en = safeSpCast<Engine>(ev->currentTarget);
  TextStyle style;
  style.multiline = true;
  style.linesOffset = 2;

  std::string info = "";
  info += "<div c='00ff00'>Name:</div> ";
  info += en->getName().c_str();
  info += " by ";
  info += en->getBrand().c_str();
  info += "<br/><div c='00ff00'>Description:</div> ";
  info += en->getDescription();
  info += "<br/><div c='00ff00'>Resistances:</div> ";
  info += std::to_string(en->getDamageResistance(Damage::Type::Ballistic));
  info += "/";
  info += std::to_string(en->getDamageResistance(Damage::Type::Electrical));
  info += "/";
  info += std::to_string(en->getDamageResistance(Damage::Type::Chemical));

  _item_info_text->setStyle(style);
  _item_info_text->setSize(_item_info_bar->getWidth() - 6, _item_info_bar->getHeight() - 5);
  _item_info_text->setHtmlText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 100);
}

void BattleGui::detailBatteryShow(Event * ev)
{
  spBattery bt = safeSpCast<Battery>(ev->currentTarget);
  TextStyle style;
  style.multiline = true;
  style.linesOffset = 2;

  std::string info = "";
  info += "<div c='00ff00'>Name:</div> ";
  info += bt->getName().c_str();
  info += " by ";
  info += bt->getBrand().c_str();
  info += "<br/><div c='00ff00'>Description:</div> ";
  info += bt->getDescription();
  info += "<br/><div c='00ff00'>Resistances:</div> ";
  info += std::to_string(bt->getDamageResistance(Damage::Type::Ballistic));
  info += "/";
  info += std::to_string(bt->getDamageResistance(Damage::Type::Electrical));
  info += "/";
  info += std::to_string(bt->getDamageResistance(Damage::Type::Chemical));

  _item_info_text->setStyle(style);
  _item_info_text->setSize(_item_info_bar->getWidth() - 6, _item_info_bar->getHeight() - 5);
  _item_info_text->setHtmlText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 100);
}

void BattleGui::detailHullShow(Event * ev)
{
  spHull hl = safeSpCast<Hull>(ev->currentTarget);
  TextStyle style;
  style.multiline = true;
  style.linesOffset = 2;

  std::string info = "";
  info += "<div c='00ff00'>Name:</div> ";
  info += hl->getName().c_str();
  info += " by ";
  info += hl->getBrand().c_str();
  info += "<br/><div c='00ff00'>Description:</div> ";
  info += hl->getDescription();
  info += "<br/><div c='00ff00'>Resistances:</div> ";
  info += std::to_string(hl->getDamageResistance(Damage::Type::Ballistic));
  info += "/";
  info += std::to_string(hl->getDamageResistance(Damage::Type::Electrical));
  info += "/";
  info += std::to_string(hl->getDamageResistance(Damage::Type::Chemical));

  _hull_text = info;

  _item_info_text->setStyle(style);
  _item_info_text->setSize(_item_info_bar->getWidth() - 6, _item_info_bar->getHeight() - 5);
  _item_info_text->setHtmlText(info);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 100);
}

void BattleGui::detailPartHide(Event* ev)
{
  _item_info_text->setHtmlText(_hull_text);

  _item_info_bar->addTween(Actor::TweenAlpha(255), 100);
}

void BattleGui::endTurn(Event * ev)
{
  deselectEquipment();

  _battle->endTurn();
  _battle->requestEnemyTurn();
}

void BattleGui::escapeBattle(Event * ev)
{
  _battle->setBattleFinished(true);
  _battle->finishBattle();

  log::messageln("ESCAPED FROM BATTLE!");
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

//! Returns true if the equipment eq is owned by player, false otherwise
bool BattleGui::isPlayerEquipment(spEquipment eq)
{
  for (int i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    log::messageln("Comparing ");
    if (_player->getHull()->getEquipment()[i] == eq)
    {
      return true;
    }
  }

  log::messageln("Cannot select non-player equipment for use.");
  return false;
}

void BattleGui::deselectEquipment()
{
  if (_equipment)
  {
    //reset cursor back to normal
    Game::cursor->setResAnim(resources::game_ui.getResAnim("cursor"));
    Game::cursor->setRotation(0.0f);
    Game::cursor->setScale(1.0f);

    //deselect the equipment
    _equipment->getSprite()->setColor(Color(255, 255, 255));
    _equipment = nullptr;
  }
}
