/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "damage.h"

using namespace oxygine;

class Damageable : public Actor
{
  public:
    Damageable();

    void setDamageResistance(Damage::Type type, int resistance);
    void setDamageResistanceDefault();
    void setDamageAbsorbtion(int absorb);

    int getDamageResistance(Damage::Type type);
    int getDamageAbsorbtion();

  private:
    int _damage_resistance[3];
    int _damage_absorbtion;
};