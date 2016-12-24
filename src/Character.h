/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Character, spCharacter);

class Character : public Actor
{
  public:
	  Character();

    void init(
      std::string first_name,
      std::string last_name,
      std::string nickname,
      std::string race,
      std::string faction,
      int intelligence,
      int discourse,
      int strength
      );

    void log();

    //SETTERS
	  void setFirstName(std::string first_name);
	  void setLastName(std::string last_name);
	  void setNickname(std::string nickname);
    void setRace(std::string race);
    void setFaction(std::string faction);
    void setIntelligence(int intelligence);
    void setDiscourse(int discourse);
    void setStrength(int strength);
    void setStatus(std::string status);

    //GETTERS
	  std::string getFirstName();
	  std::string getLastName();
	  std::string getNickname();
    std::string getFullName();
    std::string getRace();
    std::string getFaction();
    int getIntelligence();
    int getDiscourse();
    int getStrength();
    std::string getStatus();

    void kill(std::string death);

  private:
	  void doUpdate(const UpdateState &us);

	  std::string _first_name;
	  std::string _last_name;
	  std::string _nickname;

    std::string _status;
    std::string _race;
    std::string _faction;
    int _intelligence;
    int _discourse; //aka "charisma"
    int _strength;
};