
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "engine.h"

Engine::Engine()
{

}

int Engine::getEvasion()
{
  return _evasion;
}

spArmor Engine::getArmorPiece()
{
  return _armor_piece;
}

void Engine::setEvasion(int evasion)
{
  _evasion = evasion;
}

void Engine::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}