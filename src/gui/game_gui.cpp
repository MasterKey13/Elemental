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
  _equipment_slots_player.resize(_player->getHull()->getMaxEquip());
  _equipment_stats_player.resize(_player->getHull()->getMaxEquip());
  _equipment_sprites_player.resize(_player->getHull()->getEquipment().size());

  _equipment_bar_player = new Sprite();
  _equipment_bar_player->attachTo(getStage());

  //set up equipment slots
  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equipment_slots_player[i] = new Sprite();
    _equipment_slots_player[i]->attachTo(_equipment_bar_player);
  }

  //attach equipment onto the ships and GUI
  for (size_t i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _equipment_sprites_player[i] = new Sprite();
    _equipment_sprites_player[i]->attachTo(_equipment_slots_player[i]);

    _equipment_stats_player[i] = new ColorRectSprite();
    _equipment_stats_player[i]->attachTo(_equipment_slots_player[i]);
  }

  //set up stat sprites
  for (int i = 0; i < 3; i++)
  {
    _hp_stats_player[i] = new ColorRectSprite();
    _hp_stats_player[i]->attachTo(getStage());

    _armor_stats_player[i] = new ColorRectSprite();
    _armor_stats_player[i]->attachTo(getStage());

    _hp_stats_text_player[i] = new TextField();
    _hp_stats_text_player[i]->attachTo(getStage());
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

  //resize vectors
  _equipment_slots_enemy.resize(_enemy->getHull()->getMaxEquip());
  _equipment_stats_enemy.resize(_enemy->getHull()->getMaxEquip());
  _equipment_sprites_enemy.resize(_enemy->getHull()->getEquipment().size());

  _equipment_bar_enemy = new Sprite();
  _equipment_bar_enemy->attachTo(getStage());

  for (int i = 0; i < _enemy->getHull()->getMaxEquip(); i++)
  {
    _equipment_slots_enemy[i] = new Sprite();
    _equipment_slots_enemy[i]->attachTo(_equipment_bar_enemy);
  }

  for (size_t i = 0; i < _enemy->getHull()->getEquipment().size(); i++)
  {
    _equipment_sprites_enemy[i] = new Sprite();
    _equipment_sprites_enemy[i]->attachTo(_equipment_slots_enemy[i]);

    _equipment_stats_enemy[i] = new ColorRectSprite();
    _equipment_stats_enemy[i]->attachTo(_equipment_slots_enemy[i]);
  }

  //set up stat sprites
  for (int i = 0; i < 3; i++)
  {
    _hp_stats_enemy[i] = new ColorRectSprite();
    _hp_stats_enemy[i]->attachTo(getStage());

    _armor_stats_enemy[i] = new ColorRectSprite();
    _armor_stats_enemy[i]->attachTo(getStage());

    _hp_stats_text_enemy[i] = new TextField();
    _hp_stats_text_enemy[i]->attachTo(getStage());
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
    _hp_stats_player[i]->setSize(_equipment_bar_player->getWidth(), 16);
    _hp_stats_player[i]->setAnchor(0.0f, 0.0f);
    _hp_stats_player[i]->setPosition(_x_margin, y_offset);

    _armor_stats_player[i]->setSize(_hp_stats_player[i]->getWidth(), 16);
    _armor_stats_player[i]->setAnchor(0.0f, 0.0f);
    _armor_stats_player[i]->setPosition(_x_margin, y_offset);
    _armor_stats_player[i]->setColor(_armor_color);

    _hp_stats_text_player[i]->setAlign(
      TextStyle::VerticalAlign::VALIGN_MIDDLE, 
      TextStyle::HorizontalAlign::HALIGN_MIDDLE
      );
    _hp_stats_text_player[i]->setPosition(
      _hp_stats_player[i]->getX() + _hp_stats_player[0]->getWidth() / 2,
      _hp_stats_player[i]->getY() + _hp_stats_player[0]->getHeight() / 2);
  
    y_offset += (int)_hp_stats_player[i]->getHeight() + 6;
  }

  updateHitpointStatsPlayer();
}

