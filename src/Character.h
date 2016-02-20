#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

#define FIRST_NAME_MAX_CHAR 10
#define LAST_NAME_MAX_CHAR 10
#define NICKNAME_MAX_CHAR 10

//Declare smart pointers
DECLARE_SMART(Character, spCharacter);

class Character : public Actor
{
public:
	Character();

	void init(char *firstName, char *lastName, char *nickname); //with a nickname
	void init(char *firstName, char *lastName); //without a nickname

	void setFirstName(char *firstName); //set first name
	void setLastName(char *lastName); //set last name
	void setNickname(char *nickname); //set nickname

	char *getFirstName(); //get first name
	char *getLastName(); //get last name
	char *getNickname(); //get nickname

private:
	void doUpdate(const UpdateState &us); //update function

	int _credits; //amount of credits
	char *_firstName; //first name
	char *_lastName; //last name
	char *_nickname; //nickname
};