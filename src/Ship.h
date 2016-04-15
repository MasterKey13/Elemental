/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Ship, spShip);
DECLARE_SMART(Character, spCharacter);

class Ship : public Actor
{
  public:
	  Ship();

	  void init(std::string name, int x, int y, std::string serial);

	  void setName(std::string name); //name setting function
	  void setCoordinates(int x, int y); //sets coordiantes of the ship
	  void setCaptain(spCharacter *captain); //set the ship's captain
	  std::string getSerial(); //retrieve the serial number
	  std::string getName(); //retrieve the name of the ship

  private:
	  void doUpdate(const UpdateState &us);

	  int _x, _y; //coordinates of the ship
	  std::string _name; //name of the ship
	  spCharacter *_captain; //captian of the ship
	  std::string _serial; //ship's serial number
};