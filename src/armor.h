/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "damage.h"
#include "target.h"

//declare smart pointer
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Armor : public Item
{
  public:
    Armor();

    void init(
      int hitpoints,
      int ballistic_res, 
      int electrical_res, 
      int chemical_ress
      );

    void init(std::string ID);

    //SETTERS
    void setHitPoints(int hitpoints);
    void setHitPointsMax(int hitpoints_cap);
    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();

    //GETTERS
    int getHitPoints();
    int getHitPointsMax();
    int getDamageResistance(Damage::Type type);

  private:
    int _hitpoints;
    int _hitpoints_max;
    int _damage_resistance[3];
};