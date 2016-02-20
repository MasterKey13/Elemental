#include "setup.h"
#include "Character.h"

Character::Character()
{

}

void Character::init(char *firstName, char *lastName, char *nickname)
{
	//initialize the names
	_firstName = new char[FIRST_NAME_MAX_CHAR];
	_lastName = new char[LAST_NAME_MAX_CHAR];
	_nickname = new char[NICKNAME_MAX_CHAR];

	//set the name of the character (first, last and nickname)
	setFirstName(firstName);
	setLastName(lastName);
	setNickname(nickname);
}

void Character::init(char *firstName, char *lastName)
{
	//set the name of the character (first and last, nickname is blank)
	setFirstName(firstName);
	setLastName(lastName);
	setNickname("");
}

void Character::setFirstName(char *firstName)
{
	//set the first name, cut off at 10 characters
	strncpy(_firstName, firstName, FIRST_NAME_MAX_CHAR);
	_firstName[FIRST_NAME_MAX_CHAR - 1] = '\0';
}

void Character::setLastName(char *lastName)
{
	//set the last name, cut off at 10 characters
	strncpy(_lastName, lastName, LAST_NAME_MAX_CHAR);
	_lastName[LAST_NAME_MAX_CHAR - 1] = '\0';
}

void Character::setNickname(char *nickname)
{
	//set the ship name, cut off at 10 characters
	strncpy(_nickname, nickname, NICKNAME_MAX_CHAR);
	_nickname[NICKNAME_MAX_CHAR - 1] = '\0';
}

char *Character::getFirstName()
{
	return _firstName;
}

char *Character::getLastName()
{
	return _lastName;
}

char *Character::getNickname()
{
	return _nickname;
}

void Character::doUpdate(const UpdateState & us)
{
	//debug names
	DebugActor::instance->addDebugString("%s, %s: %s\n",
				this->_firstName, this->_lastName, this->_nickname);
}
