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

    void init(int ballistic_res, int electrical_res, int chemical_res, int damage_absorbtion, float inventory_volume);

    void init(std::string ID);

    void setArmorPiece(spArmor armor);
    void setInventoryVolume(float volume);
    void setMaxInventoryVolume(float volume);

    spArmor getArmorPiece();
    float getInventoryVolume();
    float getMaxInventoryVolume();

  private:
    spArmor _armor_piece;
    float _inventory_volume;
    float _max_inventory_volume;
};