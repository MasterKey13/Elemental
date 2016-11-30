/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <vector>
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

    void init(
      int ballistic_res, 
      int electrical_res, 
      int chemical_res,
      float inventory_volume
      );

    void init(std::string ID);

    void setArmorPiece(spArmor armor);
    void setInventoryVolume(float volume);
    void setMaxInventoryVolume(float volume);

    spArmor getArmorPiece();
    float getInventoryVolume();
    float getMaxInventoryVolume();
    std::vector<spItem> getInventory();

  private:
    spArmor _armor_piece;
    float _inventory_volume;
    float _max_inventory_volume;
    std::vector<spItem> _inventory;
};