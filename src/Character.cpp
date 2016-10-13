/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "character.h"

Character::Character()
{

}

//! Initializes a custom Character with given parameterss
/*!
\param first_name first name of the character
\param last_name last name of the character
\param nickname nickname of the character, optional
\param type race of character, ie. human, android, etc
\param inventory_cap maximum inventory capacity
\param faction faction to which the character aligns
\param hostility how hostile this character is to other characters
\param intelligence how intelligent the character is
\param discourse the level of this character's social skills
\param strength physical strength of the character
*/
void Character::init(
  std::string first_name,
  std::string last_name,
  std::string nickname,
  std::string type,
  int inventory_cap,
  std::string faction,
  int hostility,
  int intelligence,
  int discourse,
  int strength)
{
  //set character names
  setFirstName(first_name);
  setLastName(last_name);
  setNickname(nickname);

  setType(type);
  setInventoryCap(inventory_cap);
  setFaction(faction);
  setHostility(hostility);
  setIntelligence(intelligence);
  setDiscourse(discourse);
  setStrength(strength);
  setStatus("alive");

}

void Character::log()
{
  log::messageln("\n[CHARACTER]\nFirst Name: %s\nLast Name: %s\nNickname: %s\nType: %s\nInventory Cap: %d\nFaction: %s\nIntelligence: %d\nDiscourse: %d\nStrength: %d\nStatus: %s\n",
    this->getFirstName().c_str(),
    this->getLastName().c_str(),
    this->getNickname().c_str(),
    this->getType().c_str(),
    this->getInventoryCap(),
    this->getFaction().c_str(),
    this->getIntelligence(),
    this->getDiscourse(),
    this->getStrength(),
    this->getStatus().c_str());
}

void Character::setFirstName(std::string first_name)
{
	_first_name = first_name;
}

void Character::setLastName(std::string last_name)
{
	_last_name = last_name;
}

void Character::setNickname(std::string nickname)
{
	_nickname = nickname;
}

void Character::setType(std::string type)
{
  _type = type;
}

void Character::setInventoryCap(int inventory_cap)
{
  _inventory_cap = inventory_cap;
}

void Character::setFaction(std::string faction)
{
  _faction = faction;
}

void Character::setHostility(int hostility)
{
  _hostility = hostility;
}

void Character::setIntelligence(int intelligence)
{
  _intelligence = intelligence;
}

void Character::setDiscourse(int discourse)
{
  _discourse = discourse;
}

void Character::setStrength(int strength)
{
  _strength = strength;
}

//! Set the status of the character
/*!
\param status status of the character ("alive", "deceased", "injured", etc)
*/
void Character::setStatus(std::string status)
{
  _status = status;
}

std::string Character::getFirstName()
{
	return _first_name;
}

std::string Character::getLastName()
{
	return _last_name;
}

std::string Character::getNickname()
{
	return _nickname;
}

std::string Character::getFullName()
{
  return getFirstName() + ' ' + getLastName();
}

std::string Character::getType()
{
  return _type;
}

int Character::getInventoryCap()
{
  return _inventory_cap;
}

std::string Character::getFaction()
{
  return _faction;
}

int Character::getHostility()
{
  return _hostility;
}

int Character::getIntelligence()
{
  return _intelligence;
}

int Character::getDiscourse()
{
  return _discourse;
}

int Character::getStrength()
{
  return _strength;
}

//! Get the health status of the character

std::string Character::getStatus()
{
  return _status;
}

//! Kills the character using specified death type and log it
/*!
\param death type of death ("drowning", "assassination", "natural causes", etc.)
*/
void Character::kill(std::string death)
{
  _status = "dead by " + death;

  log::messageln("\n%s %s is now %s\n", 
    this->getFirstName().c_str(),
    this->getLastName().c_str(),
    this->getStatus().c_str());
}

void Character::doUpdate(const UpdateState & us)
{

}