/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "ship.h"

Ship::Ship()
{
  setName("");
  setHull(nullptr);
}

//! Initialize a custom ship with given parameters
/*!
\param name name of the ship
\param hull hull of the ship
*/
void Ship::init(
  std::string name,
  spHull hull
  )
{
  setName(name);
  setHull(hull);
}

void Ship::log()
{
  log::messageln(
    "=============\n"
    "Name: %s\n"
    "Status: %s\n"
    "Hull HP: %d/%d\n"
    "Engine HP: %d/%d\n"
    "Battery HP: %d/%d"
    "\n=============",
    getName().c_str(),
    (isAlive() ? "alive" : "dead"),
    getHull()->getHitPoints(),
    getHull()->getHitPointsMax(),
    getHull()->getEngine()->getHitPoints(),
    getHull()->getEngine()->getHitPointsMax(),
    getHull()->getBattery()->getHitPoints(),
    getHull()->getBattery()->getHitPointsMax()
    );
}

bool Ship::isAlive()
{
  //the ship is considered "alive" as long as the hull is not destroyed and either
  //one of the battery or engine is not destroyed
  if (getHull()->getHitPoints() != 0 &&
    (getHull()->getBattery()->getHitPoints() != 0 ||
     getHull()->getEngine()->getHitPoints() != 0))
  {
    return true;
  }

  return false;
}

void Ship::setName(std::string name)
{
	_name = name;
}

void Ship::setHull(spHull hull)
{
  _hull = hull;
}
void Ship::setShipPosition(POSITION pos)
{
  if (pos == player)
  {
    setPosition(
      getStage()->getWidth() / 6 - _hull->computeBounds().getWidth() / 2, 
      getStage()->getHeight() / 3 + _hull->computeBounds().getHeight() / 2
      );
  }
  else if (pos == enemy)
  {
    setPosition(
      getStage()->getWidth() / 6 * 5, 
      getStage()->getHeight() / 3 + _hull->computeBounds().getHeight()
      );

    setAnchorInPixels(
      _hull->computeBounds().getWidth() / 2, 
      _hull->computeBounds().getHeight() / 2
      );

    setRotation(MATH_PI);
  }
  else
  {
    log::messageln("Invalid ship position requested!");
  }
}

void Ship::setPilot(spCharacter pilot)
{
  _pilot = pilot;
}

//!Find the part inside the ship. Return true if found, false if not found
bool Ship::find(Target* part)
{
  //check if it's either the hull, battery or engine
  if (
    getHull().get() == part ||
    getHull()->getBattery().get() == part ||
    getHull()->getEngine().get() == part
    )
  {
    return true;
  }
  
  //check equipment pieces
  for (size_t i = 0; i < getHull()->getEquipment().size(); i++)
  {
    if (getHull()->getEquipment()[i].get() == part)
    {
      return true;
    }
  }

  return false;
}

//! Process turn for the enemy (basic AI)
/*!
\param battle smart pointer to the battle
\param enemy smart pointer to the player ship
*/
void Ship::processTurn(spBattle battle, spShip player)
{
  log::messageln("PERFORMING ENEMY ACTION...");

  spBattleAction action = new BattleAction();

  battle->addAction(action, getHull()->getEquipment()[0], player->getHull().get());
  battle->checkStatus();
}

void Ship::resetTurnStats()
{
  getHull()->getBattery()->setActionPoints(getHull()->getBattery()->getActionPointsMax());
  getHull()->getBattery()->setActionSlots(getHull()->getBattery()->getActionSlotsMax());
}

std::string Ship::getName()
{
	return _name;
}

spHull Ship::getHull()
{
  return _hull;
}

spCharacter Ship::getPilot()
{
  return _pilot;
}
