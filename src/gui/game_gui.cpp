/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "game_gui.h"

//custom cursor
spSprite GameGui::cursor = new Sprite();

GameGui::GameGui()
{
  //custom cursor (default)
  SDL_ShowCursor(0);
  GameGui::cursor->attachTo(getStage());
  GameGui::cursor->setAnchor(0.5f, 0.5f);
  GameGui::cursor->setResAnim(resources::game_ui.getResAnim("cursor"));
  GameGui::cursor->setVisible(true);
  GameGui::cursor->setTouchEnabled(false);
  GameGui::cursor->setPriority(32000);
  getStage()->addEventListener(TouchEvent::MOVE, CLOSURE(this, &GameGui::updateCursor));

  _armor_color = Color(100, 100, 130);
}

//! Initialize a game GUI (create all required objects)
/*!
\param player smart pointer to player's ship
*/
void GameGui::init(spShip player)
{
  _player = player;

  //position ship onto screen
  _player->attachTo(getStage());
  _player->setShipPosition(POSITION::player);

  //resize vectors
  _equip_slots_player.resize(_player->getHull()->getMaxEquip());
  _player_equipment_stats.resize(_player->getHull()->getMaxEquip());

  _equipment_bar_player = new Sprite();
  _equipment_bar_player->attachTo(getStage());

  //set up equipment slots
  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots_player[i] = new Sprite();
    _equip_slots_player[i]->attachTo(_equipment_bar_player);
  }

  //attach equipment onto the ships and GUI
  for (size_t i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _player_equipment_stats[i] = new ColorRectSprite();
    _player_equipment_stats[i]->attachTo(_equip_slots_player[i]);
  }

  //set up stat sprites
  for (int i = 0; i < 3; i++)
  {
    _player_hp_stats[i] = new ColorRectSprite();
    _player_hp_stats[i]->attachTo(getStage());

    _player_armor_stats[i] = new ColorRectSprite();
    _player_armor_stats[i]->attachTo(getStage());

    _player_hp_stats_text[i] = new TextField();
    _player_hp_stats_text[i]->attachTo(getStage());
  }

  _x_margin = 8;
  _y_margin = 8;

  drawGUI();
}

//! Initialize a game GUI (create all required objects)
/*!
\param player smart pointer to player's ship
\param enemy smart pointer to enemy's ship
*/
void GameGui::init(spShip player, spShip enemy)
{
  //do the player gui setup first
  init(player);

  _enemy = enemy;

  //position ship onto screen
  _enemy->attachTo(getStage());
  _enemy->setShipPosition(POSITION::enemy);

  _equip_slots_enemy.resize(_enemy->getHull()->getMaxEquip());
  _enemy_equipment_stats.resize(_enemy->getHull()->getMaxEquip());

  _equipment_bar_enemy = new Sprite();
  _equipment_bar_enemy->attachTo(getStage());

  for (int i = 0; i < _enemy->getHull()->getMaxEquip(); i++)
  {
    _equip_slots_enemy[i] = new Sprite();
    _equip_slots_enemy[i]->attachTo(_equipment_bar_enemy);
  }

  for (size_t i = 0; i < _enemy->getHull()->getEquipment().size(); i++)
  {
    _enemy_equipment_stats[i] = new ColorRectSprite();
    _enemy_equipment_stats[i]->attachTo(_equip_slots_enemy[i]);
  }

  //set up stat sprites
  for (int i = 0; i < 3; i++)
  {
    _enemy_hp_stats[i] = new ColorRectSprite();
    _enemy_hp_stats[i]->attachTo(getStage());

    _enemy_armor_stats[i] = new ColorRectSprite();
    _enemy_armor_stats[i]->attachTo(getStage());

    _enemy_hp_stats_text[i] = new TextField();
    _enemy_hp_stats_text[i]->attachTo(getStage());
  }

  drawGUI();
}

void GameGui::drawGUI()
{
  drawStatsPlayer();
  drawEquipmentBarPlayer();
  drawEquipmentSlotsPlayer();

  updateHitpointStatsPlayer();

  if (_enemy)
  {
    drawStatsEnemy();
    drawEquipmentBarEnemy();
    drawEquipmentSlotsEnemy();

    updateHitpointStatsEnemy();
  }
}

