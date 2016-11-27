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
  /*
  _hull = new Hull();
  _armor = new Armor();
  _engine = new Engine();
  _battery = new Battery();
  _weapon = new Weapon();

  _player_ship->init();

  _battle = new Battle();
  _battle->init();
  */
}

void Game::doUpdate(const UpdateState &us)
{

}