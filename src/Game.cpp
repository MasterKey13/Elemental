/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "game.h"
#include "item.h"

Game::Game()
{
  srand((unsigned int)time(NULL));
}

void Game::init()
{
  //TEST PLAYER SHIP
  _engine = new Engine();
  _engine->init("engine_tracer");

  _battery = new Battery();
  _battery->init("battery_celladon");

  _weapon = new Equipment();
  _weapon->init("equipment_tek_cannon");

  _hull = new Hull();
  _hull->init("hull_hugh_voyager");
  _hull->setEngine(_engine);
  _hull->setBattery(_battery);
  _hull->addEquipment(_weapon);

  _player_ship = new Ship();
  _player_ship->init("Player Ship", _hull);

  //TEST ENEMY SHIP
  _engine2 = new Engine();
  _engine2->init("engine_tracer");

  _battery2 = new Battery();
  _battery2->init("battery_celladon");

  _weapon2 = new Equipment();
  _weapon2->init("equipment_tek_cannon");

  _hull2 = new Hull();
  _hull2->init("hull_hugh_voyager");
  _hull2->setEngine(_engine);
  _hull2->setBattery(_battery);
  _hull2->addEquipment(_weapon2);

  _enemy_ship = new Ship();
  _enemy_ship->init("Enemy Ship", _hull2);

  //start battle
  _battle = new Battle();
  _battle->init(_player_ship, _enemy_ship, true);

}

void Game::doUpdate(const UpdateState &us)
{

}