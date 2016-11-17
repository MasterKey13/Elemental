/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "damage.h"
#include "armor.h"

//declare smart pointer
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Equipment : public Item
{
  public:
    Equipment();

    void setDamage(Damage::Type damage_type, int damage_resistance);
    void setDamageDefault();
    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();
    void setDamageAbsorbtion(int absorb);

    void setArmorPiece(spArmor armor);

    int getDamage(Damage::Type damage_type);
    int getDamageResistance(Damage::Type type);
    int getDamageAbsorbtion();

    spArmor getArmorPiece();

  private:
    spArmor _armor_piece;
    int _action_point_cost;
    int _damage[3];
    int _damage_resistance[3];
    int _damage_absorbtion;
};