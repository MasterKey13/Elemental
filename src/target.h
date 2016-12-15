/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "damage.h"
#include "armor.h"

using namespace oxygine;

DECLARE_SMART(Armor, spArmor);

class Target
{
  public:
    Target();

    void init(
      int hitpoints,
      int ballistic_res,
      int electrical_res,
      int chemical_res
      );

    //SETTERS
    void setHitPoints(int hitpoints);
    void setHitPointsMax(int hitpoints_cap);
    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();
    void setArmorPiece(spArmor armor);

    //GETTERS
    int getHitPoints();
    int getHitPointsMax();
    int getDamageResistance(Damage::Type type);
    spArmor getArmorPiece();

    bool hasArmor();

  private:
    int _hitpoints;
    int _hitpoints_max;
    int _damage_resistance[3];
    spArmor _armor_piece;
};