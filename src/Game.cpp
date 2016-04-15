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

	//create new Ship and attach it to the location
	_player_ship = new Ship;
	_player_ship->init("Shogun", _space->getX(), _space->getY(), "F4T455");
	_player_ship->attachTo(this);

	//add the ship to the location
	_location->addShip(&_player_ship);

	//create a Player and attach it to the Ship
	_player = new Player;
	_player->init("Heiko", "Evilyn", "");
	_player->attachTo(_player_ship);

	//set the ship's captain
	_player_ship->setCaptain(&_player);

	//create a TravelBar
	_travel_bar = new TravelBar;
	_travel_bar->init();
	_travel_bar->attachTo(this);
}

void Game::doUpdate(const UpdateState &us)
{

}