//! Draw the hitpoint bars for hull, battery and engine of both player and enemy
void GameGui::drawStatsPlayer()
{
  int y_offset = _y_margin;

  for (int i = 0; i < 3; i++)
  {
    //player stats go on the left top corner
    _player_hp_stats[i]->setSize(_equipment_bar_player->getWidth(), 16);
    _player_hp_stats[i]->setAnchor(0.0f, 0.0f);
    _player_hp_stats[i]->setPosition(_x_margin, y_offset);

    _player_armor_stats[i]->setSize(_player_hp_stats[i]->getWidth(), 16);
    _player_armor_stats[i]->setAnchor(0.0f, 0.0f);
    _player_armor_stats[i]->setPosition(_x_margin, y_offset);
    _player_armor_stats[i]->setColor(_armor_color);

    _player_hp_stats_text[i]->setAlign(
      TextStyle::VerticalAlign::VALIGN_MIDDLE, 
      TextStyle::HorizontalAlign::HALIGN_MIDDLE
      );
    _player_hp_stats_text[i]->setPosition(
      _player_hp_stats[i]->getX() + _player_hp_stats[0]->getWidth() / 2,
      _player_hp_stats[i]->getY() + _player_hp_stats[0]->getHeight() / 2);
  
    y_offset += (int)_player_hp_stats[i]->getHeight() + 6;
  }

  updateHitpointStatsPlayer();
}

void GameGui::drawStatsEnemy()
{
  int y_offset = _y_margin;

  for (int i = 0; i < 3; i++)
  {
    //enemy stats go on the top right corner
    _enemy_hp_stats[i]->setSize(_equipment_bar_enemy->getWidth(), 16);
    _enemy_hp_stats[i]->setAnchor(1.0f, 0.0f);
    _enemy_hp_stats[i]->setPosition(
      getStage()->getWidth() - _x_margin,
      (float)y_offset);

    _enemy_armor_stats[i]->setSize(_enemy_hp_stats[i]->getWidth(), 16);
    _enemy_armor_stats[i]->setAnchor(1.0f, 0.0f);
    _enemy_armor_stats[i]->setPosition(
      getStage()->getWidth() - _x_margin,
      (float)y_offset);
    _enemy_armor_stats[i]->setColor(_armor_color);

    _enemy_hp_stats_text[i]->setAlign(
      TextStyle::VerticalAlign::VALIGN_MIDDLE, 
      TextStyle::HorizontalAlign::HALIGN_MIDDLE
      );  
    _enemy_hp_stats_text[i]->setPosition(
        _enemy_hp_stats[i]->getX() - _enemy_hp_stats[0]->getWidth() / 2,
        _enemy_hp_stats[i]->getY() + _enemy_hp_stats[0]->getHeight() / 2);

    y_offset += (int)_enemy_hp_stats[i]->getHeight() + 6;
  }

  updateHitpointStatsEnemy();
}

void GameGui::drawEquipmentBarPlayer()
{
  _equipment_bar_player->setResAnim(resources::game_ui.getResAnim("equipment_bar"));
  _equipment_bar_player->setPosition(
    _x_margin, 
    getStage()->getHeight() - _equipment_bar_player->getHeight() - _y_margin
    );
}

void GameGui::drawEquipmentBarEnemy()
{
  _equipment_bar_enemy->setResAnim(resources::game_ui.getResAnim("equipment_bar"));
  _equipment_bar_enemy->setPosition(
    getStage()->getWidth() - _equipment_bar_enemy->getWidth() - _x_margin, 
    getStage()->getHeight() - _equipment_bar_enemy->getHeight() - _y_margin
    );
}

void GameGui::drawEquipmentSlotsPlayer()
{
  int x_offset = 4;

  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equip_slots_player[i]->setResAnim(resources::game_ui.getResAnim("item_slot"));
    _equip_slots_player[i]->setPosition((float)x_offset, 
      _equipment_bar_player->getHeight() - _equip_slots_player[i]->getHeight() - 6.0f);

    x_offset += 4 + (int)_equip_slots_player[i]->getWidth();
  }
}

