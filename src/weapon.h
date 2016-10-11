/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Weapon, spWeapon);

class Weapon : public Item
{
  public:
    Weapon();

    enum DamageType { Ballistic, Electrical, Radioactive, Chemical };

    void init(
      int ID,
      int size,
      int hitpoints,
      int hitpoints_cap,
      int ballistic_dmg = 0,
      int electrical_dmg = 0,
      int radioactive_dmg = 0,
      int chemical_dmg = 0,
      std::string name = "",
      std::string brand = "",
      std::string model = "");

    void log();

    //GETTERS
    int getDamageResistance(DamageType damage_type);

    //SETTERS
    void setDamageResistance(DamageType damage_type, int damage_resistance);

  private:
    int _AP_cost;
    int _damage[4];
};