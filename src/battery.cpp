
/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "battery.h"

Battery::Battery()
{

}

int Battery::getActionSlots()
{
  return _action_slots;
}

int Battery::getActionSlotsMax()
{
  return _action_slots_max;
}

int Battery::getActionPoints()
{
  return _action_points;
}

int Battery::getActionPointsMax()
{
  return _action_points_max;
}

spArmor Battery::getArmorPiece()
{
  return _armor_piece;
}

void Battery::setActionSlots(int action_slots)
{
  _action_slots = action_slots;
}

void Battery::setActionSlotsMax(int action_slots_max)
{
  _action_slots_max = action_slots_max;
}

void Battery::setActionPoints(int action_points)
{
  _action_points = action_points;
}

void Battery::setActionPointsMax(int action_points_max)
{
  _action_points_max = action_points_max;
}

void Battery::setArmorPiece(spArmor armor)
{
  _armor_piece = armor;
}