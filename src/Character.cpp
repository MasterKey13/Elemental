/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "character.h"

Character::Character()
{

}

/*
Initialize a Character
  (string) first name
  (string) last name
  (string) nickname - empty string if no nickname
*/
void Character::init(std::string first_name, 
                     std::string last_name, 
                     std::string nickname)
{
  setFirstName(first_name);
	setLastName(last_name);
	setNickname(nickname);
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

void Character::doUpdate(const UpdateState & us)
{
	//debug the names
	DebugActor::instance->addDebugString("%s, %s: %s\n",
	                    this->_first_name.c_str(), 
                      this->_last_name.c_str(), 
                      this->_nickname.c_str());
}
