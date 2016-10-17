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

  //create Ship Hull
  _hull = new Hull();
  _hull->init(2, 2, 100, 100, "", "Chronoz", "X32B");

  //create Ship Battery
  _battery = new Battery();
  _battery->init(3, 1, 150, 150, 100, 100, "", "Bate-X", "Vogue");

  //create Ship Engine
  _engine = new Engine();
  _engine->init(4, 3, 100, 100, "", "VRUM", "B-3");

  //create armor
  _armor = new Armor();
  _armor->init(6, "Weak Aluminum Pad", 1, 1, 1, 0, 2, "PADD", "D2");
  _armor->setDamageResistance(Armor::Electrical, 2);

  //create weapon
  _weapon = new Weapon();
  _weapon->init(8, 1, 10, 120, 3, 1, 0, 0, "", "Earth Germany", "MastaBlasta");

	//create new Ship and attach it to the location
	_player_ship = new Ship();
  _player_ship->init("Shogun", 50, 50, 1000, 5, 100.0f, 100.0f, 2, _hull, _battery, _engine, _player);
	_player_ship->attachTo(this);

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
  
  //create a new Mine
  _mine = new Mine();
  _mine->init(3234, "Generic Mine", 50, 1, 1000, 1023, "MineX", "1c");
  _mine->attachTo(this);
  _mine->setHostBody(_planet);
  _planet->addMine(_mine);
  _mine->extract();

  //create new Item
  _item = new Item();
  _item->init(99, "Spoon", 1, "Sp00Nz", "Steel");
  _item->setCompositionDefault();
  _item->setComposition(4, 12);

  //create new Synthesizer
  _synth = new Synthesizer();
  _synth->setSize(2);
  _synth->setHostShip(_player_ship);
  _synth->decomposeItem(_item);
}

void Game::doUpdate(const UpdateState &us)
{

}