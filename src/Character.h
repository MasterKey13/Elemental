/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "item.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Character, spCharacter);

class Character : public Actor
{
  public:
	  Character();

	  void init(std::string first_name, 
              std::string last_name, 
              std::string nickname,
              int inventory_limit);

    //name setters
	  void setFirstName(std::string first_name);
	  void setLastName(std::string last_name);
	  void setNickname(std::string nickname);
	
    //name getters
	  std::string getFirstName();
	  std::string getLastName();
	  std::string getNickname();

  private:
	  void doUpdate(const UpdateState &us);

    //name stuff
	  std::string _first_name;
	  std::string _last_name;
	  std::string _nickname;
};