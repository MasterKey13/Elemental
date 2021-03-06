/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "game.h"
#include "item.h"

Game::Game()
{
  srand((unsigned int)time(NULL));

  _battle = new Battle();
  _battle->attachTo(getStage());

  _player_ship = new Ship();
  _hull = new Hull();
  _battery = new Battery();
  _engine = new Engine();
  _weapon = new Equipment();
  _player_armor = new Armor();
  _hull->attachTo(_player_ship);
  _engine->attachTo(_hull);
  _battery->attachTo(_hull);
  _weapon->attachTo(_hull);
  _player_armor->attachTo(_hull);

  _eric = new NPC();

  _enemy_ship = new Ship();
  _hull2 = new Hull();
  _battery2 = new Battery();
  _engine2 = new Engine();
  _weapon2 = new Equipment();
  _hull2->attachTo(_enemy_ship);
  _engine2->attachTo(_hull2);
  _battery2->attachTo(_hull2);
  _weapon2->attachTo(_hull2);
}

void Game::init()
{
  //TEST PLAYER SHIP
  _player_ship->init("Player Ship", _hull);
  _engine->init("engine_tracer");
  _battery->init("battery_celladon");
  _weapon->init("equipment_tek_cannon");
  _hull->init("hull_hugh_voyager");
  _player_armor->init("armor_bron");
  _hull->setEngine(_engine);
  _hull->setBattery(_battery);
  _hull->addEquipment(_weapon);
  _player_ship->setShipPosition(POSITION::player);

  //ENEMY
  _eric->init("npc_eric_markovic");

  //TEST ENEMY SHIP
  _enemy_ship->init("Eric's Ship", _hull2);
  _enemy_ship->setPilot(_eric);
  _engine2->init("engine_tracer");
  _battery2->init("battery_celladon");
  _weapon2->init("equipment_tek_cannon");
  _hull2->init("hull_hugh_voyager");
  _hull2->setEngine(_engine2);
  _hull2->setBattery(_battery2);
  _hull2->addEquipment(_weapon2);

  //make gui
  _game_gui = new GameGui();
  _game_gui->init(_player_ship, _enemy_ship);

  //start battle
  _battle->init(_game_gui, _player_ship, _enemy_ship, true);
}

void Game::doUpdate(const UpdateState &us)
{

}