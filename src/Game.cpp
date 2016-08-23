/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "game.h"

Game::Game()
{

}

void Game::init()
{
  //create a Player and attach it to the Ship
  _player = new Player;
  _player->init("Heiko", "Evilyn", "", "Human", 5, "none", 4, 3, 2);

	//create new Ship and attach it to the location
	_player_ship = new Ship;
	_player_ship->init("Shogun", 50, 50, 1000, 5, 100.0f, 100.0f, 2, _player);
	_player_ship->attachTo(this);

  //create a new Location and attach it
  _location = new Location();
  _location->init(_player_ship->getXPos(), _player_ship->getYPos(), 5);
  _location->attachTo(this);

  //create a new Item
  _item = new Item();
  _item->init(1, "Apple", 1, 1, "Applauza");
  _item->attachTo(this);
}

void Game::doUpdate(const UpdateState &us)
{

}