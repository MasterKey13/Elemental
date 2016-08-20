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
	//create new Space and attach to stage
	_space = new Space;
	_space->init(50, 50);
	_space->attachTo(this);

	//create a new Location and attach it to the space
	_location = new Location();
	_location->init(_space->getX(), _space->getY(), 5);
	_location->attachTo(this);

  //create a Player and attach it to the Ship
  _player = new Player;
  _player->init("Heiko", "Evilyn", "", 10);

	//create new Ship and attach it to the location
	_player_ship = new Ship;
	_player_ship->init("Shogun", _space->getX(), _space->getY(), 2, 3, 100, 100, _player);
	_player_ship->attachTo(this);

  _player->attachTo(_player_ship);
}

void Game::doUpdate(const UpdateState &us)
{

}