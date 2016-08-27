/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "armor.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Armor, spArmor);

class Battery : public Item
{
  public:
    Battery();

    void init(
      int ID,
      int size,
      int rarity,
      int power,
      int power_cap,
      int hitpoints,
      int hitpoints_cap,
      std::string name = "",
      std::string brand = "",
      std::string model = "");

    void log();
    
    //GETTERS
    int getHitPoints();
    int getHitPointsCap();
    int getPower();
    int getPowerCap();
    spArmor getArmor();

    //SETTERS
    void setHitPoints(int hitpoints);
    void setHitPointsCap(int hitpoints_cap);
    void setPower(int power);
    void setPowerCap(int power_cap);
    void setArmor(spArmor armor);

  private:
    int _hitpoints;
    int _hitpoints_cap;
    int _power;
    int _power_cap;
    spArmor _armor;
};