/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "damage.h"
#include "armor.h"
#include "damageable.h"

//declare smart pointer
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Equipment : public Item, public Damageable
{
  public:
    Equipment();

    void init(
      int ballistic_res, 
      int electrical_res, 
      int chemical_res,
      int ballistic_dmg, 
      int electrical_dmg, 
      int chemical_dmg, 
      int action_point_cost
      );

    void init(std::string ID);

    //SETTERS
    void setArmorPiece(spArmor armor);
    void setDamage(Damage::Type damage_type, int damage_resistance);
    void setDamageDefault();
    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();
    void setDamageAbsorbtion(int absorb);
    void setAPCost(int APcost);

    //GETTERS
    int getDamage(Damage::Type damage_type);
    int getDamageResistance(Damage::Type type);
    int getDamageAbsorbtion();
    spArmor getArmorPiece();
    bool hasArmor();
    int getAPCost();

  private:
    spArmor _armor_piece;
    int _action_point_cost;
    int _damage[3];
    int _damage_resistance[3];
    int _damage_absorbtion;
};