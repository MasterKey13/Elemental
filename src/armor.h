/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "json/json.h"
#include "item.h"
#include "damage.h"

//declare smart pointer
DECLARE_SMART(Item, spItem);

using namespace oxygine;

class Armor : public Item
{
  public:
    Armor();

    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();
    void setDamageAbsorbtion(int absorb);

    int getDamageResistance(Damage::Type type);
    int getDamageAbsorbtion();

  private:
    int _damage_resistance[3];
    int _damage_absorbtion;
};