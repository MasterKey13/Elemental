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
  _hull = new Hull();
  _hull->init("hull_hugh_voyager");
}

void Game::doUpdate(const UpdateState &us)
{

}