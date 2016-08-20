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
  _player->init("Heiko", "Evilyn", "", 10);

	//create new Ship and attach it to the location
	_player_ship = new Ship;
	_player_ship->init("Shogun", 50, 50, 2, 3, 100.0f, 100.0f, _player);
	_player_ship->attachTo(this);

  //create a new Location and attach it
  _location = new Location();
  _location->init(_player_ship->getXPos(), _player_ship->getYPos(), 5);
  _location->attachTo(this);

  _player_ship->travelTo(200, 300);
}

void Game::doUpdate(const UpdateState &us)
{

}