void GameGui::drawStatsEnemy()
{
  int y_offset = _y_margin;

  for (int i = 0; i < 3; i++)
  {
    //enemy stats go on the top right corner
    _hp_stats_enemy[i]->setSize(_equipment_bar_enemy->getWidth(), 16);
    _hp_stats_enemy[i]->setAnchor(1.0f, 0.0f);
    _hp_stats_enemy[i]->setPosition(
      getStage()->getWidth() - _x_margin,
      (float)y_offset);

    _armor_stats_enemy[i]->setSize(_hp_stats_enemy[i]->getWidth(), 16);
    _armor_stats_enemy[i]->setAnchor(1.0f, 0.0f);
    _armor_stats_enemy[i]->setPosition(
      getStage()->getWidth() - _x_margin,
      (float)y_offset);
    _armor_stats_enemy[i]->setColor(_armor_color);

    _hp_stats_text_enemy[i]->setAlign(
      TextStyle::VerticalAlign::VALIGN_MIDDLE, 
      TextStyle::HorizontalAlign::HALIGN_MIDDLE
      );  
    _hp_stats_text_enemy[i]->setPosition(
        _hp_stats_enemy[i]->getX() - _hp_stats_enemy[0]->getWidth() / 2,
        _hp_stats_enemy[i]->getY() + _hp_stats_enemy[0]->getHeight() / 2);

    y_offset += (int)_hp_stats_enemy[i]->getHeight() + 6;
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

  //draw the slots themselves
  for (int i = 0; i < _player->getHull()->getMaxEquip(); i++)
  {
    _equipment_slots_player[i]->setResAnim(resources::game_ui.getResAnim("item_slot"));
    _equipment_slots_player[i]->setPosition(
      (float)x_offset, 
      (_equipment_bar_player->getHeight() - _equipment_slots_player[i]->getHeight()) / 2
      );

    x_offset += 4 + (int)_equipment_slots_player[i]->getWidth();
  }

  //draw the equipment inside of the slots
  for (int i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _equipment_sprites_player[i]->setResAnim(
      resources::equipment.getResAnim(_player->getHull()->getEquipment()[i]->getID())
      );
    _equipment_sprites_player[i]->setScale(
      (_equipment_slots_player[i]->getWidth() - 4) / _equipment_sprites_player[i]->getWidth(),
      (_equipment_slots_player[i]->getHeight() - 4) / _equipment_sprites_player[i]->getHeight()
      );
    _equipment_sprites_player[i]->setAnchor(0.5f, 0.5f);
    _equipment_sprites_player[i]->setPosition(_equipment_slots_player[i]->getSize() / 2);
  }
}

void GameGui::drawEquipmentSlotsEnemy()
{
  int x_offset = 4;

  //draw the slots themselves
  for (int i = 0; i < _enemy->getHull()->getMaxEquip(); i++)
  {
    _equipment_slots_enemy[i]->setResAnim(resources::game_ui.getResAnim("item_slot"));
    _equipment_slots_enemy[i]->setPosition(
      (float)x_offset, 
      (_equipment_bar_enemy->getHeight() - _equipment_slots_enemy[i]->getHeight()) / 2
      );

    x_offset += 4 + (int)_equipment_slots_enemy[i]->getWidth();
  }

  //draw the equipment inside of the slots
  for (int i = 0; i < _enemy->getHull()->getEquipment().size(); i++)
  {
    _equipment_sprites_enemy[i]->setResAnim(
      resources::equipment.getResAnim(_enemy->getHull()->getEquipment()[i]->getID())
      );
    _equipment_sprites_enemy[i]->setScale(
      (_equipment_slots_enemy[i]->getWidth() - 4) / _equipment_sprites_enemy[i]->getWidth(),
      (_equipment_slots_enemy[i]->getHeight() - 4) / _equipment_sprites_enemy[i]->getHeight()
      );
    _equipment_sprites_enemy[i]->setAnchor(0.5f,0.5f);
    _equipment_sprites_enemy[i]->setPosition(_equipment_slots_enemy[i]->getSize() / 2);
  }
}

int GameGui::getYMargin()
{
  return _y_margin;
}

spSprite GameGui::getEquipmentBarPlayer()
{
  return _equipment_bar_player;
}

spSprite GameGui::getEquipmentBarEnemy()
{
  return _equipment_bar_enemy;
}

//! Updates the scale and color of hitpoints stats for player
void GameGui::updateHitpointStatsPlayer()
{
  //update hitpoints of hulls
  _hp_stats_player[0]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getHitPoints() /
    (float)_player->getHull()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _hp_stats_player[0]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_player->getHull()->getArmorPiece())
  {
    _armor_stats_player[0]->addTween(Actor::TweenScaleX(
      (float)_player->getHull()->getArmorPiece()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _hp_stats_total_player[0] =
      _player->getHull()->getHitPoints() +
      _player->getHull()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _armor_stats_player[0]->setScaleX(0.0f);
    _hp_stats_total_player[0] = _player->getHull()->getHitPoints();
  }

  _hp_stats_text_player[0]->setText(
    "Hull: " +
    std::to_string(_hp_stats_total_player[0]) +
    "/" +
    std::to_string(_player->getHull()->getHitPointsMax()));

  //update hitpoints of batteries
  _hp_stats_player[1]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getBattery()->getHitPoints() /
    (float)_player->getHull()->getBattery()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _hp_stats_player[1]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getBattery()->getHitPoints() /
      (float)_player->getHull()->getBattery()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_player->getHull()->getBattery()->getArmorPiece())
  {
    _armor_stats_player[1]->addTween(Actor::TweenScaleX(
      (float)_player->getHull()->getBattery()->getArmorPiece()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _hp_stats_total_player[1] =
      _player->getHull()->getBattery()->getHitPoints() +
      _player->getHull()->getBattery()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _armor_stats_player[1]->setScaleX(0.0f);
    _hp_stats_total_player[1] = _player->getHull()->getBattery()->getHitPoints();
  }

  _hp_stats_text_player[1]->setText(
    "Battery: " +
    std::to_string(_hp_stats_total_player[1]) +
    "/" +
    std::to_string(_player->getHull()->getBattery()->getHitPointsMax()));

  //update hitpoints of engines
  _hp_stats_player[2]->addTween(Actor::TweenScaleX(
    (float)_player->getHull()->getEngine()->getHitPoints() /
    (float)_player->getHull()->getEngine()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _hp_stats_player[2]->setColor(
    getHitpointColor(
      (float)_player->getHull()->getEngine()->getHitPoints() /
      (float)_player->getHull()->getEngine()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_player->getHull()->getEngine()->getArmorPiece())
  {
    _armor_stats_player[2]->addTween(Actor::TweenScaleX(
      (float)_player->getHull()->getEngine()->getArmorPiece()->getHitPoints() /
      (float)_player->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _hp_stats_total_player[2] =
      _player->getHull()->getEngine()->getHitPoints() +
      _player->getHull()->getEngine()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _armor_stats_player[2]->setScaleX(0.0f);
    _hp_stats_total_player[2] = _player->getHull()->getEngine()->getHitPoints();;
  }

  _hp_stats_text_player[2]->setText(
    "Engine: " +
    std::to_string(_hp_stats_total_player[2]) +
    "/" +
    std::to_string(_player->getHull()->getEngine()->getHitPointsMax()));
}

//! Updates the scale and color of hitpoints stats for player
void GameGui::updateHitpointStatsEnemy()
{
  //update hitpoints of hulls
  _hp_stats_enemy[0]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getHitPoints() /
    (float)_enemy->getHull()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _hp_stats_enemy[0]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_enemy->getHull()->getArmorPiece())
  {
    _armor_stats_enemy[0]->addTween(Actor::TweenScaleX(
      (float)_enemy->getHull()->getArmorPiece()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _hp_stats_total_enemy[0] =
      _enemy->getHull()->getHitPoints() +
      _enemy->getHull()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _armor_stats_enemy[0]->setScaleX(0.0f);
    _hp_stats_total_enemy[0] = _enemy->getHull()->getHitPoints();
  }

  _hp_stats_text_enemy[0]->setText(
    "Hull: " +
    std::to_string(_hp_stats_total_enemy[0]) +
    "/" +
    std::to_string(_enemy->getHull()->getHitPointsMax()));

  //update hitpoints of batteries
  _hp_stats_enemy[1]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getBattery()->getHitPoints() /
    (float)_enemy->getHull()->getBattery()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _hp_stats_enemy[1]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getBattery()->getHitPoints() /
      (float)_enemy->getHull()->getBattery()->getHitPointsMax()));

  //if they have armor, show the armor hitpoint stats
  if (_enemy->getHull()->getBattery()->getArmorPiece())
  {
    _armor_stats_enemy[1]->addTween(Actor::TweenScaleX(
      (float)_enemy->getHull()->getBattery()->getArmorPiece()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _hp_stats_total_enemy[1] =
      _enemy->getHull()->getBattery()->getHitPoints() +
      _enemy->getHull()->getBattery()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _armor_stats_enemy[1]->setScaleX(0.0f);
    _hp_stats_total_enemy[1] = _enemy->getHull()->getBattery()->getHitPoints();
  }

  _hp_stats_text_enemy[1]->setText(
    "Battery: " +
    std::to_string(_hp_stats_total_enemy[1]) +
    "/" +
    std::to_string(_enemy->getHull()->getBattery()->getHitPointsMax()));

  //update hitpoints of engines
  _hp_stats_enemy[2]->addTween(Actor::TweenScaleX(
    (float)_enemy->getHull()->getEngine()->getHitPoints() /
    (float)_enemy->getHull()->getEngine()->getHitPointsMax()
    ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

  _hp_stats_enemy[2]->setColor(
    getHitpointColor(
      (float)_enemy->getHull()->getEngine()->getHitPoints() /
      (float)_enemy->getHull()->getEngine()->getHitPointsMax()));

  if (_enemy->getHull()->getEngine()->getArmorPiece())
  {
    _armor_stats_enemy[1]->addTween(Actor::TweenScaleX(
      (float)_enemy->getHull()->getEngine()->getArmorPiece()->getHitPoints() /
      (float)_enemy->getHull()->getHitPointsMax()
      ), TweenOptions(500).loops(1).globalEase(Tween::EASE::ease_outBounce));

    _hp_stats_total_enemy[2] =
      _enemy->getHull()->getEngine()->getHitPoints() +
      _enemy->getHull()->getEngine()->getArmorPiece()->getHitPoints();
  }
  else
  {
    _armor_stats_enemy[2]->setScaleX(0.0f);
    _hp_stats_total_enemy[2] = _enemy->getHull()->getEngine()->getHitPoints();
  }

  _hp_stats_text_enemy[2]->setText(
    "Engine: " +
    std::to_string(_hp_stats_total_enemy[2]) +
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