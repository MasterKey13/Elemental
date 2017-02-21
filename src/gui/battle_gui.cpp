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

  _escape_battle_button = new Sprite();
  _escape_battle_button->attachTo(this);

  _escape_battle_ap = new TextField();
  _escape_battle_ap->attachTo(this);

  _pre_escape_battle = new Sprite();
  _pre_escape_battle->attachTo(this);

  _damage_color = Color(255, 175, 175);

  //resize vectors
  _action_slots.resize(_player->getHull()->getBattery()->getActionSlotsMax());

  //set up action slots
  for (int i = 0; i < _player->getHull()->getBattery()->getActionSlotsMax(); i++)
  {
    _action_slots[i] = new Sprite();
    _action_slots[i]->attachTo(_battle_bar);
  }

  addShipEventListeners();
  drawGUI();
}

void BattleGui::drawGUI()
{
  drawActionSlots();
  drawActionPoints();
  drawEscapeBattleButton();
  drawEscapeAPStatus();
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
  for (size_t i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _player->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEquipment));
  }

  for (size_t i = 0; i < _enemy->getHull()->getEquipment().size(); i++)
  {
    _enemy->getHull()->getEquipment()[i]->addEventListener
      (TouchEvent::CLICK, CLOSURE(this, &BattleGui::clickEquipment));
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
      spEquipment eq = safeSpCast<Equipment>(ev->currentTarget);

      if (eq.get() && _equipment)
      {
        if (BattleAction::canPerform(_player, _equipment, eq.get()))
        {
          _battle->addAction(_action, _equipment, eq.get());

          spTween tween = eq.get()->getSprite()->addTween(Sprite::TweenColor(_damage_color), 250, 1, true, Tween::ease_inOutExpo);
          tween->setDoneCallback(CLOSURE(this, &BattleGui::resetColors));
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
    GameGui::cursor->setResAnim(resources::game_ui.getResAnim("cursor_attack"));
    GameGui::cursor->addTween(Actor::TweenScale(0.8f), 1500, 0, true);
    GameGui::cursor->addTween(Actor::TweenRotation(MATH_PI), 6000, 0, false);

    _equipment = safeSpCast<Equipment>(ev->currentTarget);
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
        
        spTween tween = t.get()->getSprite()->addTween(Sprite::TweenColor(_damage_color), 250, 1, true, Tween::ease_inOutExpo);
        tween->setDoneCallback(CLOSURE(this, &BattleGui::resetColors));
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
        
        spTween tween = b.get()->getSprite()->addTween(Sprite::TweenColor(_damage_color), 250, 1, true, Tween::ease_inOutExpo);
        tween->setDoneCallback(CLOSURE(this, &BattleGui::resetColors));
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
        
        spTween tween = e.get()->getSprite()->addTween(Sprite::TweenColor(_damage_color), 250, 1, true, Tween::ease_inOutExpo);
        tween->setDoneCallback(CLOSURE(this, &BattleGui::resetColors));
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
    GameGui::cursor->setResAnim(resources::game_ui.getResAnim("cursor"));
    GameGui::cursor->setRotation(0.0f);
    GameGui::cursor->setScale(1.0f);

    //deselect the equipment
    _equipment->getSprite()->setColor(Color(255, 255, 255));
    _equipment = nullptr;
  }
}

//! Reset all spaceship part colors back to normal after damage tweens
void BattleGui::resetColors(Event* ev)
{
  _player->getHull()->getSprite()->setColor(Color::White);
  _player->getHull()->getEngine()->getSprite()->setColor(Color::White);
  _player->getHull()->getBattery()->getSprite()->setColor(Color::White);

  for (size_t i = 0; i < _player->getHull()->getEquipment().size(); i++)
  {
    _player->getHull()->getEquipment()[i]->getSprite()->setColor(Color::White);
  }

  _enemy->getHull()->getSprite()->setColor(Color::White);
  _enemy->getHull()->getEngine()->getSprite()->setColor(Color::White);
  _enemy->getHull()->getBattery()->getSprite()->setColor(Color::White);

  for (size_t i = 0; i < _enemy->getHull()->getEquipment().size(); i++)
  {
    _enemy->getHull()->getEquipment()[i]->getSprite()->setColor(Color::White);
  }
}
