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

    void init(
      std::string first_name,
      std::string last_name,
      std::string nickname,
      std::string type,
      int inventory_cap,
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
    void setType(std::string type);
    void setInventoryCap(int inventory_cap);
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
    std::string getType();
    int getInventoryCap();
    std::string getFaction();
    int getIntelligence();
    int getDiscourse();
    int getStrength();
    std::string getStatus();

    void kill(std::string death);

  private:
	  void doUpdate(const UpdateState &us);

    //names
	  std::string _first_name;
	  std::string _last_name;
	  std::string _nickname;

    std::string _status; //character's status (alive, dead, injured)
    std::string _type; //type, or race, of character (human, android, etc)
    int _inventory_cap; //inventory capacity
    std::vector<spItem> _inventory; //inventory
    std::string _faction; //character's faction
    int _hostility; //how hostile they are to their enemies
    int _intelligence; //how intelligent they are
    int _discourse; //also known as "charisma"
    int _strength; //physical strength
};