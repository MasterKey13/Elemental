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
\param race race of character, ie. human, android, etc
\param faction faction to which the character aligns
\param intelligence how intelligent the character is
\param discourse the level of this character's social skills
\param strength physical strength of the character
*/
void Character::init(
  std::string first_name,
  std::string last_name,
  std::string nickname,
  std::string race,
  std::string faction,
  int intelligence,
  int discourse,
  int strength)
{
  //set character names
  setFirstName(first_name);
  setLastName(last_name);
  setNickname(nickname);

  setRace(race);
  setFaction(faction);
  setIntelligence(intelligence);
  setDiscourse(discourse);
  setStrength(strength);
  setStatus("alive");
}

void Character::log()
{
  log::messageln("\n[CHARACTER]\nFirst Name: %s\nLast Name: %s\nNickname: %s\nRace: %s\nInventory Cap: %d\nFaction: %s\nIntelligence: %d\nDiscourse: %d\nStrength: %d\nStatus: %s\n",
    this->getFirstName().c_str(),
    this->getLastName().c_str(),
    this->getNickname().c_str(),
    this->getRace().c_str(),
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

void Character::setRace(std::string race)
{
  _race = race;
}

void Character::setFaction(std::string faction)
{
  _faction = faction;
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

std::string Character::getRace()
{
  return _race;
}

std::string Character::getFaction()
{
  return _faction;
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