void GameGui::drawEquipmentSlotsEnemy()
{
  int x_offset = 4;

  for (int i = 0; i < _enemy->getHull()->getMaxEquip(); i++)
  {
    _equip_slots_enemy[i]->setResAnim(resources::game_ui.getResAnim("item_slot"));
    _equip_slots_enemy[i]->setPosition((float)x_offset, 
      _equipment_bar_enemy->getHeight() - _equip_slots_enemy[i]->getHeight() - 6.0f);

    x_offset += 4 + (int)_equip_slots_enemy[i]->getWidth();
  }
}

int GameGui::getYMargin()
{
  return _y_margin;
}

//! Updates the scale and color of hitpoints stats for player
void GameGui::updateHitpointStatsPlayer()
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

  _player_hp_stats_text[0]->setText(
    "Hull: " +
    std::to_string(_player_hp_stats_total[0]) +
    "/" +
    std::to_string(_player->getHull()->getHitPointsMax()));

  //update hitpoints of batteries
  _player_hp_stats[1]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getBattery()->getHitPoints() /
    (float)_player->getHull()->getBattery()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _player_hp_stats[1]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getBattery()->getHitPoints() /
      (float)_player->getHull()->getBattery()->getHitPointsMax()));

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

  _player_hp_stats_text[1]->setText(
    "Battery: " +
    std::to_string(_player_hp_stats_total[1]) +
    "/" +
    std::to_string(_player->getHull()->getBattery()->getHitPointsMax()));

  //update hitpoints of engines
  _player_hp_stats[2]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getEngine()->getHitPoints() /
    (float)_player->getHull()->getEngine()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _player_hp_stats[2]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getEngine()->getHitPoints() /
      (float)_player->getHull()->getEngine()->getHitPointsMax()));

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

  _player_hp_stats_text[2]->setText(
    "Engine: " +
    std::to_string(_player_hp_stats_total[2]) +
    "/" +
    std::to_string(_player->getHull()->getEngine()->getHitPointsMax()));
}

//! Updates the scale and color of hitpoints stats for player
void GameGui::updateHitpointStatsEnemy()
{
  //update hitpoints of hulls
  _enemy_hp_stats[0]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getHitPoints() /
    (float)_enemy->getHull()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _enemy_hp_stats[0]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
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

  _enemy_hp_stats_text[0]->setText(
    "Hull: " +
    std::to_string(_enemy_hp_stats_total[0]) +
    "/" +
    std::to_string(_enemy->getHull()->getHitPointsMax()));

  //update hitpoints of batteries
  _enemy_hp_stats[1]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getBattery()->getHitPoints() /
    (float)_enemy->getHull()->getBattery()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _enemy_hp_stats[1]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getBattery()->getHitPoints() /
      (float)_enemy->getHull()->getBattery()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
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

  _enemy_hp_stats_text[1]->setText(
    "Battery: " +
    std::to_string(_enemy_hp_stats_total[1]) +
    "/" +
    std::to_string(_enemy->getHull()->getBattery()->getHitPointsMax()));

  //update hitpoints of engines
  _enemy_hp_stats[2]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getEngine()->getHitPoints() /
    (float)_enemy->getHull()->getEngine()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _enemy_hp_stats[2]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getEngine()->getHitPoints() /
      (float)_enemy->getHull()->getEngine()->getHitPointsMax()));

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

  _enemy_hp_stats_text[2]->setText(
    "Engine: " +
    std::to_string(_enemy_hp_stats_total[2]) +
    "/" +
    std::to_string(_enemy->getHull()->getEngine()->getHitPointsMax()));
}

//! Returns color based on remaining hitpoints (from green->yellow->red)
/*!
\param hitpoints float percentage of hitpoints left (1.0f - 0.0f)
*/
Color GameGui::getHitpointColor(float hitpoints)
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

void GameGui::updateCursor(Event * ev)
{
  TouchEvent* touch = (TouchEvent*)ev;
  cursor->setPosition(touch->localPosition);
}