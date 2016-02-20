#include "Game.h"

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
	_playerShip = new Ship;
	_playerShip->init("Shogun", _space->getX(), _space->getY(), "F4T455");
	_playerShip->attachTo(this);

	//add the ship to the location
	_location->addShip(&_playerShip);

	//create a Player and attach it to the Ship
	_player = new Player;
	_player->init("Heiko", "Evilyn", "");
	_player->attachTo(_playerShip);

	//set the ship's captain
	_playerShip->setCaptain(&_player);

	//create a TravelBar
	_travelBar = new TravelBar;
	_travelBar->init();
	_travelBar->attachTo(this);
}

void Game::doUpdate(const UpdateState &us)
{

}