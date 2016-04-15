/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Character, spCharacter);

class Character : public Actor
{
  public:
	  Character();

	  void init(std::string first_name, 
              std::string last_name, 
              std::string nickname);

	  void setFirstName(std::string first_name); //set first name
	  void setLastName(std::string last_name); //set last name
	  void setNickname(std::string nickname); //set nickname
	
	  std::string getFirstName(); //get first name
	  std::string getLastName(); //get last name
	  std::string getNickname(); //get nickname

  private:
	  void doUpdate(const UpdateState &us); //update function

	  int _credits; //amount of credits
	  std::string _first_name; //first name
	  std::string _last_name; //last name
	  std::string _nickname; //nickname
};