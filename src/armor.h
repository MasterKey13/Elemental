/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Armor, spArmor);

class Armor : public Item
{
  public:
    Armor();

    enum DamageType { Ballistic, Electrical, Radioactive, Chemical };

    void init(
      int ID,
      std::string name,
      int size,
      int ballistic_res = 0,
      int electrical_res = 0,
      int radioactive_res = 0,
      int chemical_res = 0,
      std::string brand = "",
      std::string model = "");

    void log();

    //GETTERS
    int getDamageResistance(DamageType damage_type);

    //SETTERS
    void setDamageResistance(DamageType damage_type, int damage_resistance);

  private:
    int _damage_resistance[4];
};