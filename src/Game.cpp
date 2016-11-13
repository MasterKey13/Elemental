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
  //debugging
  spItem armor = new Item();
  armor->init(4);

  spItem weap = new Item();
  weap->init(3);

  spItem eng = new Item();
  eng->init(5);

  spItem hull = new Item();

  spItem bat = new Item();

  spShip ship = new Ship();
  ship->init("Shipname", 1, 1, 0, 0, 0, 0, 2, hull, bat, eng, nullptr);

  spBattle battle = new Battle();
  battle->init(ship, ship);

  spBattleGui battle_gui = new BattleGui();
}

void Game::doUpdate(const UpdateState &us)
{

}