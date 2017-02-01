/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "armor.h"
#include "target.h"
#include "resources.h"

//declare smart pointer
DECLARE_SMART(Battery, spBattery);
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Battery : public Item, public Target
{
  public:
    Battery();

    void init(
      int ballistic_res, 
      int electrical_res, 
      int chemical_res,
      int action_slots, 
      int action_points
      );

    void init(std::string ID);

    //SETTERS
    void setActionSlots(int action_slots);
    void setActionSlotsMax(int action_slots_max);
    void setActionPoints(int action_points);
    void setActionPointsMax(int action_points_max);

    //GETTERS
    int getActionSlots();
    int getActionSlotsMax();
    int getActionPoints();
    int getActionPointsMax();
    int getActionPointsMaxAvailable();
    spSprite getSprite();

  private:
    int _action_points;
    int _action_points_max;
    int _action_slots;
    int _action_slots_max;
    spSprite _sprite;
};