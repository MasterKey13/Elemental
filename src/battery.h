/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "armor.h"

//declare smart pointer
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Battery : public Item
{
  public:
    Battery();

    void setActionSlots(int action_slots);
    void setActionSlotsMax(int action_slots_max);
    void setActionPoints(int action_points);
    void setActionPointsMax(int action_points_max);

    void setArmorPiece(spArmor armor);

    int getActionSlots();
    int getActionSlotsMax();
    int getActionPoints();
    int getActionPointsMax();
    
    spArmor getArmorPiece();

  private:
    spArmor _armor_piece;
    int _action_points;
    int _action_points_max;
    int _action_slots;
    int _action_slots_max;
};