/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "character.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(NPC, spNPC);

class NPC : public Character
{
  public:
	  NPC();

	  void init(
      std::string ID,
      int hostility,
      int bravery,
      int brutality);

    void init(std::string ID);

    //SETTERS
    void setID(std::string ID);
    void setHostility(int hostility);
    void setBravery(int bravery);
    void setBrutality(int brutality);

    //GETTERS
    std::string getID();
    int getHostility();
    int getBravery();
    int getBrutality();

  private:
    std::string _ID;
    int _hostility;
    int _bravery;
    int _brutality;
};