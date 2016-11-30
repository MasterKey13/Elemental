/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "damage.h"

using namespace oxygine;

class Damageable
{
  public:
    Damageable();

    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();

    int getDamageResistance(Damage::Type type);

  private:
    int _damage_resistance[3];
};