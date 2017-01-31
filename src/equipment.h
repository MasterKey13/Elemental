/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "damage.h"
#include "armor.h"
#include "target.h"
#include "ship.h"

//declare smart pointer
DECLARE_SMART(Equipment, spEquipment);
DECLARE_SMART(Armor, spArmor);
DECLARE_SMART(Ship, spShip);

using namespace oxygine;

class Equipment : public Item, public Target
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
      int action_point_cost,
      bool self_targetable
      );

    void init(std::string ID);

    //SETTERS
    void setDamage(Damage::Type damage_type, int damage_resistance);
    void setDamageDefault();
    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();
    void setAPCost(int APcost);
    void setSelfTargetable(bool self_targetable);

    //GETTERS
    int getDamage(Damage::Type damage_type);
    int getDamageResistance(Damage::Type type);
    int getAPCost();
    bool isSelfTargetable();
    spSprite getSprite();

  private:
    int _action_point_cost;
    int _damage[3];
    int _damage_resistance[3];
    int _damage_absorbtion;
    bool _self_targetable;
    spSprite _sprite;
};