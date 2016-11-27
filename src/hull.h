/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "armor.h"
#include "damageable.h"

//declare smart pointer
DECLARE_SMART(Hull, spHull);
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Hull : public Item, public Damageable
{
  public:
    Hull();

    void setArmorPiece(spArmor armor);

    spArmor getArmorPiece();

  private:
    spArmor _armor_piece;

};