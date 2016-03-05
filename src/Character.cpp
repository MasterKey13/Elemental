#include "setup.h"
#include "Character.h"

Character::Character()
{

}

void Character::init(std::string firstName, std::string lastName, std::string nickname)
{
	//set the first, last and nickname
	setFirstName(firstName);
	setLastName(lastName);
	setNickname(nickname);
}

void Character::setFirstName(std::string firstName)
{
	_firstName = firstName;
}

void Character::setLastName(std::string lastName)
{
	_lastName = lastName;
}

void Character::setNickname(std::string nickname)
{
	_nickname = nickname;
}

std::string Character::getFirstName()
{
	return _firstName;
}

std::string Character::getLastName()
{
	return _lastName;
}

std::string Character::getNickname()
{
	return _nickname;
}

void Character::doUpdate(const UpdateState & us)
{
	//debug names
	DebugActor::instance->addDebugString("%s, %s: %s\n",
				this->_firstName.c_str(), this->_lastName.c_str(), this->_nickname.c_str());
}
