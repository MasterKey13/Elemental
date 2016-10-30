/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "game.h"
#include "armor.h"

Game::Game()
{
  srand((unsigned int)time(NULL));
}

void Game::init()
{
  //create a Player and attach it to the Ship
  _player = new Player();
  _player->init("Heiko", "Evilyn", "", "Human", 5, "none", 4, 10, 2, 6);

	//create new Ship and attach it to the location
	_player_ship = new Ship();

  //create a new Location and attach it
  _location = new Location();
  _location->init(_player_ship->getXPos(), _player_ship->getYPos());
  _location->attachTo(this);

  //create a new Star
  _star = new CelestialBody();
  _star->generateStar();
  _star->attachTo(this);

  //create a new Planet
  _planet = new CelestialBody();
  _planet->generatePlanet(1);
  _planet->attachTo(this);

  //create new Item
  _item = new Item();
  _item->init(99, 1, true, "Spoon", "It's a spoon", "Sp00Nz");
  _item->setCompositionDefault();
  _item->setComposition(4, 12);

  //create new Synthesizer
  _synth = new Synthesizer();
  _synth->setSize(2);
  _synth->setHostShip(_player_ship);
  _synth->decomposeItem(_item);

  //create a new Mine
  _mine = new Mine();
  _mine->initByID(1);

  //create item by ID
  _file_item = new Item();
  _file_item->initByID(1);

  //create weapon by ID
  _weapon = new Weapon();
  _weapon->initByID(1);

  //create armor
  _armor = new Armor();
  _armor->initByID(1);

  //create Ship Engine
  _engine = new Engine();
  _engine->initByID(1);

  //create Ship Battery
  _battery = new Battery();
  _battery->initByID(1);

  //create Ship Hull
  _hull = new Hull();
  _hull->initByID(1);

  //create new Battle
  _battle = new Battle();
  _battle->init(new Ship, new Ship);
}

void Game::doUpdate(const UpdateState &us)
{

}