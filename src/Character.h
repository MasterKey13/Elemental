#pragma once
#include "oxygine-framework.h"
#include <string>
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

	void init(std::string firstName, std::string lastName, std::string nickname = ""); //with a nickname

	void setFirstName(std::string firstName); //set first name
	void setLastName(std::string lastName); //set last name
	void setNickname(std::string nickName); //set nickname
	
	std::string getFirstName(); //get first name
	std::string getLastName(); //get last name
	std::string getNickname(); //get nickname

private:
	void doUpdate(const UpdateState &us); //update function

	int _credits; //amount of credits
	std::string _firstName; //first name
	std::string _lastName; //last name
	std::string _nickname; //nickname
};