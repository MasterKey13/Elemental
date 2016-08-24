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
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Armor, spArmor);

class Hull : public Item
{
  public:
    Hull();

    void init(
      int ID,
      int size,
      int rarity,
      int hitpoints,
      int hitpoints_cap,
      std::string name = "",
      std::string brand = "",
      std::string model = "");

    //GETTERS
    int getHitPoints();
    int getHitPointsCap();
    spArmor getArmor();

    //SETTERS
    void setHitPoints(int hitpoints);
    void setHitPointsCap(int hitpoints_cap);
    void setArmor(spArmor armor);

  private:
    int _hitpoints;
    int _hitpoints_cap;
    spArmor _armor;

};